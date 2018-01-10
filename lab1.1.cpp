// lab1.1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include "IniParser.h"

using namespace std;


int main()
{
	setlocale(LC_ALL, "Rus");
	const string filename_cstr = "C:\\Users\\FSWL\\Desktop\\proga\\3sem\\lab1\\input_correct.ini";
	IniParser Parser;
	try
	{
		Parser.Initialize(filename_cstr);
	}
	catch (const FileException &ex)
	{
		cout << ex.whats() << endl;
		system("pause");
		return 0;
	}
	const string section_name = "ADC_DEV";
	const string param_name = "BufferLenSeconds";
	try
	{
		cout << endl << Parser.get<int>(section_name, param_name);
	}
	catch (const CantConvertTypeException &ex) 
	{
		cout << ex.whats() << endl;
	}
	catch (const NoSuchSectionOrParameterException &ex)
	{
		cout << ex.whats() << endl;
	}
	system("pause");
    return 0;
}

