/* Exp 20: Reader-Writer problem using semaphores (readers preference).
   Compile: gcc -pthread */
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t wrt;                                       /* exclusive access to the data */
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int readcount = 0;
int data = 0;                                    /* shared resource */

void *reader(void *arg)
{
    int id = *(int *)arg;

    pthread_mutex_lock(&mutex);
    readcount++;
    if (readcount == 1) sem_wait(&wrt);          /* first reader locks out writers */
    pthread_mutex_unlock(&mutex);

    printf("Reader %d is reading data = %d\n", id, data);
    usleep(300000);
    printf("Reader %d finished reading\n", id);

    pthread_mutex_lock(&mutex);
    readcount--;
    if (readcount == 0) sem_post(&wrt);          /* last reader lets writers in */
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void *writer(void *arg)
{
    int id = *(int *)arg;

    sem_wait(&wrt);
    data++;
    printf("Writer %d wrote data = %d\n", id, data);
    usleep(300000);
    sem_post(&wrt);
    return NULL;
}

int main()
{
    pthread_t r[3], w[2];
    int ids[3] = {1, 2, 3};

    sem_init(&wrt, 0, 1);

    pthread_create(&r[0], NULL, reader, &ids[0]);
    usleep(50000);
    pthread_create(&w[0], NULL, writer, &ids[0]);
    usleep(50000);
    pthread_create(&r[1], NULL, reader, &ids[1]);
    usleep(500000);
    pthread_create(&w[1], NULL, writer, &ids[1]);
    usleep(50000);
    pthread_create(&r[2], NULL, reader, &ids[2]);

    for (int i = 0; i < 3; i++) pthread_join(r[i], NULL);
    for (int i = 0; i < 2; i++) pthread_join(w[i], NULL);

    sem_destroy(&wrt);
    return 0;
}
