//
//  square1.c
//  
//
//  Created by Phillip Kriegel on 1/18/15.
//
//

#include <stdio.h>
#include "square1.h"

void print10Square() {
    int array[10][10];
    for (int i = 0; i < 10; i++){
        for(int j = 0; j < 10; j++){
            array[i][j] = j;
        }
    }
    for(int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++) {
            printf("%d ", array[i][j]);
        }
        printf("\n");
    }
}