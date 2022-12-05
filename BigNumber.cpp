#include <iostream>
#include <regex>
#include <Windows.h>
#include <cstring>
#include "Num.h"

using namespace std;

/// <summary>
/// 正则表达式匹配是否输入正确指令
/// </summary>
/// <param name="command">输入的指令</param>
/// <returns></returns>
bool isCommand(string command)
{
	regex re("[1-9]");
	return regex_match(command, re);
}

/// <summary>
/// 正则表达式匹配是否输入正确数字
/// </summary>
/// <param name="num">输入的数字</param>
/// <returns></returns>
bool isNum(string num)
{
	regex re("-[0-9]+(.[0-9]+)?|[0-9]+(.[0-9]+)?");
	return regex_match(num, re);
}

int main()
{
	string command;
	do
	{
		system("cls");
		cout << "大数类：" << endl;
		cout << "1.+" << endl;
		cout << "2.-" << endl;
		cout << "3.*" << endl;
		cout << "4./" << endl;
		cout << "5.>" << endl;
		cout << "6.>=" << endl;
		cout << "7.%" << endl;
		cout << "8.++(后置/前置)" << endl;
		cout << "9.退出" << endl;
		cout << "请输入命令序号：";
		cin >> command;
		// 指令错误
		if (!isCommand(command))
		{
			cout << "指令错误" << endl;
			system("pause");
			continue;
		}
		// 将字符串转为整形
		int num = atoi(command.c_str());
		string numStr1, numStr2;
		switch (num)
		{
		case 1:
		{
			system("cls");
			cout << "======  +  ======" << endl;
			cout << "请输入第一个数：";
			cin >> numStr1;
			cout << "请输入第二个数：";
			cin >> numStr2;
			if (!(isNum(numStr1) && isNum(numStr2)))
			{
				cout << "请输入正确数字" << endl;
				system("pause");
				continue;
			}
			Num num1(numStr1), num2(numStr2);
			Num res = num1 + num2;
			cout << numStr1 << " + " << numStr2 << " = " << res.getNumStr() << endl;
			system("pause");
			break;
		}
		case 2:
		{
			system("cls");
			cout << "======  -  ======" << endl;
			cout << "请输入第一个数：";
			cin >> numStr1;
			cout << "请输入第二个数：";
			cin >> numStr2;
			if (!(isNum(numStr1) && isNum(numStr2)))
			{
				cout << "请输入正确数字" << endl;
				system("pause");
				continue;
			}
			Num num1(numStr1), num2(numStr2);
			Num res = num1 - num2;
			cout << numStr1 << " - " << numStr2 << " = " << res.getNumStr() << endl;
			system("pause");
			break;
		}
		case 3:
		{
			system("cls");
			cout << "======  *  ======" << endl;
			cout << "请输入第一个数：";
			cin >> numStr1;
			cout << "请输入第二个数：";
			cin >> numStr2;
			if (!(isNum(numStr1) && isNum(numStr2)))
			{
				cout << "请输入正确数字" << endl;
				system("pause");
				continue;
			}
			Num num1(numStr1), num2(numStr2);
			Num res = num1 * num2;
			cout << numStr1 << " * " << numStr2 << " = " << res.getNumStr() << endl;
			system("pause");
			break;
		}
		case 4:
		{
			system("cls");
			cout << "======  /  ======" << endl;
			cout << "请输入第一个数：";
			cin >> numStr1;
			cout << "请输入第二个数：";
			cin >> numStr2;
			if (!(isNum(numStr1) && isNum(numStr2)))
			{
				cout << "请输入正确数字" << endl;
				system("pause");
				continue;
			}
			Num num1(numStr1), num2(numStr2);
			Num res = num1 / num2;
			cout << numStr1 << " / " << numStr2 << " = " << res.getNumStr() << endl;
			system("pause");
			break;
		}
		case 5:
		{
			system("cls");
			cout << "======  >  ======" << endl;
			cout << "请输入第一个数：";
			cin >> numStr1;
			cout << "请输入第二个数：";
			cin >> numStr2;
			if (!(isNum(numStr1) && isNum(numStr2)))
			{
				cout << "请输入正确数字" << endl;
				system("pause");
				continue;
			}
			Num num1(numStr1), num2(numStr2);
			bool res = num1 > num2;
			cout << numStr1 << " > " << numStr2 << " => " << res << endl;
			system("pause");
			break;
		}
		case 6:
		{
			system("cls");
			cout << "======  >=  ======" << endl;
			cout << "请输入第一个数：";
			cin >> numStr1;
			cout << "请输入第二个数：";
			cin >> numStr2;
			if (!(isNum(numStr1) && isNum(numStr2)))
			{
				cout << "请输入正确数字" << endl;
				system("pause");
				continue;
			}
			Num num1(numStr1), num2(numStr2);
			bool res = num1 >= num2;
			cout << numStr1 << " >= " << numStr2 << " => " << res << endl;
			system("pause");
			break;
		}
		case 7:
		{
			system("cls");
			cout << "======  %  ======" << endl;
			cout << "请输入第一个数：";
			cin >> numStr1;
			cout << "请输入第二个数：";
			cin >> numStr2;
			if (!(isNum(numStr1) && isNum(numStr2)))
			{
				cout << "请输入正确数字" << endl;
				system("pause");
				continue;
			}
			Num num1(numStr1), num2(numStr2);
			Num res = num1 % num2;
			cout << numStr1 << " % " << numStr2 << " = " << res.getNumStr() << endl;
			system("pause");
			break;
		}
		case 8:
		{
			system("cls");
			cout << "======  ++(后置)  ======" << endl;
			cout << "请输入一个数：";
			cin >> numStr1;
			if (!isNum(numStr1))
			{
				cout << "请输入正确数字" << endl;
				system("pause");
				continue;
			}
			Num num1(numStr1);
			num1++;
			cout << num1.getNumStr() << endl;
			system("pause");
			break;
		}
		}
	} while (command != "9");
	
	return 0;
}
