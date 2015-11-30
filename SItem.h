// Brandon Chai, Fall 2015
// SItem for Hash Table 
// CMPS 101 Programming Assignment

#ifndef SITEM_H_INCLUDED
#define SITEM_H_INCLUDED
#include <iostream>
#include <string>

using namespace std;

struct SItem
{
private:
	string userId;	// key 
	int customerId;
	SItem* next;
public:
	// Constructors
	SItem() { userId = ""; customerId = -1; next = NULL; }
	SItem(string userId, int customerId, SItem* next) {
		this->userId = userId; this->customerId = customerId; this->next = next;
	}

	// Accessors
	string getUserId() const { return userId; }
	int getCustomerId() const { return customerId; }
	SItem* getNext() const { return next; }

	// Mutators
	void setUserId(string userId) { this->userId = userId; }
	void setCustomerId(int customerId) { this->customerId = customerId; }
	void setNext(SItem* next) { this->next = next; }
};

#endif // SITEM_H_INCLUDED