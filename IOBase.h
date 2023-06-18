#pragma once

#include <stdlib.h>

struct IOBase
{
    void (*WriteData)(struct IOBase *, char *, size_t);
    void (*ReadData)(struct IOBase *, char *, size_t);
};
