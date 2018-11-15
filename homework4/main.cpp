#include<iostream>
#include<fstream>
using namespace std;
//�ڵ�
class Node
{
public:
	int index;
	Node* next;
	Node(int index0 = 0) { index = index0;}
};
//����ѭ������
class Circle
{
public:
	Node * head=new Node(1);
	Circle(int n)
	{//�������Ѿ������n�ĺ�����
		head->next = head;
		Node *p,*q;
		q = head;
		for (int i = 2; i <= n; i++)
		{
			p = new Node(i);
			p->next = q->next;
			q->next = p;
			q = p;
		}
	}
	bool have_one()
	{
		if (head->next == head)
			return true;
		else
			return false;
	}
};
void Josephus1(int n,int m)
{//��ʽ������ʵ��
	int* a = new int[n+1];
	for (int i = 1; i <= n; i++)
		a[i] = i;
	int k=1;//���ڻص��ײ�
	int s = 0;//���ڼ���
	int num = n-1;
	while (num)
	{//�����ҳ�n-1����
		if (a[k] != 0)
			s++;
		if (s == m)
		{
			cout << a[k] << " ";
			a[k] = 0;
			s = 0;
			--num;
		}
		k++;
		if (k >n)
			k =1;
	}
	
	for (int i = 1; i <= n; i++)
		if (a[i])
			cout << a[i] << endl;

}
void Josephus2(int n,int m)
{//������ʵ��
	Circle circle(n);//��n���ڵ�ĵ���ѭ������
	Node* tmp;
	int i;
	while (!circle.have_one())
	{
		i = m-1;
		tmp = circle.head;
		while (--i)
		{
			tmp = tmp->next;
			//tmp->next��Ҫɾ���Ľڵ�
		}
		circle.head = tmp->next->next;//�ı���ʼλ��
		cout << tmp->next->index << " ";
		tmp->next = circle.head;
	}
	cout << circle.head->index << endl;
}
int main()
{
	ifstream infile;
	infile.open("E://����/input1.txt");
	if (infile.fail())
	{
		cout << "���ļ�ʧ�ܣ�" << endl;
		system("pause");
		return -1;
	}
	int n,m;
	if (!(infile >> n >> m))
	{
		cout << "�������ͳ���" << endl;
		system("pause");
		return -1;
	}
	infile.close();
	if (!(n >= 3 && n <= 100 && m >= 1 && m <= n))
	{
		cout << "WRONG" << endl;
		system("pause");
		return -1;
	}
	Josephus1(n,m);//��ʽ������ʵ��
	Josephus2(n,m);//������ʵ��
	cout << endl;
	system("pause");
	return 0;
}