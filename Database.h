#ifndef __DATABASE_H__
#define __DATABASE_H__

#define ITEM_MAX_NUM 100
#define	ITEM_COLUMNS 5

#define SALELIST_MAX_NUM 2000
#define SALELIST_COLUMNS 6

#define ACCOUNT_MAX_NUM 20
#define ACCOUNT_COLUMNS 2

#define CART_MAX_NUM 100
#define CART_COLUMNS 5

#include <string>
using namespace std;

enum Type { INT_T, FLOAT_T, STRING_T };

template <int row_len, int column_len>
class Database
{
public:
	Database();
	Database(string*, Type*);
	string get(int, string);
	Database& print();
	Database& add(string[column_len]);
	Database& del(int);
	Database& set(string, int, string);
protected:
	int __col_name_posi(string);
	void __print_row(string*);
	int __column_max;
	int __row_max;
	int __row_count;
	Type *__type_list;
	string *__names;
	string __base[row_len][column_len];
};

template <int row_len, int column_len>
class AccountDB: public Database<row_len, column_len>
{
public:
	AccountDB();
	AccountDB(string*, Type*, string);
	//~AccountDB();
	bool Login(string, string);
	bool SignUp(string, string);
	void Save();
	void delItemFromAllUsers(string);
private:
	string __db_path;
};

template <int row_len, int column_len>
class ItemDB :public Database<row_len, column_len>
{
public:
	ItemDB();
	ItemDB(string*, Type*, string);
	void deleteItem(string);
	void searchItem(string, string*);
	void addItem(string[column_len - 1]);
	void setItem(string, string, string);
	void printDB();
	void printRows(string*);
	void Save();
private:
	string __next_id(string);
	string __db_path;
};

template <int row_len, int column_len>
class SaleListDB : public Database<row_len, column_len>
{
public:
	SaleListDB();
	SaleListDB(string*, Type*, string);
	void addSaled(string*);
	void printList();
	void Save();
private:
	void __sort();
	void __exchange(int, int);
	bool __id_front(string, string);
	bool __row_front(string*, string*);
	string __db_path;
};

template <int row_len, int column_len>
class CartDB :public Database<row_len, column_len>
{
public:
	CartDB();
	CartDB(string*, Type*, string, string);
	void addItem(string, string, ItemDB<ITEM_MAX_NUM, ITEM_COLUMNS>*);
	void delItem(string, string);
	void printCart();
	void Settle(ItemDB<ITEM_MAX_NUM, ITEM_COLUMNS>*, SaleListDB<SALELIST_MAX_NUM, SALELIST_COLUMNS>*);
	void Save();
private:
	void __clear();
	float __total();
	void __itemDB_settle(ItemDB<ITEM_MAX_NUM, ITEM_COLUMNS>*);
	void __salelistDB_settle(SaleListDB<SALELIST_MAX_NUM, SALELIST_COLUMNS>*);
	string __db_path;
	string __user_name;
};

#endif // !__DATABASE_H__
