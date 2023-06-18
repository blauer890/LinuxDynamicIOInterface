#include <stdio.h>
#include <string.h>

#include "NamedPipeIO.h"

#define MAX_BUF_SIZE 100

int main()
{
    char outBuf[MAX_BUF_SIZE];
    char inBuf[MAX_BUF_SIZE];
    strcpy(outBuf, "hello from Program1");

    struct IOBase *namedPipeIO = CreateNamedPipeIO("/tmp/fifotest", 0666);
    namedPipeIO->WriteData(namedPipeIO, outBuf, strlen(outBuf));
    namedPipeIO->ReadData(namedPipeIO, inBuf, MAX_BUF_SIZE - 1);
    printf("inBuf: %s\n", inBuf);
    DestroyNamedPipeIO(namedPipeIO);
    return 0;
}
