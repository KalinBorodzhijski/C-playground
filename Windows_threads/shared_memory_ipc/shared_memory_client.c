// Description: This program demonstrates a client for inter-process communication (IPC) using shared memory in Windows.
//              It reads data from the shared memory region created by the server.

#include <stdio.h>
#include <windows.h>

#define SHARED_MEM_NAME "Local\\MySharedMemory"

int main() {
    HANDLE hMapFile;
    LPCTSTR pBuf;

    hMapFile = OpenFileMapping(FILE_MAP_READ, FALSE, SHARED_MEM_NAME);
    if (hMapFile == NULL) {
        printf("Failed to open shared memory. Error %d\n", GetLastError());
        return 1;
    }

    pBuf = (LPTSTR)MapViewOfFile(hMapFile, FILE_MAP_READ, 0, 0, 0);
    if (pBuf == NULL) {
        printf("Failed to map view of file. Error %d\n", GetLastError());
        CloseHandle(hMapFile);
        return 1;
    }

    printf("Data read from shared memory: %s\n", pBuf);

    UnmapViewOfFile(pBuf);
    CloseHandle(hMapFile);

    return 0;
}
