#include <sstream>     	// std::istringstream
#include <fstream>
#include <map>		// std::multimap
#include <algorithm>   	// std::copy, std::for_each

#include "mr.hpp"
#include "ioutils.hpp"
#include "sentenceStats.hpp"

namespace mr {
// Map and reduce methods to count occurrences of a word in a given text.

// A specialized map function with string keys and int values
void
SentenceStats::MRmap(const std::map<std::string,std::string> &input,
				std::multimap<std::string,double> &out_values) {
	IOUtils io;
	// input: in a real Map Reduce application the input will also be a map
	// where the key is a file name or URL, and the value is the document's contents.
	// Here we just take the string input and process it.
	for (auto it = input.begin(); it != input.end(); it++ ) {
		std::string inputString = io.readFromFile(it->first);
		double count = 0;
		// Split up the input into words
		std::istringstream iss(inputString);
		do {
			std::string word;
			iss >> word;
			count++;
			if (word[word.length() - 1] == '.' || word[word.length() - 1] == '?' || word[word.length() - 1] == '!' ) {
				out_values.insert(std::pair<std::string,double>("sentence", count));
				count = 0.0;
			}
		} while (iss);
			//Clean up goes ahead and saves any sentence at the end of the file that didn't have a period.
			if (count > 0){
				out_values.insert(std::pair<std::string,double>("sentence", count));
				count = 0.0;
			}
	}
}

// A specialized reduce function with string keys and int values
void
SentenceStats::MRreduce(const std::multimap<std::string,double> &intermediate_values,
					std::map<std::string,double> &out_values) {

	// Sum up the counts for all intermediate_values with the same key
	// The result is the out_values map with each unique word as
	// the key and a total count of occurrences of that word as the value.
	double totalsize = 0.0;
	double totalsentences = 0.0;
	std::for_each(intermediate_values.begin(), intermediate_values.end(),
			// Anonymous function that increments the sum for each unique key (word)
			[&](std::pair<std::string,double> mapElement)->void
			{
				if (out_values["min"] == 0){
					out_values["min"] = mapElement.second;
				}
				if (mapElement.second > out_values["max"]){
					out_values["max"] = mapElement.second;
				}
				if (mapElement.second < out_values["min"]){
					out_values["min"] = mapElement.second;
				}
				totalsentences++;
				totalsize += mapElement.second;

			});  // end of for_each

		out_values["average"] = totalsize/totalsentences;
}

}; // namespace mr
