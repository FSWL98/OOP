#include "stdafx.h"
#include "IniParser.h"
#include "MainObject.h"


IniParser::IniParser()
{
	
}


IniParser::~IniParser()
{
}



void IniParser::DeleteSpaces(std::string& str) const {
	std::string result;
	int i = 0, spaces = 0;
	while ((str)[i] == ' ')
		i++;
	(str).erase(0, i);
	for (i = 0; i < (str).size(); i++)
	{
		if ((str)[i] == ' ')
			while ((str)[i + 1] == ' ')
				(str).erase(i + 1, 1);
	}
}




void IniParser::Initialize (const std::string& filename) throw (FileException)
{
	std::ifstream fs;
	fs.open(filename);
	if (!fs.good())
		throw FileException(filename);
	std::string str, section, parameter, value;
	std::map<std::string, std::string> inner;
	while (fs.good())
	{

		getline(fs, str);
		DeleteSpaces(str);
		std::cout << str << std::endl;
		if (str.find("[") == 0)
		{
			if (CollectionSize != 0)
			{
				ItemCollection.insert(std::make_pair(section, inner));
				inner.clear();
			}
			section = str.substr(1, str.find("]") - str.find("[") - 1);
			CollectionSize++;
		}
		else
		{
			if (str[0])
			{

				int i = 0;
				while (str[i] != ' ' && str[i] != '=')
					i++;
				if (str[0] != ';')
				{
					parameter = str.substr(0, i);
					i++;
					i++;
					if (str[i] == ' ')
						i++;
					int j = i;
					while (str[i] != ' ' && str[i] != ';')
						i++;
					value = str.substr(j, i - j);
					inner.insert(std::make_pair(parameter, value));

				}
			}
		}

	}
	ItemCollection.insert(std::make_pair(section, inner));
	inner.clear();
	fs.close();
}

bool IniParser::IsHaveSection(const std::string& section_name) const
{
	for (auto it = ItemCollection.begin(); it != ItemCollection.end(); it++)
	{
		if (it->first == section_name)
			return true;
		
	}
	return false;
}

bool IniParser::IsHaveParam(const std::string& section_name, const std::string& param_name) const
{
	if (!this->IsHaveSection(section_name))
		return false;
	std::map<std::string, std::string> parameters = this->ItemCollection.find(section_name)->second;
	return parameters.find(param_name) != parameters.end();
}

template<> std::string IniParser::get<std::string>(const std::string& section_name
	, const std::string& param_name) const throw (NoSuchSectionOrParameterException)
{
	if (!this->IsHaveSection(section_name))
		throw NoSuchSectionOrParameterException("Section [" + section_name + "] isn't founded");
	if (!this->IsHaveParam(section_name, param_name))
		throw NoSuchSectionOrParameterException("Parameter " + param_name + " in section [" + section_name + "] isn't founded");
	std::map<std::string, std::string> parameters = this->ItemCollection.find(section_name)->second;
	return parameters.find(param_name)->second;
}

template<> int IniParser::get<int>(const std::string& section_name, const std::string& param_name) const
{
	std::string value = this->get<std::string>(section_name, param_name);
	int result;
	try
	{
		result = stoi(value);
	}
	catch (const std::invalid_argument &exc)
	{
		throw CantConvertTypeException("Can't convert " + value + " to int");
	}
	
	return result;
}

template<> double IniParser::get<double>(const std::string& section_name, const std::string& param_name) const
{
	std::string value = this->get<std::string>(section_name, param_name);
	double result;
	try
	{
		result = stod(value);
	}
	catch(const std::invalid_argument &exc)
	{
		throw CantConvertTypeException("Can't convert " + value + " to double");
	}
	
	return result;
}