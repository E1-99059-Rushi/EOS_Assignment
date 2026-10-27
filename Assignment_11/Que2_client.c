
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

    d1.mtype = 11;

    // Actual source file on the server
    strcpy(d1.file_name,
           "/home/rushikesh/sample.txt");

    // FIFO path shared by both programs
    strcpy(d1.fifo_name,
           "/home/rushikesh/my_fifo1");

    if (msgsnd(msgid, &d1,
               sizeof(d1) - sizeof(long), 0) == -1)
    {
        perror("msgsnd");
        return 1;
    }

    printf("Client: request sent.\n");

    int fd1 = open(d1.fifo_name, O_RDONLY);

    if (fd1 == -1)
    {
        perror("open FIFO");
        return 1;
    }

    int fd2 = open("received_file.txt",
                   O_WRONLY | O_CREAT | O_TRUNC, 0644);

    if (fd2 == -1)
    {
        perror("open output file");
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
                perror("write output file");
                close(fd1);
                close(fd2);
                return 1;
            }

            total += w;
        }
    }

    if (n == -1)
        perror("read FIFO");
    else
        printf("Client: file saved successfully.\n");

    close(fd1);
    close(fd2);

    printf("Client exiting.\n");

    return n == -1 ? 1 : 0;
}
