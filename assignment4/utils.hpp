/*
 * utils.hpp
 *      Author: norris
 */

#ifndef UTILS_HPP_
#define UTILS_HPP_

#include "maze.hpp"

class Utils {
public:
	Utils(int,std::ifstream&);
	void print(int row, int col);
	void reset();

private:
	bool clearFirst;
	std::string data;
	int size;
	int row;
	int col;
};

#endif /* UTILS_HPP_ */
