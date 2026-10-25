#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	int arr[2];
	pipe(arr);

	int pid1 = fork();
	if(pid1 == 0)
	{
		close(arr[0]);
		dup2(arr[1], 1);
		close(arr[1]);

		char *args[] = {"who", NULL};
		execvp(args[0], args);
		_exit(1);
	}
	
	int pid2 = fork();
	if(pid2 == 0)
	{
		close(arr[1]);
		dup2(arr[0],0);
		close(arr[0]);

		char *args[] ={"wc",NULL};
		execvp(args[0], args);
		_exit(1);
	}
	
	close(arr[0]);
	close(arr[1]);

	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);

return 0;
}
