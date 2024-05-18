/*
 * File: ls.h
 * Description: Header file for the ls command implementation.
 */

#ifndef LS_H
#define LS_H

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h> 
#include <limits.h>
#include <time.h>

#ifdef _WIN32
#include <stdlib.h>
#define realpath(N,R) _fullpath((R),(N),PATH_MAX)
#else
#include <unistd.h>
#endif

// Flag defines
typedef uint8_t tFlag;

typedef struct {
    char *name;
    char *path;
    off_t size;
    time_t mtime;
} FileEntry;

#define FLAG_L              ((tFlag)0x01)  // Long listing format -l
#define FLAG_A              ((tFlag)0x02)  // Show all files including hidden -a
#define FLAG_ALMOST_ALL     ((tFlag)0x04)  // Show almost all files, excluding '.' and '..' -A
#define FLAG_H              ((tFlag)0x08)  // Human readable sizes with -l -h
#define FLAG_R              ((tFlag)0x10)  // Reverse the order of the sort -r
#define FLAG_T              ((tFlag)0x20)  // Sort by modification time, newest first -t
#define FLAG_S              ((tFlag)0x40)  // Sort by file size, largest first -S


#define MAX_PATHS           100

/*
 * Function: handleInput
 * ------------------------------
 * Description:
 *   Processes and parses the command-line arguments passed to the program, distinguishing between
 *   flags and file or directory paths. It updates a flags variable based on command-line options
 *   and stores valid directory or file paths in an array if they exist.
 *
 * Inputs:
 *   argc - The count of command-line arguments provided to the program.
 *   argv - An array of strings representing the command-line arguments.
 *   flags - A pointer to a tFlag variable where the function will store the status of the parsed flags.
 *   filePaths - A pointer to an array of strings where valid paths will be stored.
 *
 * Outputs:
 *   Modifies the 'flags' variable to reflect the combined status of all command flags encountered in the arguments.
 *   Updates the 'filePaths' array with the valid paths provided in the arguments, if they exist.
 *   No return value, but the function uses standard output and error output to communicate with the user about invalid options or paths.
 */
void handleInput(int argc, char** argv, tFlag* flags, char** filePaths);

/*
 * Function: handleInputFlags
 * ------------------------------
 * Description:
 *   This function determines which flags have been set by the user and configures the 
 *   behavior of the program accordingly.
 *
 * Inputs:
 *   flag - Character from the input that should be assigned to flag.
 *
 * Outputs:
 *   Return the bit value for the specific flag.
 *
 */
tFlag handleInputFlags(const char flag);


/*
 * Function: handleInputFolders
 * ------------------------------
 * Description:
 *   Parses command line arguments to extract and handle directory paths. 
 *   This function is intended to store valid directory paths into an array
 *   for further processing. Each directory path parsed from the command line
 *   arguments is verified and added to the filePaths array if it represents 
 *   a valid directory.
 *
 * Inputs:
 *   currentArgument - A const char pointer to the current command line argument,
 *                     which is expected to potentially contain a directory path.
 *   filePaths       - A pointer to an array of char pointers where valid directory
 *                     paths will be stored. This array must be pre-allocated.
 *
 * Outputs:
 *   Updates the filePaths array with valid directory paths extracted from the 
 *   currentArgument. The function itself does not return a value but alters
 *   the state of filePaths to reflect the parsed directories.
 */
void handleInputFolders(const char* currentArgument, char** filePaths);

/*
 * Function: handleFolder
 * ----------------------
 * Description:
 *   Processes a specified folder according to various flags.  It acts based on the flags 
 *   passed, which dictate whether to show hidden files, list details, sort by size/time, 
 *   and more.
 *
 * Inputs:
 *   folderPath - A pointer to a character array that holds the path of the folder to be processed.
 *                This path should be absolute to the current working directory.
 *   flags      - A bitwise combination of tFlag values that specify how the folder should be handled.
 *                These flags could control behaviors like recursive listing, showing hidden files,
 *                sorting order, etc.
 *
 * Outputs:
 *   There are no direct outputs from the function (void return type), but it will output to the standard 
 *   output (e.g., printing folder contents) based on the flags.
 */
void handleFolder(char * folderPath, tFlag flags);

/*
 * Function: compareSize
 * ----------------------
 * Description:
 *   A comparison function used for sorting an array of FileEntry structures by file size.
 *   Designed to be used with qsort.
 *
 * Inputs:
 *   a - A pointer to the first FileEntry to compare.
 *   b - A pointer to the second FileEntry to compare.
 *
 * Returns:
 *   An integer less than, equal to, or greater than zero if the size of the first argument is
 *   considered to be respectively less than, equal to, or greater than that of the second.
 */
int compareSize(const void *a, const void *b);


/*
 * Function: compareTime
 * ----------------------
 * Description:
 *   A comparison function used for sorting an array of FileEntry structures by modification time.
 *   Designed to be used with qsort.
 *
 * Inputs:
 *   a - A pointer to the first FileEntry to compare.
 *   b - A pointer to the second FileEntry to compare.
 *
 * Returns:
 *   An integer less than, equal to, or greater than zero if the modification time of the first argument
 *   is considered to be respectively less than, equal to, or greater than that of the second.
 */
int compareTime(const void *a, const void *b);

/*
 * Function: loadDirectoryEntries
 * ----------------------
 * Description:
 *   Loads directory entries into a dynamically allocated array of FileEntry structures.
 *   Filters entries based on the flags provided, such as ignoring hidden files unless
 *   specified by the flags.
 *
 * Inputs:
 *   folderPath - A string containing the path to the directory whose entries are to be loaded.
 *   entries    - A pointer to an array of FileEntry structures where the directory entries will be stored.
 *   flags      - A set of bitwise flags that control which files are loaded (e.g., hidden or not, all files).
 *
 * Returns:
 *   The number of entries loaded into the array.
 */
size_t loadDirectoryEntries(const char *folderPath, FileEntry **entries, tFlag flags);

/*
 * Function: sortEntries
 * ----------------------
 * Description:
 *   Sorts an array of FileEntry structures based on specified criteria controlled by flags, 
 *   such as size or modification time.
 *
 * Inputs:
 *   entries    - An array of FileEntry structures to be sorted.
 *   numEntries - The number of elements in the entries array.
 *   flags      - A set of bitwise flags that determine the sorting criteria (size, time).
 *
 * Returns:
 *   None.
 */
void sortEntries(FileEntry *entries, size_t numEntries, tFlag flags);

/*
 * Function: printEntries
 * ----------------------
 * Description:
 *   Prints the details of each FileEntry in the array to the standard output.
 *   The level of detail printed is controlled by the flags, such as whether to
 *   display file sizes or just file names.
 *
 * Inputs:
 *   entries    - An array of FileEntry structures to be printed.
 *   numEntries - The number of elements in the entries array.
 *   flags      - A set of bitwise flags that control the output format (detailed or simple).
 *
 * Returns:
 *   None.
 */
void printEntries(const FileEntry *entries, size_t numEntries, tFlag flags);

/*
 * Function: freeEntries
 * ----------------------
 * Description:
 *   Frees the memory allocated for an array of FileEntry structures, including
 *   memory allocated for the name and path of each entry.
 *
 * Inputs:
 *   entries    - An array of FileEntry structures whose memory is to be freed.
 *   numEntries - The number of elements in the entries array.
 *
 * Returns:
 *   None.
 */
void freeEntries(FileEntry *entries, size_t numEntries);

/*
 * Function: handleRecursive
 * ----------------------
 * Description:
 *   Recursively processes directories listed in an array of FileEntry structures.
 *   This function is called if the recursive flag is set, and it will call handleFolder
 *   recursively on each directory found.
 *
 * Inputs:
 *   entries    - An array of FileEntry structures representing the directories to be processed.
 *   numEntries - The number of elements in the entries array.
 *   flags      - A set of bitwise flags that may affect the recursive processing (e.g., flags passed to handleFolder).
 *
 * Returns:
 *   None.
 */
void handleRecursive(const FileEntry *entries, size_t numEntries, tFlag flags);
#endif //LS_H