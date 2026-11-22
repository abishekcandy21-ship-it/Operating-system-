/* Exp 9: Inter-process communication using shared memory */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define SHM_SIZE 1024

int main()
{
    int shmid;
    char *shm_ptr;
    pid_t pid;

    /* create a shared memory segment */
    shmid = shmget(IPC_PRIVATE, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid == -1) { perror("shmget"); exit(1); }
    printf("Shared memory segment created, id = %d\n", shmid);

    pid = fork();
    if (pid < 0) { perror("fork"); exit(1); }

    if (pid == 0) {                              /* child: writer */
        shm_ptr = (char *)shmat(shmid, NULL, 0);
        if (shm_ptr == (char *)-1) { perror("shmat"); exit(1); }
        strcpy(shm_ptr, "Hello, shared memory!");
        printf("Child  (writer): Data written to shared memory: %s\n", shm_ptr);
        shmdt(shm_ptr);
        exit(0);
    }

    wait(NULL);                                  /* parent: reader */
    shm_ptr = (char *)shmat(shmid, NULL, 0);
    if (shm_ptr == (char *)-1) { perror("shmat"); exit(1); }
    printf("Parent (reader): Data read from shared memory:   %s\n", shm_ptr);
    shmdt(shm_ptr);

    shmctl(shmid, IPC_RMID, NULL);               /* remove the segment */
    printf("Shared memory segment removed.\n");
    return 0;
}
