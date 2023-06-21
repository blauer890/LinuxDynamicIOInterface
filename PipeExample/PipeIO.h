#pragma once

#include <stdlib.h>
#include <unistd.h>
#include <IOBase.h>

struct PipeIO
{
    struct IOBase vtable;
    int pipefd[2];
    pid_t cpid;
};

struct IOBase *CreatePipeIO();
void CreateSubprocess(struct IOBase *ioBase);
pid_t GetChildPID(struct IOBase *ioBase);
void DestroyPipeIO(struct IOBase *ioBase);
