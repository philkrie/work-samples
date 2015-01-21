//
//  diamond.c
//  
//
//  Created by Phillip Kriegel on 1/19/15.
//
//

#include "diamond.h"
#include <stdio.h>

void printNumberDiamond(const int size, char **square){
    int i;
    int j;
    int k = -1;
    for(int i = 0; i < size; i++) {
        if (i <= (size-1)/2){
            k = k + 2;
            for(int j = 0; j < (size - k)/2; j++){
                printf("  ");
            }
            
            for(int j = 0; j < k; j++) {
                printf("%d ", square[i][j]);
           }
        }
        
     
        
        else {
            
            if (size%2 ==1){
                k = k-2;
            }
            for(int j = 0; j < (size - k)/2; j++){
                printf("  ");
            }
            
            for(int j = 0; j < k; j++){
              printf("%d ", square[i][j]);
            }
            if (size%2==0){
                k=k-2;
            }
        }
        printf("\n");
    }

}
