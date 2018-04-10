#include "Database.h"
#define ID_COL 0
#define NAME_COL 1
#define BRAND_COL 2
#define PRICE_COL 3
#define NUM_COL 4
#define USER_COL 5

template <int row_len, int column_len>
SaleListDB<row_len, column_len>::SaleListDB(
	string* names,
	Type* type_list,
	string db_path) :
	Database(names, type_list),
	__db_path(db_path)
{
	FILE *fp = fopen(__db_path.c_str(), "r");
	if (fp == NULL)
	{
		cerr << "ItemDB::ItemDB: Can not find file.\n";
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
		if (__base[__row_count][ID_COL] != "")
			__row_count++;
	}
	fclose(fp);
}

template <int row_len, int column_len>
void SaleListDB<row_len, column_len>::addSaled(
	string *item)
{
	if (__row_count >= __row_max)
	{
		cerr << "SaleListDB::addSaled: Table is full.\n";
		return;
	}
	for (int j = 0; j < __column_max; j++)
		__base[__row_count][j] = item[j];
	__row_count++;
	return;
}

template <int row_len, int column_len>
void SaleListDB<row_len, column_len>::printList()
{
	__sort();
	print();
	return;
}

template <int row_len, int column_len>
void SaleListDB<row_len, column_len>::__sort()
{
	for (int i = 0; i < __row_count; i++)
	{
		int front_posi = i;
		for (int k = i + 1; k < __row_count; k++)
			if (!__row_front(__base[front_posi], __base[k]))
				front_posi = k;
			//if (!__id_front(__base[front_posi][ID_COL], __base[k][ID_COL]))
			//	front_posi = k;
		__exchange(front_posi, i);
	}
	return;
}

template <int row_len, int column_len>
void SaleListDB<row_len, column_len>::__exchange(
	int x, 
	int y)
{
	string cache;
	for (int j = 0; j < __column_max; j++)
	{
		cache = __base[x][j];
		__base[x][j] = __base[y][j];
		__base[y][j] = cache;
	}
	return;
}

template <int row_len, int column_len>
bool SaleListDB<row_len, column_len>::__id_front(
	string _id_x,
	string _id_y)
{
	int x = atoi(_id_x.substr(1, _id_x.length() - 1).c_str());
	int y = atoi(_id_y.substr(1, _id_y.length() - 1).c_str());
	if (x < y)
		return true;
	else
		return false;
}

template <int row_len, int column_len>
bool SaleListDB<row_len, column_len>::__row_front(
	string* _row_x,
	string* _row_y)
{
	string x_id = _row_x[ID_COL];
	string y_id = _row_y[ID_COL];
	int x_id_code = atoi(x_id.substr(1, x_id.length() - 1).c_str());
	int y_id_code = atoi(y_id.substr(1, y_id.length() - 1).c_str());
	float x_price = atof(_row_x[PRICE_COL].c_str());
	float y_price = atof(_row_y[PRICE_COL].c_str());

	if (x_id_code < y_id_code)
		return true;
	else if (x_id_code == y_id_code && x_price < y_price)
		return true;
	else
		return false;
}