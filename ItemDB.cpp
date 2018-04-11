#include "Database.h"
#define ID_COL 0
#define NAME_COL 1
#define BRAND_COL 2
#define PRICE_COL 3
#define NUM_COL 4

template <int row_len, int column_len>
ItemDB<row_len, column_len>::ItemDB() {}

template <int row_len, int column_len>
ItemDB<row_len, column_len>::ItemDB(
	string* names,
	Type* type_list,
	string db_path):
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
void ItemDB<row_len, column_len>::deleteItem(
	string _del_id)
{
	string del_num = "-1";
	for (int i = 0; i < __row_count; i++)
	{
		if (__base[i][ID_COL] == _del_id)
			__base[i][NUM_COL] = del_num;
	}
	return;
}

template <int row_len, int column_len>
void ItemDB<row_len, column_len>::searchItem(
	string target_name,
	string* _id_list)
{
	int count = 0;
	for (int i = 0; i < __row_count; i++)
		if (__base[i][NAME_COL] == target_name)
			_id_list[count++] = __base[i][ID_COL];
	return;
}

template <int row_len, int column_len>
void ItemDB<row_len, column_len>::addItem(
	string item[column_len - 1])
{
	string t_name = item[NAME_COL - 1];
	string t_brand = item[BRAND_COL - 1];
	string t_price = item[PRICE_COL - 1];
	string t_num = item[NUM_COL - 1];
	for (int i = 0; i < __row_count; i++)
	{
		bool nIsSame = (__base[i][NAME_COL] == t_name);
		bool bIsSame = (__base[i][BRAND_COL] == t_brand);
		bool pIsSame = (__base[i][PRICE_COL] == t_price);
		if (nIsSame && bIsSame && pIsSame)
		{
			int int_num = atoi(t_num.c_str());
			int base_int_num = atoi(__base[i][NUM_COL].c_str());
			if (base_int_num == -1)
				base_int_num = 0;
			char total_num[10] = { 0 };
			_itoa(int_num + base_int_num, total_num, 10);
			string total_str(total_num);
			__base[i][NUM_COL] = total_str;
			return;
		}
		//else if (nIsSame && bIsSame && !pIsSame)
		//{
		//	__base[__row_count][ID_COL] = __base[i][ID_COL];
		//	for (int j = 1; j < __column_max; j++)
		//		__base[__row_count][j] = item[j - 1];
		//	__row_count++;
		//	return;
		//}
	}
	string last_id = __base[__row_count - 1][ID_COL];
	__base[__row_count][ID_COL] = __next_id(last_id);
	for (int j = 1; j < __column_max; j++)
		__base[__row_count][j] = item[j - 1];
	__row_count++;
	return;
}

template <int row_len, int column_len>
void ItemDB<row_len, column_len>::setItem(
	string __target_id, 
	string _set_col, 
	string _set_value)
{
	int _col_posi = -1;
	for (int j = 0; j < __column_max; j++)
	{
		if (__names[j] == _set_col)
		{
			_col_posi = j;
			break;
		}
	}
	if (_col_posi == -1)
	{
		printf("ItemDB::setItem: Column %s is not found.\n",
			_set_col.c_str());
		return;
	}
	bool idFound = false;
	for (int i = 0; i < __row_count; i++)
	{
		if (__base[i][ID_COL] == __target_id)
		{
			__base[i][_col_posi] = _set_value;
			idFound = true;
			break;
		}
	}
	if(!idFound)
		printf("ItemDB::setItem: ID %s is not found.\n",
			__target_id.c_str());
	return;
}

template <int row_len, int column_len>
void ItemDB<row_len, column_len>::printDB()
{
	__print_row(__names);
	for (int i = 0; i < __row_count; i++)
	{
		int _item_num = atoi(__base[i][NUM_COL].c_str());
		if (_item_num <= 0)
			continue;
		__print_row(__base[i]);
	}
	return;
}

template <int row_len, int column_len>
void ItemDB<row_len, column_len>::printRows(
	string *_id_list)
{
	int list_count = 0;
	__print_row(__names);
	for (int i = 0; i < __row_count; i++)
	{
		if (__base[i][ID_COL] == _id_list[list_count])
		{
			__print_row(__base[i]);
			list_count++;
		}
		if (_id_list[list_count].empty())
			break;
	}
	return;
}

template <int row_len, int column_len>
void ItemDB<row_len, column_len>::Save()
{
	FILE *fp = fopen(__db_path.c_str(), "w");
	if (fp == NULL)
	{
		cerr << "ItemDB::ItemDB: Can not find file.\n";
		exit(-1);
	}
	string cache = "";
	string blank = " ";
	for (int j = 0; j < __column_max; j++)
	{
		cache += __names[j];
		cache += blank;
	}
	fprintf(fp, "%s\n", cache.c_str());
	cache.clear();

	for (int i = 0; i < __row_count; i++)
	{
		for (int j = 0; j < __column_max; j++)
		{
			cache += __base[i][j];
			cache += blank;
		}
		fprintf(fp, "%s\n", cache.c_str());
		cache.clear();
	}
	return;
}

template <int row_len, int column_len>
string ItemDB<row_len, column_len>::__next_id(
	string __id)
{
	string __next_id = "F";
	int __id_code = atoi(__id.substr(1, __id.size() - 1).c_str());
	__id_code++;

	char __code_char[10] = { 0 };
	_itoa(__id_code, __code_char, 10);

	string __code_str(__code_char);
	string __zero_str = "0";
	for (int i = 0; i < 4 - __code_str.size(); i++)
		__next_id += __zero_str;
	__next_id += __code_str;

	return __next_id;
}