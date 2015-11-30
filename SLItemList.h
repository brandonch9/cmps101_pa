#ifndef SLITEMLIST_H_INCLUDED
#define SLITEMLIST_H_INCLUDED

#include "SItem.h"
#include <iostream>
#include <string>
using namespace std;

class SLItemList
{
private: 
	SItem* header;
	SItem* tail;
public:
	SItem* getHeader() { return header; }
	SItem* getTail() { return tail; }
	SLItemList() { header = NULL; tail = NULL; }
	void pushFront(string userId, int customerId);
	void pushBack(string userId, int customerId);
	SItem* find(string userId);
};

void SLItemList::pushFront(string userId, int customerId) 
{
	SItem* newItem = new SItem(userId, customerId, 0);
	if (header) {
		newItem->setNext(header);
		header = newItem;
	}
	else {
		header = newItem;
	}
}

void SLItemList::pushBack(string userId, int customerId)
{
	SItem* newItem = new SItem(userId, customerId, 0);

	if (!header) {
		header = newItem;
		tail = newItem;
	}
	else {
		tail->setNext(newItem);
		tail = newItem;
	}
}

SItem* SLItemList::find(string userId) 
{
	SItem* curr = header;
	while (curr)
	{
		if (curr->getUserId() == userId)
		{
			return curr;
		}
		curr = curr->getNext();
	}
	return NULL;
}

#endif // SLITEMLIST_H_INCLUDED
