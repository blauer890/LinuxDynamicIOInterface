#pragma once

#include <netinet/in.h>
#include <IOBase.h>

struct UDPServer
{
    struct IOBase vtable;
    int socketDesc;
    struct sockaddr_in servaddr;
    struct sockaddr_in clientaddr;
};

struct IOBase *CreateUDPServer(int port);
void DestroyUDPServer(struct IOBase *ioBase);

