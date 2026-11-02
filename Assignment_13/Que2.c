
#include <stdio.h>
#include <pthread.h>

void *selection_sort(void *arg)
{
    int *a = (int *)arg;
    int i, j, min, temp;

    for(i = 0; i < 9; i++)
    {
        min = i;

        for(j = i + 1; j < 10; j++)
        {
            if(a[j] < a[min])
            {
                min = j;
            }
        }

        temp = a[i];
        a[i] = a[min];
        a[min] = temp;
    }

    return NULL;
}

int main()
{
    int a[10];
    pthread_t t1;

    printf("Enter 10 elements:\n");

    for(int i = 0; i < 10; i++)
    {
        scanf("%d", &a[i]);
    }

    pthread_create(&t1, NULL, selection_sort, a);

    pthread_join(t1, NULL);

    printf("Sorted array:\n");

    for(int i = 0; i < 10; i++)
    {
        printf("%d ", a[i]);
    }

    printf("\n");

    return 0;
}
