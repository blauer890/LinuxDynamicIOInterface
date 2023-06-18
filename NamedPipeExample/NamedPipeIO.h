#pragma once

#include <IOBase.h>

struct NamedPipeIO
{
    struct IOBase vtable;
    char *filename;
    mode_t mode;
};

struct IOBase *CreateNamedPipeIO();
void DestroyNamedPipeIO(struct IOBase *ioBase);
