
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <pthread.h>

struct range
{
    int num1;
    int num2;
};

void *fun1(void *arg)
{
	// struct range *r = (struct range *)arg;
    
     int *arr = (int *)arg;
    int sum = 0;

    for (int i = arr[0]; i <= arr[1]; i++)
    {
        sum = sum + i;
        
    }
sleep(1);
    printf("[%d] :Sum : %d\n",gettid(), sum);

    return NULL;
}

int main(void)
{
    printf("[%d] main() function is started !!!\n", gettid());

    pthread_t t1;
    struct range r;
 
	int arr[2];
    printf("Enter range : ");
    scanf("%d %d", &arr[0], &arr[1]);

// scanf("%d %d", &r.num1, &r.num2);
  
    pthread_create(&t1, NULL, fun1, arr);//&r
    pthread_join(t1, NULL);

    printf("[%d] main() function is finished !!!\n", gettid());

    return 0;
}

