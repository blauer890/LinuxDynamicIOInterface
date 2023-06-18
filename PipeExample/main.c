#include <stdio.h>
#include <string.h>
#include "PipeIO.h"

#define MAX_BUF_SIZE 100

int main()
{
    char buf[MAX_BUF_SIZE];

    struct IOBase *pipeIO = CreatePipeIO();
    CreateSubprocess(pipeIO);
    pid_t cpid = GetChildPID(pipeIO);
    printf("cpid: %d\n", cpid);
    if (cpid > 0)
    {
        strcpy(buf, "Hello man");
        pipeIO->WriteData(pipeIO, buf, strlen(buf));
    }
    else
    {
        pipeIO->ReadData(pipeIO, buf, MAX_BUF_SIZE - 1);
        printf("buf: %s\n", buf);
    }
    DestroyPipeIO(pipeIO);
    return 0;
}
