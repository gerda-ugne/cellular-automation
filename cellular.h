#ifndef __CELL_HEADER__
#define __CELL_HEADER__ 


/** ERROR CODES */

/** The error codes will be returned in case there are distruptions in the code. */

#define SUCCESS                  100   // Value to be returned if a function is completed successfully
#define INVALID_INPUT_PARAMETER  101   // Value to be returned if one of the input parameters 
                                       // into the function is invalid
#define MEMORY_ALLOCATION_ERROR  102   // Value to be returned if a memory allocation error occurs during the function
#define INVALID_OPERATION  103         // Value to be returned if your function detects an operation that is being
                                       // attempted on data structure that isn't valid.

#define ERROR 104                      // General error that does not fit in with the rest of criteria.
#define FILE_ERROR 105                 // Unable to open a file
/**
Structure of the Cell

state - current state of the cell, 1 - alive, 0 - dead
prevState - stores the previous state of the cell
neighbours - count of the alive neighbours of the cell

*/
typedef struct cell{
    int state;
    int prevState;
    int neighbours;
} Cell;

/**
Information to hold the information of each pattern:
111 	110 	101 	100 	011 	010 	001 	000 
to match the required roles

*/
typedef struct pattern{
    int binaryPattern;
    int correspondingVal;
    struct pattern *next;
} Pattern;

/**
Hashtable to contain all the patterns, which defines a set of rules
*/
typedef struct rules{
    int size;
    Pattern **ruleset;
} Rules;


/** Allocates the memory and initializes the default values of the cell */
Cell *initializeCell();

Cell **intializeArray();

/** Converts a decimal number to binary*/
long long convertToBinary(int number);

/** Converts a binary number to decimal*/
int convertToDecimal(long long number);

/** Completes 1D cellular automation*/
void cellularAutomation (Cell *array);

/** Displays the current generation to screen*/
void displayGeneration(Cell *array);

/** Fills the first generation according to the rule*/
int fillGeneration (Cell *array, int rule);

/** Returns hashcode for the key parameter*/
int hashCode(Rules *r, int value);

/** Returns values for the key parameter*/
int findValue(Rules *r, int value);

/**Generates the corresponding values for the rule*/
Rules* generateRuleValues(int rule);

/** Calculates the next generation based on neighbours*/
int calculateNextGeneration (Cell *array, Rules* rules);

/** Saves the current generation to a file*/
void saveGenerationToFile (Cell *array);



#endif
