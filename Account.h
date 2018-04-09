#ifndef __ACCOUNT_H__
#define __ACCOUNT_H__
#include <string>
using namespace std;

class Account
{
public:
	Account();
private:
	string __id;
	string __password;
};

class User : public Account
{
public:
	void exit();
	void browse();
	void search();
	void addCart();
	void delCart();
	void printCart();
	void settle();
private:
	string __cart[];
};

class Administrator : public Account
{
public:
	void exit();
	void browse();
	void addItem();
	void delItem();
	void setItem();
	void printSaleList();
private:

};
#endif // !__ACCOUNT_H__
