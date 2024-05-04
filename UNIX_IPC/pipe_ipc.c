/*
    Description: Demonstrates inter-process communication using pipes.
    Features:
    - Creates a pipe between parent and child processes.
    - Sends a message from the parent to the child process.
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int pipefd[2];
    pid_t pid;
    char message[] = "Hello, child process!";

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {  // Child process
        close(pipefd[1]);  // Close the write end of the pipe
        char buffer[100];
        read(pipefd[0], buffer, sizeof(buffer));
        printf("Child received message: %s\n", buffer);
        close(pipefd[0]);  // Close the read end of the pipe
    } else {  // Parent process
        close(pipefd[0]);  // Close the read end of the pipe
        write(pipefd[1], message, strlen(message) + 1);
        close(pipefd[1]);  // Close the write end of the pipe
    }

    return 0;
}
