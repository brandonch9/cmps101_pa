#ifndef TESTDRIVERS_H_INCLUDED
#define TESTDRIVERS_H_INCLUDED

#include "UIMS.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class TestDrivers
{
private:
	UIMS* u;
public:
	TestDrivers() { u = new UIMS();}
	void readFromFile(string input);
	void generateOutput();
};

void TestDrivers::readFromFile(string input)
{
	string line;
	ifstream inputFile(input.c_str());
	if (inputFile.is_open())
	{
		while (getline(inputFile, line))
		{
			//cout << line << '\n';
			u->add(line);
		}
		inputFile.close();
	}
	else cout << "Unable to open file";
}

void TestDrivers::generateOutput()
{
	u->show();
}

#endif // TESTDRIVERS_H_INCLUDED