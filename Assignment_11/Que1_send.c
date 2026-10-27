#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
int main()
{
    int fd1 = open("/home/rushikesh/my_fifo1" , O_WRONLY);
    int fd2 = open("/home/rushikesh/my_fifo2", O_RDONLY);
    int buf[2];
    printf("Client started...\n");

    printf("Enter two number:");
    scanf("%d %d",&buf[0], &buf[1]);

    printf("Sending numbers to server...\n");
    write(fd1, &buf, sizeof(buf));
    printf("Numbers sent successfully!\n");

    printf("Waiting for result from server...\n");
    int sum;
    read(fd2, &sum, sizeof(sum));
    printf("Received result from server.\n");
    printf("sum = %d \n",sum);

    close(fd1);
    close(fd2);
     printf("Client stopped.\n");
    return 0;
}