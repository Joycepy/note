#include"linkedStack.h"
void main()
{
	/*linkedStack<char> s;
	char x;
	delete_all<char>(s, x);*/

	linkedStack<char> s;
	char x;
	ifstream infile;
	char tmp;
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
	infile >> x;
	while (infile >> tmp)
	{
		i++;
		if (tmp == x)
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
	lastElement = k - 1;
	s.push('a' + lastElement);

	delete_all2<char>(s, x);

	system("pause");
}