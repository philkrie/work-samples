/*
 * ioutils.cpp
 *      Author: norris
 */

#include <cstdlib>
#include <cstring> // for memcpy
#include "ioutils.hpp"

IOUtils::IOUtils() : isFile(false), inputStream(& std::cin) {
	// By default, read from standard input (cin)
}

IOUtils::~IOUtils() {
	this->closeStream();
}

void
IOUtils::openStream(int argc, const char *argv[]) {
	// If a file name is given read from file instead of standard input
	if( argc == 2 ) { //checks for an optional input file name
		inputStream = new std::ifstream( argv[1] );	// open the input file
		if (! inputStream) {
			std::cerr << "The specified file " << argv[1] << " does not exist!" << std::endl;
			return;
		}
		isFile = true;
	} else {
		std::cout << "Please enter some the full paths of some files, one per line" << std::endl <<
			"To finish, type CTRL-D on a new line (or CTRL-Z in Windows)." << std::endl;
		inputStream = & std::cin;
		isFile = false;
	}
}

void
IOUtils::closeStream() {
	if (isFile && inputStream != nullptr) {
		std::ifstream *fstr = dynamic_cast<std::ifstream *>(inputStream);
		if (fstr != NULL) {
			if (fstr->is_open())
				fstr->close();
			delete fstr;
		}
	}
	inputStream = nullptr;
	// if it's not a file (i.e., the stream is cin), don't close it
}

std::string
IOUtils::readFromStream() {
	return this->readFromStream(*(this->inputStream));
}

std::string
IOUtils::readFromStream(std::istream &istream) {
	std::string theInput;
	char ch;

	istream >> std::noskipws;  // disable skipping of whitespace
	while ( ! istream.eof() ) {
		istream >> ch;
	    theInput += ch;
	}

	return theInput;
}


std::string
IOUtils::readFromFile(std::string fileName) {
	std::string fileContents;
	std::ifstream iStream( fileName );	// open the input file
	if (! iStream) {
		std::cerr << "The specified file " << fileName << " does not exist!" << std::endl;
		return "";
	}
	fileContents = this->readFromStream(iStream);
	iStream.close();
	return fileContents;
}
	
// Helper functions for splitting a string given a delimeter
std::vector<std::string> &
IOUtils::splitHelper(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

// Split a string using a delimeter (e.g., new line, space, comma, etc.)
std::vector<std::string>
IOUtils::split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    splitHelper(s, delim, elems);
    return elems;
}
