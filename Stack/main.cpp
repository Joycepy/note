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
	infile.open("E://桌面/input.txt");
	if (infile.fail())
	{
		cout << "打开文件失败！" << endl;
		system("pause");
		return;
	}
	infile >> x;
	while (infile >> tmp)
	{
		i++;
		if (tmp == x)
			a[j++] = i;//从栈底向上，第j个a的位置在第i个
		s.push(tmp);
	}
	if (s.empty())
	{
		cout << "栈中无字符！" << endl;
		return;
	}
	int k = 1;
	int lastElement = 0;//栈底最后一个不是a的位置
	while (a[k++] == k);
	lastElement = k - 1;
	s.push('a' + lastElement);

	delete_all2<char>(s, x);

	system("pause");
}