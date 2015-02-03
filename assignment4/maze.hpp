/*
 * maze.hpp
 *      Author: norris
 */

#ifndef MAZE_HPP_
#define MAZE_HPP_

#include <fstream>

class Maze
{
public:
	Maze(int size);
    ~Maze() {};

	enum Direction { DOWN, RIGHT, UP, LEFT };

	// Implement the following functions:

	// read maze from file, find starting location
	void readFromFile(std::ifstream &f);

	// make a single step advancing toward the exit
	void step();

	// return true if the maze exit has been reached, false otherwise
	bool atExit();

	// set row and col to current position of 'x'
	void getCurrentPosition(int &row, int &col);

	// You can add more functions if you like
private:
    int mazeSize;
    char **array2D;
    enum Direction direction;
    int currentRow;
    int currentColumn;
	// Private data and methods 
};


#endif /* MAZE_HPP_ */
