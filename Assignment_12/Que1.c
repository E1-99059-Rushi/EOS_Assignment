#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<pthread.h>
#include<sys/shm.h>
#include<sys/sem.h>

#define KEY 0x1234

int semid;
struct sembuf arr[1];
union semun
{
   int val;
};

void *fun1(void *val)
{
	char str[32] = "SUNBEAM";
	while(1)
	{	
	    arr[0].sem_num = 0;
            arr[0].sem_op = -1;
            arr[0].sem_flg = 0;
            semop(semid, arr, 1);
	
		printf("[%d] : %s \n" , gettid(), str);
		sleep(1); 
	
	    arr[0].sem_num = 0;
            arr[0].sem_op = +1;
            arr[0].sem_flg = 0;
            semop(semid, arr, 1);

	}
}

void *fun2(void *val)
{
	char str[32] = "INFOTECH";
	while(1)
	{
      	    arr[0].sem_num = 0;
            arr[0].sem_op = -1;
            arr[0].sem_flg = 0;
            semop(semid, arr, 1);

		printf("[%d] : %s \n", gettid(), str);
		sleep(1);
	
	    arr[0].sem_num = 0;
            arr[0].sem_op = +1;
            arr[0].sem_flg = 0;
            semop(semid, arr, 1);
	}
}

int main()
{
	 semid = semget(KEY, 1, IPC_CREAT | 0600);

	union semun su;
	su.val = 1;
	semctl(semid, 0 ,SETVAL,su);	
		


	printf("[%d] main process started!!!\n", gettid());
	
	pthread_t t1, t2;
	
	pthread_create(&t1, NULL, fun1, NULL);
	pthread_create(&t2, NULL, fun2, NULL);
	
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	semctl(semid, 0, IPC_RMID);
	printf("[%d] main function is finished!!!\n", getpid());
return 0;
}





