#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "UDPClient.h"

#define MAX_BUF_SIZE 100

int main()
{
    char outBuf[MAX_BUF_SIZE];
    char inBuf[MAX_BUF_SIZE];

    struct IOBase *udpClient = CreateUDPClient("127.0.0.1", 8888);

    if (udpClient == NULL)
    {
        printf("Unable to create UDP client\n");
        exit(EXIT_FAILURE);
    }

    strcpy(outBuf, "lol");

    udpClient->WriteData(udpClient, outBuf, strlen(outBuf));

    printf("Waiting for response from server...\n");
    udpClient->ReadData(udpClient, inBuf, MAX_BUF_SIZE - 1);

    printf("inBuf: %s\n", inBuf);

    DestroyUDPClient(udpClient);
    return 0;
}
