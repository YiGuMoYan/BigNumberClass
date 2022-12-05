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
	// 小数点后位数
	int len = 0;
	// 是否为负数
	bool negative = false;

	Num();
	Num(string);
	~Num();

	// 获取数字字符串
	string getNumStr() {return numStr;}
	// 设置数字字符串
	void setNumStr(string num) { numStr = num;}

	// 获取数字 list 存储
	list<int> getNumList() { return numList; }
	// 设置数字 list 存储
	void setNumList(list<int> num) { numList = num; }

	// 将字符串转为 list
	list<int> str2List(string);
	// 将 list 转为字符串
	string list2Str(list<int>);

	// 整理分割字符串【判断正负，去除小数点】
	void subStr();
	// 填充 0 进行补位，方便计算
	void fillNum(Num&);
	// 比较两个字符串对应数字的大小
	bool compare(string, string);
	// 删除前置 0
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

