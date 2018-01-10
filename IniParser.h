#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include "Exceptions.h"
class IniParser {
public:     IniParser();     ~IniParser();

			

			void Initialize(const std::string& filename_cstr) throw (FileException);

			bool IsHaveSection(const std::string& section_name) const;

			bool IsHaveParam(const std::string& section_name, const std::string& param_name) const;

			template<class T> T get(const std::string& section_name, const std::string& param_name) const throw (NoSuchSectionOrParameterException, CantConvertTypeException);

			void DeleteSpaces(std::string& filename_cstr) const;
			
			int CollectionSize = 0;

			std::map<std::string, std::map<std::string, std::string>> ItemCollection;

};