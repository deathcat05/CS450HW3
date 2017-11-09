
//#include "sudoku.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <pthread.h>


#define NUMTHREADS 27
#define MAXNUM 81
#define MAXROW 9
#define MAXCOLUMN 9

typedef struct Paramaters
{
  // constructor to pass the sudoku table in
  Parameters(*sudokuTable) {}
  
  int row;
  int column;
  int threadNumber;

};


void *validateRow(void *sudokuTable);
void *validateColumn(void *sudokuTable);
void *validateGrid(void *sudokuTable);


void *validateRow(void *sudokuTable) {
  // size for future decrementing if necessary
  int size = 9;

  // initilize to 0 so we can flip to 1 later 
  int checker[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
  // loop through row
  for( int i = 0; i < 9; i++ ) {
    int sudoku_num = sudokuTable[row][i];
    // Check to see if the sudoku number 
    // has been found yet.
    if(checker[sudoku_num] == 1)
      printf("The value %d has already appeared in the array.", sudoku_num);
    // Sudoku number has not been found so 
    // set index at sudoku_num in checker to 1.
    else
      checker[sudoku_num] == 1;
  }
}


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
