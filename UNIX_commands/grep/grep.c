/*
 * File: grep.c
 * Description: Searches for lines matching a given pattern in a file.
 * Supports optional flags for case-insensitive search, line numbering, inverted matching, and count of matched lines.
 * Usage: grep [options] "pattern" filename.txt
 */

#include "grep.h"

int main(int argc, char const *argv[])
{
    GrepConfig config;
    bool bPrintFileNameL = false;

    if(argc < 3)
    {
        fprintf(stderr, "grep: insufficient arguments\n");
        fprintf(stderr, "Usage: grep [options] \"pattern\" filename\n");
        exit(EXIT_FAILURE);
    }

    handleInput(argc, argv, &config);

    if(config.fileCount > 1)
    {
        bPrintFileNameL = true;
    }
    

    for (int i = 0; i < config.fileCount; i++)
    {
        handleFile(config.filename[i], config.options, config.pattern, bPrintFileNameL);
        free(config.filename[i]);
    }
    
    free(config.pattern);
    return 0;
}
//----------------------------------------------------------------------------------
void handleFile(char* filename, unsigned int options, char * pattern, bool printFileName)
{
    FILE* currentFile = NULL;
    char currentLine[MAX_LINE_LEN] = { 0 };
    char* lineToSearch = NULL;
    char* patternToSearch = pattern;
    char* lowerPattern = NULL;
    int lineCount = 0;
    int matchCount = 0;

    currentFile = fopen(filename, "r");
    if (currentFile == NULL)
    {
        fprintf(stderr, "grep: %s: No such file or directory", filename);
    }

    if (options & OPTION_IGNORE_CASE) {
        lowerPattern = strdup(pattern);
        strcpy(lowerPattern, pattern);
        toLowercase(lowerPattern);
        patternToSearch = lowerPattern;
    }

    while (fgets(currentLine, MAX_LINE_LEN,currentFile))
    {
        lineCount++;
        lineToSearch = currentLine;

        if (options & OPTION_IGNORE_CASE) 
        {
            toLowercase(lineToSearch);
        }

        if (strstr(lineToSearch, patternToSearch) != NULL) 
        {            
            if (!(options & OPTION_INVERT_MATCH)) 
            { // Normal match
                if (!(options & OPTION_COUNT_LINES))
                {
                    if ((!(options & OPTION_COUNT_LINES)) && (printFileName == true))
                    {
                        printf("%s:", filename);
                    }
                    if (options & OPTION_LINE_NUMBER) 
                    {
                        printf("%d:", lineCount);
                    }
                    printf("%s", currentLine);
                }
                matchCount++;
            }
        } 
        else if (options & OPTION_INVERT_MATCH) 
        { // Inverted match
            if (!(options & OPTION_COUNT_LINES))
            {
                if ((!(options & OPTION_COUNT_LINES)) && (printFileName == true))
                {
                    printf("%s:", filename);
                }
                if (options & OPTION_LINE_NUMBER) 
                {
                    printf("%d:", lineCount);
                }
                printf("%s", currentLine);
            }
            matchCount++;
        }
    }

    if (options & OPTION_COUNT_LINES) {
        printf("Count: %d\n", matchCount);
    }
    
    if (lowerPattern != NULL)
    {
        free(lowerPattern);
    }
    
    fclose(currentFile);
}
//----------------------------------------------------------------------------------
void handleInput(int argc, char const * argv[], GrepConfig* config)
{
    config->options = 0;
    config->pattern = NULL;
    *config->filename  = NULL;
    config->fileCount = 0;
    
    for (int i = 1; i < argc; i++)
    {   
        int parameterLen = strlen(argv[i]);
        // Handle options
        if (argv[i][0] == '-')
        {
            for (int j = 1; j < parameterLen; j++)
            {
                switch (argv[i][j]) {
                    case 'i':
                        config->options |= OPTION_IGNORE_CASE;
                        break;
                    case 'v':
                        config->options |= OPTION_INVERT_MATCH;
                        break;
                    case 'c':
                        config->options |= OPTION_COUNT_LINES;
                        break;
                    case 'n':
                        config->options |= OPTION_LINE_NUMBER;
                        break;
                    default:
                        fprintf(stderr, "Unsupported option: -%c\n", argv[i][j]);
                }
            }
        }
        else if (config->pattern == NULL) 
        {  // The first non-option argument is the pattern
        
            config->pattern = strdup(argv[i]);
        } 
        else
        {  // The third and the next non-option argument are the filenames
            config->filename[config->fileCount] = strdup(argv[i]);
            config->fileCount++;
        }
    }

    if (config->pattern == NULL || config->fileCount == 0) {
        fprintf(stderr, "Usage: grep [options] pattern file\n");
        exit(EXIT_FAILURE);
    }
}
//----------------------------------------------------------------------------------
void toLowercase(char* str) {
    for (; *str; ++str) *str = tolower(*str);
}
//----------------------------------------------------------------------------------
