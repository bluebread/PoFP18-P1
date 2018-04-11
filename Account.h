
#ifndef __USER_H__
#define __USER_H__
#include "Database.h"
#include <string>
using namespace std;

class Account
{
public:
	Account();
	Account(string, string);
protected:
	string __id;
	string __password;
};

class User : public Account
{
public:
	User();
	User(string, string);
	void browse(ItemDB<ITEM_MAX_NUM, ITEM_COLUMNS>*);
	void search(string, ItemDB<ITEM_MAX_NUM, ITEM_COLUMNS>*);
	void addCart(string, string, ItemDB<ITEM_MAX_NUM, ITEM_COLUMNS>*);
	void delCart(string, string);
	void silentDelCart(string, string);
	void printCart();
	void settle(ItemDB<ITEM_MAX_NUM, ITEM_COLUMNS>*, SaleListDB<SALELIST_MAX_NUM, SALELIST_COLUMNS>*);
	void Exit();
private:
	CartDB<CART_MAX_NUM, CART_COLUMNS> __CART_DATABASE;
	CartDB<CART_MAX_NUM, CART_COLUMNS> __CartDB_init(string);
	void __printAddSuccess();
	void __printDelSuccess();
	string __id2filepath(string);
};

class Administrator : public Account
{
public:
	Administrator();
	Administrator(string, string);
	void browse(ItemDB<ITEM_MAX_NUM, ITEM_COLUMNS>*);
	void addItem(string[ITEM_COLUMNS - 1], ItemDB<ITEM_MAX_NUM, ITEM_COLUMNS>*);
	void delItem(string, ItemDB<ITEM_MAX_NUM, ITEM_COLUMNS>*, AccountDB<ACCOUNT_MAX_NUM, ACCOUNT_COLUMNS>*);
	void setItem(string, string, string, ItemDB<ITEM_MAX_NUM, ITEM_COLUMNS>*);
	void printSaleList(SaleListDB<SALELIST_MAX_NUM, SALELIST_COLUMNS>*);
};
#endif // !__USER_H__
