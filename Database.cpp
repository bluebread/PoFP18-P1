#include "Database.h"

template <int row_len, int column_len>
Database<row_len, column_len>::Database(
	string* names,
	Type* type_list):
	__column_max(column_len),
	__row_max(row_len),
	__row_count(0),
	__type_list(type_list)
{ 
	__names = new string[column_len];
	for (int j = 0; j < column_len; j++)
		__names[j] = names[j];
}

template <int row_len, int column_len>
string Database<row_len, column_len>::get(int row_posi, string col_name)
{
	string emptyStr = "";
	int col_posi = __col_name_posi(col_name);
	bool colNotExist = (col_posi == -1);
	bool isRowCrossing = (row_posi < 0 || row_posi >= __row_count);
	//bool isColCrossing = (col_posi < 0 || col_posi >= __column_max);
	if (isRowCrossing || colNotExist)
	{
		cerr << "Database::get: Array crossing.\n";
		return emptyStr;
	}
	return __base[row_posi][col_posi];
}

template <int row_len, int column_len>
void Database<row_len, column_len>::__print_row(
	string* output_row)
{
	const int blank_num = 12;
	string blank = " ";
	for (int j = 0; j < __column_max; j++)
	{
		string str = output_row[j];
		int blank_len = blank_num - str.size();
		cout << str;
		for (int k = 0; k < blank_len; k++)
			cout << blank;
	}
	cout << endl;
	return;
}

template <int row_len, int column_len>
Database<row_len, column_len>& Database<row_len, column_len>::print()
{
	//const int blank_num = 8;
	//string blank = " ";
	__print_row(__names);
	//for (int j = 0; j < __column_max; j++)
	//{
	//	string str = __names[j];
	//	int blank_len = blank_num - str.size();
	//	for (int k = 0; k < blank_len; k++)
	//		cout << blank;
	//	cout << endl;
	//}
	for (int i = 0; i < __row_count; i++)
	{
		__print_row(__base[i]);
		//for (int j = 0; j < __column_max; j++)
		//{
		//	string str = __base[i][j];
		//	int blank_len = blank_num - str.size();
		//}
	}
	return *this;
}


template <int row_len, int column_len>
Database<row_len, column_len>& Database<row_len, column_len>::add(
	string row[column_len])
{
	if (__row_count >= __row_max)
	{
		cerr << "Database::add: Table is full.\n";
		return *this;
	}
	for (int j = 0; j < __column_max; j++)
		__base[__row_count][j] = row[j];
	__row_count++;

	return *this;
}


template <int row_len, int column_len>
Database<row_len, column_len>& Database<row_len, column_len>::del(
	int posi)
{
	string emptyStr = "";
	if (posi >= __row_count || posi < 0)
	{
		cerr << "Database::del: Array crossing.\n";
		return *this;
	}
	for (int i = posi; i < __row_count - 1; i++)
	{
		for (int j = 0; j < __column_max; j++)
		{
			__base[i][j] = __base[i + 1][j];
		}
	}
	for (int j = 0; j < __column_max; j++)
		__base[__row_count - 1][j] = emptyStr;
	__row_count--;

	return *this;
}


template <int row_len, int column_len>
Database<row_len, column_len>& Database<row_len, column_len>::set(
	string column_name,
	int posi,
	string set_content)
{
	if (posi >= __row_count || posi < 0)
	{
		cerr << "Database::set: Row array crossing.\n";
		return *this;
	}

	int col_posi = this->__col_name_posi(column_name);
	if (col_posi == -1)
		return *this;
	//for (int j = 0; j < __column_max; j++)
	//{
	//	if (__names[j] == column_name)
	//	{
	//		col_posi = j;
	//		break;
	//	}
	//}

	//if (col_posi == -1)
	//{
	//	printf("Database::set: %s is not found.\n",
	//		column_name.c_str());
	//	return *this;
	//}

	__base[posi][col_posi] = set_content;
	return *this;
}

template <int row_len, int column_len>
int Database<row_len, column_len>::__col_name_posi(string column_name)
{
	int col_posi = -1;
	for (int j = 0; j < __column_max; j++)
	{
		if (__names[j] == column_name)
		{
			col_posi = j;
			break;
		}
	}	
	if (col_posi == -1)
		printf("Database::__col_name_posi: %s is not found.\n",
			column_name.c_str());
	return col_posi;
}