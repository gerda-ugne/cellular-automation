#include <stdlib.h>
#include <string.h> 
#include <stdio.h>
#include <unistd.h>
#include "cellular.h"

/* ## FUNCTION IMPLEMENTATIONS ## */


/*
Allocates the space for the cell and initializes its values.
@return pointer to the allocated Cell 
*/
Cell *initializeCell()
{
    Cell* cell = (Cell*)malloc(sizeof(Cell));
    if (cell == NULL) return NULL;

    cell->state = 0;
    cell->prevState = 0;
    cell->neighbours = 0;

    return cell;
}


/*
Initializes the array of cells
@return double pointer to the allocated array
*/
Cell **initializeArray(int generationSize)
{
    Cell **p = (Cell**)malloc(sizeof(Cell*)*generationSize);
    if(p == NULL) return NULL;

    for (int i=0; i<generationSize; i++)
    {
        p[i] = initializeCell();
    }

    return p;
}

/*
Initializes a 2D array of cells
#return double pointer to the allocated 2D array
*/
Cell ***intialize2DArray(int columns, int rows)
{
    Cell ***p = (Cell***)malloc(sizeof(Cell**)*rows);
    if(p == NULL) return NULL;

    for (int i=0; i<rows; i++)
    { 
        p[i] = (Cell**)malloc(columns * sizeof(Cell*)); 
        for(int j=0; j<columns; j++)
        {
            p[i][j] = initializeCell();
        }
    }

    return p;
}

/*
Frees the allocated memory for the 1D array
@param c - double pointer to the array
@param length - size of the array

@return SUCCESS if no errors present
*/
int freeArray(Cell **c, int length)
{
    for (int i=0; i<length; i++)
    {
        free(c[i]);
    }

    free(c);
    return SUCCESS;

}

/*
Frees the allocated memory for the 2D array
@param c - triple pointer to the array
@param columns - size parameter for the array
@param rows - size parameter for the array

@return SUCCESS if no errors present
*/
int free2DArray (Cell*** c, int columns, int rows)
{
    for (int i=0; i<rows; i++)
    { 
        for(int j=0; j<columns; j++)
        {
            free(c[i][j]);
        }

        free(c[i]); 
    }

    free(c);
    return SUCCESS;

}


/*
Converts a decimal number into binary and returnts it.
param @int - number to be converted
@return - binary number
*/
long long convertToBinary(int dec)
{
    long long bin=0;
    long long remainder;
    long long f =1;

    while(dec !=0)
    {
        remainder = dec%2;
        bin = bin + remainder * f;
        f = f *10;
        dec = dec/2;

    }

    return bin;
}

/*
Converts a binary number into decimal and returnts it.
param @long long - number to be converted
@return - decimal number
*/
int convertToDecimal(long long number)
{
    long long dec = 0, i = 1, remainder = 0;
    
    while (number!=0)
    {
        remainder = number%10;
        dec = dec+remainder*i;
        i=i*2;
        number=number/10;

    }

    return dec;
}


/*
Prints the generation to the screen/terminal.
@param *array - pointer to the array of the generation to print
*/
void displayGeneration(Cell **array, int generationSize)
{ 
    for(int i=0; i<generationSize; i++)
    {
        if(array[i]->state == 0) printf(" . ");
        else if(array[i]->state == 1) printf( " # ");
    }

    printf("\n");

}

/*
Fills the first generation with 0's and 1's
bsaed on the provided rule.

@param *array - pointer to the array of the generation
@param rule - rule to use for the filling of the generation

@return SUCCESS or an error code depending on outcome.

*/
int fillFirstGeneration (Cell **array, int pattern, int length)
{
    if(array == NULL) return INVALID_INPUT_PARAMETER;
    if(pattern < 0 || pattern > 255) return INVALID_INPUT_PARAMETER;
    if(length < 8 || length > 55) return INVALID_INPUT_PARAMETER;

    //If the pattern is chosen as 0, we are using the default Wolfram model: all cells states are 0, except for the middle one.
    if(pattern == 0)
    {
        for(int i=0; i<length; i++)
        {
            array[i]->prevState = 0;
            array[i]->state = 0;
        }

        int midpoint = length/2;
        array[midpoint]->state=1;
        array[midpoint]->prevState=1;

        return SUCCESS;
    }

    //Else we fill the array with a repeated binary expression of the provided number.

    //Retains the binary expression of the rule
    long long binaryConversion = convertToBinary(pattern);

    //Converts the rule numbers into an array of digits for easier comparison
    int binaryPattern[8];

    for (int i=7; i>=0; i--)
    {
        binaryPattern[i] = binaryConversion % 10;
        binaryConversion = binaryConversion/10;
    }
    
    //Cells are filled with matching numbers.
    for(int i=0, j=i; i<length; i++, j++)
    {
        if(j>8) j=j-8;

        array[i]->state = binaryPattern[j];
        array[i]->prevState = binaryPattern[j];
    
    }
    return SUCCESS;

}


/*
Returns key value for the matched rule pattern.
@param Rules *r - pointer to a hashtable of chosen rules
@param char[] value - value to be looked up

@return 0 or 1 depending on the pairing of the rule
Logic adapted from github.com/BaseMax/HashMapC Hash*GetValue method.

*/
int findValue(Rules *r, char value[])
{

    for(size_t index=0; index < r->size; index++) {
		Pattern *item=r->map[index];
		if(item != NULL && strcmp(item->binaryPattern,value)==0) {
			return item->correspondingVal;
		}
	}

    return -1;

}

/*
Allocates memory for a new rule hashmap.
@return pointer to allocated memory for new rules

*/
Rules *initializeRuleTable()
{
    Rules *r = (Rules*)malloc(sizeof(Rules));
    
    //The default size of the rule table will always be 8
    r->size = 8;

    r->map = (Pattern**)malloc(sizeof(Pattern*)*r->size);
    for(int i=0;i<r->size;i++)
    {
        r->map[i] = (Pattern*)malloc(sizeof(Pattern));
    }
    return r;
}

/*
Frees the allocated memory for the rule map
@param r - double pointer to the rules

@return SUCCESS if no errors present
*/
int freeRules(Rules *r)
{
    for(int i=0;i<8;i++)
    {
        free(r->map[i]);
    }

    free(r->map);
    free(r);
    
    return SUCCESS;
}


/*
Generates the rule values and returns them.
Each pattern of 111  	110 	101 	100 	011 	010 	001 	000 
is paired with each integer form the converted binary number of the rule.

@param rule - rule of which values to generate
@return rules - generated rule values
*/

Rules *generateRuleValues(int rule)
{

    Rules *r = initializeRuleTable(rule);

    //Retains the binary expression of the rule
    long long binaryRuleNumber = convertToBinary(rule);

    //Converts the rule numbers into an array of digits for easier comparison
    int rulePattern[9];
    for (int i=8; i>=1; i--)
    {
        rulePattern[i] = binaryRuleNumber % 10;
        binaryRuleNumber = binaryRuleNumber/ 10;

    }

    const char defaultPatterns[8][4] = {"111", "110", "101", "100", "011", "010", "001", "000"};
    for(int i=0,j=1; i< r->size; i++, j++)
    {
        strcpy(r->map[i]->binaryPattern, defaultPatterns[i]);
        r->map[i]->correspondingVal = rulePattern[j];

    }

    return r;
}


/*
Calculates the next generation of cells by examining the neighbours.

@param *array - pointer to the array of the generation
@param rule - rule to calculate by
@param length - length of the generation

@return SUCCESS if successful/error code otherwise
*/
int calculateNextGeneration (Cell **array, Rules *rules, int length)
{
    if (array == NULL) return INVALID_INPUT_PARAMETER;
    if(length < 8 || length > 55) return INVALID_INPUT_PARAMETER;

    char newState, number1,number2,number3;

    for (int i=0; i<length; i++)
    {
        if(i==0)
        {
            number1 = array[length-1]->prevState + '0';
            number2 = array[i]->prevState + '0';
            number3 = array[1]->prevState+ '0';
        }
        else if(i==length-1)
        {
            number1 = array[i-1]->prevState + '0';
            number2 = array[i]->prevState + '0';
            number3 = array[0]->prevState+ '0';
        }
        else
        {
            number1 = array[i-1]->prevState + '0';
            number2 = array[i]->prevState + '0';
            number3 = array[i+1]->prevState+ '0';
        }
        char binaryPattern [] = {number1,number2,number3};

        newState = findValue(rules, binaryPattern);
        if(newState == -1) return ERROR;
        array[i]->state = newState;
        
    }
    
    for(int i=0; i<length; i++)
    {
        array[i]->prevState = array[i]->state;
    }

    return SUCCESS;

}


/*
Saves the current generation of cells to a file.
@param *array - a pointer to the generation to be saved
@param generationSize - a size of an array
@param fileName[] - a file where the output is saved to
@param count - a number to indicate whether the headline of Cellular Automaton should be printed
@param gen - a number to display that  Wolfram's model was used
@param rule - a number of a rule applied

@return SUCCESS if successful/error code otherwise
*/
int saveGenerationToFile (Cell **array, int generationSize, char fileName[], int count,int gen, int rule)
{
    if(array == NULL) return INVALID_INPUT_PARAMETER;
    if(generationSize < 8 || generationSize > 55) return INVALID_INPUT_PARAMETER;
    if(fileName == NULL || strlen(fileName) > 50 || strlen(fileName) == 0) return INVALID_INPUT_PARAMETER;
    if(count < 0 || count > 1) return INVALID_INPUT_PARAMETER;
    if(rule < 0 || rule >  255)  return INVALID_INPUT_PARAMETER;
    if(rule < 0 || rule >  255)  return INVALID_INPUT_PARAMETER;

    FILE *f;
    f = fopen(fileName, "a");
    if(f == NULL)
        return FILE_ERROR;
    
    if(count == 1)
    {
        if(gen==0)
            fprintf(f, "\nCellular Automaton. Wolfram's model RULE %d\n", rule);
        else
            fprintf(f, "\nCellular Automaton RULE %d\n", rule);
    }
    
    for(int i =0; i<generationSize; i++)
    {
        if(array[i]->state == 0) fprintf(f," . ");
        else if(array[i]->state == 1) fprintf(f, " # ");
        //fprintf(f,"%d ", array[i]->state); 
    }
    fprintf(f,"\n");
    if(fclose(f) != 0)
		return FILE_ERROR;
    return SUCCESS;
}

/**
Loads all generations that forms a pattern from a file and displays it for a user
@param fileName - a name of file to read data from

@return SUCCESS if successful/error code otherwise
*/
int readFromFile(char fileName[])
{
    if(fileName == NULL || strlen(fileName) > 50 || strlen(fileName) == 0)
        return INVALID_INPUT_PARAMETER;

    FILE *f;
    f = fopen(fileName, "r");

    if(f==NULL)
        return FILE_ERROR; // failed to open a specified file-> probably file with such name does not exit
    
    //e.g 256; it should be a max size of a generation that a user can choose
    char t[256];  
    while(fgets(t, 256,f) != NULL)
    {
        printf("%s",t);
    }

    if(fclose(f) != 0)
		return FILE_ERROR;
    return SUCCESS;
}

/*
Main method to simulate Conway's Game of Life.
@param cells - triple pointer to the 2D array of cells
@param columns - size parameter for the 2D array
@param rows - size parameter for the 2D array
@param loops - amount of loops to generate the array for

*/
void gameOfLife(Cell*** cells, int columns, int rows, int loops)
{
    //Fill the grid with random 0's and 1's
    for (int i=1; i<columns-1; i++)
    {
        for(int j=1; j<rows-1; j++)
        {
            //Set each cell's previous and current state
            cells[i][j]->state = rand()%2;
            cells[i][j]->prevState = cells[i][j]->state;
        }
    }

    //Generate game of life for x loops
    for(int i=0; i<loops; i++)
    {
        //For every cell in the game
        for(int i=1; i<columns-1; i++)
        {
            for(int j=1; j<rows-1; j++)
            {
                calculateNeighboursForGame(cells,i,j);
                cells[i][j]->state = gameOfLifeRules(cells, i, j);
            }
        }
       system("clear");
       displayGameOfLife(cells, columns, rows);
       sleep(1);

       // Resets neighbours and sets prev state to match the current state
       resetParameters(cells, columns, rows);
    
    }
    
}

/*
Reset parameters of the 2D array for the next iteration of the loop.
@param p - triple pointer to the 2D array
@param columns - size parameter for the 2D array
@param rows - size parameter for the 2D array
*/
void resetParameters(Cell ***p, int columns, int rows)
{
           
    //For every cell in the game
    for(int i=1; i<columns-1; i++)
    {
            for(int j=1; j<rows-1; j++)
            {
              p[i][j]->neighbours = 0;
            }

    }

    //Set previous state to match the current state
        for (int i=1; i<columns-1; i++)
         {
            for(int j=1; j<rows-1; j++)
            {
                p[i][j]->prevState = p[i][j]->state;
            }
         }

  
}

/*
Calculates the neighbour cells for the 2D array.
@param p - triple pointer to the 2D array
@param x - x position of the cell element to count neighbours for
@param y - y position of the cell element to count neighbours for
*/
void calculateNeighboursForGame(Cell*** p, int x, int y)
{
    for(int i=-1; i<=1; i++)
    {
        for(int j=-1; j<=1; j++)
        {
            p[x][y]->neighbours= p[x][y]-> neighbours + p[x+i][y+j]->prevState;
        }
    }

    if(p[x][y]->prevState == 1) p[x][y]->neighbours = p[x][y]->neighbours - 1;

}

/*
Uses the game of life rules to calculate the outcome of the cell state.
@param p - triple pointer to the 2D array
@param x - x position of the cell element to count new state for
@param y - y position of the cell element to count new state for

@return int - new state of the cell
*/
int gameOfLifeRules(Cell ***p, int x, int y)
{

    if((p[x][y]->prevState ==  1) && (p[x][y]->neighbours < 2)) {return 0;}
    else if (((p[x][y]->prevState == 1) && (p[x][y]->neighbours >  3))) { return 0;}
    else if ((p[x][y]->prevState == 0) && (p[x][y]->neighbours == 3))  {return 1;}
    else {return p[x][y]->prevState;}

}

/*
Displays the game of life generation to the terminal.
@param p - triple pointer to the 2D array
@param columns - size parameter for the 2D array
@param rows - size parameter for the 2D array

*/
void displayGameOfLife(Cell ***cells, int columns, int rows)
{

    for (int i=1; i<columns-1; i++)
    {
        for(int j=1; j<rows-1; j++)
        {
            if(cells[i][j]->state == 0) printf(" . ");
            else if(cells[i][j]->state == 1) printf( " # ");
        }

        printf("\n");
    }
    
}
