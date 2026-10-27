
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <semaphore.h>
#include <time.h>

#define SIZE 5
#define COUNT 10

typedef struct
{
    int queue[SIZE];
    int front;
    int rear;
    sem_t empty;
    sem_t full;
    sem_t mutex;
} SharedData;

int main(void)
{
    int shmid;
    SharedData *shm;

    shmid = shmget(IPC_PRIVATE, sizeof(SharedData),
                   IPC_CREAT | 0666);

    if (shmid == -1)
    {
        perror("shmget");
        return 1;
    }

    shm = (SharedData *)shmat(shmid, NULL, 0);

    if (shm == (void *)-1)
    {
        perror("shmat");
        shmctl(shmid, IPC_RMID, NULL);
        return 1;
    }

    shm->front = 0;
    shm->rear = 0;

    sem_init(&shm->empty, 1, SIZE);
    sem_init(&shm->full, 1, 0);
    sem_init(&shm->mutex, 1, 1);

    srand(time(NULL));

    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork");
        sem_destroy(&shm->empty);
        sem_destroy(&shm->full);
        sem_destroy(&shm->mutex);
        shmdt(shm);
        shmctl(shmid, IPC_RMID, NULL);
        return 1;
    }

    if (pid == 0)
    {
        /* Child: Consumer */
        for (int i = 0; i < COUNT; i++)
        {
            sem_wait(&shm->full);
            sem_wait(&shm->mutex);

            int value = shm->queue[shm->front];
            shm->front = (shm->front + 1) % SIZE;

            printf("Child consumed: %d\n", value);
            fflush(stdout);

            sem_post(&shm->mutex);
            sem_post(&shm->empty);

            sleep(1);
        }

        shmdt(shm);
        exit(0);
    }
    else
    {
        /* Parent: Producer */
        for (int i = 0; i < COUNT; i++)
        {
            int value = rand() % 100;

            sem_wait(&shm->empty);
            sem_wait(&shm->mutex);

            shm->queue[shm->rear] = value;
            printf("Parent produced: %d\n", value);

            shm->rear = (shm->rear + 1) % SIZE;

            sem_post(&shm->mutex);
            sem_post(&shm->full);

            sleep(1);
        }

        wait(NULL);

        sem_destroy(&shm->empty);
        sem_destroy(&shm->full);
        sem_destroy(&shm->mutex);

        shmdt(shm);
        shmctl(shmid, IPC_RMID, NULL);
    }

    return 0;
}
