//
//  test.c
//  
//
//  Created by Phillip Kriegel on 1/18/15.
//
//

#include <stdlib.h>
#include <stdio.h>
#include "square1.h"
#include "square2.h"
#include "diamond.h"


int main() {
    printf("Problem 1 (a square of size 10):\n"); /* Fixed-size square */
    print10Square();
    char **square;
    
    int size;
    int flag = 0;
    
    printf("\nProblem 2:");
    while (flag == 0) {
        printf("\nPlease enter the size of the square [2-10]:  ");
            scanf("%d", &size);
            if (size < 2 || size > 10){
                continue;
            } else {
                flag = 1;
            }
        }
        
    allocateNumberSquare((const int) size, &square);
    
    initializeNumberSquare((const int) size, square);
    
    printNumberSquare((const int) size, square);
    
    printf("\nProblem 3:\n");

    printNumberDiamond((const int) size, square);
    
    deallocateNumberSquare((const int) size, square);

    return 0;
}
