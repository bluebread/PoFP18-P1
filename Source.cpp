#include <iostream>
#include "Database.h"
#include "Database.cpp"

int main()
{
	Type typetest[4] = { INT_T , FLOAT_T , INT_T , STRING_T };
	string natest[4] = {
		"ID",
		"種類",
		"數量",
		"廠商"
	};
	string row1[4] = { "F0001", "牛奶", "5", "林鳳營" };
	string row2[4] = { "F0002", "牛奶", "4", "林鳳營" };
	string row3[4] = { "F0003", "牛奶", "3", "林鳳營" };
	string row4[4] = { "F0004", "牛奶", "2", "林鳳營" };
	string row5[4] = { "F0005", "牛奶", "1", "林鳳營" };
	Database<4, 4> testdb(natest, typetest);
	testdb.add(row1).add(row2).add(row3).add(row4).add(row5);

	return 0;
}