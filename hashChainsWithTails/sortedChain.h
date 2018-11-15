#pragma once
// sorted chain, implements dictionary

#ifndef sortedChain_
#define sortedChain_



#include <iostream>
#include "dictionary.h"
#include "pairNode.h"

using namespace std;

pair<int, int> last = pair<int, int>(INT_MAX, 0);
template<class K, class E>
static pairNode<K, E>* lastNode= new pairNode<K, E>(last,NULL);

template<class K, class E>
class sortedChain : public dictionary<K, E>
{
public:
	sortedChain() { firstNode = lastNode<K,E>; dSize = 0; }
	~sortedChain();

	bool empty() const { return dSize == 0; }
	int size() const { return dSize; }
	pair<const K, E>* find(const K&) const;
	bool erase(const K&);
	void insert(const pair<const K, E>&);
	void output(ostream& out) const;

protected:
	pairNode<K, E>* firstNode;  // pointer to first node in chain
	int dSize;                 // number of elements in dictionary
};

template<class K, class E>
sortedChain<K, E>::~sortedChain()
{// Destructor.  Delete all nodes.
	while (firstNode != lastNode<K,E>)
	{// delete firstNode
		pairNode<K, E>* nextNode = firstNode->next;
		delete firstNode;
		firstNode = nextNode;
	}
}

template<class K, class E>
pair<const K, E>* sortedChain<K, E>::find(const K& theKey) const
{// Return pointer to matching pair.
 // Return NULL if no matching pair.
	pairNode<K, E>* currentNode = firstNode;

	// search for match with theKey
	while (currentNode->element.first != theKey)
		currentNode = currentNode->next;

	// verify match
	if (currentNode != lastNode<K, E> && currentNode->element.first == theKey)
		// yes, found match
		return &currentNode->element;

	// no match
	return NULL;
}

template<class K, class E>
void sortedChain<K, E>::insert(const pair<const K, E>& thePair)
{// Insert thePair into the dictionary. Overwrite existing
 // pair, if any, with same key.

	pairNode<K, E> *p = firstNode,
		*tp = NULL; // tp trails p

					// move tp so that thePair can be inserted after tp
	while (p->element.first < thePair.first)
	{
		tp = p;
		p = p->next;
	}

	// check if there is a matching pair
	if (p->element.first == thePair.first)
	{// replace old value
		p->element.second = thePair.second;
		return;
	}

	// no match, set up node for thePair
	pairNode<K, E> *newNode = new pairNode<K, E>(thePair, p);

	// insert newNode just after tp
	if (tp == NULL) firstNode = newNode;
	else tp->next = newNode;

	dSize++;
	return;
}

template<class K, class E>
bool sortedChain<K, E>::erase(const K& theKey)
{// Delete the pair, if any, whose key equals theKey.
	pairNode<K, E> *p = firstNode,
		*tp = NULL; // tp trails p

					// search for match with theKey
	while (p->element.first < theKey)
	{
		tp = p;
		p = p->next;
	}

	// verify match
	if (p->element.first == theKey)
	{// found a match
	 // remove p from the chain
		if (tp == NULL) firstNode = p->next;  // p is first node
		else tp->next = p->next;

		delete p;
		dSize--;
		return 1;
	}
	else 
	{
		cout << "No found !";
		return 0;
	}
}

template<class K, class E>
void sortedChain<K, E>::output(ostream& out) const
{// Insert the chain elements into the stream out.
	for (pairNode<K, E>* currentNode = firstNode;
		currentNode != lastNode<K,E>;
		currentNode = currentNode->next)
		out << currentNode->element.first << " "
		<< currentNode->element.second << "  ";
}

// overload <<
template <class K, class E>
ostream& operator<<(ostream& out, const sortedChain<K, E>& x)
{
	x.output(out); return out;
}

#endif

