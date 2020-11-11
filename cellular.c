#include <stdlib.h>
#include <string.h> 
#include "cellular.h"

/** ## FUNCTION IMPLEMENTATIONS ## */


/**
Allocates the space for the cell and initializes its values.
*/
Cell *intializeCell ()
{
    Cell* cell = (Cell*)malloc(sizeof(Cell));
    if (cell == NULL) return NULL;

    cell->state = 0;
    cell->prevState = -1;
    cell->neighbours = -1;

    return cell;
}

/**
Method which performs the cellular automation.
*/
void cellularAutomation (Cell *array)
{

}

/**
Prints the generation to the screen/terminal.
@param *array - pointer to the array of the generation to print
*/
void displayGeneration(Cell *array, int length)
{   
    for(int i=0; i<length); i++)
    {
        printf(" %d ", array->state);
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

    //Converts the rule into binary
    char binaryRule[] = sprintf(str, "%lld",converToBinary(rule));

    for(int i=0; i<strlen(binaryRule); i++)
    {
        array[i]->state = binaryRule[i];
    }


    return SUCCESS;

}

/**
Calculates the next generation of cells by examining the neighbours.

@param *array - pointer to the array of the generation
@param rule - rule to calculate by
*/
int calculateNextGeneration (Cell *array, int rule)
{
    if (array == NULL) return INVALID_INPUT_PARAMETER;
    if (rule < 1 || rule > 256) return INVALID_INPUT_PARAMETER;


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
    r->ruleset = (Pattern**)malloc(sizeof(Pattern*)*size);

    //Retains the binary expression of the rule
    longlong binaryRuleNumber = converToBinary(rule);

    //Converts the rule numbers into an array of digits for easier comparison
    int rulePattern[8];

    for (int i=8; i>=0; i--)
    {
        rulePattern[i] = binaryRuleNumber % 10;
        binaryRuleNumber = binaryRuleNumber/ 10;
    }

    int defaultPatterns[] = {111, 110, 101, 100, 011, 010, 001, 000};

    for(i=0;i<size;i++)
    {
        r->ruleset[i]->binaryPattern = defaultPatterns[i];
        r->ruleset[i]->correspondingValue = rulePattern[i];
    }


    return r;
}


/**
Converts a decimal number into binary and returnts it.
param @int - number to be converted
@return - binary number
*/
long long convertToBinary(int number)
{
    return 0;
}

/**
Converts a binary number into decimal and returnts it.
param @long long - number to be converted
@return - decimal number
*/
int convertToDecimal(long long number)
{
    return 0;
}

/**
Saves the current generation of cells to a file.
@param *array - pointer to the generation to be saved
@param *f - file to be written to
*/
void saveGenerationToFile (Cell *array, File *f)
{

}

