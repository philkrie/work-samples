/*
 * utils.cpp
 *      Author: norris
 */

#include <fstream>
#include <iostream>
#include <string>
#include "utils.hpp"

Utils::Utils(int size, std::ifstream &f)
		: clearFirst(false), data(""), size(0), row(0), col(0) {
	std::streampos cPos = f.tellg();
	std::string theline;
	this->size = size;
	getline(f, theline);
	for (int i = 0; i < size; i++) {
		getline( f, theline );
		data += theline.substr(0,size);
	}
	// reset the file stream
	f.seekg(cPos);
}

void Utils::print(int row, int col) {

	std::string tmpMaze = data;
	tmpMaze[row*size + col] = 'x';
	for (int i = 0; i < size; i++ )
		std::cout << tmpMaze.substr(i*size,size) << std::endl;
}

void Utils::reset() {
	clearFirst = false;
}

