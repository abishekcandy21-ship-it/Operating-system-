/* Exp 10: Inter-process communication using a message queue */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>

struct message {
    long msg_type;
    char msg_text[100];
};

int main()
{
    int msgid;
    struct message msg;
    pid_t pid;

    msgid = msgget(IPC_PRIVATE, IPC_CREAT | 0666);
    if (msgid == -1) { perror("msgget"); exit(1); }
    printf("Message queue created, id = %d\n", msgid);

    pid = fork();
    if (pid < 0) { perror("fork"); exit(1); }

    if (pid == 0) {                              /* child: producer (sender) */
        msg.msg_type = 1;
        strcpy(msg.msg_text, "Hello, message queue!");
        if (msgsnd(msgid, &msg, sizeof(msg.msg_text), 0) == -1) { perror("msgsnd"); exit(1); }
        printf("Producer: Data sent to message queue    : %s\n", msg.msg_text);
        exit(0);
    }

    wait(NULL);                                  /* parent: consumer (receiver) */
    if (msgrcv(msgid, &msg, sizeof(msg.msg_text), 1, 0) == -1) { perror("msgrcv"); exit(1); }
    printf("Consumer: Data received from the queue  : %s\n", msg.msg_text);

    msgctl(msgid, IPC_RMID, NULL);               /* remove the queue */
    printf("Message queue removed.\n");
    return 0;
}
