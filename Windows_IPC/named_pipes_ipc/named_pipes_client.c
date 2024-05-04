// Description: This program demonstrates a client for inter-process communication (IPC) using named pipes in Windows.
//              It connects to the named pipe server, sends a message, and receives the echoed message back.

#include <stdio.h>
#include <windows.h>

#define PIPE_NAME "\\\\.\\pipe\\MyNamedPipe"

int main() {
    HANDLE hPipe;
    char buffer[1024];
    DWORD bytesRead, bytesWritten;

    // Connect to the named pipe
    hPipe = CreateFile(PIPE_NAME, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (hPipe == INVALID_HANDLE_VALUE) {
        printf("Failed to connect to named pipe. Error %d\n", GetLastError());
        return 1;
    }

    // Send message to server
    printf("Enter message to send to server: ");
    fgets(buffer, sizeof(buffer), stdin);
    WriteFile(hPipe, buffer, strlen(buffer) + 1, &bytesWritten, NULL);

    // Receive echoed message from server
    ReadFile(hPipe, buffer, sizeof(buffer), &bytesRead, NULL);
    printf("Received echoed message from server: %s\n", buffer);

    // Close the pipe handle
    CloseHandle(hPipe);

    return 0;
}
