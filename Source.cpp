#include <iostream>
#include "Database.h"
#include "Database.cpp"

int main()
{
	Type typetest[4] = { INT_T , FLOAT_T , INT_T , STRING_T };
	string natest[4] = {
		"ID",
		"����",
		"�ƶq",
		"�t��"
	};
	string row1[4] = { "F0001", "����", "5", "�L����" };
	string row2[4] = { "F0002", "����", "4", "�L����" };
	string row3[4] = { "F0003", "����", "3", "�L����" };
	string row4[4] = { "F0004", "����", "2", "�L����" };
	string row5[4] = { "F0005", "����", "1", "�L����" };
	Database<4, 4> testdb(natest, typetest);
	testdb.add(row1).add(row2).add(row3).add(row4).add(row5);

	return 0;
}