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
	Database<4, 4> testdb(natest, typetest);

	return 0;
}