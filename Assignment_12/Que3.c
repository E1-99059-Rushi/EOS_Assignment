
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *thread_func(void *param)
{
    int *arr = (int *)param;
    int i, j, min, temp;

    // Selection Sort
    for (i = 0; i < 9; i++)
    {
        min = i;

        for (j = i + 1; j < 10; j++)
        {
            if (arr[j] < arr[min])
            {
                min = j;
            }
        }

        // Swap elements
        temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;
    }

    return NULL;
}

int main(void)
{
    pthread_t t1;
    int arr[10];

    printf("Enter 10 integers: ");
    for (int i = 0; i < 10; i++)
    {
        scanf("%d", &arr[i]);
    }

    pthread_create(&t1, NULL, thread_func, (void *)arr);

    pthread_join(t1, NULL);

    printf("Sorted array: ");
    for (int i = 0; i < 10; i++)
    {
        printf("%d ", arr[i]);
    }

    printf("\n");

    return 0;
}

