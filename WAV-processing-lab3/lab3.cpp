// lab3.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "WAV.h"
#include <iostream>

using namespace std;


int main()
{
	string inputFilename = "0.wav";
	string outputFilename = "out.wav";
	WAV file;

		file.open(inputFilename);
	file.printInfo();
	file.mono();
	cout << "done\n";
	file.reverb(0.500, 0.6f);
	cout << "done\n";
	file.saveToFile(outputFilename);
	system("pause");
}

