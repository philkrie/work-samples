/*
 * test-wordCount.cpp
 *
 * Testing the word count MR problem.
 *
 *  Created on: Februrary 16, 2014
 *      Author: norris
 */


#include <iostream>
#include <string>
#include <future>       // std::async, std::future, std::launch
#include <thread>       // std::this_thread::sleep_for
#include <chrono>       // std::chrono (timing)

#include "ioutils.hpp"
#include "mr.hpp"
#include "wordCount.hpp"


int main(int argc, const char *argv[]) {
	using namespace std;

	// Use MapReduce to compute a word count
	mr::WordCount wordCount;
	std::map<string,int> final;

	// Assume that the URLs to process are listed (one per line)
	// a file called wordCount-input.txt in the current directory
	IOUtils io;
	io.openStream(argc,argv);
	vector<string> fileNames = io.split(io.readFromStream(),'\n');
	io.closeStream();

	auto start = std::chrono::steady_clock::now(); // start timer

#ifndef PARALLEL_MR
	// Invoke the Map Reduce runtime
	mr::run(wordCount, fileNames, final);
#else	
	// To run the parallel Map Reduce, include -DPARALLEL_MR to 
	// the CXXFLAGS variable in the Makefile,
	// then make clean and make
	mr::prun<string,int>(wordCount, fileNames, final, 10, 4);
#endif

	auto end = std::chrono::steady_clock::now();

	// Print the final results
	for (auto it = final.begin(); it != final.end(); it++ )
		cout << it->first << ": " << it->second << endl;

	auto diff = end - start;
	cout << "MapReduce time: " << std::chrono::duration <double, std::milli> (diff).count() << " ms" << endl;
	return 0;
}
