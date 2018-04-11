
#ifndef __USER_H__
#define __USER_H__
#include "Database.h"
#include <string>
using namespace std;

class Account
{
public:
	Account(string, string);
private:
	string __id;
	string __password;
};
//
//class User : public Account
//{
//public:
//	void exit();
//	void browse();
//	void search();
//	void addCart();
//	void delCart();
//	void printCart();
//	void settle();
//private:
//	string __cart[];
//};
//
//class Administrator : public Account
//{
//public:
//	void exit();
//	void browse();
//	void addItem();
//	void delItem();
//	void setItem();
//	void printSaleList();
//};
#endif // !__USER_H__
