#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>
#include<string.h>
#include<signal.h>


void signal_handler(int sig)
{
	printf("Signal captured!!!\n");
}

int main()
{
	char cmd[254], *arr[32], *ptr;

   while(1)
     {
	signal(SIGINT,signal_handler);
	printf("cmd > ");
	scanf(" %[^\n]s", cmd);
	
	ptr = strtok(cmd, " "); 

	int i=0;
	while(ptr != NULL)
	{
		arr[i] = ptr;
		i++;
		ptr = strtok(NULL, " ");
	}
	arr[i] = NULL;

	if(strcmp(arr[0], "cd") == 0)
		chdir(arr[1]);
	
	else if(strcmp(arr[0] , "exit") == 0)
		_exit(0);
	
	else
	{
		int pid = fork();
		if(pid == 0)
		{
			execvp(arr[0], arr);
			
		}
		
		else
		{
			int s;
			wait(&s);
		
		}
	
	}
}
return 0;
}
