/*
    Description: Demonstrates inter-process communication using message queues.
    Features:
    - Creates a message queue.
    - Sends a message from the parent to the child process.
*/
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>

struct message {
    long mtype;
    char mtext[100];
};

int main() {
    key_t key;
    int msgid;
    struct message msg;
    pid_t pid;

    key = ftok("/tmp", 'A');
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {  // Child process
        msgrcv(msgid, &msg, sizeof(msg.mtext), 1, 0);
        printf("Child received message: %s\n", msg.mtext);
    } else {  // Parent process
        strcpy(msg.mtext, "Hello, child process!");
        msg.mtype = 1;
        msgsnd(msgid, &msg, sizeof(msg.mtext), 0);
    }

    return 0;
}
