// Tramvai.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>     // std::cout
#include <fstream>      // std::ifstream

using namespace std;

int main()
{
	long count = 0;

	ifstream infile("text.txt");

	int m = 0;
	int n = 0;
	int ways = 0;

	int row = 0;
	int c1 = 0;
	int c2 = 0;

	infile >> m >> n >> ways;

	count = m * n;

	while (infile >> row >> c1 >> c2)
	{
		cout << "C1 is: " << c1 << endl;   // just to see if the loop is working.
		cout << "C2 is: " << c2 << endl;   // just to see if the loop is working.

	}

    return 0;
}

