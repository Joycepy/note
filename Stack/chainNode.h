// chain node

#pragma once
#ifndef chainNode_
#define chainNode_

typedef char T;
struct chainNode
{
	// data members
	T element;
	chainNode *next;

	// methods
	chainNode() {}
	chainNode(const T& element)
	{
		this->element = element;
	}
	chainNode(const T& element, chainNode* next)
	{
		this->element = element;
		this->next = next;
	}
};

#endif
