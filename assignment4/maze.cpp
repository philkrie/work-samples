//
//  maze.cpp
//  
//
//  Created by Phillip Kriegel on 2/2/15.
//
//

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include "maze.hpp"

//Initialization of the maze, finds the
Maze::Maze(int size) {
    mazeSize = size;
}

void Maze::readFromFile(std::ifstream &f){
    
    //We create the array and intialize its values
    array2D = new char*[mazeSize];
    for (int i = 0; i < mazeSize; i++){
        array2D[i] = new char[mazeSize];
    }
    
    std::string currentLine;
    
    for (int i = 0; i < mazeSize; i++) {
        f >> currentLine;
        for (int j = 0; j < mazeSize; j++){
            array2D[i][j] = currentLine[j];
        }
    }
    
    //Now we have to find x
    
    for (int i = 0; i < mazeSize; i++) {
        for (int j = 0; j < mazeSize; j++){
            if(array2D[i][j] == 'x'){
                currentRow = i;
                currentColumn = j;
                break;
            }
        }
    }
    
    if (currentColumn == 0) {
        direction = RIGHT;
    }
    
    if (currentColumn == mazeSize - 1) {
        direction = LEFT;
    }
    
    if (currentRow == 0){
        direction = DOWN;
    }
    
    if (currentRow == mazeSize - 1) {
        direction = UP;
    }
}

void Maze::getCurrentPosition(int &row, int &column){
    row = currentRow;
    column = currentColumn;
}

void Maze::step() {
        
        if (direction == UP) {
            if (array2D[currentRow][currentColumn + 1] == '@' && array2D[currentRow - 1][currentColumn] == '.') {
                direction = UP;
                currentRow = currentRow - 1;
            }
            else if (array2D[currentRow + 1][currentColumn + 1] == '@' && array2D[currentRow][currentColumn + 1] == '.') {
                direction = RIGHT;
                currentColumn = currentColumn + 1;
            }
            else if (array2D[currentRow - 1][currentColumn] == '@' && array2D[currentRow][currentColumn - 1] == '.'){
                direction = LEFT;
                currentColumn = currentColumn - 1;
            }
            else if (array2D[currentRow - 1][currentColumn] == '@'){
                direction = DOWN;
                currentRow = currentRow + 1;
            }
        }
        
        else if (direction == DOWN) {
            if (array2D[currentRow][currentColumn - 1] == '@' && array2D[currentRow + 1][currentColumn] == '.') {
                direction = DOWN;
                currentRow = currentRow + 1;
            }
            else if (array2D[currentRow - 1][currentColumn - 1] == '@' && array2D[currentRow][currentColumn - 1] == '.') {
                direction = LEFT;
                currentColumn = currentColumn - 1;
            }
            else if (array2D[currentRow + 1][currentColumn] == '@' && array2D[currentRow][currentColumn + 1] == '.'){
                direction = RIGHT;
                currentColumn = currentColumn + 1;
                
            }
            else if (array2D[currentRow + 1][currentColumn] == '@'){
                direction = UP;
                currentRow = currentRow - 1;
                
            }
            
        }
        
        else if (direction == LEFT) {
            if (array2D[currentRow - 1][currentColumn] == '@' && array2D[currentRow][currentColumn - 1] == '.') {
                direction = LEFT;
                currentColumn = currentColumn - 1;
                
            }
            else if (array2D[currentRow - 1][currentColumn + 1] == '@' && array2D[currentRow - 1][currentColumn] == '.') {
                direction = UP;
                currentRow = currentRow - 1;
                
            }
            else if (array2D[currentRow][currentColumn - 1] == '@' && array2D[currentRow + 1][currentColumn] == '.'){
                direction = DOWN;
                currentRow = currentRow + 1;
                
            }
            else if (array2D[currentRow][currentColumn - 1] == '@'){
                direction = RIGHT;
                currentColumn = currentColumn + 1;
                
            }
            
        }
        
        else if (direction == RIGHT) {
            if (array2D[currentRow + 1][currentColumn] == '@' && array2D[currentRow][currentColumn + 1] == '.') {
                direction = RIGHT;
                currentColumn = currentColumn + 1;
                
            }
            else if (array2D[currentRow + 1][currentColumn - 1] == '@' && array2D[currentRow + 1][currentColumn] == '.') {
                direction = DOWN;
                currentRow = currentRow + 1;
                
            }
            else if (array2D[currentRow][currentColumn + 1] == '@' && array2D[currentRow - 1][currentColumn] == '.'){
                direction = UP;
                currentRow = currentRow - 1;
                
            }
            else if (array2D[currentRow][currentColumn + 1] == '@'){
                direction = LEFT;
                currentColumn = currentColumn - 1;
                
            }
            
        }
    

}

bool Maze::atExit(){
    if (direction == UP){
        if (currentRow - 1 < 0){
            return true;
        }
    }
    
    if (direction == DOWN){
        if (currentRow + 1 == mazeSize){
            return true;
        }
    }
    
    if (direction == LEFT){
        if (currentColumn - 1 < 0){
            return true;
        }
    }
    
    if (direction == RIGHT){
        if (currentColumn + 1 == mazeSize){
            return true;
        }
    }
    return false;
}
