#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "cellular.h"


/** ## FUNCTION IMPLEMENTATIONS ## */


/**
Allocates the space for the cell and initializes its values.
*/
Cell *initializeCell()
{
    Cell* cell = (Cell*)malloc(sizeof(Cell));
    if (cell == NULL) return NULL;

    cell->state = 0;
    cell->prevState = -1;
    cell->neighbours = -1;

    return cell;
}


/**
Initializes the array of cells
*/
Cell **initializeArray(int generationSize)
{
    Cell **p = (Cell**)malloc(sizeof(Cell*)*generationSize);

    for (int i=0; i<generationSize; i++)
    {
        Cell *cell = initializeCell();
        p[i] = cell;
    }

    return p;
}


/**
Converts a decimal number into binary and returnts it.
param @int - number to be converted
@return - binary number
*/
long long convertToBinary(int number)
{
    (void)number;
    return 0;
}

/**
Converts a binary number into decimal and returnts it.
param @long long - number to be converted
@return - decimal number
*/
int convertToDecimal(long long number)
{
    (void)number;
    return 0;
}

/**
Method which performs the cellular automation.
*/
void cellularAutomation (Cell *array)
{
    (void)array;
}

/**
Prints the generation to the screen/terminal.
@param *array - pointer to the array of the generation to print
*/
void displayGeneration(Cell *array, int generationSize)
{   
    for(int i=1; i<generationSize; i++)
    {
        printf(" %d ", array[i].state);
    }

}

/**
Fills the first generation with 0's and 1's
bsaed on the provided rule.

@param *array - pointer to the array of the generation
@param rule - rule to use for the filling of the generation

*/
int fillGeneration (Cell *array, int rule)
{
    if(array == NULL) return INVALID_INPUT_PARAMETER;
    if(rule < 1 || rule > 256) return INVALID_INPUT_PARAMETER;

    //Retains the binary expression of the rule
    long long binaryRuleNumber = convertToBinary(rule);

    //Converts the rule numbers into an array of digits for easier comparison
    int rulePattern[9];

    for (int i=9; i>=1; i--)
    {
        rulePattern[i] = binaryRuleNumber % 10;
        binaryRuleNumber = binaryRuleNumber/ 10;
    }

    for(int i=1; i<9; i++)
    {
        array[i].state = rulePattern[i];
    }


    return SUCCESS;

}

/**
Calculates the next generation of cells by examining the neighbours.

@param *array - pointer to the array of the generation
@param rule - rule to calculate by
*/
int calculateNextGeneration (Cell *array, Rules *rules)
{
    if (array == NULL) return INVALID_INPUT_PARAMETER;

    int binaryPattern [3];
    int binaryPatternAsInt = 0;
    char newState;

    for (int i=1; i<9; i++)
    {
        binaryPattern[0] = array[i-1].prevState;
        binaryPattern[1] = array[i].prevState;
        binaryPattern[2] = array[i+1].prevState;
        
        
        binaryPatternAsInt = binaryPattern[0]*100 + binaryPattern[1]*10+binaryPattern[2];

        newState = hashCode(rules, binaryPatternAsInt);
        if(newState == -1) return ERROR;
        array[i].state = newState;
        
    }

    return SUCCESS;

}

/**
Returns key value for the matched rule pattern.
@param Rules *r - pointer to a hashtable of chosen rules
@param char[] value - value to be looked up

@return 0 or 1 depending on the pairing of the rule
*/
int findValue(Rules *r, int value)
{

    int pos = hashCode(r,value);

    Pattern *ruleset = r->ruleset[pos];
    Pattern *temp = ruleset;

    while(temp)
    {

    if(temp->binaryPattern == value) return temp->correspondingVal;
    temp = temp->next;
    
    }

    return -1;

}

int hashCode(Rules *r, int value)
{
    return value%r->size;
}


/**
Generates the rule values and returns them.
Each number of 111  	110 	101 	100 	011 	010 	001 	000 
is paired with each integer form the converted binary number of the rule.


*/

Rules* generateRuleValues(int rule)
{
    Rules *r = (Rules*)malloc(sizeof(Rules));
    if (r==NULL) return NULL;

    //Default size of the ruleset will always be 8.
    r->size = 8;
    r->ruleset = (Pattern**)malloc(sizeof(Pattern*)*8);

    //Retains the binary expression of the rule
    long long binaryRuleNumber = convertToBinary(rule);

    //Converts the rule numbers into an array of digits for easier comparison
    int rulePattern[8];

    for (int i=8; i>=0; i--)
    {
        rulePattern[i] = binaryRuleNumber % 10;
        binaryRuleNumber = binaryRuleNumber/ 10;
    }

    int defaultPatterns[] = {111, 110, 101, 100, 011, 010, 001, 000};

    for(int i=0; i< r->size ;i++)
    {
        r->ruleset[i]->binaryPattern = defaultPatterns[i];
        r->ruleset[i]->correspondingVal = rulePattern[i];
    }


    return r;
}





/**
Saves the current generation of cells to a file.
@param *array - pointer to the generation to be saved
@param generationSize - a size of an array
@param fileName[] - a file where the output is saved to
*/
int saveGenerationToFile (Cell *array, int generationSize, char fileName[] )
{
    if(array == NULL)
        return INVALID_INPUT_PARAMETER;
    
    if(fileName == NULL || strlen(fileName) > 50 || strlen(filename) == 0)
        return INVALID_INPUT_PARAMETER;
        
    FILE *f;
    f = fopen(fileName, "a");
    if(f == NULL)
        return FILE_ERROR;
    
    for(int i =0, i<generationSize; i++)
    {
        fprintf(f,"%d ", array[i].state); 
    }
    fprintf(f,"\n");
    fclose(f);
    return SUCCESS;
}

/**
Loads all generations that forms a pattern from a file and displays it for a user
@param fileName - a name of file to read data from
*/
int readFromFile(char fileName[])
{
    if(fileName == NULL || strlen(fileName) > 50 || strlen(filename) == 0)
        return INVALID_INPUT_PARAMETER;

    FILE *f;
    f = fopen(fileName, "r")
    if(f==NULL)
        return FILE_ERROR; // failed to open a specified file-> probably file with such name does not exit
    
    //e.g 256; it should be a max size of a generation that a user can choose
    char t[256];  
    while(fgets(t, 256,f) != NULL)
    {
        printf("%s",t);
    }

    fclose(f);
    return SUCCESS;
}

