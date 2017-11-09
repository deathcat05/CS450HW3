
//#include "sudoku.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>


#define NUMTHREADS 27
#define MAXNUM 81
#define MAXROW 9
#define MAXCOLUMN 9
//The struct for the threads you
typedef struct
{
   // pthread_t threadID;
    int row;
    int column;
    int threadNumber;
    int sudokuPuzzle[9][9];
    
} parameters;

void validateRow(int **sudokuTable);
void validateColumn(int **sudokuTable);
void  *validateGrid(void *sudokuTable);

int main(void)
{
    //parameters *puzzle = (parameters*) malloc(sizeof(parameters));

    //File readin operations
    FILE *file;
    int puzzle[9][9];
    int i,j,count = 0;
    
    file = fopen("sudoku.txt", "r");
    
    if (file == NULL)
    {
        printf("Error: file pointer is null.");
        exit(1);
    }
    
    for( i = 0; i < MAXROW; i++ )
    {
        for( j = 0; j < MAXCOLUMN; j++ )
        {
            fscanf(file, " %d", &puzzle[i][j]);
            //printf("%d\n", puzzle[i][j]); //This is just for test purposes DELETE BEFORE SUBMITTING!
            count++;
            
        }
    }
    
//Establishing the thread(s) for interaction 
    
    pthread_t thread[NUMTHREADS];
    int threadNum = 0;
    
    for(int i = 0; i < MAXROW; i++)
    {
        for(int j =0; j < MAXCOLUMN; j++)
        {
            printf("%d", puzzle[i][j]);
            if((i%3 == 0) && (j%3 == 0)) //Establishing 3x3 grid
            {
                parameters *gridData = (parameters*) malloc(sizeof(parameters));
                gridData->row = i; //Assigning the i value to row of the struct
                gridData->column = j; //Assigning the j value to the column of the struct
                gridData->sudokuPuzzle[i][j] = puzzle[i][j];
                //pthread_t thread = gridData->threadID;
                gridData->threadNumber = threadNum;
                pthread_create(&thread[threadNum++], NULL, validateGrid, gridData); //Creating the subsections threads
            }
        }
    }
    
}

void *validateGrid(void *sudokuPuzzle)
{
    parameters *grid = (parameters*) sudokuPuzzle;
    int row = grid->row;
    int col = grid->column;
    int arrayToCheck[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0}; //The array used to check
   // int num = puzzle[row][col];
    
    for(int i = row; i < i+3; i++)
    {
        for(int j = col; j < j+3; j++)
        {
            int num = grid->sudokuPuzzle[i][j];
            if(arrayToCheck[num-1] == 1)
            {
                printf("Error in grid");
            }
            else
            {
               arrayToCheck[num-1] = 1;
                printf("grids are valid");
                
            }
        }
    }
    return 0;
}
