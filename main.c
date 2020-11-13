#include <stdio.h>
#include <stdlib.h>
#include "cellular.h"

void displayMenu();
void processUserChoices();
int  selectGenerationRule();

int main()
{
    Cell **cells = initializeArray(10);
    if(cells != NULL) printf ("Array intialized successfully!\n");

    if (fillGeneration(cells,30) == SUCCESS)
    {
        printf("Generation filled successfully!\n");
    }
    displayGeneration(cells, 10);
    Rules *rules = generateRuleValues(30);

    for(int i=0; i<50; i++)
    {
        calculateNextGeneration(cells, rules);
        displayGeneration(cells,10);

    }

    processUserChoices();
    return 0;
}

/**
Displays the available menu functions for the user to choose.
*/
void displayMenu()
{

}

/**
Proccesses the input of the user
*/
void processUserChoices()
{
    
}

/**
Selects the generation rule
*/
int selectGenerationRule ()
{
    return 0;
}
