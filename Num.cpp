#include "Num.h"

Num::Num()
{

}

Num::Num(string num)
{
	numStr = num;
}

Num::~Num()
{

}

/// <summary>
/// 将字符串转为 list
/// </summary>
/// <param name="num">字符串</param>
/// <returns>list</returns>
list<int> Num::str2List(string num)
{
	list<int> numList;
	for (string::iterator it = num.begin(); it != num.end(); it++)
	{
		// 将对应字符转为数字，存储在 list 中
		numList.push_back(*it - '0');
	}
	return numList;
}

/// <summary>
/// 将 list 转为字符串
/// </summary>
/// <param name="numList">list</param>
/// <returns>字符串</returns>
string Num::list2Str(list<int> numList)
{
	string str = "";
	for (list<int>::iterator it = numList.begin(); it != numList.end(); it++)
	{
		// 将对应数字转为字符，存储在 string 中
		str += *it + '0';
	}
	return str;
}

/// <summary>
/// 整理分割字符串【判断正负，去除小数点】
/// </summary>
void Num::subStr()
{
	// 判断正负
	if (numStr[0] == '-')
	{
		negative = true;
		numStr = numStr.substr(1);
	}
	// 判断小数
	isDecimal = !(numStr.find('.') == numStr.npos);
	if (isDecimal)
	{
		int index = numStr.find('.');
		len = numStr.length() - index - 1;
		numStr = numStr.substr(0, index) + numStr.substr(index + 1);
	}
	numList = str2List(numStr);
}

/// <summary>
/// 填充 0 进行补位，方便计算
/// </summary>
/// <param name="num"></param>
void Num::fillNum(Num& num)
{
	if (len > num.len)
	{
		for (int i = 0; i < len - num.len; i++)
		{
			num.numList.push_back(0);
		}
	}
	else
	{
		for (int i = 0; i < num.len - len; i++)
		{
			numList.push_back(0);
		}
	}
}

/// <summary>
/// 比较两个字符串对应数字的大小
/// </summary>
/// <param name="s1">字符串</param>
/// <param name="s2">字符串</param>
/// <returns></returns>
bool Num::compare(string s1, string s2)
{
	if ((s1.length() < s2.length()) || (s1.length() == s2.length() && s1 < s2))
	{
		return false;
	}
	return true;
}

/// <summary>
/// 删除前置 0
/// </summary>
/// <param name="num"></param>
void Num::delFront(list<int>& num)
{
	while (!num.empty() && num.front() == 0)
	{
		num.pop_front();
	}
}

/// <summary>
/// +
/// 这里通过两个 list 相加，提高复用性
/// </summary>
/// <param name="list1"></param>
/// <param name="list2"></param>
/// <returns></returns>
list<int> Num::add(list<int> list1, list<int> list2)
{
	list<int> res;
	list<int>::reverse_iterator it1, it2;
	// 是否有进位
	// 在两个数相加中，最多进一位
	bool is = false;
	// 遍历两个 list 末位相加，从右开始
	for (it1 = list1.rbegin(), it2 = list2.rbegin(); it1 != list1.rend() && it2 != list2.rend();)
	{
		int num = *it1 + *it2;
		if (is)
		{
			num++;
			is = false;
		}
		if (num > 9)
		{
			num -= 10;
			is = true;
		}
		res.push_front(num);
		if (it1 != list1.rend())
		{
			it1++;
		}
		if (it2 != list2.rend())
		{
			it2++;
		}
	}
	// 查找是否存在没有遍历完的 list
	if (it1 != list1.rend())
	{
		for (; it1 != list1.rend(); it1++)
		{
			int num = *it1;
			if (is)
			{
				num++;
				is = false;
			}
			if (num > 9)
			{
				num -= 10;
				is = true;
			}
			res.push_front(num);
		}
	}
	if (it2 != list2.rend())
	{
		for (; it2 != list2.rend(); it2++)
		{
			int num = *it2;
			if (is)
			{
				num++;
				is = false;
			}
			if (num > 9)
			{
				num -= 10;
				is = true;
			}
			res.push_front(num);
		}
	}
	// 如果两个 list 同时遍历完了，需要再往前进一位
	if (is)
	{
		res.push_front(1);
	}
	// 删除前置 0
	delFront(res);
	return res;
}

/// <summary>
/// -
/// </summary>
/// <param name="list1"></param>
/// <param name="list2"></param>
/// <returns></returns>
list<int> Num::reduce(list<int> list1, list<int> list2)
{
	list<int> res;
	list<int>::reverse_iterator it1, it2;
	bool is = false;
	// 判断两个数大小
	// 如果被减数比较小，则必然是负数
	// 交换被减数与减数
	if (list1.size() < list2.size())
	{
		negative = true;
		return reduce(list2, list1);
	}
	else
	{
		for (it1 = list1.rbegin(), it2 = list2.rbegin(); it1 != list1.rend() && it2 != list2.rend(); it1++, it2++)
		{
			int num = *it1 - *it2;
			if (is)
			{
				num--;
				is = false;
			}
			if (num < 0)
			{
				num += 10;
				is = true;
			}
			res.push_front(num);
		}
		if (it1 != list1.rend())
		{
			for (; it1 != list1.rend(); it1++)
			{
				int num = *it1;
				if (is)
				{
					num--;
					is = false;
				}
				if (num < 0)
				{
					num += 10;
					is = true;
				}
				res.push_front(num);
			}
		}
		else
		{
			if (is)
			{
				negative = true;
				return reduce(list2, list1);
			}
		}
	}
	delFront(res);
	// 这种情况是两个数相等
	// 本身的 0 会在上面删除前置 0 时删除，这里加上
	if (res.empty())
	{
		res.push_back(0);
	}
	return res;
}

/// <summary>
/// *
/// </summary>
/// <param name="list1"></param>
/// <param name="list2"></param>
/// <returns></returns>
list<int> Num::multiple(list<int> list1, list<int> list2)
{
	vector<int> vec(list1.size() + list2.size());
	fill(vec.begin(), vec.end(), 0);
	list<int>::reverse_iterator it1, it2;
	int i = 0;
	// 将第一个 list 与第二个 list 中的每一个数相乘，加在 i + j 这个位置
	// 这里将整个答案颠倒，个位在第 0 个下标
	for (it1 = list1.rbegin(); it1 != list1.rend(); it1++)
	{
		int j = 0;
		for (it2 = list2.rbegin(); it2 != list2.rend(); it2++)
		{
			vec[i + j] += *it1 * (*it2);;
			j++;
		} 
		i++;
	}
	for (int i = 0; i < vec.size(); i++)
	{
		if (vec[i] > 9)
		{
			vec[i + 1] += vec[i] / 10;
			vec[i] %= 10;
		}
	}
	// 删除前置0
	while (vec[vec.size() - 1] == 0)
	{
		vec.pop_back();
	}
	// 将 vecort 颠倒，恢复成正常的顺序
	list<int> res;
	for (int i = vec.size() - 1; i >= 0; i--)
	{
		res.push_back(vec[i]);
	}
	delFront(res);
	return res;
}

Num Num::operator+(Num num)
{
	// 正 + 负
	if (numStr[0] != '-' && num.numStr[0] == '-')
	{
		num.subStr();
		return *this - num;
	}
	// 负 + 正
	else if (numStr[0] == '-' && num.numStr[0] != '-')
	{
		subStr();
		return num - *this;
	}
	// 两个同号，都是相加
	else
	{
		subStr();
		num.subStr();
		fillNum(num);
		Num res;
		res.setNumList(add(numList, num.getNumList()));
		string s = res.list2Str(res.getNumList());
		if (isDecimal || num.isDecimal)
		{
			int point = s.length() - (len > num.len ? len : num.len);
			s.insert(point, ".");
		}
		// 如果两个是负号，在这里给结果也加上负号
		if (negative && num.negative)
		{
			s = '-' + s;
		}
		res.setNumStr(s);
		return res;
	}
}

Num Num::operator-(Num num)
{
	// 正 - 负
	if (numStr[0] != '-' && num.numStr[0] == '-')
	{
		num.subStr();
		return *this + num;
	}
	// 负 - 正
	else if (numStr[0] == '-' && num.numStr[0] != '-')
	{
		negative = true;
		num.negative = true;
		subStr();
		return num + *this;
	}
	// 负 - 负
	else if (numStr[0] == '-' && num.numStr[0] == '-')
	{
		subStr();
		negative = false;
		num.subStr();
		num.negative = false;
		return num - *this;
	}
	else
	{
		subStr();
		num.subStr();
		fillNum(num);
		Num res;
		res.setNumList(reduce(numList, num.getNumList()));
		string s = res.list2Str(res.getNumList());
		if (isDecimal || num.isDecimal)
		{
			int point = s.length() - (len > num.len ? len : num.len);
			s.insert(point, ".");
		}
		if (negative)
		{
			s = '-' + s;
		}
		res.setNumStr(s);
		return res;
	}
}

/// <summary>
/// *
/// </summary>
/// <param name="num"></param>
/// <returns></returns>
Num Num::operator*(Num num)
{
	// 同号正，异号负
	bool nega = true;
	if ((numStr[0] == '-' && num.numStr[0] == '-') || (numStr[0] != '-' && num.numStr[0] != '-'))
	{
		nega = false;
	}
	subStr();
	num.subStr();
	Num res;
	string s = list2Str(multiple(numList, num.numList));
	if (isDecimal || num.isDecimal)
	{
		int point = s.length() - len - num.len;
		s.insert(point, ".");
	}
	if (nega)
	{
		s = '-' + s;
	}
	res.setNumStr(s);
	return res;
}

/// <summary>
/// /
/// / 我这里的思路是不断地 -
/// 这样虽然速度慢，但暂时没有想到别的办法
/// </summary>
/// <param name="num"></param>
/// <returns></returns>
Num Num::operator/(Num num)
{
	bool nega = true;
	if ((numStr[0] == '-' && num.numStr[0] == '-') || (numStr[0] != '-' && num.numStr[0] != '-'))
	{
		nega = false;
	}
	numStr = numStr.substr(0, numStr.find("."));
	num.setNumStr(num.getNumStr().substr(0, num.getNumStr().find(".")));
	int res = 0; 
	string nStr = numStr;
	while (compare(nStr, num.numStr))
	{
		nStr = list2Str(reduce(str2List(nStr), str2List(num.numStr)));
		res++;
	}
	return Num(to_string(res));
}

/// <summary>
/// %
/// 在 / 的基础上 %
/// </summary>
/// <param name="num"></param>
/// <returns></returns>
Num Num::operator%(Num num)
{
	bool nega = numStr[0] == '-';
	numStr = numStr.substr(0, numStr.find("."));
	num.setNumStr(num.getNumStr().substr(0, num.getNumStr().find(".")));
	string nStr = numStr;
	while (compare(nStr, num.numStr))
	{
		nStr = list2Str(reduce(str2List(nStr), str2List(num.numStr)));
	}
	return Num(nStr);
}

/// <summary>
/// >
/// </summary>
/// <param name="num"></param>
/// <returns></returns>
bool Num::operator>(Num num)
{
	if ((numStr.length() < num.getNumStr().length()) || (numStr.length() == num.getNumStr().length() && numStr <= num.getNumStr()))
	{
		return false;
	}
	return true;
}

/// <summary>
/// >=
/// </summary>
/// <param name="num"></param>
/// <returns></returns>
bool Num::operator>=(Num num)
{
	if ((numStr.length() < num.getNumStr().length()) || (numStr.length() == num.getNumStr().length() && numStr < num.getNumStr()))
	{
		return false;
	}
	return true;
}

/// <summary>
/// ++
/// 后置
/// </summary>
/// <returns></returns>
Num Num::operator++()
{
	*this = *this + Num("1");
	return *this;
}

/// <summary>
/// ++
/// 前置
/// </summary>
/// <param name=""></param>
/// <returns></returns>
Num Num::operator++(int)
{
	Num num(*this);
	*this = *this + Num("1");
	return num;
}