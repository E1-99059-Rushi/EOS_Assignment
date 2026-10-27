
#include <stdio.h>
#include <sys/msg.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define MSG_KEY 0x1234

typedef struct file_data
{
    long mtype;
    char file_name[100];
    char fifo_name[100];
} data_t;

int main()
{
    int msgid = msgget(MSG_KEY, IPC_CREAT | 0666);

    if (msgid == -1)
    {
        perror("msgget");
        return 1;
    }

    data_t d1;

    printf("Server waiting for client request...\n");

    if (msgrcv(msgid, &d1, sizeof(d1) - sizeof(long), 11, 0) == -1)
    {
        perror("msgrcv");
        return 1;
    }

    printf("File: %s\n", d1.file_name);
    printf("FIFO: %s\n", d1.fifo_name);

    int fd1 = open(d1.file_name, O_RDONLY);

    if (fd1 == -1)
    {
        perror("open source file");
        return 1;
    }

    int fd2 = open(d1.fifo_name, O_WRONLY);

    if (fd2 == -1)
    {
        perror("open FIFO");
        close(fd1);
        return 1;
    }

    char buf[1024];
    ssize_t n;

    while ((n = read(fd1, buf, sizeof(buf))) > 0)
    {
        ssize_t total = 0;

        while (total < n)
        {
            ssize_t w = write(fd2, buf + total, n - total);

            if (w <= 0)
            {
                perror("write FIFO");
                close(fd1);
                close(fd2);
                return 1;
            }

            total += w;
        }
    }

    if (n == -1)
        perror("read source file");
    else
        printf("Server: file sent successfully.\n");

    close(fd1);
    close(fd2);

    printf("Server exiting.\n");

    return n == -1 ? 1 : 0;
}
