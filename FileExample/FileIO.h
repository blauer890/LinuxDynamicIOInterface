#pragma once

#include <stdio.h>
#include <stdlib.h>

#include <IOBase.h>

struct FileIO
{
    struct IOBase vtable;
    FILE *filePtr;
};

struct IOBase *CreateFileIO(char *pathname, char *mode);
void DestroyFileIO(struct IOBase *ioBase);
