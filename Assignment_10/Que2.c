#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
    int fd[2];

    pipe(fd);

    int size = fcntl(fd[0], F_GETPIPE_SZ);

    printf("Pipe buffer size = %d bytes\n", size);

    close(fd[0]);
    close(fd[1]);

    return 0;
}

