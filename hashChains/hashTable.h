#pragma once
// hash table using linear open addressing and division
// implements dictionary methods other than erase

#ifndef hashTable_
#define hashTable_



#include <iostream>
#include "hash.h"  // mapping functions from K to nonnegative integer
#include "myExceptions.h"

using namespace std;

template<class K, class E>
class hashTable
{
public:
	hashTable(int theDivisor = 11);
	~hashTable() { delete[] table; }

	bool empty() const { return dSize == 0; }
	int size() const { return dSize; }
	pair<const K, E>* find(const K&) const;
	int find1(const K&) const;
	void insert(const pair<const K, E>&);
	void erase(const K&);
	void reBuild();
	void output(ostream& out) const;

protected:
	int search(const K&) const;
	pair<const K, E>** table;  // hash table
	bool* neverUsed;
	hash1<K> hash1;              // maps type K to nonnegative integer
	int dSize;                 // number of pairs in dictionary
	int divisor;               // hash function divisor
};

template<class K, class E>
hashTable<K, E>::hashTable(int theDivisor)
{
	divisor = theDivisor;
	dSize = 0;

	// allocate and initialize hash table array
	table = new pair<const K, E>*[divisor];
	neverUsed = new bool[divisor];
	for (int i = 0; i < divisor; i++)
	{
		neverUsed[i] = true;
		table[i] = NULL;
	}
}

template<class K, class E>
int hashTable<K, E>::search(const K& theKey) const
{// Search an open addressed hash table for a pair with key theKey.
 // Return location of matching pair if found, otherwise return
 // location where a pair with key theKey may be inserted
 // provided the hash table is not full.

	int i = (int)hash1(theKey) % divisor;  // home bucket
	int j = i;    // start at home bucket
	do
	{
		if (table[j] == NULL|| table[j]->first == theKey)
			return j;
		j = (j + 1) % divisor;  // next bucket
	} while (j != i);          // returned to home bucket?

	return j;  // table full
}

template<class K, class E>
pair<const K, E>* hashTable<K, E>::find(const K& theKey) const
{// Return pointer to matching pair.
 // Return NULL if no matching pair.
 // search the table
	int i = (int)hash1(theKey) % divisor; // home bucket
	int b = i;    // start at home bucket
	do
	{
		if ((!table[b] && neverUsed[b]) || (table[b]&&table[b]->first == theKey))
			break;
		b= (b + 1) % divisor;  // next bucket
	} while (b != i);          // returned to home bucket?
	
	// see if a match was found at table[b]
	if (table[b] == NULL ||(i==b&& table[b]->first != theKey))
		return NULL;           // no match

	return table[b];  // matching pair
}

template<class K, class E>
int hashTable<K, E>::find1(const K &theKey) const
{
	int i = (int)hash1(theKey) % divisor; // home bucket
	int b = i;    // start at home bucket
	do
	{
		if ((!table[b] && neverUsed[b]) || (table[b] && table[b]->first == theKey))
			break;
		b = (b + 1) % divisor;  // next bucket
	} while (b != i);          // returned to home bucket?

							   // see if a match was found at table[b]
	if (table[b] == NULL || (i == b && table[b]->first != theKey))
		return -1;           // no match

	return b;  // matching pair
}

template<class K, class E>
void hashTable<K, E>::insert(const pair<const K, E>& thePair)
{// Insert thePair into the dictionary. Overwrite existing
 // pair, if any, with same key.
 // Throw hashTableFull exception in case table is full.
 // search the table for a matching pair
	int b = search(thePair.first);

	// check if matching pair found
	if (table[b] == NULL)
	{
		// no matching pair and table not full
		table[b] = new pair<const K, E>(thePair);
		neverUsed[b] = false;
		dSize++;
	}
	else
	{// check if duplicate or table full
		if (table[b]->first == thePair.first)
		{// duplicate, change table[b]->second
			table[b]->second = thePair.second;
		}
		else // table is full
			throw hashTableFull();
	}
}

template<class K, class E>
void hashTable<K, E>::erase(const K &theKey)
{
	int b = find1(theKey);
	if (b==-1)
	{
		cout << "no found !" << endl;
		return;
	}
	else
	{
		if (table[b]->first == theKey)
		{
			table[b] = NULL;
			dSize--;
		}
		else
		{
			throw hashTableFull();
		}
	}
		reBuild();
}

template<class K, class E>
void hashTable<K, E>::reBuild()
{
	float total = 0, never = 0;
	for (int i = 0; i < divisor; i++)
		if (!table[i])
		{
			total++;
			if (!neverUsed[i])
				never++;
		}
	if (total == 0)
		return;
	else if (never/total < 0.6)
		return;
	//重新组织散列表
	for (int i = 0; i < divisor; i++)
	{//用过的空桶在总空桶数中比例超过0.6
		if (!table[i] && !neverUsed[i])
		{//从前往后依次处理用过的空桶
			for(int j=i+1;j!=i;j++)
			{
				if (table[j]&&((table[j]->first%divisor) == i))
				{//找到原应放在这一位置的值
					int key = table[j]->first;
					int value = table[j]->second;
					table[i] = new pair<const K, E>(key,value);
					table[j] = NULL;
				}
				j = j % divisor;
			}
		}
	}
	for (int i = 0; i < divisor; i++)
	{
		if (!table[i])
			neverUsed[i] = true;
	}
}

template<class K, class E>
void hashTable<K, E>::output(ostream& out) const
{// Insert the hash table into the stream out.
	for (int i = 0; i < divisor; i++)
		if (table[i] == NULL)
			cout << "NULL" << endl;
		else
			cout << table[i]->first << " "
			<< table[i]->second << endl;
}

// overload <<
template <class K, class E>
ostream& operator<<(ostream& out, const hashTable<K, E>& x)
{
	x.output(out); return out;
}

#endif
