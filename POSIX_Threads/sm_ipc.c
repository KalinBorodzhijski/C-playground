/*
    Description: Demonstrates inter-process communication using shared memory.
    Features:
    - Creates a shared memory segment.
    - Writes a message from the parent process.
    - Reads the message in the child process.
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <string.h>

#define SHMSZ 100

int main() {
    key_t key;
    int shmid;
    char *shm, *s;
    pid_t pid;

    key = ftok("/tmp", 'A');
    shmid = shmget(key, SHMSZ, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    shm = shmat(shmid, NULL, 0);
    if (shm == (char *)-1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {  // Child process
        printf("Child received message: %s\n", shm);
    } else {  // Parent process
        strcpy(shm, "Hello, child process!");
    }

    return 0;
}
