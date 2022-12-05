#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <string>

using namespace std;

class Num
{
private:
	string numStr;
	bool isDecimal;
	list<int> numList;
	

public:
	// С�����λ��
	int len = 0;
	// �Ƿ�Ϊ����
	bool negative = false;

	Num();
	Num(string);
	~Num();

	// ��ȡ�����ַ���
	string getNumStr() {return numStr;}
	// ���������ַ���
	void setNumStr(string num) { numStr = num;}

	// ��ȡ���� list �洢
	list<int> getNumList() { return numList; }
	// �������� list �洢
	void setNumList(list<int> num) { numList = num; }

	// ���ַ���תΪ list
	list<int> str2List(string);
	// �� list תΪ�ַ���
	string list2Str(list<int>);

	// ����ָ��ַ������ж�������ȥ��С���㡿
	void subStr();
	// ��� 0 ���в�λ���������
	void fillNum(Num&);
	// �Ƚ������ַ�����Ӧ���ֵĴ�С
	bool compare(string, string);
	// ɾ��ǰ�� 0
	void delFront(list<int>&);

	// +
	list<int> add(list<int>, list<int>);
	// -
	list<int> reduce(list<int>, list<int>);
	// *
	list<int> multiple(list<int>, list<int>);
	

	Num operator+(Num);
	Num operator-(Num);
	Num operator*(Num);
	Num operator/(Num);
	Num operator%(Num);
	bool operator>=(Num);
	bool operator>(Num);
	Num operator++();
	Num operator++(int);
};

