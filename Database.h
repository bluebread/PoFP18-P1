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
	Database& search();
	Database& print();
	Database& add();
	Database& del();
	Database& set();
private:
	int __column_count;
	int __row_count;
	Type *__type_list;
	string *__names;
	string __base[row_len][column_len];
};

//template <int row_len, int column_len>
//class AccountDB: public Database<row_len, column_len>
//{
//public:
//	AccountDB();
//	void Login();
//	void Sign();
//private:
//	int __user_count;
//};
//
//
//template <int row_len, int column_len>
//class ItemDB :public Database<row_len, column_len>
//{
//public:
//	void deleteItem();
//	void searchItem();
//	void addItem();
//	void setItem();
//	void printList();
//private:
//	int __item_count;
//};
//
//template <int row_len, int column_len>
//class SaleListDB : public Database<row_len, column_len>
//{
//public:
//	void addSaled();
//};

#endif // !__DATABASE_H__
