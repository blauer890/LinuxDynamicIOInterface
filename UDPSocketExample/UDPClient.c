#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "UDPClient.h"

static void UDPClient_WriteData(struct IOBase *ioBase, char *data, size_t len)
{
    struct UDPClient *udpClient = (struct UDPClient *)ioBase;
    ssize_t n = sendto(udpClient->socketDesc, data, len, 0,
                       (const struct sockaddr *)&udpClient->servaddr,
                       sizeof(udpClient->servaddr));
    if (n < 0)
    {
        perror("UDP socket");
    }
}

static void UDPClient_ReadData(struct IOBase *ioBase, char *data, size_t len)
{
    struct UDPClient *udpClient = (struct UDPClient *)ioBase;
    socklen_t socklen = sizeof(udpClient->servaddr);
    ssize_t n = recvfrom(udpClient->socketDesc, data, len, 0,
                         (struct sockaddr *)&udpClient->servaddr,
                         &socklen);
    if (n < 0)
    {
        perror("UDP socket");
    }
    data[n] = '\0';
}

static struct IOBase UDPClientvtable =
{
    .WriteData = UDPClient_WriteData,
    .ReadData = UDPClient_ReadData
};

struct IOBase *CreateUDPClient(char *serverIP, int serverPort)
{
    struct UDPClient *udpClient = (struct UDPClient *)malloc(sizeof(struct UDPClient));
    struct sockaddr_in servaddr;

    // Unreliable two-way communication
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0)
    {
        perror("UDP socket");
        free(udpClient);
        return NULL;
    }

    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(serverPort);

    in_addr_t ip = inet_addr(serverIP);
    if (ip < 0)
    {
        printf("Failed converting IP address to network byte order\n");
        free(udpClient);
        return NULL;
    }
    
    servaddr.sin_addr.s_addr = ip;

    udpClient->vtable = UDPClientvtable;
    udpClient->socketDesc = sock;
    memcpy(&udpClient->servaddr, &servaddr, sizeof(servaddr));
    return (struct IOBase *)udpClient;
}

void DestroyUDPClient(struct IOBase *ioBase)
{
    struct UDPClient *udpClient = (struct UDPClient *)ioBase;

    close(udpClient->socketDesc);

    free(udpClient);
}
