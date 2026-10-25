
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>

void signal_handler(int sig)
{
    printf("\nSignal captured!!!\n");
}

void child_handler(int sig)
{
    while (waitpid(-1, NULL, WNOHANG) > 0);
}

int main()
{
    char cmd[254], *arr[32], *ptr;
    int i, background, status;
    pid_t pid;

    signal(SIGINT, signal_handler);
    signal(SIGCHLD, child_handler);

    while (1)
    {
        printf("cmd > ");
        fflush(stdout);

        if (fgets(cmd, sizeof(cmd), stdin) == NULL)
            break;

        cmd[strcspn(cmd, "\n")] = '\0';

        ptr = strtok(cmd, " ");
        i = 0;

        while (ptr != NULL && i < 31)
        {
            arr[i++] = ptr;
            ptr = strtok(NULL, " ");
        }

        arr[i] = NULL;

        if (arr[0] == NULL)
            continue;

        if (strcmp(arr[0], "exit") == 0)
            break;

        if (strcmp(arr[0], "cd") == 0)
        {
            if (arr[1] != NULL)
                chdir(arr[1]);
            else
                fprintf(stderr, "Usage: cd directory\n");

            continue;
        }

        background = 0;

        for (i = 0; arr[i] != NULL; i++)
        {
            if (strcmp(arr[i], "&") == 0 && arr[i + 1] == NULL)
            {
                arr[i] = NULL;
                background = 1;
                break;
            }
        }

        if (arr[0] == NULL)
            continue;

        pid = fork();

        if (pid == 0)
        {
            signal(SIGINT, SIG_DFL);
            signal(SIGCHLD, SIG_DFL);

            execvp(arr[0], arr);
            perror("execvp");
            _exit(1);
        }
        else if (pid > 0)
        {
            if (background)
            {
                printf("Background PID: %d\n", pid);
            }
            else
            {
                while (waitpid(pid, &status, 0) < 0)
                {
                    
                        break;
                }
            }
        }
        else
        {
            perror("fork");
        }
    }

    return 0;
}

