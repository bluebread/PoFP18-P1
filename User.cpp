#include <iostream>
using namespace std;
#include "Account.h"
#include "Other.h"
#include "Database.cpp"
#include "AccountDB.cpp"
#include "ItemDB.cpp"
#include "SaleListDB.cpp"
#include "CartDB.cpp"

//User::User
User::User(const string _id, const string _pw) :
	Account(_id, _pw)
{
	string __file_path = __id2filepath(_id);
	__CART_DATABASE = __CartDB_init(__file_path);
}

string User::__id2filepath(const string _id)
{
	string __file_extension = ".txt";
	return _id + __file_extension;
}

CartDB<CART_MAX_NUM, CART_COLUMNS> User::__CartDB_init(
	string __file_path)
{
	Type type_list[5] = {
		STRING_T,
		STRING_T,
		STRING_T,
		FLOAT_T,
		INT_T
	};
	string column_names[5] = {
		"ID",
		"名稱",
		"品牌",
		"價格",
		"數量"
	};
	CartDB<CART_MAX_NUM, CART_COLUMNS> cart(
		column_names,
		type_list,
		__file_path,
		__id);
	return cart;
}
//END User::User

//void User::browse
void User::browse(
	ItemDB<ITEM_MAX_NUM, ITEM_COLUMNS>* ITEM_DATABASE)
{
	ITEM_DATABASE->printDB();
	return;
}
//END User::browse

//void User::search
void User::search(
	string target_item, 
	ItemDB<ITEM_MAX_NUM, ITEM_COLUMNS>* ITEM_DATABASE)
{
	string id_list[ITEM_MAX_NUM];
	ITEM_DATABASE->searchItem(target_item, id_list);
	ITEM_DATABASE->printRows(id_list);
	return;
}
//END User::search

//void User::addCart
void User::addCart(
	string addID, 
	string num_str, 
	ItemDB<ITEM_MAX_NUM, ITEM_COLUMNS>* ITEM_DATABASE)
{
	__CART_DATABASE.addItem(addID, num_str, ITEM_DATABASE);
	__printAddSuccess();
	return;
}
void User::__printAddSuccess()
{
	printStar();
	cout << "已經加入購物車!\n";
	printStar();
	cout << "購物車中有:\n";
	printStar();
	__CART_DATABASE.printCart();
	printStar();
}
//END User::addCart

//void User::delCart
void User::delCart(string del_id, string num_str)
{
	__CART_DATABASE.delItem(del_id, num_str);
	return;
}
//END User::delCart

//void User::printCart
void User::printCart()
{
	__CART_DATABASE.printCart();
	return;
}
//END User::printCart

//void User::settle
void User::settle(
	ItemDB<ITEM_MAX_NUM, ITEM_COLUMNS>* ITEM_DATABASE,
	SaleListDB<SALELIST_MAX_NUM, SALELIST_COLUMNS>* SALELIST_DATABASE)
{
	__CART_DATABASE.Settle(ITEM_DATABASE, SALELIST_DATABASE);
	return;
}
//END void User::settle

//void User::Exit()
void User::Exit()
{
	__CART_DATABASE.Save();
	return;
}
//END User::Exit()