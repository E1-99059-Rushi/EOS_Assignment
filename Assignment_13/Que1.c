
#include <stdio.h>
#include <pthread.h>

struct range
{
    int start;
    int end;
};

void *thread_sum(void *arg)
{
    struct range *r = (struct range *)arg;
    int sum = 0;

    for(int i = r->start; i <= r->end; i++)
    {
        sum = sum + i;
    }

    return (void *)(long)sum;
}

int main()
{
    pthread_t t1;
    struct range r;
    void *result;

    printf("Enter start number: ");
    scanf("%d", &r.start);

    printf("Enter end number: ");
    scanf("%d", &r.end);

    if(r.start > r.end)
    {
        printf("Invalid range\n");
        return 0;
    }

    pthread_create(&t1, NULL, thread_sum, &r);

    pthread_join(t1, &result);

    printf("Sum = %ld\n", (long)result);

    return 0;
}
