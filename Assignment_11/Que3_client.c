#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include <arpa/inet.h>

#define SERV_IP     "127.0.0.1"
#define SERV_PORT   4000

int main(void)
{
    //1. create a socket communication endpoint
    int cli_fd = socket(AF_INET, SOCK_STREAM, 0);

    //2. bind ip and port to the socket endpoint
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERV_PORT);
    inet_aton(SERV_IP, &serv_addr.sin_addr);
    connect(cli_fd, (const struct sockaddr *)&serv_addr, sizeof(serv_addr));

    //3. send and receive messages from client
    char buf[64];
    do{
        printf("client > ");
        scanf(" %[^\n]s", buf);
        send(cli_fd, buf, strlen(buf) + 1, 0);
        recv(cli_fd, buf, sizeof(buf), 0);
        printf("server > %s\n", buf);
    }while(strcmp(buf, "bye") != 0);

    //6. close connection with server
    close(cli_fd);
    
    return 0;
}

























