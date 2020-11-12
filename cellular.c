#include <stdlib.h>
#include <string.h> 
#include <stdio.h>
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
Cell **initializeArray()
{
    Cell **p = (Cell**)malloc(sizeof(Cell*)*8);

    for (int i=0; i<8; i++)
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
void displayGeneration(Cell *array)
{   
    for(int i=1; i<9; i++)
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

int hashCode(Rules *r, int value)
{
    return value%r->size;
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

        newState = findValue(rules, binaryPatternAsInt);
        if(newState == -1) return ERROR;
        array[i].state = newState;
        
    }

    return SUCCESS;

}



/**
Saves the current generation of cells to a file.
@param *array - pointer to the generation to be saved
@param *f - file to be written to
*/
void saveGenerationToFile (Cell *array)
{
    (void)array;
}

