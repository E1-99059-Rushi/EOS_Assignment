#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>


int main()
{
	int ret,status;
	printf("progarm started!!!\n");
	sleep(5);
	ret = fork();
	if(ret == 0)
	{
		printf("parent1 pid :%d ppid: %d\n ",getpid(),getppid());
		ret = -1;
		ret = fork();
		sleep(5);
		if(ret == 0)
		{
			printf("parent2 pid :%d ppid:%d\n",getpid(),getppid());
			ret = -1;
			ret = fork();
			sleep(5);
			if(ret == 0)
			{	
				printf("parent3 pid :%d ppid:%d\n",getpid(),getppid());	
				ret = -1;
				ret = fork();
				sleep(5);
				if(ret == 0)
				{
					printf("parent4 pid :%d ppid:%d\n",getpid(),getppid());	
				}
			}
		}
	}
	
	for(int i =1 ; i<5; i++)
		{
			wait(&status);
		}	

return 0;

}












