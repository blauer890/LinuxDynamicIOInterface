#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "NamedPipeIO.h"

void NamedPipeIO_WriteData(struct IOBase *ioBase, char *data, size_t len)
{
    struct NamedPipeIO *namedPipeIO = (struct NamedPipeIO *)ioBase;
    ssize_t fd = open(namedPipeIO->filename, O_WRONLY);
    if (write(fd, data, len) < 0)
    {
        perror("Named pipe");
    }
    close(fd);
}

void NamedPipeIO_ReadData(struct IOBase *ioBase, char *data, size_t len)
{
    struct NamedPipeIO *namedPipeIO = (struct NamedPipeIO *)ioBase;
    ssize_t fd = open(namedPipeIO->filename, O_RDONLY);
    ssize_t n = read(fd, data, len);
    if (n < 0)
    {
        perror("Named pipe");
    }
    data[n] = '\0';
    close(fd);
}

struct IOBase namedPipeIOvtable =
{
    .WriteData = NamedPipeIO_WriteData,
    .ReadData = NamedPipeIO_ReadData
};

struct IOBase *CreateNamedPipeIO(char *filename, mode_t mode)
{
    struct NamedPipeIO *namedPipeIO = (struct NamedPipeIO *)malloc(sizeof(struct NamedPipeIO));

    if (mkfifo(filename, mode) < 0)
    {
        perror("Named pipe");
    }

    namedPipeIO->vtable = namedPipeIOvtable;
    namedPipeIO->filename = filename;
    namedPipeIO->mode = mode;
}

void DestroyNamedPipeIO(struct IOBase *ioBase)
{
    struct NamedPipeIO *namedPipeIO = (struct NamedPipeIO *)ioBase;

    free(namedPipeIO);
}
