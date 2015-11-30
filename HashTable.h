// Brandon Chai, Fall 2015
// SItem for Hash Table 
// CMPS 101 Programming Assignment

#ifndef HASHTABLE_H_INCLUDED
#define HASHTABLE_H_INCLUDED
#include "SLItemList.h"
#include <iostream>
#include <string>
#include <math.h> 
#include <stdlib.h>   
#include <time.h> 
#include <random>
using namespace std;

class HashTable
{
private:
	int m = 13;		// hash table size
	int w;
	int k;
	int* a;			// salt
	int customerId = 0;
	SLItemList** userT = new SLItemList*[m];	// initialize a hash table of singly linked item lists

	// internal functions
	int hash(string userId);	// basic hash function 
	int multHash(string userId);	// prime multiplicative hash function
	float getLoad();
	void reallocate();
	int* char2num16(string userId);
	int* numToBitSeq(int n);
	int* num162bit96(int* n);
	int* bitSeqToDigitSeq(int* bs);
	int bitSeqToBigNum(int* bs);
	int* generateSalt();
	int scalarMult(int* x);
	int* sieve(int n);
	int nextPrime();

public:
	// Admin functions
	HashTable();				//Constructor
	~HashTable();				//Destructor

	// Public user functions
	void add(string userId);
	void add(string userId, int customerId);
	void show();
	bool isAvailable(string userId);
	int lookupCustomerId(string userId);	
};

// Default constructor
HashTable::HashTable()
{
	//Initialize all the elements in the hashtable
	for (int i = 0; i < m; i++)
		userT[i] = new SLItemList();
	w = log(m) / log(2);
	k = 96 / w;
	a = generateSalt();
}

HashTable::~HashTable()
{
	//Deletes all the elements in the hashtable 
	for (int i = 0; i < m; i++)
	{
		SItem* item = userT[i]->getHeader();
		while (item->getNext())
		{
			SItem* prev = item;
			item = item->getNext();
			delete prev;
		}
	}
}

//hash - takes the key, sums the ascii value of each character
//       in the key and returns the total mod table size as index
int HashTable::hash(string userId)
{
	int sum = 0;
	for (int k = 0; k < int(userId.length()); k++)
		sum = sum + int(userId[k]);			//Gets the sum of the ASCII value of the whole string.
	return sum % m;							//Return the index on where to store the string data
}

// add - inserts item into the hash based on the key value
void HashTable::add(string userId)
{
	if (getLoad() > 0.75)
	{
		reallocate();
	}

	customerId++;
	int index = multHash(userId);
	//int index = hash(userId);	
	userT[index]->pushFront(userId, customerId);
}

// add - Used in reallocate. CustomerId is already known.
void HashTable::add(string userId, int customerId)
{
	int index = multHash(userId);
	//int index = hash(userId);
	userT[index]->pushFront(userId, customerId);
}

void HashTable::show()
{
	for (int i = 0; i < m; i++) {
		SItem* curr = userT[i]->getHeader();
		cout << i << " ";
		while (curr)
		{
			cout << curr->getUserId() << ": " << curr->getCustomerId() << " ";
			curr = curr->getNext();
		}
		cout << endl;
	}
	cout << endl;
}

bool HashTable::isAvailable(string userId)
{
	int index = multHash(userId);
	SItem* curr = userT[index]->find(userId);

	if (curr)
	{
		return false;
	}
	else
	{
		return true;
	}
}

int HashTable::lookupCustomerId(string userId)
{
	int index = hash(userId);
	SItem* curr = userT[index]->getHeader();

	while (curr)
	{
		if (curr->getUserId() == userId)
		{
			return curr->getCustomerId();
		}
		curr = curr->getNext();
	}
	return 0;
}

float HashTable::getLoad()
{
	return float(customerId) / float(m);
}

void HashTable::reallocate()
{
	int prevM = m;
	m = nextPrime();
	w = log(m) / log(2);
	k = 96 / w;
	a = generateSalt();

	SLItemList** prevUserT = userT;
	userT = new SLItemList*[m]; // intialize a new userT of size m * 2

	for (int i = 0; i < m; i++)
	{
		userT[i] = new SLItemList();
	}


	for (int i = 0; i < prevM; i++)
	{
		SItem* curr = prevUserT[i]->getHeader();
		while (curr)
		{
			string userId = curr->getUserId();
			int customerId = curr->getCustomerId();
			add(userId, customerId);
			curr = curr->getNext();
		}
	}
}

int* HashTable::char2num16(string userId)
{
	char charArr[64] = { '_', '0', '1', '2','3', '4', '5', '6', '7', '8', '9'
		, '10', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i'
		, 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's'
		, 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C'
		, 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M'
		, 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W'
		, 'X', 'Y', 'Z' };

	int* num16 = new int[16];

	for (int i = 0; i < 16; i++)
	{
		num16[i] = 0;		// initialize each digit to 0 to account for padding
	}

	int k = 15;	// start from the last char in userId

	for (int i = userId.length() - 1; i > -1; i--)
	{
		int j = 0;
		while (userId[i] != charArr[j])
		{
			j++;
		}
		num16[k] = j;
		k--;
	}

	return num16;
}

int* HashTable::numToBitSeq(int n)
{
	int* bs = new int[6];

	// initialize bits to 0
	for (int i = 0; i < 6; i++)
	{
		bs[i] = 0;
	}

	int i = 5;
	while (n >= 1)
	{
		int n2 = n / 2;
		bs[i] = n - (2 * n2);
		n = n2;
		i--;
	}
	return bs;
}

int* HashTable::num162bit96(int* n)
{
	int* bitSeq96 = new int[96];
	int i = 0;
	while (i < 96)
	{
		for (int j = 0; j < 16; j++)
		{
			int* bitSeq6 = numToBitSeq(n[j]);
			for (int k = 0; k < 6; k++)
			{
				bitSeq96[i] = bitSeq6[k];
				i++;
			}
		}
	}
	return bitSeq96;
}

int* HashTable::bitSeqToDigitSeq(int* bs)
{
	int* ds = new int[k];
	int* bitSeqW = new int[w];

	int i = 0; // pos in bs
	int l = 0; // pos in ds
	while (i < 96 && l < k)
	{
		for (int j = 0; j < w; j++)
		{
			bitSeqW[j] = bs[i];
			i++;
		}
		ds[l] = bitSeqToBigNum(bitSeqW);
		l++;
	}
	return ds;
}

int HashTable::bitSeqToBigNum(int* bs)
{
	int bn = 0;
	int j = 0; // base pos 
	for (int i = w - 1; i > -1; i--)
	{
		bn += bs[i] * pow(2, j);
		j++;
	}
	return bn;
}

int* HashTable::generateSalt()
{
	int* a = new int[k];	// salt
	int b = pow(2, w);		// base
	int n;
	srand(time(NULL));
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 eng(rd()); // seed the generator
	std::uniform_int_distribution<> distr(0, b - 1); // define the range

	//srand((int)time(0));

	for (int i = 0; i < k; i++)
	{
		a[i] = distr(eng);
		//a[i] = (rand() % k);
	}
	return a;
}

int HashTable::scalarMult(int* x)
{
	int res = 0;
	for (int i = 0; i < k; i++)
	{
		res += a[i] * x[i];
	}
	return res;
}

int HashTable::multHash(string userId)
{
	int* num16 = char2num16(userId);
	int* bit96 = num162bit96(num16);
	int* x = bitSeqToDigitSeq(bit96);
	return scalarMult(x) % m;
}

int* HashTable::sieve(int n)
{
	int* arr = new int[n];
	for (int i = 0; i < n; i++)
	{
		arr[i] = 1;
	}
	for (int i = 2; i < sqrt(n); i++)
	{
		if (arr[i])
		{
			for (int j = 2*i; j < n; j += i)
			{
				arr[j] = 0;
			}
		}
	}
	return arr;
}

int HashTable::nextPrime()
{
	int r = ceil(pow(pow(2, w+1), float(1) / float(3))) - 1;
	int pMax = pow(r + 2, 3);
	int* primes = sieve(pMax);
	int lowBound = pow(2, w + 1);
	int i = lowBound;
	while (!primes[i]) {
		i++;
	}
	return i;
}
#endif // HASHTABLE_H_INCLUDED
