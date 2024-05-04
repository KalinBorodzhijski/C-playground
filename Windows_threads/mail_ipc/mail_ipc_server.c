// Description: This program demonstrates inter-process communication (IPC) using mailslots in Windows.
//              It creates a mailslot server that listens for messages from clients.

#include <stdio.h>
#include <windows.h>

#define MAILSLOT_NAME "\\\\.\\mailslot\\MyMailSlot"

int main() {
    HANDLE hMailSlot;
    char buffer[1024];
    DWORD bytesRead;

    hMailSlot = CreateMailslot(MAILSLOT_NAME, 0, MAILSLOT_WAIT_FOREVER, NULL);
    if (hMailSlot == INVALID_HANDLE_VALUE) {
        printf("Failed to create mailslot. Error %d\n", GetLastError());
        return 1;
    }

    printf("Mailslot server listening for messages...\n");
    while (1) {
        if (ReadFile(hMailSlot, buffer, sizeof(buffer), &bytesRead, NULL)) {
            printf("Received message from client: %s\n", buffer);
        }
    }

    CloseHandle(hMailSlot);

    return 0;
}
