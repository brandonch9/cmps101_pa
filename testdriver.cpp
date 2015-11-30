#include "HashTable.h"
#include <iostream>
#include <string>
#include <math.h>
using namespace std;

int main()
{
	HashTable* h = new HashTable();
	h->add("Andre");
	//h->add("Klay");
	//h->add("Draymond");
	//h->add("Harrison");
	//h->show();
	//h->add("Festus");
	//h->add("Leandro");
	//h->add("Stephen");
	//h->add("Brandon");
	//h->add("Andrew");
	//h->add("Shaun");
	//h->add("Ian");
	//h->show();
	//h->add("Marresse");
	//h->add("James");
	//h->add("Kevon");
	//h->show();
	
	string userId;
	cout << "Please enter a user ID: ";
	cin >> userId;
	while (!h->isAvailable(userId))
	{
		cout << "User ID already exists. Please enter another user ID : ";
		cin >> userId;
	}
	return 0;
}
