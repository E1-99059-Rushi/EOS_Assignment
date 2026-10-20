#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{

    int ret = fork();

    if (ret == -1)
    {
        perror("Fork failed");
        return 1;
    }
    else if (ret == 0)
    {
        // Child process: open browser with the given URL
        execlp("firefox", "firefox",
               "https://www.google.com", (char *)NULL);

        // Executes only if browser launch fails
        perror("Firefox failed");
        exit(1);
    }
    else
    {
        // Parent process
        printf("Parent process ID: %d\n", getpid());
        printf("Child process ID: %d\n", getpid());

        wait(NULL);
        printf("Child process completed.\n");
    }

    return 0;
}
