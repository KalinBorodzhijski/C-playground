#include "main.h"
#include "../String_manipulation/string_local.h"

int main()
{
    // Initialize an array of Person structures with data for three different individuals.
    tPerson people[3];
    tAddress address;
    my_strcpy(address.city, "Sofia", MAX_CITY_SIZE);
    my_strcpy(address.street, "Vitoshka", MAX_STREET_SIZE);
    my_strcpy(address.zipCode, "1000", MAX_ZIPCODE_SIZE);
    
    my_strcpy(people[0].firstName, "Kalin", MAX_NAME_SIZE);
    my_strcpy(people[0].lastName, "Borodzhijski", MAX_NAME_SIZE);
    people[0].age = 23;
    people[0].address = address;

    my_strcpy(people[1].firstName, "Ivan", MAX_NAME_SIZE);
    my_strcpy(people[1].lastName, "Petrov", MAX_NAME_SIZE);
    people[1].age = 18;
    my_strcpy(people[1].address.street, "Slivnitsa", MAX_STREET_SIZE);

    my_strcpy(people[2].firstName, "Georgi", MAX_NAME_SIZE);
    my_strcpy(people[2].lastName, "Ivanov", MAX_NAME_SIZE);
    people[2].age = 30;
    people[2].address = address;

    // Test additional functions
    printf("Person's age before - %d\n", people[0].age);
    updateAge(&people[0], 25);
    printf("Person's age after - %d\n", people[0].age);

    printInformation(&people[0]);
    printInformation(&people[1]);
    printInformation(&people[2]);

    printf("Is over 23 - %d\n", isOverAge(&people[0], 23));

    // Test file operations
    saveListToFile(people, 3);

    appendPersonToFile(&people[0]);

    size_t readPeopleSize = 0;
    tPerson* readPeople = readListFromFlie(&readPeopleSize);
    if(readPeople != NULL)
    {
        printf("Information from the file:\n");
        for (size_t i = 0; i < readPeopleSize; i++)
        {
            printInformation(&readPeople[i]);
        }
        free(readPeople);
    }

    return 0;
}

void updateAge(tPerson * const person, const uint8_t newAge)
{
    if((newAge > 0) && (newAge < 120))
    {
        person->age = newAge;
    }
}

void printInformation(const tPerson * const person)
{
    printf("%s %s is %d years old and he is living in city %s street %s with zip code %s\n", \
    person->firstName, person->lastName, person->age, person->address.city, person->address.street, person->address.zipCode);
}

bool isOverAge(const tPerson * const person, const uint8_t ageToCheck)
{
    return person->age > ageToCheck;
}
