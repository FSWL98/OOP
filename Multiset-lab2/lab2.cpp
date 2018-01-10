// lab2.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "StatMultiset.h"
#include <iostream>

using namespace std;

int main()
{
	StatisticMultiset<int> multiSet, multiSet1;
	multiSet1.AddNumbersFromFile("C:\\Users\\FSWL\\Desktop\\proga\\3sem\\lab2\\text.txt");
	multiSet.AddNumbersFromFile("C:\\Users\\FSWL\\Desktop\\proga\\3sem\\lab2\\text.txt");
	cout << multiSet.GetAmountAbove(3) << endl;
	multiSet.AddNumber(40);
	cout << multiSet.GetAmountAbove(3) << endl;
	multiSet.AddNumbers(multiSet1);
	cout << multiSet.GetAmountAbove(3) << endl;
	system("pause");
    return 0;
}

