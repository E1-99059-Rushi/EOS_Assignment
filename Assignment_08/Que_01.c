#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
int main()
{
	printf("program started!!!\n");	
	int ret,status;
	for(int i = 1 ; i <= 5; i++)
	{
		ret = fork();
		sleep(5);
	
		if(ret == 0)
		{
			printf("child :%d : %d \n",getpid(), i);
			exit(0);
		} 
	}
	
	for(int i =1 ;i <= 5; i++)
	{
		wait(&status);
		
	}
	printf("All child clean..\n");

return 0;

}
