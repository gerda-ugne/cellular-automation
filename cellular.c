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
Cell **initializeArray(int generationSize)
{
    Cell **p = (Cell**)malloc(sizeof(Cell*)*generationSize);

    for (int i=0; i<generationSize; i++)
    {
        p[i] = initializeCell();
    }

    return p;
}


/**
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

/**
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

/**
Method which performs the cellular automation.
*/
void cellularAutomation (Cell **array)
{
    (void)array;
}

/**
Prints the generation to the screen/terminal.
@param *array - pointer to the array of the generation to print
*/
void displayGeneration(Cell **array, int generationSize)
{   
    for(int i=1; i<generationSize-1; i++)
    {
        if(array[i]->state == 0) printf(" . ");
        else if(array[i]->state == 1) printf( " # ");
        //printf(" %d ", array[i]->state);
    }

    printf("\n");

}

/**
Fills the first generation with 0's and 1's
bsaed on the provided rule.

@param *array - pointer to the array of the generation
@param rule - rule to use for the filling of the generation

*/
int fillFirstGeneration (Cell **array, int rule, int length)
{
    if(array == NULL) return INVALID_INPUT_PARAMETER;
    if(rule < 0 || rule > 256) return INVALID_INPUT_PARAMETER;

    //If rule is chosen as 0, we are using the default Wolfram model: all cells states are 0, except for the middle one.
    if(rule == 0)
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

    //Else we fill the array with provided digits.

    //Retains the binary expression of the rule
    long long binaryRuleNumber = convertToBinary(rule);

    //Converts the rule numbers into an array of digits for easier comparison
    int rulePattern[8];

    for (int i=8; i>=1; i--)
    {
        rulePattern[i] = binaryRuleNumber % 10;
        binaryRuleNumber = binaryRuleNumber/ 10;
    }


    
    //Cells are filled with matching numbers.
    for(int i=1, j=i; i<length-1; i++, j++)
    {
        if(j>8) j=j-8;

        array[i]->state = rulePattern[j];
        array[i]->prevState = rulePattern[j];
    
    }

    //First and last cell are set to 0, as they are edges and won't be manipulated.
    array[0]->state = 0;
    array[0]->prevState = 0;

    //array[length]->state = 0;
    //array[length]->prevState = 0;

    return SUCCESS;

}


/**
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

/**
Allocates memory for a new rule hashtable.
@return pointer to allocated memory for new rules

*/
Rules *initializeRuleTable(int rule)
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


/**
Generates the rule values and returns them.
Each number of 111  	110 	101 	100 	011 	010 	001 	000 
is paired with each integer form the converted binary number of the rule.

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


/**
Calculates the next generation of cells by examining the neighbours.

@param *array - pointer to the array of the generation
@param rule - rule to calculate by
@param length - length of the generation
*/
int calculateNextGeneration (Cell **array, Rules *rules, int length)
{
    if (array == NULL) return INVALID_INPUT_PARAMETER;

    char newState;

    for (int i=1; i<length-1; i++)
    {
        char number1 = array[i-1]->prevState + '0';
        char number2 = array[i]->prevState + '0';
        char number3 = array[i+1]->prevState+ '0';

        char binaryPattern [] = {number1,number2,number3};

        newState = findValue(rules, binaryPattern);
        if(newState == -1) return ERROR;
        array[i]->state = newState;
        
    }

    for(int i=1; i<length-1; i++)
    {
        array[i]->prevState = array[i]->state;
    }

    return SUCCESS;

}



/**
Saves the current generation of cells to a file.
@param *array - pointer to the generation to be saved
@param generationSize - a size of an array
@param fileName[] - a file where the output is saved to
*/
int saveGenerationToFile (Cell **array, int generationSize, char fileName[] )
{
    if(array == NULL)
        return INVALID_INPUT_PARAMETER;
    
    if(fileName == NULL || strlen(fileName) > 50 || strlen(fileName) == 0)
        return INVALID_INPUT_PARAMETER;
        
    FILE *f;
    f = fopen(fileName, "a");
    if(f == NULL)
        return FILE_ERROR;
    
    for(int i =0; i<generationSize; i++)
    {
        fprintf(f,"%d ", array[i]->state); 
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

    fclose(f);
    return SUCCESS;
}

