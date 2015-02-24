#ifndef SENTENCESTATS_HPP_
#define SENTENCESTATS_HPP_

#include <fstream>
#include <string>
#include <map>

#include "mr.hpp"

namespace mr {

class SentenceStats : public MapReduce<std::string,double> {
public:
	virtual void MRmap(const std::map<std::string,std::string> &input,
			std::multimap<std::string,double> &out_values);
	virtual void MRreduce(const std::multimap<std::string,double> &intermediate_values,
			std::map<std::string,double> &out_values);
};

} /* namespace mr */

#endif /* SENTENCESTATS_HPP_ */
