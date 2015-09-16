/*
 * ioutils.hpp
 *      Author: norris
 */

#ifndef IOUTILS_HPP_
#define IOUTILS_HPP_

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class IOUtils {
public:
	IOUtils();
	virtual ~IOUtils();
	void openStream(int argc, const char *argv[]);
	void closeStream();
	std::string readFromStream();
	std::string readFromStream(std::istream &);
	std::string readFromFile(std::string fileName);
	std::istream getStream();
	std::vector<std::string> split(const std::string &s, char delim);

private:
	bool isFile;
	std::istream *inputStream;
        std::vector<std::string> &splitHelper(const std::string &s,
                        char delim, std::vector<std::string> &elems);

};


#endif /* IOUTILS_HPP_ */
