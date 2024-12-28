#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <malloc.h>

int CreateTCPIpv4Socket()
{
    return socket(AF_INET,SOCK_STREAM,0);;
}

struct sockaddr_in* createIpv4Address(char* ip, int port)
{
    //char* ip = "142.251.140.78";
    //struct sockaddr_in* address = malloc(sizeof(struct sockaddr_in));
    struct sockaddr_in* address = (struct sockaddr_in*)malloc(sizeof(struct sockaddr_in));

    address->sin_port = htons(port);
    address->sin_family = AF_INET;
    if (strlen(ip) == 0)
    {
        address->sin_addr.s_addr = INADDR_ANY;
    } else
    {
        inet_pton(AF_INET, ip, &address->sin_addr.s_addr);
    }
    

    return address;
}