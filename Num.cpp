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
/// ���ַ���תΪ list
/// </summary>
/// <param name="num">�ַ���</param>
/// <returns>list</returns>
list<int> Num::str2List(string num)
{
	list<int> numList;
	for (string::iterator it = num.begin(); it != num.end(); it++)
	{
		// ����Ӧ�ַ�תΪ���֣��洢�� list ��
		numList.push_back(*it - '0');
	}
	return numList;
}

/// <summary>
/// �� list תΪ�ַ���
/// </summary>
/// <param name="numList">list</param>
/// <returns>�ַ���</returns>
string Num::list2Str(list<int> numList)
{
	string str = "";
	for (list<int>::iterator it = numList.begin(); it != numList.end(); it++)
	{
		// ����Ӧ����תΪ�ַ����洢�� string ��
		str += *it + '0';
	}
	return str;
}

/// <summary>
/// ����ָ��ַ������ж�������ȥ��С���㡿
/// </summary>
void Num::subStr()
{
	// �ж�����
	if (numStr[0] == '-')
	{
		negative = true;
		numStr = numStr.substr(1);
	}
	// �ж�С��
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
/// ��� 0 ���в�λ���������
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
/// �Ƚ������ַ�����Ӧ���ֵĴ�С
/// </summary>
/// <param name="s1">�ַ���</param>
/// <param name="s2">�ַ���</param>
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
/// ɾ��ǰ�� 0
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
/// ����ͨ������ list ��ӣ���߸�����
/// </summary>
/// <param name="list1"></param>
/// <param name="list2"></param>
/// <returns></returns>
list<int> Num::add(list<int> list1, list<int> list2)
{
	list<int> res;
	list<int>::reverse_iterator it1, it2;
	// �Ƿ��н�λ
	// ������������У�����һλ
	bool is = false;
	// �������� list ĩλ��ӣ����ҿ�ʼ
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
	// �����Ƿ����û�б������ list
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
	// ������� list ͬʱ�������ˣ���Ҫ����ǰ��һλ
	if (is)
	{
		res.push_front(1);
	}
	// ɾ��ǰ�� 0
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
	// �ж���������С
	// ����������Ƚ�С�����Ȼ�Ǹ���
	// ���������������
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
	// ������������������
	// ����� 0 ��������ɾ��ǰ�� 0 ʱɾ�����������
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
	// ����һ�� list ��ڶ��� list �е�ÿһ������ˣ����� i + j ���λ��
	// ���ｫ�����𰸵ߵ�����λ�ڵ� 0 ���±�
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
	// ɾ��ǰ��0
	while (vec[vec.size() - 1] == 0)
	{
		vec.pop_back();
	}
	// �� vecort �ߵ����ָ���������˳��
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
	// �� + ��
	if (numStr[0] != '-' && num.numStr[0] == '-')
	{
		num.subStr();
		return *this - num;
	}
	// �� + ��
	else if (numStr[0] == '-' && num.numStr[0] != '-')
	{
		subStr();
		return num - *this;
	}
	// ����ͬ�ţ��������
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
		// ��������Ǹ��ţ�����������Ҳ���ϸ���
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
	// �� - ��
	if (numStr[0] != '-' && num.numStr[0] == '-')
	{
		num.subStr();
		return *this + num;
	}
	// �� - ��
	else if (numStr[0] == '-' && num.numStr[0] != '-')
	{
		negative = true;
		num.negative = true;
		subStr();
		return num + *this;
	}
	// �� - ��
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
	// ͬ��������Ÿ�
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
/// / �������˼·�ǲ��ϵ� -
/// ������Ȼ�ٶ���������ʱû���뵽��İ취
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
/// �� / �Ļ����� %
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
/// ����
/// </summary>
/// <returns></returns>
Num Num::operator++()
{
	*this = *this + Num("1");
	return *this;
}

/// <summary>
/// ++
/// ǰ��
/// </summary>
/// <param name=""></param>
/// <returns></returns>
Num Num::operator++(int)
{
	Num num(*this);
	*this = *this + Num("1");
	return num;
}