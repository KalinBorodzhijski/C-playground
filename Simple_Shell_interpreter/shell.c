/**
 * @file shell.c
 * @brief Simple Shell Interpreter
 *
 * This shell interpreter supports basic commands such as ls, cd, and exit, as well as additional
 * commands and functionalities. The shell uses UNIX process control including fork(), exec(),
 * and wait() to handle command execution.
 *
 * The shell supports:
 * - Redirection of standard input and output
 * - Piping between commands
 * - Background and foreground job control
 * - Signal handling (e.g., Ctrl-C and Ctrl-Z)
 *
 */

#include "command.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    char *cmdLine;
    printf("Simple Shell Interpreter\n");
    while (1) {
        printf("> ");
        cmdLine = readCommandLine();
        trimWhitespace(cmdLine);
        if (feof(stdin)) { 
            break;
        }

        int executeResult = executeCommand(cmdLine);
        if (executeResult == EXIT_SHELL) {
            break;
        }

        free(cmdLine);
    }

    printf("Exiting shell...\n");
    return 0;
}
