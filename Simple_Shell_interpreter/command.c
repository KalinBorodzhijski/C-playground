#include "command.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * Executes the command specified by the command line input.
 * Supports built-in commands and external commands via fork/exec.
 *
 * @param cmdLine The command line input from user.
 * @return int Status code to control shell behavior (e.g., exit shell).
 */
#include <unistd.h>
#include <fcntl.h>

int executeCommand(char *cmdLine) {
    char *args[128];
    char *redirectionFile = NULL;
    int background = 0;
    int argCount = 0;

    char *token = strtok(cmdLine, " \n");

    while (token != NULL) 
    {
        if (strcmp(token, ">") == 0) 
        {
            token = strtok(NULL, " \n");
            redirectionFile = token;
            break;
        } 
        else if (strcmp(token, "&") == 0) 
        {
            background = 1;
            break;
        }
        else 
        {
            args[argCount++] = token;
        }

        token = strtok(NULL, " \n");
    }
    args[argCount] = NULL;

    if (args[0] == NULL) 
    {
        return 0;
    }

    if (strcmp(args[0], "exit") == 0) 
    {
        exit(0);
    }

    int stdout_backup = -1;

    if (redirectionFile) 
    {
        stdout_backup = dup(STDOUT_FILENO);

        int fd = open(redirectionFile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd < 0) 
        {
            perror("Failed to open file for redirection");
            return -1;
        }

        dup2(fd, STDOUT_FILENO);
        close(fd);
    }

    pid_t pid = fork();
    if (pid == 0) 
    {
        if (execvp(args[0], args) == -1) 
        {
            perror("execvp failed");
            exit(EXIT_FAILURE);
        }

    } 
    else if (pid > 0) 
    {
        if (!background) 
        {
            int status;
            waitpid(pid, &status, 0);
        } else 
        {
            printf("Process running in background with PID: %d\n", pid);
        }
    } 
    else
    {
        perror("fork failed");
        return -1;
    }

    if (redirectionFile) 
    {
        dup2(stdout_backup, STDOUT_FILENO);
        close(stdout_backup);
    }

    return 0;
}


/**
 * Reads a line of text from standard input.
 * @return char* Pointer to the line read.
 */
char *readCommandLine(void) 
{
    char *line = NULL;
    size_t bufsize = 0;
    getline(&line, &bufsize, stdin);
    return line;
}
