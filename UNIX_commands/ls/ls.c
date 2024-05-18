/*
 * File: ls.c
 * Description: Emulates the ls command, which lists directory contents in long format.
 * Usage: ls -l /home/user
 * 
 *  * Supported flags:
 *  -l: Long listing format
 *  -a: Include hidden files
 *  -A: Include hidden files but not '.' or '..'
 *  -h: Human-readable sizes
 *  -r: Reverse the order of the sort
 *  -t: Sort by modification time
 *  -S: Sort by file size
 */
#include "ls.h"


int main(int argc, char** argv)
{
    tFlag flags;
    char* filePaths[MAX_PATHS] = { NULL };
    char cwd[PATH_MAX];

    handleInput(argc, argv, &flags, filePaths);

    if(filePaths[0] == NULL)
    {
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            filePaths[0] = strdup(cwd);
        } 
    }

    // Handle each directory that is valid
    for (size_t i = 0; (i < MAX_PATHS) && (filePaths[i] != NULL); i++)
    {
        printf("Directory Path '%s':\n", filePaths[i]);
        handleFolder(filePaths[i], flags);
        free(filePaths[i]);
    }

    return 0;
}
//---------------------------------------------------------------------------------------------------------------
void handleFolder(char * folderPath, tFlag flags)
{
    FileEntry *entries = NULL;
    size_t numEntries;

    numEntries = loadDirectoryEntries(folderPath, &entries, flags);

    if (numEntries == 0) {
        fprintf(stderr, "No entries to process in %s or unable to read directory.\n", folderPath);
        return;
    }

    sortEntries(entries, numEntries, flags);

    printEntries(entries, numEntries, flags);

    freeEntries(entries, numEntries);
}

//---------------------------------------------------------------------------------------------------------------
void handleInput(int argc, char** argv, tFlag* flags, char** filePaths)
{
    tFlag current_flag = 0;
    int currentArgLenL = 0;

    if(argc > 1)
    {
        for (int i = 1; i < argc; i++)
        {
            char* currentArgument = argv[i];

            currentArgLenL = strlen(currentArgument);

            if(currentArgLenL > 0)
            {
                // Folder name
                if(currentArgument[0] != '-')
                {   
                    handleInputFolders(currentArgument, filePaths);
                }
                // Flags
                else
                {
                    for (int j = 1; j < currentArgLenL; j++)
                    {
                        current_flag = handleInputFlags(currentArgument[j]);

                        if(current_flag == 0)
                        {
                            fprintf(stderr, "ls: '%c' is not a valid argument !\n", currentArgument[j]);
                            continue;
                        }

                        (*flags) |= current_flag;
                    }
                }
            }
        }
    }
}
//---------------------------------------------------------------------------------------------------------------
void handleInputFolders(const char* currentArgument, char** filePaths)
{
    static int pathIndex = 0;
    struct stat pathStat = {0};
    char resolvedPath[PATH_MAX];

    if (realpath(currentArgument, resolvedPath)) {
        int len = strlen(resolvedPath);
        if (len > 0 && resolvedPath[len - 1] == '\\') {
            if (len > 1 || (len == 1 && resolvedPath[0] != '\\')) {
                resolvedPath[len - 1] = '\0';
            }
        }

        if (stat(resolvedPath, &pathStat) == 0) {
            if (pathIndex < MAX_PATHS) {
                filePaths[pathIndex++] = strdup(resolvedPath);
            } else {
                fprintf(stderr, "ls: Maximum number of paths (%d) exceeded.\n", MAX_PATHS);
            }
        } else {
            fprintf(stderr, "ls: Error: The path '%s' does not exist.\n", resolvedPath);
        }
    } else {
        fprintf(stderr, "ls: Error: Failed to resolve the path '%s'.\n", currentArgument);
    }
}

//---------------------------------------------------------------------------------------------------------------
tFlag handleInputFlags(const char flag)
{
    switch (flag)
    {
        case 'l': return FLAG_L;
        case 'a': return FLAG_A;
        case 'A': return FLAG_ALMOST_ALL;
        case 'h': return FLAG_H;
        case 'r': return FLAG_R;
        case 't': return FLAG_T;
        case 'S': return FLAG_S;
        default:  return 0;
    }
}
//---------------------------------------------------------------------------------------------------------------
int compareSize(const void *a, const void *b) {
    FileEntry *fa = (FileEntry *)a;
    FileEntry *fb = (FileEntry *)b;
    return (fb->size - fa->size);
}
//---------------------------------------------------------------------------------------------------------------
int compareTime(const void *a, const void *b) {
    FileEntry *fa = (FileEntry *)a;
    FileEntry *fb = (FileEntry *)b;
    return (fb->mtime - fa->mtime);
}
//---------------------------------------------------------------------------------------------------------------

size_t loadDirectoryEntries(const char *folderPath, FileEntry **entries, tFlag flags) {

    DIR *dir = opendir(folderPath);
    if (!dir) {
        fprintf(stderr, "ls: Error: Unable to open directory %s\n", folderPath);
        return 0;
    }

    size_t numEntries = 0, capacity = 10;
    *entries = malloc(capacity * sizeof(FileEntry));
    if (!*entries) {
        perror("ls: Failed to allocate memory");
        closedir(dir);
        return 0;
    }

    struct dirent *entry;
    struct stat statbuf;
    char fullPath[1024];

    while ((entry = readdir(dir))) {
        if (!(flags & FLAG_A) && entry->d_name[0] == '.') continue;
        if ((flags & FLAG_ALMOST_ALL) && (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)) continue;

        snprintf(fullPath, sizeof(fullPath), "%s/%s", folderPath, entry->d_name);
        if (stat(fullPath, &statbuf) == -1) {
            fprintf(stderr, "ls: Error: Unable to stat file %s\n", fullPath);
            continue;
        }

        if (numEntries >= capacity) {
            capacity *= 2;
            *entries = realloc(*entries, capacity * sizeof(FileEntry));
            if (!*entries) {
                perror("Failed to resize memory");
                break;
            }
        }

        (*entries)[numEntries].name = strdup(entry->d_name);
        (*entries)[numEntries].path = strdup(fullPath);
        (*entries)[numEntries].size = statbuf.st_size;
        (*entries)[numEntries].mtime = statbuf.st_mtime;
        numEntries++;
    }

    closedir(dir);
    return numEntries;
}
//---------------------------------------------------------------------------------------------------------------
void sortEntries(FileEntry *entries, size_t numEntries, tFlag flags) {
    if (flags & FLAG_S) qsort(entries, numEntries, sizeof(FileEntry), compareSize);
    if (flags & FLAG_T) qsort(entries, numEntries, sizeof(FileEntry), compareTime);
}
//---------------------------------------------------------------------------------------------------------------
void printEntries(const FileEntry *entries, size_t numEntries, tFlag flags) {
    for (size_t i = 0; i < numEntries; i++) {
        if (flags & FLAG_L) {
            printf("%s - %ld bytes\n", entries[i].name, entries[i].size);
        } else {
            printf("%s\n", entries[i].name);
        }
    }
}
//---------------------------------------------------------------------------------------------------------------
void freeEntries(FileEntry *entries, size_t numEntries) {
    for (size_t i = 0; i < numEntries; i++) {
        free(entries[i].name);
        free(entries[i].path);
    }
    free(entries);
}
//---------------------------------------------------------------------------------------------------------------