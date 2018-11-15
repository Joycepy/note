#include<iostream>
#include<fstream>
using namespace std;
//节点
class Node
{
public:
	int index;
	Node* next;
	Node(int index0 = 0) { index = index0;}
};
//单向循环链表
class Circle
{
public:
	Node * head=new Node(1);
	Circle(int n)
	{//主函数已经检验过n的合理性
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
{//公式化方法实现
	int* a = new int[n+1];
	for (int i = 1; i <= n; i++)
		a[i] = i;
	int k=1;//用于回到首部
	int s = 0;//用于计数
	int num = n-1;
	while (num)
	{//依次找出n-1个人
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
{//链表方法实现
	Circle circle(n);//有n个节点的单向循环链表
	Node* tmp;
	int i;
	while (!circle.have_one())
	{
		i = m-1;
		tmp = circle.head;
		while (--i)
		{
			tmp = tmp->next;
			//tmp->next是要删除的节点
		}
		circle.head = tmp->next->next;//改变起始位置
		cout << tmp->next->index << " ";
		tmp->next = circle.head;
	}
	cout << circle.head->index << endl;
}
int main()
{
	ifstream infile;
	infile.open("E://桌面/input1.txt");
	if (infile.fail())
	{
		cout << "打开文件失败！" << endl;
		system("pause");
		return -1;
	}
	int n,m;
	if (!(infile >> n >> m))
	{
		cout << "数据类型出错！" << endl;
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
	Josephus1(n,m);//公式化方法实现
	Josephus2(n,m);//链表方法实现
	cout << endl;
	system("pause");
	return 0;
}