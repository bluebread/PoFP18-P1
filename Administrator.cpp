#include <iostream>
using namespace std;
#include "Account.h"
#include "Other.h"
#include "Database.cpp"
#include "AccountDB.cpp"
#include "ItemDB.cpp"
#include "SaleListDB.cpp"
#include "CartDB.cpp"

//Administrator::Administrator
Administrator::Administrator(
	string _id,
	string _pw):
	Account(_id, _pw){ }
//END Administrator::Administrator

//Administrator::browse
void Administrator::browse(
	ItemDB<ITEM_MAX_NUM, ITEM_COLUMNS>* ITEM_DATABASE)
{
	ITEM_DATABASE->printDB();
	return;
}
//END Administrator::browse

//Administrator::addItem()
void Administrator::addItem(
	string addItem_row[ITEM_COLUMNS - 1], 
	ItemDB<ITEM_MAX_NUM, ITEM_COLUMNS>* ITEM_DATABASE)
{	
	ITEM_DATABASE->addItem(addItem_row);
	return;
}
//END Administrator::addItem()

//void Administrator::delItem
void Administrator::delItem(
	string _del_id,
	ItemDB<ITEM_MAX_NUM, ITEM_COLUMNS>* ITEM_DATABASE)
{
	ITEM_DATABASE->deleteItem(_del_id);
	return;
}
//END void Administrator::delItem

//void Administrator::setItem
void Administrator::setItem(
	string __target_id,
	string _set_col,
	string _set_value,
	ItemDB<ITEM_MAX_NUM, ITEM_COLUMNS>* ITEM_DATABASE)
{
	ITEM_DATABASE->setItem(__target_id, _set_col, _set_value);
	return;
}
//END void Administrator::setItem

//void Administrator::printSaleList
void Administrator::printSaleList(
	SaleListDB<SALELIST_MAX_NUM, SALELIST_COLUMNS>* SALELIST_DATABASE)
{
	SALELIST_DATABASE->printList();
	return;
}
//END void Administrator::printSaleList