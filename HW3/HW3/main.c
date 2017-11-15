/*
 * This is a multiethreaded suduko validator program created using pthreads.
 */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#define NUMTHREADS 27 //number of threads in the program


/* structure for passing data to threads*/
typedef struct
{
    int row;
    int column;
    int (*puzzle)[9];
    int valid[NUMTHREADS];
    int invalidCase;
} parameters;


void* validateRow(void* sudokuData);
void* validateColumn(void* sudokuData);
void* validateGrid(void* sudokuData);

// method to validate that each column has numbers 1-9
int main()
{
    int puzzle[9][9];
    int threadNum = 0;
    pthread_t* thread;
    thread = malloc(NUMTHREADS*sizeof(pthread_t));
    parameters *data = (parameters*) malloc(sizeof(parameters));
    
    FILE *file = fopen("sudoku.txt", "r");
    
    if (file == NULL)
    {
        printf("Error: file pointer is null.");
        exit(1);
    }
    
    for( int i = 0; i < 9; i++ )
    {
        for( int j = 0; j < 9; j++ )
        {
            fscanf(file, " %d", &puzzle[i][j]);
        }
    }
    fclose(file);
    
    
    //print suduko after reading DELETE BEFORE SUBMISSION
    printf("The given solution is:\n");
    for(int i=0; i<9; i++){
        for(int j=0; j<9; j++){
            printf("%d ", puzzle[i][j]);
        }
        printf("\n");
    }
    
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            //threads to check 3X3 squares
            if (i%3 == 0 && j%3 == 0)
            {
                parameters *gridData = (parameters*) malloc(sizeof(parameters));
                gridData->row = i;
                gridData->column = j;
                gridData->puzzle = &puzzle[9];
                gridData->invalidCase =0;
                pthread_create(&thread[threadNum++], NULL, validateGrid, gridData);
            }
            //threads to check coloumn
            if(i==0)
            {
                parameters *colData = (parameters *) malloc(sizeof(parameters));
                colData->row = i;
                colData->column = j;
                colData->puzzle = &puzzle[9];
                colData->invalidCase =0;
                pthread_create(&thread[threadNum++], NULL, validateColumn, colData);
            }
            //threads to check row
            if(j==0)
            {
                parameters *rowData = (parameters *) malloc(sizeof(parameters));
                rowData->row = i;
                rowData->column = j;
                rowData->puzzle = &puzzle[9];
                rowData->invalidCase =0;
                pthread_create(&thread[threadNum++], NULL, validateRow, rowData);
            }
        }
    }
    
    //waiting for all threads to finish
    for (int threadNum = 0; threadNum < NUMTHREADS; threadNum++)
    {
        pthread_join(thread[threadNum], NULL);
        if(data->valid[threadNum] == 0 && data->invalidCase==1)
        {
            printf("Row %d doesn't have the required values.\n", data->row);
        }
        printf("THe solution is invalid\n");

    }
    
    printf("Valid Solution\n");
    return 0;
}

void *validateRow(void *sudokuData)
{
    parameters *rowData = (parameters*) sudokuData;
    int row = rowData->row;
    int checkRowArray[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    
    //check if row contains all number from 1-9, if not then set the Crow array to be 0
    //in order to check for all numbers. then set the valid array to 1 if row is valid.
    for(int i = 0; i < 9 ; i++)
    {
        int num = rowData->puzzle[row][i];
        if((num<1) || (num>9) || (checkRowArray[num - 1] == 1))
        {
            rowData->valid[row] = 0;
        }
        else
        {
            checkRowArray[num-1] = 1;
        }
    }
    //set the valid array starting from 10-18
    rowData->valid[9 + row] = 1;
    pthread_exit(NULL);
}

// method to validate that each square has numbers 1-9
void *validateGrid(void* sudokuData)
{
    parameters *grid = (parameters*) sudokuData;
    int row = grid->row;
    int column = grid->column;
    int checkArrayGrid[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
    
    //check if squares contain all number from 1-9, if not then set the csqua array to be 0
    //in order to check for all numbers. then set the valid array to 1 if row is valid.
    for (int i=row; i < row + 3; i++)
    {
        for (int j=column; j < column + 3; j++)
        {
            int num = grid->puzzle[i][j];
            if (num < 1 || num > 9 || checkArrayGrid[num - 1] == 1)
            {
                //grid->invalidCase = grid+1;
            }
            else
            {
                checkArrayGrid[num - 1] = 1;
            }
        }
    }
    //set the valid array starting from 1-9
    grid->valid[row+column/3] = 1;
    pthread_exit(NULL);
}


// method to validate that each column has numbers 1-9
void *validateColumn(void *sudokuData)
{
    parameters *columns = (parameters*) sudokuData;
    int column = columns->column;
    int checkColumnArray[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

    
    //check if column contains all number from 1-9, if not then set the Ccol array to be 0
    //in order to check for all numbers. then set the valid array to 1 if col is valid.
    for(int i=0; i < 9 ; i++)
    {
        int num = columns->puzzle[i][column];
        if((num < 1) || (num > 9) || (checkColumnArray[num - 1] == 1))
        {
            pthread_exit(NULL);
        }
        else
        {
            checkColumnArray[18+column] = 1;
        }
    }
    
    //set the valid array starting from 19-27
    
    columns->valid[18 + column] = 1;
    pthread_exit(NULL);
}


