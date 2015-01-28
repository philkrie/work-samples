//
//  maze.c
//  
//
//  Created by Phillip Kriegel on 1/23/15.
//
//

#include <stdio.h>
#include <stdlib.h>

void allocateMaze(const int size, unsigned char ***matrix){
    (*matrix) = (unsigned char **) calloc (size, size * sizeof(char *));
    for (int i = 0; i < size; i++) {
        (*matrix)[i] = (unsigned char *) calloc (size, size * sizeof(char) );
    }
    
}

void deallocateMaze(const int size, unsigned char **matrix){
    for (int i = 0; i < size; i++){
        free(matrix[i]);
    }
}

enum Direction { DOWN, RIGHT, UP, LEFT }; //might be useful

void moveUp(enum Direction *direction, int *currentRow){
    *direction = UP;
    printf("UP\n");
    *currentRow = *currentRow - 1;
}

void moveDown(enum Direction *direction, int *currentRow){
    *direction = DOWN;
    printf("DOWN\n");
    *currentRow = *currentRow + 1;
}

void moveLeft(enum Direction *direction, int *currentColumn){
    *direction = LEFT;
    printf("LEFT\n");
    *currentColumn = *currentColumn - 1;
}

void moveRight(enum Direction *direction, int *currentColumn){
    *direction = RIGHT;
    printf("RIGHT\n");
    *currentColumn = *currentColumn + 1;
}

int checkWin(enum Direction *direction, int *currentColumn, int *currentRow, int *mazeSize){
    if (*direction == UP){
        if (*currentRow - 1 < 0){
            return 1;
        }
    }
    
    if (*direction == DOWN){
        if (*currentRow + 1 == *mazeSize){
            return 1;
        }
    }
    
    if (*direction == LEFT){
        if (*currentColumn - 1 < 0){
            return 1;
        }
    }
    
    if (*direction == RIGHT){
        if (*currentColumn + 1 == *mazeSize){
            return 1;
        }
    }
    return 0;
}


//void mazeSolve( char[][MAX_MAZE_SIZE], const int, const int, int, int, int );

int main( int argc, const char* argv[] ){
    
    if( argc != 2 ) {
        //checks for the input file name
        printf( "error; no input file name\n" );
        return 1;
    }
    
    FILE *filePointer = fopen( argv[1], "r" );
    
    // You can choose to use static or dynamic memory for your maze data structure
    // An example static array declaration can be:
    //char maze[MAX_MAZE_SIZE][MAX_MAZE_SIZE] = { 0 };
    
    int numberOfTestCases = 0;
    fscanf( filePointer, "%d\n", &numberOfTestCases );
    
    for( int testCaseNumber = 0; testCaseNumber < numberOfTestCases; testCaseNumber++ ) {
        int mazeSize = 0;
        fscanf( filePointer, "%d\n", &mazeSize );
        
        unsigned char **matrix;
        allocateMaze((const int) mazeSize, &matrix);
        
        enum Direction direction = UP;
        int currentRow = 0;
        int currentColumn = 0;
        
        char space = ' ';
        
        for (int j = 0; j < mazeSize; j++) {
            for (int k = 0; k < mazeSize; k++){
                fscanf(filePointer, "%c", &matrix[j][k]);
            }
            fscanf(filePointer, "%c", &space); //Skip over the space
            
        }
        
        printf( "ENTER\n" );
        
        //We first have to find the x. It can be in either side of the maze; depending on where we find it, we have to change the direction
        
        for (int j = 0; j < mazeSize; j++) {
            for (int k = 0; k < mazeSize; k++){
                if(matrix[j][k] == 'x'){
                    currentRow = j;
                    currentColumn = k;
                    direction = UP;
                    break;
                }
            }
        }
        
        //We have found the x, now we decide the direction. Furthermore, we go ahead and take the first step. We naturally have to move straight into the maze.
        if (currentColumn == 0) {
            moveRight(&direction, &currentColumn);
        }
        
        if (currentColumn == mazeSize - 1) {
            moveLeft(&direction, &currentColumn);
        }
        
        if (currentRow == 0){
            moveDown(&direction, &currentRow);
        }
        
        if (currentRow == mazeSize - 1) {
            moveUp(&direction, &currentRow);
        }
        

        //We have gone ahead and entered the maze. We will now loop through a series of if then statements based off of the direction until we set the win condition off.
        
        int i = 1;
        while (i == 1) {
            //check win condition every single time
            
            int win = checkWin(&direction, &currentColumn, &currentRow, &mazeSize);
            if (win == 1){
                break;
            }
            
            if (direction == UP) {
                if (matrix[currentRow][currentColumn + 1] == '@' && matrix[currentRow - 1][currentColumn] == '.') {
                    moveUp(&direction, &currentRow);
                    continue;
                }
                else if (matrix[currentRow + 1][currentColumn + 1] == '@' && matrix[currentRow][currentColumn + 1] == '.') {
                    moveRight(&direction, &currentColumn);
                    continue;
                }
                else if (matrix[currentRow - 1][currentColumn] == '@' && matrix[currentRow][currentColumn - 1] == '.'){
                    moveLeft(&direction, &currentColumn);
                    continue;
                }
                else if (matrix[currentRow - 1][currentColumn] == '@'){
                    moveDown(&direction, &currentRow);
                    continue;
                }
            }
            
            if (direction == DOWN) {
                if (matrix[currentRow][currentColumn - 1] == '@' && matrix[currentRow + 1][currentColumn] == '.') {
                    moveDown(&direction, &currentRow);
                    continue;
                }
                else if (matrix[currentRow - 1][currentColumn - 1] == '@' && matrix[currentRow][currentColumn - 1] == '.') {
                    moveLeft(&direction, &currentColumn);
                    continue;
                }
                else if (matrix[currentRow + 1][currentColumn] == '@' && matrix[currentRow][currentColumn + 1] == '.'){
                    moveRight(&direction, &currentColumn);
                    continue;
                }
                else if (matrix[currentRow + 1][currentColumn] == '@'){
                    moveUp(&direction, &currentRow);
                    continue;
                }

            }
            
            if (direction == LEFT) {
                if (matrix[currentRow - 1][currentColumn] == '@' && matrix[currentRow][currentColumn - 1] == '.') {
                    moveLeft(&direction, &currentColumn);
                    continue;
                }
                else if (matrix[currentRow - 1][currentColumn + 1] == '@' && matrix[currentRow - 1][currentColumn] == '.') {
                    moveUp(&direction, &currentRow);
                    continue;
                }
                else if (matrix[currentRow][currentColumn - 1] == '@' && matrix[currentRow + 1][currentColumn] == '.'){
                    moveDown(&direction, &currentRow);
                    continue;
                }
                else if (matrix[currentRow][currentColumn - 1] == '@'){
                    moveRight(&direction, &currentColumn);
                    continue;
                }

            }
            
            if (direction == RIGHT) {
                if (matrix[currentRow + 1][currentColumn] == '@' && matrix[currentRow][currentColumn + 1] == '.') {
                    moveRight(&direction, &currentColumn);
                    continue;
                }
                else if (matrix[currentRow + 1][currentColumn - 1] == '@' && matrix[currentRow + 1][currentColumn] == '.') {
                    moveDown(&direction, &currentRow);
                    continue;
                }
                else if (matrix[currentRow][currentColumn + 1] == '@' && matrix[currentRow - 1][currentColumn] == '.'){
                    moveUp(&direction, &currentRow);
                    continue;
                }
                else if (matrix[currentRow][currentColumn + 1] == '@'){
                    moveLeft(&direction, &currentColumn);
                    continue;
                }

            }
        }
        
        printf( "EXIT\n***\n" );
    }
    
    fclose( filePointer );
    return 0;
}