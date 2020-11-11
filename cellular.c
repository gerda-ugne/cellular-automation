#include <stdlib.h>
#include <string.h> 
#include "cellular.h"

/** ## FUNCTION IMPLEMENTATIONS ## */


/**
Allocates the space for Cell
*/
Cell *createCell ()
{
    return null;
}

/**
Initializes the default cell values.
*/
Cell *intializeCell()
{
    return null;
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
void displayGeneration(Cell *array)
{

}

/**
Fills the first generation with 0's and 1's
bsaed on the provided rule.

@param *array - pointer to the array of the generation
@param rule - rule to use for the filling of the generation

*/
void fillGeneration (Cell *array, int rule)
{

}

/**
Calculates the next generation of cells by examining the neighbours.

@param *array - pointer to the array of the generation
@param rule - rule to calculate by
*/
void calculateNextGeneration (Cell *array, int rule)
{

}

/**
Allows user to choose a rule for the 
cellular automation (1-255).

return int - returns the chosen rule

*/
int selectGenerationRule ()
{
    return 0;
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

