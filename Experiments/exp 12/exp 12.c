/* Exp 12: Dining Philosophers problem (deadlock avoided by allowing at most 4
   philosophers to pick up chopsticks at a time). Compile: gcc -pthread */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5
#define MEALS 2

pthread_mutex_t chopstick[N];
sem_t room;                                      /* allows at most N-1 philosophers */

void *philosopher(void *arg)
{
    int id = *((int *)arg);
    int left = id, right = (id + 1) % N;

    for (int m = 0; m < MEALS; m++) {
        printf("Philosopher %d is thinking...\n", id);
        usleep(100000 * (id + 1));

        sem_wait(&room);
        pthread_mutex_lock(&chopstick[left]);
        pthread_mutex_lock(&chopstick[right]);

        printf("Philosopher %d is eating (meal %d)\n", id, m + 1);
        usleep(200000);

        pthread_mutex_unlock(&chopstick[right]);
        pthread_mutex_unlock(&chopstick[left]);
        sem_post(&room);
        printf("Philosopher %d finished eating and put down the chopsticks\n", id);
    }
    return NULL;
}

int main()
{
    pthread_t ph[N];
    int ids[N];

    sem_init(&room, 0, N - 1);
    for (int i = 0; i < N; i++)
        pthread_mutex_init(&chopstick[i], NULL);

    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&ph[i], NULL, philosopher, &ids[i]);
    }
    for (int i = 0; i < N; i++)
        pthread_join(ph[i], NULL);

    for (int i = 0; i < N; i++)
        pthread_mutex_destroy(&chopstick[i]);
    sem_destroy(&room);
    printf("All philosophers have finished eating.\n");
    return 0;
}
