/* Exp 11: Multithreading using POSIX threads (compile: gcc -pthread) */
#include <stdio.h>
#include <pthread.h>

void *threadFunction(void *arg)
{
    char *message = (char *)arg;
    for (int i = 1; i <= 3; i++)
        printf("%s (iteration %d)\n", message, i);
    return NULL;
}

int main()
{
    pthread_t thread1, thread2;
    char *message1 = "Hello from Thread 1!";
    char *message2 = "Hello from Thread 2!";

    pthread_create(&thread1, NULL, threadFunction, (void *)message1);
    pthread_join(thread1, NULL);                 /* wait so output is not interleaved */
    pthread_create(&thread2, NULL, threadFunction, (void *)message2);
    pthread_join(thread2, NULL);

    printf("Main thread: both threads have finished.\n");
    return 0;
}
