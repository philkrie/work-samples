/*
 * mr.hpp
 *      Author: norris
 *
 *
 * This is the interface to a very simplistic Map Reduce system.
 * The general workflow is:
 * - Read input or generate lots of data
 * - Split: split data and distribute to mappers
 * - Map: extract something you care about from the data
 * - Shuffle and/or sort the results from the mapping
 * - Reduce: aggregate, summarize, filter, or transform the
 *   shuffled/sorted intermediate result.
 * - Write out the final result
 *
 * To implement something new, you just have to provide
 * new map and reduce methods; the other steps are handled
 * automatically by the MR engine and you don't have to implement
 * them yourself.
 *
 * Introduction to Map Reduce:
 *    http://www.slideshare.net/rantav/introduction-to-map-reduce
 *    http://ksat.me/map-reduce-a-really-simple-introduction-kloudo
 *
 */

#ifndef MR_HPP_
#define MR_HPP_

#include <string>
#include <iostream>
#include <map>
#include <future>       // std::async, std::future, std::launch
#include <thread>       // std::this_thread::sleep_for

#include "ioutils.hpp"


namespace mr {

// Abstract class from which all map and reduce implementations must
// be derived.
template<typename Key, typename Val>
class MapReduce {
public:
	/*
	 *  Map: extract something you care about form the input
	 *  Map(input) -> out_values
	 */
	virtual
	void MRmap(const std::map<std::string,std::string> &input,
			  std::multimap<Key,Val> &out_values);

	/*
	 * Reduce: aggregate, summarize, filter, or transform
	 * Reduce(intermediate) -> out_values
	 */
	virtual
	void MRreduce(const std::multimap<Key,Val> &intermediate_values,
				  std::map<Key,Val> &out_values);
};

// The actual Map Reduce runtime (simplest possible sequential implementation)
template <typename Key,typename Val>
void run(MapReduce<Key,Val> &mr,
 		 std::vector<std::string> &fileNames,
		 std::map<Key,Val> &finalResult) {

	std::multimap<Key,Val> intermediate;
	std::map<Key,Val> output;
	for (auto &fileName : fileNames) {   // range-based for loop
		// Check if fileName is non-whitespace and file exists
		if (fileName.find_first_not_of(' ') == std::string::npos) continue;

		std::map<std::string,std::string> input;
		input[fileName] = "";  // the file contents will be read in the mapper

		// Iterate over input dictionary, in which each key is a file name and
		// the corresponding value has the contents of the file.

		mr.MRmap(input, intermediate);  // intermediate is the result of the map operation

		// In C++, the map is already sorted by key (lexicographically),
		// so we don't have to do it here.

	}

	// Now reduce to get the final output
	mr.MRreduce(intermediate, output);
	finalResult.insert(output.begin(), output.end());

	// That's it!
}

// The actual Map Reduce runtime (a very simplistic parallel implementation)
template <typename Key,typename Val>
void prun(MapReduce<Key,Val> &mr,
	 std::vector<std::string> &fileNames,
	 std::map<Key,Val> &finalResult,
	 size_t mapThreads=4,
	 size_t reduceThreads=2) {

	std::vector<std::future<void> > futures;  // for use with async

	std::multimap<Key,Val> intermediate;  // shared among threads
	for (auto &fileName : fileNames) {   // range-based for loop
		// Check if fileName is non-whitespace and file exists
		if (fileName.find_first_not_of(' ') == std::string::npos) continue;

		std::map<std::string,std::string> input;
		input[fileName] = "";  // the file contents will be read in the mapper

		// Iterate over input dictionary, in which each key is a file name and
		// the corresponding value has the contents of the file.
		std::multimap<Key,Val> intermediate;
		futures.push_back(std::async (std::launch::async,
				&MapReduce<Key,Val>::MRmap, &mr, std::ref(input), std::ref(intermediate)));
		// Note above that we have to use the fully-resolved function name MapReduce<Key,Val>::map,
		// and then we have to explicitly pass "this", in this case, mr, as the first argument.
		// sequential was: mr.mrMap(input, intermediate);
	}

	for (auto &mapFuture : futures) mapFuture.get();   // finish with all mapper threads

	size_t size = intermediate.size();
	size_t sizePerThread = size / reduceThreads;

    if (size <= sizePerThread) {
    	// Just run the sequential version
    	run(mr, fileNames, finalResult);
    	return;
    }

	std::map<Key,Val> output;  // shared among threads
	futures.clear();
	for (auto it = intermediate.begin(); it != intermediate.end(); ) {
		// Partition the intermediate results among the threads
		std::multimap<Key,Val> inter;

		for (int i = 0; i < sizePerThread && it != intermediate.end(); i++, it++) {
			inter.insert(*it);
		}
		futures.push_back( std::async (std::launch::async,
				&MapReduce<Key,Val>::MRreduce, &mr, std::ref(inter), std::ref(output)));
	}

	// A final pass to consolidate output
	for (auto &reduceFuture : futures) {
		reduceFuture.get();
	}
	finalResult.insert(output.begin(), output.end());
	// That's it!
}

}; // namespace mr


#endif /* MR_HPP_ */
