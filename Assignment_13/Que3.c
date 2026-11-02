
#include <stdio.h>
#include <pthread.h>

struct array
{
    int a[100];
    int size;
};

void *bubble_sort(void *arg)
{
    struct array *data = (struct array *)arg;
    int i, j, temp;

    for(i = 0; i < data->size - 1; i++)
    {
        for(j = 0; j < data->size - i - 1; j++)
        {
            if(data->a[j] > data->a[j + 1])
            {
                temp = data->a[j];
                data->a[j] = data->a[j + 1];
                data->a[j + 1] = temp;
            }
        }
    }

    return NULL;
}

int main()
{
    struct array data;
    pthread_t t1;

    printf("Enter array size: ");
    scanf("%d", &data.size);

    if(data.size <= 0 || data.size > 100)
    {
        printf("Invalid size\n");
        return 0;
    }

    printf("Enter array elements:\n");

    for(int i = 0; i < data.size; i++)
    {
        scanf("%d", &data.a[i]);
    }

    pthread_create(&t1, NULL, bubble_sort, &data);

    pthread_join(t1, NULL);

    printf("Sorted array:\n");

    for(int i = 0; i < data.size; i++)
    {
        printf("%d ", data.a[i]);
    }

    printf("\n");

    return 0;
}
