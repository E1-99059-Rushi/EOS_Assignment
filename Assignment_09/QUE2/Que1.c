#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
int main()
{
    char *files[] = {"circle.c", "square.c", "rectangle.c", "main.c"};

    int i, status, error = 0;
    pid_t pid;

    // Compile four files
    for (i = 0; i < 4; i++)
    {
        pid = fork();

        if (pid == 0)
        {
            char *args[] = {"gcc", "-c", files[i], NULL};
            execvp(args[0], args);
            perror("execvp");
            _exit(1);
        }
        wait(&status);

        if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
        {
        printf("Compilation failed!\n");
        return 1;
	}

    printf("Compilation successful!\n");

    // Link object files
    pid = fork();

    if (pid == 0)
    {
        char *args[] = { "gcc", "-o", "program.out","circle.o", "square.o","rectangle.o", "main.o", NULL};
        execvp(args[0], args);
        perror("execvp");
        _exit(1);
    }

    wait(&status);

    if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
    {
        printf("Linking failed!\n");
        return 1;
    }

    printf("Linking successful!\n");

    // Run executable
    pid = fork();

    if (pid == 0)
    {
        char *args[] = {"./program.out", NULL};

        execvp(args[0], args);
        perror("execvp");
        _exit(1);
    }

    wait(&status);

    printf("Program execution completed.\n");

    return 0;
}
}
