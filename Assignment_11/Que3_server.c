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
    int serv_fd = socket(AF_INET, SOCK_STREAM, 0);

    //2. bind ip and port to the socket endpoint
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERV_PORT);
    inet_aton(SERV_IP, &serv_addr.sin_addr);
    bind(serv_fd, (const struct sockaddr *)&serv_addr, sizeof(serv_addr));

    //3. listen for client connection/request
    listen(serv_fd, 5);

    //4. accept client connection
    struct sockaddr_in cli_addr;
    socklen_t socklen = sizeof(cli_addr);
    int cli_fd = accept(serv_fd, (struct sockaddr *)&cli_addr, &socklen);

    //5. send and receive messages from client
    char buf[64];
    do{
        recv(cli_fd, buf, sizeof(buf), 0);
        printf("client > %s\n", buf);
        printf("server > ");
        scanf(" %[^\n]s", buf);
        send(cli_fd, buf, strlen(buf) + 1, 0);
    }while(strcmp(buf, "bye") != 0);

    //6. close connection with client
    close(cli_fd);

    //7. close listening socket also
    shutdown(serv_fd, SHUT_RDWR);
    
    return 0;
}

























