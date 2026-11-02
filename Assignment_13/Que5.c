
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <pthread.h>
#include <semaphore.h>

#define SIZE 10

struct shared_data
{
    int buffer;
    pthread_mutex_t mutex;
    sem_t empty;
    sem_t full;
};

volatile sig_atomic_t stop = 0;

void signal_handler(int sig)
{
    stop = 1;
}

int main()
{
    struct shared_data *ptr;
    pthread_mutexattr_t attr;
    struct sigaction sa;
    pid_t pid;

    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);

    ptr = mmap(NULL, sizeof(struct shared_data),
               PROT_READ | PROT_WRITE,
               MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    if(ptr == MAP_FAILED)
    {
        perror("mmap");
        return 1;
    }

    pthread_mutexattr_init(&attr);

    pthread_mutexattr_setpshared(&attr,
                                  PTHREAD_PROCESS_SHARED);

    pthread_mutex_init(&ptr->mutex, &attr);

    pthread_mutexattr_destroy(&attr);

    sem_init(&ptr->empty, 1, 1);
    sem_init(&ptr->full, 1, 0);

    pid = fork();

    if(pid < 0)
    {
        perror("fork");
        return 1;
    }

    if(pid == 0)
    {
        // Consumer process

        for(int i = 0; i < SIZE && !stop; i++)
        {
            if(sem_wait(&ptr->full) == -1)
            {
                if(stop)
                    break;

                i--;
                continue;
            }

            if(stop)
                break;

            pthread_mutex_lock(&ptr->mutex);

            printf("Consumer consumed: %d\n", ptr->buffer);
            fflush(stdout);

            pthread_mutex_unlock(&ptr->mutex);

            sem_post(&ptr->empty);
        }

        munmap(ptr, sizeof(struct shared_data));

        exit(0);
    }
    else
    {
        // Producer process

        for(int i = 1; i <= SIZE && !stop; i++)
        {
            if(sem_wait(&ptr->empty) == -1)
            {
                if(stop)
                    break;

                i--;
                continue;
            }

            if(stop)
                break;

            pthread_mutex_lock(&ptr->mutex);

            ptr->buffer = i;

            printf("Producer produced: %d\n", ptr->buffer);
            fflush(stdout);

            pthread_mutex_unlock(&ptr->mutex);

            sem_post(&ptr->full);

            sleep(1);
        }

        if(stop)
        {
            kill(pid, SIGTERM);
            sem_post(&ptr->full);
        }

        wait(NULL);

        sem_destroy(&ptr->empty);
        sem_destroy(&ptr->full);

        pthread_mutex_destroy(&ptr->mutex);

        munmap(ptr, sizeof(struct shared_data));
    }

    return 0;
}
