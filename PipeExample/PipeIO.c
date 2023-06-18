#include <fcntl.h>
#include <stdio.h>
#include <string.h>

#include "PipeIO.h"

static void PipeIO_WriteData(struct IOBase *ioBase, char *data, size_t len)
{
    struct PipeIO *pipeIO = (struct PipeIO *)ioBase;

    if (pipeIO->cpid > 0) // Parent process
    {
        if (fcntl(pipeIO->pipefd[0], F_GETFD) != -1)
        {
            close(pipeIO->pipefd[0]); // Close the read end of the pipe
        }
        write(pipeIO->pipefd[1], data, len);
    }
    else // Child process
    {
        printf("Unable to write to pipe from child process\n");
    }
}

static void PipeIO_ReadData(struct IOBase *ioBase, char *data, size_t len)
{
    struct PipeIO *pipeIO = (struct PipeIO *)ioBase;

    if (pipeIO->cpid == 0) // Child process
    {
        if (fcntl(pipeIO->pipefd[1], F_GETFD) != -1)
        {
            close(pipeIO->pipefd[1]); // Close the write end of the pipe
        }
        read(pipeIO->pipefd[0], data, len);
    }
    else // Parent process
    {
        printf("Unable to read from pipe in parent process\n");
    }
}

static struct IOBase PipeIOvtable =
{
    .WriteData = PipeIO_WriteData,
    .ReadData = PipeIO_ReadData
};

struct IOBase *CreatePipeIO()
{
    int pipefd[2];

    if (pipe(pipefd) == -1)
    {
        perror("Pipe");
        exit(EXIT_FAILURE);
    }

    struct PipeIO *pipeIO = (struct PipeIO *)malloc(sizeof(struct PipeIO));
    pipeIO->vtable = PipeIOvtable;
    memcpy(pipeIO->pipefd, pipefd, sizeof(pipefd));

    return (struct IOBase *)pipeIO;
}

void CreateSubprocess(struct IOBase *ioBase)
{
    struct PipeIO *pipeIO = (struct PipeIO *)ioBase;
    pid_t cpid;

    cpid = fork();
    if (cpid == -1)
    {
        perror("Child process");
        exit(EXIT_FAILURE);
    }
    pipeIO->cpid = cpid;
}

pid_t GetChildPID(struct IOBase *ioBase)
{
    struct PipeIO *pipeIO = (struct PipeIO *)ioBase;
    return pipeIO->cpid;
}

void DestroyPipeIO(struct IOBase *ioBase)
{
    struct PipeIO *pipeIO = (struct PipeIO *)ioBase;

    if (fcntl(pipeIO->pipefd[0], F_GETFD) != -1)
    {
        close(pipeIO->pipefd[0]);
    }

    if (fcntl(pipeIO->pipefd[1], F_GETFD) != -1)
    {
        close(pipeIO->pipefd[1]);
    }

    free(pipeIO);
}
