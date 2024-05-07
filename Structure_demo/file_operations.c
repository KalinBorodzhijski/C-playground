#include "main.h"


void saveListToFile(tPerson* people, size_t peopleSize)
{
    FILE* file = fopen(FILE_NAME,"wb");

    if(file == NULL)
    {
        fprintf(stderr, "Error opening file! \n");
        return;
    }

    size_t itemsWritten = fwrite(people, sizeof(tPerson), peopleSize, file);
    if(itemsWritten != peopleSize)
    {
        fprintf(stderr, "Error writing to file\n");
    }

    fclose(file);
}

// Read people from file
tPerson* readListFromFlie(size_t* peopleSize)
{
    tPerson* readPeople = NULL;
    FILE* file = fopen(FILE_NAME,"rb");
    if(file == NULL)
    {
        fprintf(stderr, "Error opening file! \n");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    *peopleSize = fileSize / sizeof(tPerson);
    readPeople = malloc(*peopleSize * sizeof(tPerson));

    if(readPeople == NULL)
    {
        fprintf(stderr, "Error allocating memory! \n");
        fclose(file);
        return NULL;
    }

    size_t itemsRead = fread(readPeople, sizeof(tPerson), *peopleSize, file);
    if (itemsRead != *peopleSize) {
        fprintf(stderr, "Error reading from file\n");
        free(readPeople);
        fclose(file);
        return NULL;
    }

    fclose(file);
    return readPeople;
}

// Append person to file
void appendPersonToFile(const tPerson * const  person)
{
    FILE* file = fopen(FILE_NAME,"ab");

    if(file == NULL)
    {
        fprintf(stderr, "Error opening file! \n");
        return;
    }

    size_t writtenItems = fwrite(person, sizeof(tPerson), 1, file);
    if(writtenItems != 1)
    {
        fprintf(stderr, "Error writing to file\n");
    }

    fclose(file);
}