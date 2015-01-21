//
//  square2.c
//  
//
//  Created by Phillip Kriegel on 1/18/15.
//
//

#include <stdlib.h>
#include <stdio.h>
#include "square2.h"

void allocateNumberSquare(const int size, char ***square){
    int i;
    (*square) = (char **) malloc ( size * sizeof(char *));
    for (i = 0; i < size; i++) {
        (*square)[i] = (char *) malloc ( size * sizeof(char) );
    }
    
}

void initializeNumberSquare(const int size, char **square){
    int i;
    int j;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            square[i][j] = j;
        }
    }
}

void printNumberSquare(const int size, char **square){
    int i;
    int j;
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            printf("%d ", square[i][j]);
        }
        printf("\n");
    }

}

void deallocateNumberSquare(const int size, char **square){
    for (int i = 0; i < size; i++){
        free(square[i]);
    }
}


