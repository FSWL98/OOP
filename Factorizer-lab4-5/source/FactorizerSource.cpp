#include "stdafx.h"
#include "exceptions.h"
#include "Factorizer.h"
#include <fstream>
#include <iostream>

void Factorizer::factorize(const uint64_t& number)
{
	this->_multiplyers.resize(0);
	uint64_t number1 = number;
	int i = 2;
	while (i <= number1)
	{
		if (number1%i == 0)
		{
			this->_multiplyers.push_back(i);
			number1 /= i;
		}
		else
			i++;
	}

}
void Factorizer::open(const std::string& inFilename, const std::string& outFilename)
{
	std::ifstream fin;
	std::ofstream fout;
	try
	{
		fin.open(inFilename);
		fout.open(outFilename);
	}
	catch (IOException &e)
	{
		std::cout << e.what();
	}

	uint64_t a;
	while (fin.good())
	{
		fin >> a;
		this->factorize(a);
		fout << "Number is " << this->getNumberFromFactorizing() << ", Factorizing = " << this->generateString() << std::endl;
	}
	fin.close();
	fout.close();
}
uint64_t Factorizer::getNumberFromFactorizing() const
{
	uint64_t result = 1;
	int size = this->_multiplyers.size();
	for (int i = 0; i < size; i++)
		result = result * this->_multiplyers[i];
	return result;
}
std::string Factorizer::generateString()
{
	std::string result = "";
	int size = this->_multiplyers.size();
	for (int i = 0; i < size - 1; i++)
		result = result + std::to_string(this->_multiplyers[i]) + " * ";
	result += std::to_string(this->_multiplyers[size - 1]);
	return result;
}