#include <iostream>
#include "Database.h"
#include "Account.h"
#include "Database.cpp"
#include "AccountDB.cpp"
#include "ItemDB.cpp"
#include "SaleListDB.cpp"
#include "CartDB.cpp"

void test1()
{
	Type typetest[4] = { INT_T , FLOAT_T , INT_T , STRING_T };
	string natest[4] = {
		"ID",
		"種類",
		"數量",
		"廠商"
	};
	string row1[4] = { "F0001", "牛奶", "5", "林鳳營" };
	string row2[4] = { "F0002", "可樂", "4", "百事" };
	string row3[4] = { "F0003", "蘋果", "3", "隔壁水果攤" };
	string row4[4] = { "F0004", "果汁", "2", "超市" };
	string row5[4] = { "F0005", "美麗果", "1", "可口可樂" };
	Database<4, 4> testdb(natest, typetest);
	testdb.add(row1).add(row2).add(row3).add(row4);

	testdb.print();
	return;
}

void test2()
{

	Type typetest[4] = { INT_T , INT_T };
	string natest[4] = {
		"ID",
		"密碼"
	};
	string path = "用戶TEST.txt";
	AccountDB<20, 2> testadb(natest, typetest, path);

	//cout << testadb.Login("user1", "passworduser1") << endl
	//	<< testadb.Login("user2", "passworduser2") << endl
	//	<< testadb.Login("user4", "passworduser4") << endl
	//	<< testadb.Login("sdlfjsdl", "passworduser1") << endl
	//	<< testadb.Login("user1", "ldfkdlf") << endl;
	string new_id = "user5";
	string new_pw = "passworduser5";
	testadb.SignUp(new_id, new_pw);
	testadb.Save();
}

void test3()
{
	Type typetest[5] = {
		STRING_T,
		STRING_T,
		STRING_T,
		FLOAT_T,
		INT_T
	};
	string natest[5] = {
		"ID",
		"名稱",
		"品牌",
		"價格",
		"數量"
	};
	string path = "庫存.txt";
	ItemDB<100, 5> testidb(natest, typetest, path);

	//string testid = "F0001";
	//string coltest = "ulala";
	//string sett = "奶酸";
	//testidb.setItem(testid, coltest, sett);

	string testrow[4] = {
		"芒果",
		"隔壁水果攤",
		"12.0",
		"50"
	};
	testidb.addItem(testrow);

	testidb.deleteItem("F0008");

	string target = "酸奶";
	string* id_list = new string[1000];
	testidb.searchItem(target, id_list);

	testidb.printDB();

	cout << "---------------" << endl;

	testidb.printRows(id_list);

	testidb.Save();
}

void test4()
{
	Type typetest[6] = {
		STRING_T,
		STRING_T,
		STRING_T,
		FLOAT_T,
		INT_T,
		STRING_T
	};
	string natest[6] = {
		"ID",
		"名稱",
		"品牌",
		"價格",
		"數量",
		"用戶名"
	};
	string path = "已售清單.txt";
	SaleListDB<2000, 6> testsldb(natest, typetest, path);

	string addtest[6] = {
		"F0012",
		"奶油",
		"ULALA迷路帖",
		"130.8",
		"7",
		"user2"
	};
	testsldb.addSaled(addtest);

	testsldb.printList();
	testsldb.Save();
}

void test5()
{
	Type sltypetest[6] = {
		STRING_T,
		STRING_T,
		STRING_T,
		FLOAT_T,
		INT_T,
		STRING_T
	};
	string slnatest[6] = {
		"ID",
		"名稱",
		"品牌",
		"價格",
		"數量",
		"用戶名"
	};
	string slpath = "已售清單.txt";
	SaleListDB<2000, 6> testsldb(slnatest, sltypetest, slpath);

	Type typetest[5] = {
		STRING_T,
		STRING_T,
		STRING_T,
		FLOAT_T,
		INT_T
	};
	string natest[5] = {
		"ID",
		"名稱",
		"品牌",
		"價格",
		"數量"
	};
	string cpath = "user2.txt";
	string user_name = "user2";
	CartDB<20, 5> testcdb(natest, typetest, cpath, user_name);

	string ipath = "庫存.txt";
	ItemDB<100, 5> testidb(natest, typetest, ipath);

	string testid = "F0007";
	string tesn = "2";
	//testcdb.addItem(testid, tesn, &testidb);

	testcdb.printCart();

	testcdb.delItem(testid, tesn);

	cout << "------------\n";
	testcdb.printCart();

	//testcdb.Settle(&testidb, &testsldb);

	testcdb.Save();
}

void test6()
{
	Type sltypetest[6] = {
		STRING_T,
		STRING_T,
		STRING_T,
		FLOAT_T,
		INT_T,
		STRING_T
	};
	string slnatest[6] = {
		"ID",
		"名稱",
		"品牌",
		"價格",
		"數量",
		"用戶名"
	};
	string slpath = "已售清單.txt";
	SaleListDB<2000, 6> testsldb(slnatest, sltypetest, slpath);

	Type typetest[5] = {
		STRING_T,
		STRING_T,
		STRING_T,
		FLOAT_T,
		INT_T
	};
	string natest[5] = {
		"ID",
		"名稱",
		"品牌",
		"價格",
		"數量"
	};
	string user_name = "user2";
	string user_pw = "user2password";
	User USER2(user_name, user_pw);

	string ipath = "庫存.txt";
	ItemDB<100, 5> testidb(natest, typetest, ipath);

	//USER2.browse(&testidb);

	//string search_item = "酸奶";
	//USER2.search(search_item, &testidb);

	//string addId = "F0002";
	//string num_str = "2";
	//USER2.addCart(addId, num_str, &testidb);

	//USER2.printCart();

	USER2.settle(&testidb, &testsldb);
	USER2.Exit();
}