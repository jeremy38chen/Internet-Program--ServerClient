#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


int main()
{

    struct sockaddr_in server;
    int sockfd;
    char buf[32];
    char ip[50];
    int n;
    int port;
    
    printf("Enter IP:");
    scanf("%s",ip);
    
    printf("Enter Port:");
    scanf("%d",&port);
    
    //Creat Socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    //Setting IP and Port
    server.sin_family = AF_INET;
    server.sin_port = htons(port);//Port, which htons converts host number to network order
    inet_pton(AF_INET, ip, &server.sin_addr);//Convert readable IP to their binary representation
    
    //Request a connection with Server
    connect(sockfd, (struct sockaddr *)&server, sizeof(server));
    
    //Establish connection
    //Receiving Data from Server.
    memset(buf, 0, sizeof(buf));
    read(sockfd, buf, sizeof(buf));
    
    printf("\t Received Data:%s\n",buf);
    
    //End connection
    close(sockfd);  
    return 0;  
}  