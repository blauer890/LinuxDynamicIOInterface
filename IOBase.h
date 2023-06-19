#pragma once

#include <stdlib.h>

struct IOBase
{
    void (*WriteData)(struct IOBase *ioBase, char *data, size_t len);
    void (*ReadData)(struct IOBase *ioBase, char *data, size_t len);
};
