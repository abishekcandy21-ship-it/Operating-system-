/* Exp 1: Create a new process using fork() and display process IDs
   using getpid() and getppid() */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;

    printf("Before fork: Process ID = %d, Parent Process ID = %d\n", getpid(), getppid());

    pid = fork();                       /* create a new process */

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }
    else if (pid == 0) {                /* child process */
        printf("CHILD  : Process ID = %d, Parent Process ID = %d\n", getpid(), getppid());
    }
    else {                              /* parent process */
        wait(NULL);                     /* wait for child to finish */
        printf("PARENT : Process ID = %d, Child Process ID = %d, Parent's Parent ID = %d\n",
               getpid(), pid, getppid());
    }
    return 0;
}
