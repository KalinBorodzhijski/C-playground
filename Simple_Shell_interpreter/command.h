#ifndef COMMAND_H
#define COMMAND_H

#include <stddef.h>
#include "utils.h"

#define EXIT_SHELL 1

int executeCommand(char *cmdLine);
char *readCommandLine(void);

#endif
