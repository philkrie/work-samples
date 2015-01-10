#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int getHumanChoice() {
    
    int choice;
    int flag = 0;
    
    while (flag == 0) {
        printf("Player 1: How many sticks do you take (1-3)? ");
        scanf("%d", &choice);
        
        if (choice != 3 & choice != 2 & choice != 1){
            printf("Please input an integer between 1 and 3 \n");
        } else {
            flag = 1;
        }
    }
    
    return choice;
}

int getComputerChoice(int current_sticks) {
    
    /* get a pseudo-random integer between 1 and 3 (inclusive) */
    int rand_choice = rand() % 3 + 1;
    
    if (rand_choice > current_sticks) return current_sticks;
    
    /* Optionally replace with additional logic for the computer's strategy */
    
    return rand_choice;
}


int main(int argc, char** argv)
{
    int human, computer, number_sticks;
    int flag = 0;
    
    
    srand (time(NULL)); /* for reproducible results, you can call srand(1); */
    
    printf("Welcome to the game of sticks!\n");
    
    
    while (flag == 0)
    {
        printf("How many sticks are there on the table initially (10-100)? ");
        scanf("%d", &number_sticks);
        
        if (number_sticks < 10 || number_sticks > 100){
        fprintf(stderr,"Input not recognised as an appropriate integer (10-100), please try again \n");
        } else {
            flag = 1;
            printf("\nThere are %d sticks on the board\n", number_sticks);
        }
    }
    
    while (number_sticks > 0){
        human = getHumanChoice();
        number_sticks = number_sticks - human;
        if (number_sticks <= 0){
            printf("You lose!\n");
            break;
        }
        printf("\nThere are %d sticks on the board\n", number_sticks);
        computer = getComputerChoice(number_sticks);
        number_sticks = number_sticks - computer;
        printf("Computer chooses %d\n", computer);
        if (number_sticks <= 0){
            printf("You win!\n");
            break;
        }
        printf("\nThere are %d sticks on the board\n", number_sticks);
    }
    
    
    /* TODO: Main game loop:
     While some sticks remain:
     1. Print the current number of sticks, e.g., "There are 2 sticks on the board."
     2. Human: Get number of sticks by calling getHumanChoice and update number_sticks
     3. Computer: get number of sticks by calling getComputerChoice and update number_sticks
     4. Output the computer's choice, e.g., "Computer selects 3."
     After all sticks are gone, output the result of the game, e.g., "You win!" or "You lose!"
     */
    
    return 0;
}
