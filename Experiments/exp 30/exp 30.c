/* Exp 30: Thread related concepts: (i) create (ii) join (iii) equal (iv) exit
   Compile: gcc -pthread */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_t main_thread;

void *worker(void *arg)
{
    int id = *(int *)arg;
    usleep(100000 * id);                         /* keep the output in a fixed order */
    printf("Thread %d started\n", id);

    if (pthread_equal(pthread_self(), main_thread))      /* (iii) pthread_equal */
        printf("Thread %d: pthread_self() is equal to the main thread\n", id);
    else
        printf("Thread %d: pthread_self() is NOT equal to the main thread\n", id);

    int *result = malloc(sizeof(int));
    *result = id * 100;
    printf("Thread %d exiting with value %d\n", id, *result);
    pthread_exit(result);                        /* (iv) pthread_exit */
}

int main()
{
    pthread_t t1, t2;
    int a = 1, b = 2;
    void *ret;

    main_thread = pthread_self();

    pthread_create(&t1, NULL, worker, &a);       /* (i) pthread_create */
    pthread_create(&t2, NULL, worker, &b);
    printf("Main: threads t1 and t2 created\n");

    printf("Main: pthread_equal(t1, t2) = %d (0 means different threads)\n", pthread_equal(t1, t2));
    printf("Main: pthread_equal(t1, t1) = %d (non-zero means same thread)\n", pthread_equal(t1, t1) != 0);

    pthread_join(t1, &ret);                      /* (ii) pthread_join */
    printf("Main: thread t1 joined, returned %d\n", *(int *)ret);
    free(ret);
    pthread_join(t2, &ret);
    printf("Main: thread t2 joined, returned %d\n", *(int *)ret);
    free(ret);
    return 0;
}
