#include <iostream>
#include "Account.h"
#include "Database.h"
#include "Other.h"
#include "Database.cpp"
#include "AccountDB.cpp"
#include "ItemDB.cpp"
#include "SaleListDB.cpp"
#include "CartDB.cpp"

#define ADMIN_ID "Admin"
#define ADMIN_PW  "admin"

int AdminOrUser; // -1 => Administrator, 1 => User, 0 => Login Failed

string AdminID = ADMIN_ID;
string AdminPW = ADMIN_PW;

Administrator ADMIN;
User USER;

ItemDB<ITEM_MAX_NUM, ITEM_COLUMNS> ITEM_DATABASE;
SaleListDB<SALELIST_MAX_NUM, SALELIST_COLUMNS> SALELIST_DATABASE;
AccountDB<ACCOUNT_MAX_NUM, ACCOUNT_COLUMNS> ACCOUNT_DATABASE;

void INIT();
bool ACCOUNT_IN();
bool CODE_INPUT(char*);
void CODE_EXECUTE(char);
void EXIT();

int main()
{
	INIT();
	while (ACCOUNT_IN())
	{
		if (!AdminOrUser)
			continue;
		char CODE;
		while (CODE_INPUT(&CODE))
		{
			CODE_EXECUTE(CODE);
		}
	}
	EXIT();
	return 0;
}

//void INIT
ItemDB<ITEM_MAX_NUM, ITEM_COLUMNS> __idb_init();
SaleListDB<SALELIST_MAX_NUM, SALELIST_COLUMNS> __sldb_init();
AccountDB<ACCOUNT_MAX_NUM, ACCOUNT_COLUMNS> __adb_init();

void INIT()
{
	ITEM_DATABASE = __idb_init();
	SALELIST_DATABASE = __sldb_init();
	ACCOUNT_DATABASE = __adb_init();
	return;
}
ItemDB<ITEM_MAX_NUM, ITEM_COLUMNS> __idb_init()
{
	Type types[ITEM_COLUMNS] = { STRING_T,STRING_T,STRING_T,FLOAT_T,INT_T	};
	string cols[ITEM_COLUMNS] = { "ID","名稱","品牌","價格","數量" };
	string path = "庫存.txt";
	ItemDB<ITEM_MAX_NUM, ITEM_COLUMNS> idb(cols, types, path);
	return idb;
}
SaleListDB<SALELIST_MAX_NUM, SALELIST_COLUMNS> __sldb_init()
{
	Type types[SALELIST_COLUMNS] = { STRING_T,STRING_T,STRING_T,FLOAT_T,INT_T,STRING_T };
	string cols[SALELIST_COLUMNS] = { "ID","名稱","品牌","價格","數量","用戶名" };
	string path = "已售清單.txt";
	SaleListDB<SALELIST_MAX_NUM, SALELIST_COLUMNS> sldb(cols, types, path);
	return sldb;
}
AccountDB<ACCOUNT_MAX_NUM, ACCOUNT_COLUMNS> __adb_init()
{
	Type types[ACCOUNT_COLUMNS] = { INT_T,INT_T };
	string cols[ACCOUNT_COLUMNS] = { "ID","密碼" };
	string path = "用戶TEST.txt";
	AccountDB<ACCOUNT_MAX_NUM, ACCOUNT_COLUMNS> adb(cols, types, path);
	return adb;
}
//END void INIT

// bool ACCOUNT_IN
void __clear_state();
char __get_account_command();
void __user_login();
void __user_register();
void __admin_login();
bool __admin_idpw_check(string, string);

bool ACCOUNT_IN()
{
	__clear_state();
	char account_command = __get_account_command();
	switch (account_command)
	{
	case '0': __user_login(); break;
	case '1': __user_register(); break;
	case '2': __admin_login(); break;
	case '3': return false;
	default:
		printBlank();
		cout << "請輸入合法操作!\n";
		printBlank();
		break;
	}
	return true;
}
void __clear_state()
{
	AdminOrUser = 0;
	string empty;
	User u; Administrator a;
	USER = u;
	ADMIN = a;
	return;
}

char __get_account_command()
{
	
	printAccountInMenu();
	cout << "輸入操作: ";
	char __acmd = gets_char();
	//cin >> __acmd;
	return __acmd;
}

void __user_login()
{
	cout << "輸入用戶名: ";
	string id = gets_string();
	//cin >> id;
	cout << "輸入密碼: ";
	string pw = gets_string();
	//cin >> pw;
	printStar();
	bool isValid = ACCOUNT_DATABASE.Login(id, pw);
	if (isValid)
	{
		cout << "登錄成功!\n";
		printStar();
		AdminOrUser = 1;
		User u(id, pw);
		USER = u;
	}
	else
	{
		cout << "登錄失敗!\n";
		printStar();
	}
	return;
}
void __user_register()
{
	const string shutdown_kw = "\\";
	cout << "輸入用戶名: ";
	string id = gets_string();
	cout << "輸入密碼: ";
	string pw = gets_string();
	printStar();

	bool failed1 = (id == shutdown_kw || pw == shutdown_kw);
	bool failed2 = (str_hasBlank(id) || str_hasBlank(pw));
	if (failed1 || failed2)
	{
		cout << "註冊失敗!(可能含有空白)\n";
		printStar();
		return;
	}
	bool isValid = ACCOUNT_DATABASE.SignUp(id, pw);
	if (!isValid)
	{
		cout << "註冊失敗!\n";
		printStar();
		return;
	}
	cout << "註冊成功!登錄成功\n";
	printStar();
	AdminOrUser = 1;
	User u(id, pw);
	USER = u;
	return;
}
void __admin_login()
{
	cout << "輸入管理員ID: ";
	string id = gets_string();
	cout << "輸入管理員密碼: ";
	string pw = gets_string();
	printStar();

	bool isValid = __admin_idpw_check(id, pw);
	if (isValid)
	{
		cout << "登錄成功!\n";
		printStar();
		AdminOrUser = -1;
		Administrator a(id, pw);
		ADMIN = a;
	}
	else
	{
		cout << "登錄失敗!\n";
		printStar();
	}
	return;
}
bool __admin_idpw_check(string id, string pw)
{
	return (id == AdminID) && (pw == AdminPW);
}
//END bool ACCOUNT_INT

// bool CODE_INPUT
bool CODE_INPUT(char* code)
{
	switch (AdminOrUser)
	{
	case 1: printUserMenu(); break;
	case -1: printAdminMenu(); break;
	default:
		return false;
	}
	cout << "輸入操作: ";
	*code = gets_char();
	//string garbage = gets_string();
	//*code = garbage[0];
	//if (garbage.length() > 1)
	//{
	//	*code = -1;
	//	return true;
	//}
	if (*code == '0' && AdminOrUser == 1)
	{
		USER.Exit();
		return false;
	}
	else if (*code == '0' && AdminOrUser == -1)
		return false;
	return true;
}
//END CODE_INPUT

//bool CODE_EXECUTE
void __User_command_execute(char);
void __browse();
void __search();
void __addItem();
void __delItem();
void __printCart();
void __settle();

void __Admin_command_execute(char);
void __adm_browse();
void __adm_addItem();
void __adm_delItem();
void __adm_setItemNum();
void __adm_printSaleList();

void CODE_EXECUTE(char code)
{
	if (AdminOrUser == 1)
		__User_command_execute(code);
	else if (AdminOrUser == -1)
		__Admin_command_execute(code);
	return;
}
// << void __User_command_execute
void __User_command_execute(char code)
{
	switch (code)
	{
	case '0': break;
	case '1': __browse(); break;
	case '2': __search(); break;
	case '3': __addItem(); break;
	case '4': __delItem(); break;
	case '5': __printCart(); break;
	case '6': __settle(); break;
	default:
		printBlank();
		cout << "請輸入合法操作!\n";
		printBlank();
		break;
	}
	return;
}
void __browse()
{
	printBlank();
	USER.browse(&ITEM_DATABASE);
	printBlank();
	return;
}
void __search()
{
	cout << "輸入商品名稱: ";
	string item_name = gets_string();
	printBlank();
	USER.search(item_name, &ITEM_DATABASE);
	printBlank();
	return;
}
void __addItem()
{
	string item_id, item_num;
	cout << "輸入商品ID和數量: ";
	cin >> item_id >> item_num;
	printBlank();
	USER.addCart(item_id, item_num, &ITEM_DATABASE);
	printBlank();
	return;
}
void __delItem()
{
	string item_id, item_num;
	cout << "輸入商品ID和數量: ";
	cin >> item_id >> item_num;
	printBlank();
	USER.delCart(item_id, item_num);
	printBlank();
	return;
}
void __printCart()
{
	printBlank();
	USER.printCart();
	printBlank();
	return;
}
void __settle()
{
	printBlank();
	USER.settle(&ITEM_DATABASE, &SALELIST_DATABASE);
	printBlank();
	return;
}
// >> END __User_command_execute

// << void __Admin_command_execute
void __Admin_command_execute(char code)
{
	switch (code)
	{
	case '0': break;
	case '1': __adm_browse(); break;
	case '2': __adm_addItem(); break;
	case '3': __adm_delItem(); break;
	case '4': __adm_setItemNum(); break;
	case '5': __adm_printSaleList(); break;
	default:
		printBlank();
		cout << "請輸入合法操作!\n";
		printBlank();
		break;
	}
	return;
	return;
}
void __adm_browse()
{
	printBlank();
	ADMIN.browse(&ITEM_DATABASE);
	printBlank();
	return;
}
void __adm_addItem()
{
	string item_row[ITEM_COLUMNS - 1];
	cout << "依序輸入商品名稱 品牌 價格 數量: ";
	for (int i = 0; i < ITEM_COLUMNS - 1; i++)
		cin >> item_row[i];
	printBlank();
	ADMIN.addItem(item_row, &ITEM_DATABASE);
	printBlank();
	return;
}
void __adm_delItem()
{
	cout << "輸入商品ID: ";
	string item_id = gets_string();
	//cin >> item_id;
	printBlank();
	ADMIN.delItem(item_id, &ITEM_DATABASE, &ACCOUNT_DATABASE);
	printBlank();
	return;
}
void __adm_setItemNum()
{
	string item_id, item_col, new_value;
	cout << "輸入商品ID與修改欄位: ";
	cin >> item_id >> item_col;

	cout << "輸入商品新資訊: ";
	cin >> new_value; 

	printBlank();
	ADMIN.setItem(item_id, item_col, new_value, &ITEM_DATABASE);
	printBlank();
	return;
}
void __adm_printSaleList()
{
	printBlank();
	ADMIN.printSaleList(&SALELIST_DATABASE);
	printBlank();
	return;
}
// >> END __Admin_command_execute

//END bool CODE_EXECUTE

// void EXIT()
void EXIT()
{
	ITEM_DATABASE.Save();
	SALELIST_DATABASE.Save();
	ACCOUNT_DATABASE.Save();
	return;
}
// END EXIT()
