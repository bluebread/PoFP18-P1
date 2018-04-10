#ifndef __DATABASE_H__
#define __DATABASE_H__
#include <string>
using namespace std;

enum Type { INT_T, FLOAT_T, STRING_T };


template <int row_len, int column_len>
class Database
{
public:
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
	AccountDB(string*, Type*, string);
	//~AccountDB();
	bool Login(string, string);
	void SignUp(string, string);
	void Save();
private:
	string __db_path;
};



template <int row_len, int column_len>
class ItemDB :public Database<row_len, column_len>
{
public:
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
	SaleListDB(string*, Type*, string);
	void addSaled(string*);
	void printList();
private:
	void __sort();
	void __exchange(int, int);
	bool __id_front(string, string);
	bool __row_front(string*, string*);
	string __db_path;
};

#endif // !__DATABASE_H__
