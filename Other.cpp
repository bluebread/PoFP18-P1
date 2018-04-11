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
		"���P�n��",
		"�d�߰ӫ~",
		"�W�[�ӫ~",
		"�R���ӫ~",
		"�ק�ӫ~�ƶq",
		"��f�M��"
	};
	__printMenu(AdminCommands, commands_num, 4);
	return;
}

void printUserMenu()
{
	const int commands_num = 7;
	string UserCommands[commands_num] = {
		"���P�n��",
		"�d�ݰӫ~",
		"�ӫ~�j��",
		"�K�[�ӫ~���ʪ���",
		"�R���ʪ����ӫ~",
		"�d���ʪ���",
		"���b"
	};
	__printMenu(UserCommands, commands_num, 2);
	return;
}


void printAccountInMenu()
{
	const int commands_num = 4;
	string AccountInCommands[commands_num] = {
		"�Τ�n��",
		"�Τ���U",
		"�޲z���n��",
		"�����{��"
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