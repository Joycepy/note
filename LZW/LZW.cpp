#include<string>
#include<iostream>
#include<fstream>
#include"hashChains.h"
#include"pairNode.h"

using namespace std;
typedef pair<const long,int> pairType;//pair.first=key,pair.second=code
ifstream in;
ofstream out;
const int DIVISOR = 4099;//散列函数的除数
int MASK1 = 255;//2^BTYE_SIZE-1
int MASK2 = 15;//2^EXCESS-1
const int EXCESS = 4;//12-BYTE_SIZE
const int BYTE_SIZE = 8;
bool bitsLeftOver = false;//false表示没有余下的位
int leftOver;//待输出的代码位
int ALPHA = 256;
const int MAX_CODES = 4096;//2^12
void setFiles(int argc, char* argv[])
{//建立输入和输出流
	char outputFile[50], inputFile[54];
	//检查是否有文件名
	if (argc >= 2)
		strcpy_s(inputFile, argv[1]);
	else
	{//没有文件名，要求提供文件名
		cout << "Enter name of file to compress" << endl;
		cin >> inputFile;
	}
	//打开二进制文件
	in.open(inputFile, ios::binary);
	if (in.fail())
	{
		cout << "Cannot open " << inputFile << endl;
		exit(1);
	}
	strcpy_s(outputFile, inputFile);
	strcat_s(outputFile, "zzz");
	out.open(outputFile, ios::binary);
}
void output(long pcode)
{//输出8位，把剩余位保存
	int c, d;
	if (bitsLeftOver)
	{//前面剩余的位
		d = int(pcode&MASK1);//右ByteSize位
		c = int((leftOver << EXCESS) | (pcode >> BYTE_SIZE));
		out.put(c);
		out.put(d);
		bitsLeftOver = false;
	}
	else
	{//前面没有剩余的位
		leftOver = pcode & MASK2;//右EXCSEE位
		c = int(pcode >> EXCESS);
		out.put(c);
		bitsLeftOver = true;
	}
}
void compress()
{//LZW压缩器
	//定义和初始化代码字典
	hashChains<long, int>h(DIVISOR);
	for (int i = 0; i < ALPHA; i++)
		h.insert(pairType(i, i));//differ from text
	int codeUsed = ALPHA;
	//输入和压缩
	int c = in.get();//输入文件的第一个字符
	if (c != EOF)
	{//输入文件不空
		long pcode = c;//前缀代码
		while ((c = in.get()) != EOF)
		{//处理字符c
			long theKey = (pcode << BYTE_SIZE) + c;//??????????????????????
			//检查关键字theKey的代码是否在字典中
			pairType* thePair = h.find(theKey);
			if (thePair == NULL)
			{//关键字theKey不在表中
				output(pcode);
				if (codeUsed < MAX_CODES)//建立新代码
					h.insert(pairType((pcode << BYTE_SIZE) | c, codeUsed++));
				pcode = c;
			}
			else
				pcode = thePair->second;//关键字theKey在表中
		}
		//输出最后的代码
		output(pcode);
		if (bitsLeftOver)
			out.put(leftOver << EXCESS);
	}
	out.close();
	in.close();
}
void main(int argc, char* argv[])
{
	setFiles(argc, argv);
	compress();
}
