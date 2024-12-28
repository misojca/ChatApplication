/*
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
//include "sys/socket.h"
//#include "sys/types.h"
#include "socketUtils.h"

int main()
{
    //int socketFD = socket(AF_INET,SOCK_STREAM,0);
    int socketFD = CreateTCPIpv4Socket();

    struct sockaddr_in *address = createIpv4Address("127.0.0.1", 3000);
    
    int result = connect(socketFD, address, sizeof(*address));
    if(result == 0)
    {
        printf("Connection succesful\n");
    }

    char *message;
    message = "GET \\ HTTP/1.1\r\nHost:google.com\r\n\r\n";
    send(socketFD,message,strlen(message),0);

    char buffer[1024];
    recv(socketFD,buffer,sizeof(buffer),0);

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
#include <stdio.h>
int main()
{
    int socketFD = CreateTCPIpv4Socket();
    struct sockaddr_in *address = createIpv4Address("127.0.0.1", 3000);

    int result = connect(socketFD, (struct sockaddr *)address, sizeof(*address));
    if (result == 0)
    {
        printf("Connection successful\n");
    }
    else
    {
        perror("Connection failed");
        free(address);
        return 1;
    }

    char* line = NULL;
    size_t lineSize = 0;
    printf("Type a message: \n");

    while (1)
    {
        ssize_t charCounter = getline(&line, &lineSize, stdin);
        send(socketFD, line, charCounter, 0);

        if (charCounter > 0)
        {
            if (strcmp(line,"exit\n") == 0)
            {
                break;
            }
        }
    }
    

    //const char *message = "GET \\ HTTP/1.1\r\nHost: google.com\r\n\r\n";
    //send(socketFD, message, strlen(message), 0);

    char buffer[1024] = {0};
    int bytesReceived = recv(socketFD, buffer, sizeof(buffer) - 1, 0);
    if (bytesReceived > 0)
    {
        buffer[bytesReceived] = '\0'; // Završni null karakter za string
        printf("Response was: %s\n", buffer);
    }
    else
    {
        perror("Receive failed");
    }

    close(socketFD);
    free(address);

    return 0;
}
