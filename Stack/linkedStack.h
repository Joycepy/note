#pragma once
// linked implementation of a stack
// derives from the ADT stack

#ifndef linkedStack_
#define linkedStack_

#include "stack.h"
#include "chainNode.h"
#include "myExceptions.h"
#include <sstream>
#include<iostream>
#include<fstream>

using namespace std;

template<class T>
class linkedStack : public stack<T>
{//����ջ
public:
	linkedStack(int initialCapacity = 10)
	{
		stackTop = NULL; stackSize = 0;
	}
	~linkedStack();
	bool empty() const
	{
		return stackSize == 0;
	}
	int size() const
	{
		return stackSize;
	}
	T& top()
	{
		if (stackSize == 0)
			throw stackEmpty();
		return stackTop->element;
	}
	void pop();
	void push(const T& theElement)
	{
		stackTop = new chainNode(theElement, stackTop);
		stackSize++;
	}
private:
	chainNode *stackTop;// pointer to stack top
	int stackSize;// number of elements in stack
};

template<class T>
linkedStack<T>::~linkedStack()
{// Destructor.
	while (stackTop != NULL)
	{// delete top node
		chainNode* nextNode = stackTop->next;
		delete stackTop;
		stackTop = nextNode;
	}
}

template<class T>
void linkedStack<T>::pop()
{// Delete top element.
	if (stackSize == 0)
		throw stackEmpty();

	chainNode* nextNode = stackTop->next;
	delete stackTop;
	stackTop = nextNode;
	stackSize--;
}
#endif
template <class T>
void delete_all(linkedStack<T> &s, const T &x)
{
	ifstream infile;
	char tmp,x0;
	linkedStack<T> t;
	int a[20];
	int i = 0, j = 1;
	infile.open("E://����/input.txt");
	if (infile.fail())
	{
		cout << "���ļ�ʧ�ܣ�" << endl;
		system("pause");
		return;
	}
	infile >> x0;
	while (infile >> tmp)
	{
		i++;
		if (tmp == x0)
			a[j++] = i;//��ջ�����ϣ���j��a��λ���ڵ�i��
		s.push(tmp);
	}
	if (s.empty())
	{
		cout << "ջ�����ַ���" << endl;
		return;
	}
	int k = 1;
	int lastElement = 0;//ջ�����һ������a��λ��
	while (a[k++] == k);
	lastElement = k-1;
	while (!s.empty())
	{
		tmp = s.top();

		if (tmp != x0)
		{
			if (s.size() == lastElement)
			{//���һ������aԪ�س�ջ�󣬻س�
				t.push(tmp);
				cout << tmp << endl;
				s.pop();
				//���ʣ���a
				while (!s.empty())
					s.pop();
			}
			else
			{
				t.push(tmp);
				cout << tmp << " ";
				s.pop();
			}
		}
		else
			s.pop();
	}
	cout << endl;
	while (!t.empty())
	{
		tmp = t.top();
		s.push(tmp);
		t.pop();
	}
}
template <class T>
void delete_all2(linkedStack<T> &s, const T &x) 
{
	int lastElement = s.top() - 'a';
	linkedStack<T> t;
	s.pop();
	T tmp;
	while (!s.empty())
	{
		tmp = s.top();

		if (tmp != x)
		{
			if (s.size() == lastElement)
			{//���һ������aԪ�س�ջ�󣬻س�
				t.push(tmp);
				cout << tmp << endl;
				s.pop();
				//���ʣ���a
				while (!s.empty())
					s.pop();
			}
			else
			{
				t.push(tmp);
				cout << tmp << " ";
				s.pop();
			}
		}
		else
			s.pop();
	}
	cout << endl;
	while (!t.empty())
	{
		tmp = t.top();
		s.push(tmp);
		t.pop();
	}
}