#include <sstream>     	// std::istringstream
#include <fstream>
#include <map>		// std::multimap
#include <algorithm>   	// std::copy, std::for_each

#include "mr.hpp"
#include "ioutils.hpp"
#include "phrases.hpp"


namespace mr {
// Map and reduce methods to count occurrences of a word in a given text.

// A specialized map function with string keys and int values
void
Phrases::MRmap(const std::map<std::string,std::string> &input,
				std::multimap<std::string,int> &out_values) {
	IOUtils io;
	// input: in a real Map Reduce application the input will also be a map
	// where the key is a file name or URL, and the value is the document's contents.
	// Here we just take the string input and process it.
	for (auto it = input.begin(); it != input.end(); it++ ) {
		std::string inputString = io.readFromFile(it->first);

		// Split up the input into words
		std::istringstream iss(inputString);

		std::string previous_word;
		iss >> previous_word;

		for(int i = 0; i < previous_word.length(); i++){
				if(std::ispunct(previous_word[i])){
					if(previous_word[i] == '(' || previous_word[i] == ')'){
						continue;
					}
					else if(previous_word[i] == '\'' && i != previous_word.length()-1){
						continue;
					} else {
						previous_word.erase(i, 1);
						i--;
					}
				}
			}

		do {
			std::string word;
			std::string phrase;
			iss >> word;

			for(int i = 0; i < word.length(); i++){
				if(std::ispunct(word[i])){
					if(word[i] == '(' || word[i] == ')'){
						continue;
					}
					else if(word[i] == '\'' && i != word.length()-1){
						continue;
					} else {
						word.erase(i, 1);
						i--;
					}
				}
			}

			phrase = previous_word + " " + word;
			out_values.insert(std::pair<std::string,int>(phrase,1));
			previous_word = word;
		} while (iss);
	}
}

// A specialized reduce function with string keys and int values
void
Phrases::MRreduce(const std::multimap<std::string,int> &intermediate_values,
					std::map<std::string,int> &out_values) {

	// Sum up the counts for all intermediate_values with the same key
	// The result is the out_values map with each unique word as
	// the key and a total count of occurrences of that word as the value.
	std::for_each(intermediate_values.begin(), intermediate_values.end(),
			// Anonymous function that increments the sum for each unique key (word)
			[&](std::pair<std::string,int> mapElement)->void
			{
				out_values[mapElement.first] += 1;
			});  // end of for_each
}

}; // namespace mr
