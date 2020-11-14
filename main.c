#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cellular.h"

void displayMenu();
void processUserChoices();
void createNewGeneration();
void selectLengthOfGeneration(int *length);
void selectNumberOfGenerations(int *num);
void selectFirstGeneration(int *gen);
void selectGenerationRule(int *number);
void isIntValid( int min, int max, int *number, char text[]);
char *getFileName();
void loadFile();

int main()
{
   /* Cell **cells = initializeArray(10);
    if(cells != NULL) printf ("Array intialized successfully!\n");

    if (fillGeneration(cells,10) == SUCCESS)
    {
        printf("Generation filled successfully!\n");
    }
    displayGeneration(cells, 10);
    Rules *rules = generateRuleValues(30);

    for(int i=0; i<20; i++)
    {
        calculateNextGeneration(cells, rules);
        displayGeneration(cells,10);

    }
*/

   
    processUserChoices();
    return 0;
}

/**
Processes user's choices
*/
void processUserChoices()
{
    int userChoice=1;
    char text[]="Your option: ";
    
    while(userChoice != 0)
    {
        displayMenu();
        isIntValid(0,2,&userChoice, text);

        if(userChoice == 1)
            createNewGeneration();
        else if(userChoice == 2)
            loadFile();
    }
}
/**
Displays available menu functions for the user to choose from
*/
void displayMenu()
{
    printf("\n");
    printf("----------------------------MENU---------------------------\n");
    printf("1. Start a new 1-D Cellular Automaton\n");
    printf("2. Load previously saved Cellular Automaton from a text file\n");
    printf("0. Exit\n");
    printf("------------------------------------------------------------\n");
}


/**
Creates a new Cellular Automaton
*/
void createNewGeneration()
{
    //setting the values by using  pointers
    int length=0;
    printf("1. ");
    selectLengthOfGeneration(&length);

    int num=0;
    printf("2. ");
    selectNumberOfGenerations(&num);

    int gen=0;
    printf("3. ");
    selectFirstGeneration(&gen);
    
    int rule=0;
    printf("4. ");
    selectGenerationRule(&rule);

    
    printf("5. Cellular Automaton will be automatically saved to a file\n");
    char name[52];
    int size=52;
    char *fileName = getFileName(name,size);
    printf("\n");
    


    //creating a generation by using variables with their new values
    Cell **cells = initializeArray(length);
    fillGeneration(cells,rule);
    Rules *rules = generateRuleValues(rule);

    for(int i=0; i<num; i++)
    {
        calculateNextGeneration(cells, rules);
        saveGenerationToFile(cells,length,fileName);
        displayGeneration(cells,length);
    }
    printf("\n");
    printf("\n");

    free(cells);

}

/**
Reads data from a chosen file
*/
void loadFile()
{
    int result=0;
    do
    {
        char name[52];
        int size=52;
        char *fileName = getFileName(name,size);
        printf("\n");
        result= readFromFile(fileName);
        if(result == FILE_ERROR)
        printf("File with such name does not exist\n");
    }
    while(result != SUCCESS);
}

/**
Selects the size of a generation 
@param *length - a pointer to length variable
*/
void selectLengthOfGeneration(int *length)
{
    //10-100 are only theoretical boundaries, some further testings are needed to determine them
    char text[]= "Please, choose a length of a generation (10-100): ";
    isIntValid(10,100,length,text);
    
}

/**
Selects a number of generations
@param *num - a pointer to a num variable 
*/
void selectNumberOfGenerations(int *num)
{
    //1-200 are only theoretical boundaries, some further testings are needed to determine them
    char text[] = "Please, choose a number of generations  (1-200): ";
    isIntValid(1,200,num,text );
}
 

/**
Selects a number for the first generation
@param *gen - a pointer to a gen variable
*/
void selectFirstGeneration(int *gen)
{
    char text[]="A binary expression of a number will be used as a starting point for a Cellular Automaton.\n Please, enter a number for it  (1-255)";
    isIntValid(1,255,gen,text );
}

/**
Selects a rule 
@param *rule - a pointer to a rule variable
*/
void selectGenerationRule(int *rule)
{
    char text[] = "Please, choose a rule set (0-255) that you want to apply for Cellular Automaton, (e.g. Rule 45)\n Rule ";
    isIntValid(0,255,rule,text );
}


/**
Validates int variables 
@param min - a minimum value 
@param max - a maximum value
@param *number - a pointer to a variable
@param text[] - a text to be displayed to a user
*/
void isIntValid( int min, int max, int *number, char text[])
{
    int x = 0;
    int i = 0;
    do
    {
        printf("%s ", text);
        x = scanf("%d", number);
        if(x == 0 || (x == 1 && getchar() != '\n'))
        {
            i = 0;
            //flushing input buffer (e.g. letters, decimals), otherwise it causes an infinite loop
            while(getchar() != '\n');
        }
        else
        {
            if( *number >= min && *number <= max)
            {
                i = 1;
            }
        }
        
    }while(i == 0);

    printf("\n");
}

/**
Gets a valid string
@param name[] an array of characters to be filled
@param size - a size of an array 
*/
char *getFileName(char name[],int size)
{  
    int j=0  ;
    char *p;
    do
    { 
        printf("Please, enter a file name with up to 50 characters: ");
        fgets(name, size, stdin);
        if ( (p = strchr(name, '\n')) != NULL)
        {
            *p = '\0';
            j=1;
        }
        else
        {
            while(getchar() != '\n');
            printf("Invalid input. Enter a file name with up to 50 characters:");
        }
    }while(j==0);
 return name;
}
