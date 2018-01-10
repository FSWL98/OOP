// lab4.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Factorizer.h"
#include "exceptions.h"
#include <iostream>
#include <fstream>
#include <thread>

using namespace std;

void threadFunc(Factorizer& x, const string& inFilename, const string& outFilename)
{
	x.open(inFilename, outFilename);
}

int main(/*const char* inFilename, const char* outFilename*/)
{
	string inFilename, outFilename;
	cin >> inFilename >> outFilename;
	Factorizer x;
	thread thr(threadFunc, ref(x), ref(inFilename), ref(outFilename));
	thr.join();
	system("pause");
    return 0;
}

