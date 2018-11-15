#include<string>
#include<iostream>
#include<fstream>
#include"hashChains.h"
#include"pairNode.h"

using namespace std;
typedef pair<const long,int> pairType;//pair.first=key,pair.second=code
ifstream in;
ofstream out;
const int DIVISOR = 4099;//ɢ�к����ĳ���
int MASK1 = 255;//2^BTYE_SIZE-1
int MASK2 = 15;//2^EXCESS-1
const int EXCESS = 4;//12-BYTE_SIZE
const int BYTE_SIZE = 8;
bool bitsLeftOver = false;//false��ʾû�����µ�λ
int leftOver;//������Ĵ���λ
int ALPHA = 256;
const int MAX_CODES = 4096;//2^12
void setFiles(int argc, char* argv[])
{//��������������
	char outputFile[50], inputFile[54];
	//����Ƿ����ļ���
	if (argc >= 2)
		strcpy_s(inputFile, argv[1]);
	else
	{//û���ļ�����Ҫ���ṩ�ļ���
		cout << "Enter name of file to compress" << endl;
		cin >> inputFile;
	}
	//�򿪶������ļ�
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
{//���8λ����ʣ��λ����
	int c, d;
	if (bitsLeftOver)
	{//ǰ��ʣ���λ
		d = int(pcode&MASK1);//��ByteSizeλ
		c = int((leftOver << EXCESS) | (pcode >> BYTE_SIZE));
		out.put(c);
		out.put(d);
		bitsLeftOver = false;
	}
	else
	{//ǰ��û��ʣ���λ
		leftOver = pcode & MASK2;//��EXCSEEλ
		c = int(pcode >> EXCESS);
		out.put(c);
		bitsLeftOver = true;
	}
}
void compress()
{//LZWѹ����
	//����ͳ�ʼ�������ֵ�
	hashChains<long, int>h(DIVISOR);
	for (int i = 0; i < ALPHA; i++)
		h.insert(pairType(i, i));//differ from text
	int codeUsed = ALPHA;
	//�����ѹ��
	int c = in.get();//�����ļ��ĵ�һ���ַ�
	if (c != EOF)
	{//�����ļ�����
		long pcode = c;//ǰ׺����
		while ((c = in.get()) != EOF)
		{//�����ַ�c
			long theKey = (pcode << BYTE_SIZE) + c;//??????????????????????
			//���ؼ���theKey�Ĵ����Ƿ����ֵ���
			pairType* thePair = h.find(theKey);
			if (thePair == NULL)
			{//�ؼ���theKey���ڱ���
				output(pcode);
				if (codeUsed < MAX_CODES)//�����´���
					h.insert(pairType((pcode << BYTE_SIZE) | c, codeUsed++));
				pcode = c;
			}
			else
				pcode = thePair->second;//�ؼ���theKey�ڱ���
		}
		//������Ĵ���
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
