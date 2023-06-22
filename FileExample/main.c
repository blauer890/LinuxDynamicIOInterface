#include <stdio.h>
#include <string.h>

#include "FileIO.h"

#define MAX_BUF_SIZE 100

int main()
{
    char outBuf[MAX_BUF_SIZE];
    char inBuf[MAX_BUF_SIZE];

    strcpy(outBuf, "FSDFSDFSDF\n");

    struct IOBase *fileIOWriter = CreateFileIO("things.txt", "w");
    fileIOWriter->WriteData(fileIOWriter, outBuf, strlen(outBuf));
    DestroyFileIO(fileIOWriter);

    struct IOBase *fileIOReader = CreateFileIO("things.txt", "r");
    fileIOReader->ReadData(fileIOReader, inBuf, MAX_BUF_SIZE - 1);
    printf("inBuf: %s", inBuf);
    DestroyFileIO(fileIOReader);
    return 0;
}
