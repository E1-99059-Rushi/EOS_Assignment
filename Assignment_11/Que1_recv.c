#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
int main()
{
    int fd1 = open("/home/rushikesh/my_fifo1" , O_RDONLY);
    int fd2 = open("/home/rushikesh/my_fifo2", O_WRONLY);
    int buf[2];

    printf("Server started...\n");
    printf("Waiting for client to send two numbers...\n");
    
    read(fd1, &buf, sizeof(buf));
    printf("Received numbers: %d and %d\n", buf[0], buf[1]);

    int sum = buf[0] + buf[1];

    printf("Sum calculated: %d\n", sum);
    printf("Sending result to client...\n");

    write(fd2, &sum, sizeof(sum));
    printf("Result send success!!!\n");
   
    
    close(fd1);
    close(fd2);
    
    printf("Server stopped.\n");
    return 0;
}