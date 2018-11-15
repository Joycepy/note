//template<class K,class E>
//pair<const K, E>* sortedChain<K, E>::find(const K& theKey)const
//{
//	pairNode<K, E>* currentNode = firstNode;
//	while (currentNode != NULL && currentNode->element.first != theKey)	
//		currentNode = currentNode->next;
//	if (currentNode != NULL && currentNode->element.first == theKey)
//		return &currentNode->element;
//	return NULL;
//}
//template<class K,class E>
//void sortedChain<K, E>::insert(const pair<K, E>& thePair)
//{
//	pairNode<K, E> *p = firstNode, *tp = NULL;//tp trails p
//	while (p != NULL && p->element.first < thePair.first)
//	{
//		tp = p;
//		p = p->next;
//	}
//	if (p != NULL && p->element.first == thePair.first)
//	{
//		p->element.second = thePair.second;
//		return;
//	}
//	pairNode<K, E> *newNode = new pairNode<K, E>(thePair, p);
//	if (tp == NULL)
//		firstNode = newNode;
//	else
//		tp->next = newNode;
//	dSize++;
//	return;
//}
//template<class K,class E>
//void sortedChain<K, E>::erase(const K& theKey)
//{
//	pairNode<K, E> *p = firstNode, *tp = NULL;
//	while (p != NULL && p->element.first < theKey)
//	{
//		tp = p;
//		p = p->next;
//	}
//	if (p != NULL && p->element.first == theKey)
//	{
//		if (tp == NULL)
//			firstNode = p->next;
//		else
//			tp->next = p->next;
//		delete p;
//		dSize--;
//	}
//}
//#include<string>
#include<iostream>
#include<string>
using namespace std;

long threeToLong(string s)
{//����s.length()>=3
	//����ߵ��ַ�
	long answer = s.at(0);
	//����8λ��������һ���ַ�
	answer = (answer << 8) + s.at(1);
	//����8λ��������һ���ַ�
	return (answer << 8) + s.at(2);

}
int stringToInt(string s)
{
	int length = (int)s.length();
	int answer = 0;
	if (length % 2 == 1)
	{
		answer = s.at(length - 1);
		length--;
	}
	
	for (int i = 0; i < length; i+=2)
	{
		answer += s.at(i);
		answer = answer+((int)s.at(i + 1)<<8);
	}
	return answer < 0 ? -answer : answer;
}
void main()
{
	string s = "abc";
	string t = "abc";
	long b = threeToLong(t);
	int a;
	a= stringToInt(s);
	cout << a << endl;
	cout << b << endl;
	system("pause");
}
//ɢ�����ݳ�Ա
pair<const K, E>**table;//ɢ�б�
hash<K> hash;//������Kӳ�䵽һ��������
int dSize;//�ֵ������Ը���
int divisor;//ɢ�к�������

template<class K,class E>
hashTable<K, E>:; hashTable(int theDivisor)
{
	divisor = theDivisor;
	dSize = 0;
	table = new pair<const K, E>*[divisor];
	for (int i = 0; i < divisor; i++)
		table[i] = NULL;
}
template<class K,class E>
pair<const K, E>* find(const K&theKey)const
{
	return table[hash(theKey) % divisor].find(theKey);
}
void insert(const pair<const K, E>& thePair)
{
	int homeBucket = (int)hash(thePair.first) % divisor;
	int homeSize = table[homeBucket].size();
	table[homeBucket].insert(thePair);
	if (homeSize < table[homeBucket].size())
		dSize++;
}
void erase(const K& theKey>)
{
	table[hash(theKey) % divisor].erase(theKey);
}