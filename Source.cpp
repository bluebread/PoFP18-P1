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
	string row2[4] = { "F0002", "�i��", "4", "�ʨ�" };
	string row3[4] = { "F0003", "ī�G", "3", "�j�����G�u" };
	string row4[4] = { "F0004", "�G��", "2", "�W��" };
	string row5[4] = { "F0005", "���R�G", "1", "�i�f�i��" };
	Database<4, 4> testdb(natest, typetest);
	testdb.add(row1).add(row2).add(row3).add(row4);

	testdb.print();
	return 0;
}