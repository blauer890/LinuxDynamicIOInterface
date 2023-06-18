#include <stdio.h>
#include <string.h>

#include "UDPServer.h"

#define MAX_BUF_SIZE

int main()
{
    char inBuf[MAX_BUF_SIZE];
    char outBuf[MAX_BUF_SIZE];

    struct IOBase *udpServer = CreateUDPServer(8888);

    printf("Waiting for a connection from a client...\n");
    udpServer->ReadData(udpServer, inBuf, MAX_BUF_SIZE - 1);

    strcpy(outBuf, "youman");

    udpServer->WriteData(udpServer, outBuf, strlen(outBuf));

    DestroyUDPServer(udpServer);
    return 0;
}
