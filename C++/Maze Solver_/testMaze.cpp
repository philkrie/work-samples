//
//  testMaze.cpp
//  
//
//  Created by Phillip Kriegel on 2/3/15.
//
//

#include <iostream>  // needed
#include <fstream>   // needed to read from a file
#include "maze.hpp"

int main(int argc, const char *argv[]) {
    if( argc != 2 ) //checks for the input file name
    {
        std::cerr << "Error: no input file name" << std::endl;
        std::cerr << "Usage: ./" << argv[0] << " someinput.txt" << std::endl;
        return 1;
    }
    
    std::ifstream mazeInputFile ( argv[1] );	// open the input file
    int numberOfMazes = 0;
    mazeInputFile >> numberOfMazes; 			// read the number of mazes
    
    for (int currentMaze = 0; currentMaze < numberOfMazes; currentMaze++ ) {
        int mazeSize = 0;
        mazeInputFile >> mazeSize;				// read the maze size from the input file
                
        if (mazeSize < 10 || mazeSize > 30) {
            std::cerr << "Error: invalid maze size " << mazeSize << " read from " << argv[1] << std::endl;
            std::cerr << "     Maze sizes must be between 10 and 30" << std::endl;
            return 1;
        }
        
        // Create a new maze object of the given size
        Maze maze(mazeSize);
        
        // Initialize the maze
        maze.readFromFile(mazeInputFile);
        
        std::cout << "ENTER" << std::endl;
        
        do {
            
            maze.step();
            switch(maze.getCurrentDirection()){
                case Maze::LEFT:
                    std::cout << "LEFT" << std::endl;
                    break;
                case Maze::RIGHT:
                    std::cout << "RIGHT" << std::endl;
                    break;
                case Maze::UP:
                    std::cout << "UP" << std::endl;
                    break;
                case Maze::DOWN:
                    std::cout << "DOWN" << std::endl;
                    break;
            }
            
        } while (! maze.atExit());

        std::cout << "EXIT" << std::endl << "***" << std::endl;
        
    }
}
