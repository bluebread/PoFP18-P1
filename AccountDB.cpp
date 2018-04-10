#include "Database.h"
#define ID_COL 0
#define PW_COL 1


template <int row_len, int column_len>
AccountDB<row_len, column_len>::AccountDB(
	string* names,
	Type* type_list,
	string db_path):
	Database(names, type_list),
	__db_path(db_path)
{
	FILE* fp = fopen(__db_path.c_str(), "r");
	if (fp == NULL)
	{
		cerr << "AccountDB::AccountDB: Can not find file.\n";
		exit(-1);
	}

	const int cache_len = 100;
	char garbage[cache_len] = { 0 };
	for (int k = 0; k < column_len; k++)
		fscanf(fp, "%s", garbage);

	while (!feof(fp))
	{
		for (int k = 0; k < column_len; k++)
		{
			char cache[cache_len] = { 0 };
			fscanf(fp, "%s", cache);
			string new_data(cache);
			__base[__row_count][k] = new_data;
		}
		if (__base[__row_count][0] != "")
			__row_count++;
	}
	fclose(fp);
}

//template <int row_len, int column_len>
//AccountDB<row_len, column_len>::~AccountDB()
//{
//	FILE *fp = fopen(__db_path.c_str(), "w");
//	if (fp == NULL)
//	{
//		cerr << "AccountDB::~AccountDB: Can not find file.\n";
//		exit(-1);
//	}
//	for (int i = 0; i < __row_count; i++)
//	{
//		string id = __base[i][ID_COL];
//		string pw = __base[i][PW_COL];
//		fprintf(fp, "%s %s\n", id.c_str(), pw.c_str());
//	}
//}

template <int row_len, int column_len>
bool AccountDB<row_len, column_len>::Login(
	string id,
	string pw)
{
	int idPosi = 0;
	while (idPosi < __row_count)
	{
		if (__base[idPosi][ID_COL] == id)
			break;
		idPosi++;
	}
	
	if (idPosi >= __row_count)
		return false;
	else if (__base[idPosi][PW_COL] != pw)
		return false;

	return true;
}

template <int row_len, int column_len>
void AccountDB<row_len, column_len>::SignUp(
	string new_id,
	string new_pw)
{
	if (__row_count >= __row_max)
	{
		cerr << "AccountDB::SignUp: Account Table is full.\n";
		return;
	}
	__base[__row_count][ID_COL] = new_id;
	__base[__row_count][PW_COL] = new_pw;

	__row_count++;
	return;
}

template <int row_len, int column_len>
void AccountDB<row_len, column_len>::Save()
{
	FILE *fp = fopen(__db_path.c_str(), "w");
	if (fp == NULL)
	{
		cerr << "AccountDB::~AccountDB: Can not find file.\n";
		exit(-1);
	}
	string title_output = "";
	for (int j = 0; j < __column_max; j++)
	{
		title_output += __names[j];
		title_output += " ";
	}
	fprintf(fp, "%s\n", title_output.c_str());
	for (int i = 0; i < __row_count; i++)
	{
		string id = __base[i][ID_COL];
		string pw = __base[i][PW_COL];
		fprintf(fp, "%s %s\n", id.c_str(), pw.c_str());
	}
}