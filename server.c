/*
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include "socketUtils.h"

int main()
{
    int ServerSocketFD = CreateTCPIpv4Socket();
    struct sockaddr_in *serverAddress = createIpv4Address("",3000);

    int result = bind(ServerSocketFD,serverAddress,sizeof(*serverAddress));
    if (result == 0)
    {
        printf("Socket was bound sucessfully\n");
    }

    if (result != 0)
{
    perror("Bind failed");
    return 1;
}

    int listenResult = listen(ServerSocketFD,10);

    struct sockaddr_in clientAddress;
    int clientAddressSize = sizeof(struct sockaddr_in);
    //socklen_t clientLength = sizeof(clientAddress);
    int acceptResult = accept(ServerSocketFD, &clientAddress, &clientAddressSize);

    char buffer[1024];
    recv(ServerSocketFD, buffer, 1024,0);

    printf("Response was %s\n", buffer);


    return 0;
}
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "socketUtils.h"

int main()
{
    int ServerSocketFD = CreateTCPIpv4Socket();
    int opt = 1;
    setsockopt(ServerSocketFD, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in *serverAddress = createIpv4Address("0.0.0.0", 3000);

    int result = bind(ServerSocketFD, (struct sockaddr *)serverAddress, sizeof(*serverAddress));
    if (result != 0)
    {
        perror("Bind failed");
        return 1;
    }
    printf("Socket was bound successfully\n");

    int listenResult = listen(ServerSocketFD, 10);
    if (listenResult != 0)
    {
        perror("Listen failed");
        return 1;
    }

    struct sockaddr_in clientAddress;
    socklen_t clientAddressSize = sizeof(clientAddress);

    int acceptResult = accept(ServerSocketFD, (struct sockaddr *)&clientAddress, &clientAddressSize);
    if (acceptResult < 0)
    {
        perror("Accept failed");
        return 1;
    }
    printf("Connection accepted from %s:%d\n",
           inet_ntoa(clientAddress.sin_addr),
           ntohs(clientAddress.sin_port));

    char buffer[1024] = {0};
    while (1)
    {
        printf("Usao u while servera");
        int bytesReceived = recv(acceptResult, buffer, sizeof(buffer) - 1, 0);
        if (bytesReceived > 0)
        {
            buffer[bytesReceived] = '\0'; // Završni null karakter za string
            printf("Response was: %s\n", buffer);
        }
        else
        {
            perror("Receive failed");
        }
    }
    

    const char *response = "Message received by server!";
    send(acceptResult, response, strlen(response), 0);

    close(acceptResult);
    close(ServerSocketFD);
    shutdown(ServerSocketFD,SHUT_RDWR);
    free(serverAddress);

    return 0;
}
