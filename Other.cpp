#include "Other.h"
#include <iostream>
#define SAE_LEN 100
using namespace std;

//Print Menu
void __printMenu(string*, int, int);

void printBlank()
{
	cout << "\n";
	return;
}

void printStar()
{
	for (int i = 0; i < SAE_LEN; i++)
		cout << "*";
	cout << endl;
	return;
}

void printArr()
{
	for (int i = 0; i < SAE_LEN; i++)
		cout << "<";
	cout << endl; 
	return;
}

void printEqual()
{
	for (int i = 0; i < SAE_LEN; i++)
		cout << "=";
	cout << endl; 
return;
}

void printAdminMenu()
{
	const int commands_num = 6;
	string AdminCommands[commands_num] = {
		"註銷登錄",
		"查詢商品",
		"增加商品",
		"刪除商品",
		"修改商品數量",
		"售貨清單"
	};
	__printMenu(AdminCommands, commands_num, 4);
	return;
}

void printUserMenu()
{
	const int commands_num = 7;
	string UserCommands[commands_num] = {
		"註銷登錄",
		"查看商品",
		"商品搜索",
		"添加商品至購物車",
		"刪除購物車商品",
		"查看購物車",
		"結帳"
	};
	__printMenu(UserCommands, commands_num, 2);
	return;
}


void printAccountInMenu()
{
	const int commands_num = 4;
	string AccountInCommands[commands_num] = {
		"用戶登錄",
		"用戶註冊",
		"管理員登錄",
		"結束程序"
	};
	__printMenu(AccountInCommands, commands_num, 2);
	return;
}

void __printMenu(string* commands, int num, int blank_len)
{
	printEqual();
	for (int i = 0; i < num; i++)
	{
		printf("%d.%s", i, commands[i].c_str());
		for (int i = 0; i < blank_len; i++)
			printf(" ");
	}
	printf("\n");
	printEqual();
	return;
}
//END Print Menu

string gets_string()
{
	char __gets_char[100] = { 0 };
	gets_s(__gets_char);
	if (__gets_char[0] == '\0')
		gets_s(__gets_char);
	string output(__gets_char);
	return output;
}

char gets_char()
{
	string input = gets_string();
	if (input.length() > 1 || input.empty()) {
		return (char)0;
	}
	return input[0];
}


bool str_hasBlank(string str)
{
	for (int i = 0; i < str.length(); i++)
		if (str[i] == ' ')
			return true;
	return false;
}

void clean_garbage()
{
	string garbage = gets_string();
	return;
}