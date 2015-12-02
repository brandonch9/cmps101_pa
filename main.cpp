#include "TestDrivers.h"
#include <iostream>
#include <cstdlib>
using namespace std;

int main()
{
	TestDrivers* test = new TestDrivers();
	test->readFromFile("INPUT");
	test->generateOutput();

	system("PAUSE");
	return 0;
}
