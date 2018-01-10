#pragma once
#include "exceptions.h"
#include <string>
#include <vector>

class Factorizer
{
public:
	void factorize(const uint64_t& number);
	uint64_t getNumberFromFactorizing() const;
	std::string generateString();
	void open(const std::string& inFilename, const std::string& outFilename);
private:
	std::vector<int> _multiplyers;
};