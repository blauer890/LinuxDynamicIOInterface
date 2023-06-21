#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "UDPServer.h"

static void UDPServer_WriteData(struct IOBase *ioBase, char *data, size_t len)
{
    struct UDPServer *udpServer = (struct UDPServer *)ioBase;
    ssize_t n = sendto(udpServer->socketDesc, data, len, 0,
                       (const struct sockaddr *)&udpServer->clientaddr,
                       sizeof(udpServer->clientaddr));
    if (n < 0)
    {
        perror("UDP server");
    }
}

static void UDPServer_ReadData(struct IOBase *ioBase, char *data, size_t len)
{
    struct UDPServer *udpServer = (struct UDPServer *)ioBase;
    socklen_t socklen = sizeof(udpServer->clientaddr);
    ssize_t n = recvfrom(udpServer->socketDesc, data, len, MSG_WAITALL,
                         (struct sockaddr *)&udpServer->clientaddr, &socklen);
    if (n < 0)
    {
        perror("UDP server");
    }
    data[n] = '\0';
}

static struct IOBase UDPServervtable =
{
    .WriteData = UDPServer_WriteData,
    .ReadData = UDPServer_ReadData
};

struct IOBase *CreateUDPServer(int port)
{
    struct UDPServer *udpServer = (struct UDPServer *)malloc(sizeof(struct UDPServer));
    struct sockaddr_in servaddr;
    struct sockaddr clientaddr;

    udpServer->socketDesc = socket(AF_INET, SOCK_DGRAM, 0);

    if (udpServer->socketDesc < 0)
    {
        perror("UDP server");
        free(udpServer);
        return NULL;
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&clientaddr, 0, sizeof(clientaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(port);

    if (bind(udpServer->socketDesc,
             (const struct sockaddr *)&servaddr,
             sizeof(servaddr)) < 0)
    {
        perror("UDP server");
        free(udpServer);
        return NULL;
    }

    udpServer->vtable = UDPServervtable;
    memcpy(&udpServer->servaddr, &servaddr, sizeof(servaddr));
    memcpy(&udpServer->clientaddr, &clientaddr, sizeof(clientaddr));
    return (struct IOBase *)udpServer;
}

void DestroyUDPServer(struct IOBase *ioBase)
{
    struct UDPServer *udpServer = (struct UDPServer *)ioBase;

    close(udpServer->socketDesc);

    free(udpServer);
}
