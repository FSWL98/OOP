#pragma once
#include <vector>
#include <list>
#include <set>
#include <fstream>

template<class T>
class StatisticMultiset
{
#pragma region Public

public:
	StatisticMultiset()
	{
		_amoutOfNumbers = 0;
	}
	~StatisticMultiset()
	{

	}

	void AddNumber(const T& number)
	{
		if (_amoutOfNumbers == 0)
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
		if (_cacheAbove.first)
			if (number > _cacheAbove.second)
				_cacheAbove.first++;
		if (_cacheUnder.first)
			if (number < _cacheUnder.second)
				_cacheUnder.first++;
		_numbersSource.push_back(number);
		_isAmountUnchanged = false;
		_amoutOfNumbers++;
	}
	void AddNumbers(const std::vector<T>& numbers)
	{
		for (auto &it : numbers)
			AddNumber(it);
	}
	void AddNumbers(const std::list<T>& numbers)
	{
		for (auto &it : numbers)
			AddNumber(it);
	}
	void AddNumbers(const std::multiset<T>& numbers)
	{
		for (auto &it : numbers)
			AddNumber(it);
	}
	void AddNumbers(const StatisticMultiset& multiSet)
	{
		if (this != &multiSet)
			AddNumbers(multiSet._numbersSource);
	}
	void AddNumbersFromFile(const std::string& filename)
	{
		std::ifstream fs;
		fs.open(filename);
		if (!fs.good())
			return;
		T value;
		while (fs.good())
		{
			fs >> value;
			AddNumber(value);
		}
	}
	T GetMax() const
	{
		return _maxValue;
	}
	T GetMin() const
	{
		return _minValue;
	}
	float GetAverage() const
	{
		if (_isAmountUnchanged)
			return _avgValue;
		float average = 0;
		for (auto &it : _numbersSource)
			average += static_cast<float>(it);
		_isAmountUnchanged = true;
		_avgValue = average / _amoutOfNumbers;
		return _avgValue;

	}
	int GetAmountAbove(float value) const
	{
		if (_cacheAbove.second == value)
			return _cacheAbove.first;
		int amount = 0;
		for (auto &it : _numbersSource)
			if (it > value)
				amount++;
		this->_UpdateCacheAbove(amount, value);
		return amount;
	}
	int GetAmountUnder(float value) const
	{
		if (_cacheUnder.second == value)
			return _cacheUnder.first;
		int amount = 0;
		for (auto &it : _numbersSource)
			if (it < value)
				amount++;
		this->_UpdateCacheUnder(amount, value);
		return amout;
	}


#pragma endregion

#pragma region Private

private:
	int _amoutOfNumbers;
	std::vector<T> _numbersSource;
	T _maxValue;
	T _minValue;
	mutable float _avgValue;
	mutable bool _isAmountUnchanged = false;
	mutable std::pair<int, float> _cacheUnder, _cacheAbove;
	mutable float _valueAbove, _valueUnder;
	void _UpdateCacheUnder(int& amount, float& value) const
	{
		_cacheUnder = make_pair(amount, value);
	}
	void _UpdateCacheAbove(int& amount, float& value) const
	{
		_cacheAbove = make_pair(amount, value);
	}


#pragma endregion

};