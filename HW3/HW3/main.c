
//#include "sudoku.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>


#define NUMTHREADS 27
#define MAXNUM 81
#define MAXROW 9
#define MAXCOLUMN 9

typedef struct
{
    int row;
    int column;
    int threadNumber;
} parameters;

void *validateRow(void *sudokuTable);
void *validateColumn(void *sudokuTable);
void *validateGrid(void *sudokuTable);

int main(void)
{
    //File readin operations
    FILE *file;
    int sudokuPuzzle[9][9];
    int i,j,count = 0;
    
    int value[MAXNUM];
    
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
            fscanf(file, " %d", &value[count]);
            sudokuPuzzle[i][j] = value[count];
            //printf("element %d is %d\n",count,  sudokuPuzzle[i][j]);
            count++;
            
        }
    }

    pthread_t thread[NUMTHREADS];
    
    for(int i =0; i < MAXROW; i++)
    {
        for(int j =0; j < MAXCOLUMN; j++)
        {
            pthread_create(thread, NULL, validateRow, sudokuPuzzle);
        }
    }
    
}

