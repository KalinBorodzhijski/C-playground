// Description: This program demonstrates inter-process communication (IPC) using shared memory in Windows.
//              It creates a shared memory region, writes data to it, and another process reads the data.

#include <stdio.h>
#include <windows.h>

#define SHARED_MEM_SIZE 1024
#define SHARED_MEM_NAME "Local\\MySharedMemory"

int main() {
    HANDLE hMapFile;
    LPCTSTR pBuf;

    hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, SHARED_MEM_SIZE, SHARED_MEM_NAME);
    if (hMapFile == NULL) {
        printf("Failed to create shared memory. Error %d\n", GetLastError());
        return 1;
    }

    pBuf = (LPTSTR)MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, SHARED_MEM_SIZE);
    if (pBuf == NULL) {
        printf("Failed to map view of file. Error %d\n", GetLastError());
        CloseHandle(hMapFile);
        return 1;
    }

    printf("Writing data to shared memory...\n");
    sprintf((char*)pBuf, "Hello from shared memory!");

    printf("Press Enter to exit...");
    getchar();

    UnmapViewOfFile(pBuf);
    CloseHandle(hMapFile);

    return 0;
}
