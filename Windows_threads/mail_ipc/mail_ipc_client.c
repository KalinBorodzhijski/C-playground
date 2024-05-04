// Description: This program demonstrates a client for inter-process communication (IPC) using mailslots in Windows.
//              It sends a message to the mailslot server.

#include <stdio.h>
#include <windows.h>

#define MAILSLOT_NAME "\\\\.\\mailslot\\MyMailSlot"

int main() {
    HANDLE hMailSlot;
    char buffer[1024];
    DWORD bytesWritten;

    hMailSlot = CreateFile(MAILSLOT_NAME, GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
    if (hMailSlot == INVALID_HANDLE_VALUE) {
        printf("Failed to open mailslot. Error %d\n", GetLastError());
        return 1;
    }

    printf("Enter message to send to server: ");
    fgets(buffer, sizeof(buffer), stdin);
    WriteFile(hMailSlot, buffer, strlen(buffer) + 1, &bytesWritten, NULL);
    printf("Message sent to server successfully.\n");

    CloseHandle(hMailSlot);

    return 0;
}
