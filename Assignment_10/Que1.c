#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/wait.h>

int main()
{
	int arr1[2],arr2[2], a, b,sum;
	 pipe(arr1);
	 pipe(arr2);

	int pid = fork();
	if ( pid == 0)
	{
		close(arr1[0]);
		close(arr2[1]);
	
		printf("Enter number : ");
		scanf("%d %d", &a, &b);
		write(arr1[1], &a, sizeof(a));
		write(arr1[1], &b, sizeof(b));
		close(arr1[1]);
		
		read(arr2[0] , &sum, sizeof(sum));
		printf("sum : %d\n",sum);
		close(arr2[0]);
		_exit(0);
	}
	else
	{	
		close(arr1[1]);
		close(arr2[0]);
		
		read(arr1[0], &a, sizeof(a));
		read(arr1[0], &b, sizeof(b));
		printf("parent recive: %d %d \n", a, b);
		sum = a+b;
 
		write(arr2[1], &sum, sizeof(sum));
		close(arr2[1]);
		close(arr1[0]);
		
		wait(NULL);		
		printf("Success\n");
	
	}
	//int s;
	//wait(&s);
	printf("Exit!!!\n");
return 0;
}
	


