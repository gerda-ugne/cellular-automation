#ifndef __CELL_HEADER__
#define __CELL_HEADER__ 


/* ERROR CODES */

/* The error codes will be returned in case there are distruptions in the code. */

#define SUCCESS                  100   // Value to be returned if a function is completed successfully
#define INVALID_INPUT_PARAMETER  101   // Value to be returned if one of the input parameters 
                                       // into the function is invalid
#define MEMORY_ALLOCATION_ERROR  102   // Value to be returned if a memory allocation error occurs during the function
#define INVALID_OPERATION  103         // Value to be returned if your function detects an operation that is being
                                       // attempted on data structure that isn't valid.

#define ERROR 104                      // General error that does not fit in with the rest of criteria.
#define FILE_ERROR 105                 // An error to do with file handling (opening, writing to, reading, etc.)
/*
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

/*
Information to hold the information of each pattern:
111 	110 	101 	100 	011 	010 	001 	000 
to match the required roles

*/
typedef struct node{
    char binaryPattern[4];
    int correspondingVal;
    struct node *next;
} Pattern;

/*
Hashtable to contain all the patterns, which defines a set of rules
*/
typedef struct rules{
    int size;
    Pattern **map;
} Rules;


/* Allocates the memory and initializes the default values of the cell */
Cell *initializeCell();

/* Initializes an array of cells with provided generation size*/
Cell **initializeArray(int generationSize);

/*Frees the allocated memory for the 1D array*/
int freeArray(Cell **c, int length);

/*Frees the allocated memory for the 2D array*/
int free2DArray (Cell*** c, int columns, int rows);

/* Converts  a decimal number to binary*/
long long convertToBinary(int number);

/* Converts a binary number to decimal*/
int convertToDecimal(long long number);

/* Displays the current generation to screen*/
void displayGeneration(Cell **array, int generationSize);

/* Fills the first generation according to the rule*/
int fillFirstGeneration (Cell **array, int rule, int length);

/* Returns values for the key parameter*/
int findValue(Rules *r, char value[]);

/* Allocates memory for a new rule table*/
Rules *initializeRuleTable();

/*Frees the allocated memory for the rule map*/
int freeRules(Rules* r);

/* Generates the corresponding values for the rule*/
Rules* generateRuleValues(int rule);

/**Calculates the next generation based on neighbours*/
int calculateNextGeneration (Cell **array, Rules* rules, int length);

/* Saves the current generation to a file*/
int saveGenerationToFile (Cell **array, int generationSize, char fileName[], int count,int gen, int rule);

/* Reads input from a file and displas the generation to the screen*/
int readFromFile(char fileName[]);

/* FUNCTIONS FOR GAME OF LIFE */

/* Initializes a 2D array with provided size. [GAME OF LIFE]*/
Cell ***intialize2DArray(int columns, int rows);

/*Main method to simulate Conway's Game of Life.*/
void gameOfLife(Cell*** cell, int columns, int rows, int loops);

/*Reset parameters of the 2D array for the next iteration of the loop. [GAME OF LIFE}*/
void resetParameters(Cell ***p, int columns, int rows);

/*Calculates the neighbour cells for the 2D array. [GAME OF LIFE]*/
void calculateNeighboursForGame(Cell*** p, int columns, int rows);

/*Uses the game of life rules to calculate the outcome of the cell state. [GAME OF LIFE]*/
int gameOfLifeRules(Cell ***p, int x, int y); 

/*Displays the game of life generation to the terminal. [GAME OF LIFE]*/
void displayGameOfLife(Cell ***cells, int columns, int rows);

#endif
