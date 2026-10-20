#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>


int main()
{
	int i = 1;
	int ret = fork();
	while(ret == 0)
	{	
		ret = fork();
		i++;
	}
printf("max child : %d\n",i);

return 0;
}



