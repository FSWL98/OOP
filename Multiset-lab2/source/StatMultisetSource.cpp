#include "stdafx.h"
#include "StatMultiset.h"

template<class T>
StatisticMultiset::StatisticMultiset()
{
	_amountOfNumbers = 0;
}
template<class T>
StatisticMultiset::~StatisticMultiset()
{

}
template<class T>
void StatisticMultiset::AddNumber(const T& number)
{
	if (_amountOfNumbers == 0)
	{
		_minValue = number;
		_maxValue = number;
	}
	else
	{
		if (number > _maxValue)
			_maxValue = number;
		if (number < _minValue)
			_minValue = number;
	}
	_numbersSource.push_back(number);
	_isAmountUnchanged = false;
}
template<class T>
void StatisticMultiset::AddNumbers(const std::vector<T>& numbers)
{
	for (auto &it : numbers)
		AddNumber(it);
}
template<class T>
void StatisticMultiset::AddNumbers(const std::list<T>& numbers)
{
	for (auto &it : numbers)
		AddNumber(it);
}
template<class T>
void StatisticMultiset::AddNumbers(const std::multiset<T>& numbers)
{
	for (auto &it : numbers)
		AddNumber(it);
}
template<class T>
void StatisticMultiset::AddNumbers(const StatisticMultiset& multiSet)
{
	if (this != &multiSet)
		AddNumbers(multiSet._numbersSource);
}
template<class T>
void StatisticMultiset::AddNumbersFromFile(const std::string& filename)
{
	std::ifstream fs;
	fs.open(filename);
	if (!fs.good())
		return;
	T value;
	while (fs.good())
	{
		fs >> value;
		AddNumber(fs);
	}
}