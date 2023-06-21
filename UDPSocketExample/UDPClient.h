#pragma once

#include <netinet/in.h>

#include <IOBase.h>

struct UDPClient
{
    struct IOBase vtable;
    int socketDesc;
    struct sockaddr_in servaddr;
};

struct IOBase *CreateUDPClient(char *serverIP, int serverPort);
void DestroyUDPClient(struct IOBase *ioBase);
