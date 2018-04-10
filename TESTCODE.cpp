#include <iostream>
#include "Database.h"
#include "Database.cpp"

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