// test hash table class
#include <iostream>
#include "hashTable.h"

using namespace std;

void main()
{
   hashTable<int, int> z(11);
   pair<int, int> p;

   // test insert
   p.first = 2; p.second = 10;
   z.insert(p);//----"2"
   p.first = 10; p.second = 50;
   z.insert(p);//----"10"
   p.first = 24; p.second = 120;
   z.insert(p);//----"2"----"3"
   p.first = 32; p.second = 160;
   z.insert(p);//----"10"----"0"
   p.first = 3; p.second = 15;
   z.insert(p);//----"3"----"4"
   p.first = 12; p.second = 60;
   z.insert(p);//----"1"
   cout << "The dictionary is " << endl << z << endl;
   cout << "Its size is " << z.size() << endl;

   // test find
   cout << "Element associated with 2 is " << z.find(2)->second << endl;
   cout << "Element associated with 10 is " << z.find(10)->second << endl;
   cout << "Element associated with 12 is " << z.find(12)->second << endl;

   cout << endl << "------------为测试neverUsed功能，将“key=2”位置清空，找key=24的值------------" << endl;
   z.erase(2);
   cout << "The dictionary is " << endl << z << endl;
   cout << "Its size is " << z.size() << endl;
   cout << "Element associated with 24 is " << z.find(24)->second << endl;

   system("pause");
}
