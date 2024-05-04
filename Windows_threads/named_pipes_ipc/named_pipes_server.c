/*
Description: This program demonstrates inter-process communication (IPC) using named pipes in Windows.
             It creates a server that listens for client connections, receives messages from clients,
             and echoes them back.
*/
#include <stdio.h>
#include <windows.h>

#define PIPE_NAME "\\\\.\\pipe\\MyNamedPipe"

int main() {
    HANDLE hPipe;
    char buffer[1024];
    DWORD bytesRead;

    hPipe = CreateNamedPipe(PIPE_NAME, PIPE_ACCESS_DUPLEX, PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
                            PIPE_UNLIMITED_INSTANCES, 512, 512, 0, NULL);

    if (hPipe == INVALID_HANDLE_VALUE) {
        printf("Failed to create named pipe. Error %d\n", GetLastError());
        return 1;
    }
    printf("Waiting for client connection...\n");
    ConnectNamedPipe(hPipe, NULL);
    printf("Client connected. Ready to receive messages...\n");

    while (1) {
        if (ReadFile(hPipe, buffer, sizeof(buffer), &bytesRead, NULL)) {
            printf("Received message from client: %s\n", buffer);
            WriteFile(hPipe, buffer, bytesRead, NULL, NULL);
        }
    }

    CloseHandle(hPipe);

    return 0;
}
