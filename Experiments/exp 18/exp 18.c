/* Exp 18: Producer-Consumer problem using semaphores. Compile: gcc -pthread */
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define MAX_ITEMS 10

int buffer[BUFFER_SIZE];
int in = 0, out = 0;
sem_t empty, full;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *producer(void *arg)
{
    for (int i = 1; i <= MAX_ITEMS; i++) {
        sem_wait(&empty);                        /* wait for an empty slot */
        pthread_mutex_lock(&mutex);
        buffer[in] = i;
        printf("Produced: %d (slot %d)\n", i, in);
        in = (in + 1) % BUFFER_SIZE;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
        usleep(100000);
    }
    return NULL;
}

void *consumer(void *arg)
{
    for (int i = 1; i <= MAX_ITEMS; i++) {
        sem_wait(&full);                         /* wait for a filled slot */
        pthread_mutex_lock(&mutex);
        int item = buffer[out];
        printf("                    Consumed: %d (slot %d)\n", item, out);
        out = (out + 1) % BUFFER_SIZE;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        usleep(250000);
    }
    return NULL;
}

int main()
{
    pthread_t p, c;

    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);

    pthread_create(&p, NULL, producer, NULL);
    pthread_create(&c, NULL, consumer, NULL);
    pthread_join(p, NULL);
    pthread_join(c, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    printf("All %d items produced and consumed.\n", MAX_ITEMS);
    return 0;
}
