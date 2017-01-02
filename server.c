#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
    int sockfd;
    int new_fd;
    int port;
    char ip[50];
    struct sockaddr_in addr;
    struct sockaddr_in client;
    socklen_t len;
    
    
    printf("Enter Port:");
    scanf("%d",&port);
    
    
    //Create Socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    
    //Setting IP and Port
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);//Port, which htons converts host number to network order
    addr.sin_addr.s_addr = INADDR_ANY;//bind to the IP of the host it's running on
    
    //Associate the socket with Port
    bind(sockfd, (struct sockaddr*)&addr, sizeof(addr));
    printf("\t binding...\n");
    
    //Waiting for request
    listen(sockfd, 5);
    printf("\t listening...\n");
    
    //Accept request from Client
    len = sizeof(client);
    new_fd = accept(sockfd, (struct sockaddr *)&client, &len);
    char *client_addr = inet_ntoa(client.sin_addr);//Converting client's IP
    printf("\t Connection from %s...\n", client_addr);
    
    //Sending data to Client
    printf("\t Sending 'Jeremy'...\n");
    write(new_fd, "Jeremy\n", 6);
    
    //End connection
    printf("\t End connection...\n");
    close(new_fd);
    close(sockfd);
    
    return 0;  
}