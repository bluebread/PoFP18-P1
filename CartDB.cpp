#include "Database.h"
#include "Other.h"

#define ID_COL 0
#define NAME_COL 1
#define BRAND_COL 2
#define PRICE_COL 3
#define NUM_COL 4

template <int row_len, int column_len>
CartDB<row_len, column_len>::CartDB() {}


template <int row_len, int column_len>
CartDB<row_len, column_len>::CartDB(
	string* names,
	Type* type_list,
	string db_path,
	string user_name) :
	Database(names, type_list),
	__db_path(db_path),
	__user_name(user_name)
{
	FILE *fp = fopen(__db_path.c_str(), "r");
	if (fp == NULL)
	{
		cerr << "CartDB::CartDB: Can not find file.\n";
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
void CartDB<row_len, column_len>::addItem(
	string id, 
	string num_str,
	ItemDB<ITEM_MAX_NUM, ITEM_COLUMNS> *ITEMS_DATABASE)
{
	for (int i = 0; i < __row_count; i++)
	{
		if (__base[i][ID_COL] == id)
		{
			int num1 = atoi(num_str.c_str());
			int num2 = atoi(__base[i][NUM_COL].c_str());
			if (num2 < 0)
				num2 = 0;
			char cache[10] = { 0 };
			_itoa(num1 + num2, cache, 10);
			string new_num(cache);
			__base[i][NUM_COL] = new_num;
			return;
		}
	}
	int id_code = atoi(id.substr(1, id.length() - 1).c_str());
	__base[__row_count][ID_COL] = id;
	__base[__row_count][NUM_COL] = num_str;
	for (int j = 1; j < __column_max - 1; j++)
	{
		string col = __names[j];
		string content = ITEMS_DATABASE->get(id_code, col);
		__base[__row_count][j] = content;
	}
	__row_count++;
	return;
}

template <int row_len, int column_len>
void CartDB<row_len, column_len>::delItem(
	string id, 
	string num_str)
{
	for (int i = 0; i < __row_count; i++)
	{
		if (__base[i][ID_COL] == id)
		{
			int num1 = atoi(num_str.c_str());
			int num2 = atoi(__base[i][NUM_COL].c_str());
			if (num2 < 0)
				num2 = 0;
			char cache[10] = { 0 };
			_itoa(num2 - num1, cache, 10);
			string new_num(cache);
			__base[i][NUM_COL] = new_num;
			return;
		}
	}/*
	printf("CartDB::delItem: ID %s is not found.\n",
		id.c_str());*/
	return;
}

template <int row_len, int column_len>
void CartDB<row_len, column_len>::printCart()
{
	__print_row(__names);
	for (int i = 0; i < __row_count; i++)
	{
		int num = atoi(__base[i][NUM_COL].c_str());
		if (num <= 0)
			continue;
		__print_row(__base[i]);
	}
	return;
}

template <int row_len, int column_len>
void CartDB<row_len, column_len>::Settle(
	ItemDB<ITEM_MAX_NUM, ITEM_COLUMNS>* ITEMS_DATABASE,
	SaleListDB<SALELIST_MAX_NUM, SALELIST_COLUMNS>* SALELIST_DATABASE)
{
	int input = 0;
	float total = __total();
	printCart();
	printStar();
	printArr();
	printf("一共需要付款%.1f! 確認付款請按 1 , 取消請按 0 :", total);
	cin >> input;
	printArr();
	printStar();
	if (input == 1)
	{
		__itemDB_settle(ITEMS_DATABASE);
		__salelistDB_settle(SALELIST_DATABASE);
		__clear();
		cout << "付款成功!\n";
	}
	else if (input == 0)
		cout << "付款取消!\n";
	else
		cout << "操作失敗!\n";
	printStar();
	return;
}

template <int row_len, int column_len>
float CartDB<row_len, column_len>::__total()
{
	float result = 0;
	for (int i = 0; i < __row_count; i++)
	{
		float price = atof(__base[i][PRICE_COL].c_str());
		int num = atoi(__base[i][NUM_COL].c_str());
		if (num < 0)
			num = 0;
		result += price * num;
	}
	return result;
}

template <int row_len, int column_len>
void CartDB<row_len, column_len>::__itemDB_settle(
	ItemDB<ITEM_MAX_NUM, ITEM_COLUMNS>* ITEMS_DATABASE)
{
	const string NAME_NUM = __names[NUM_COL];
	for (int i = 0; i < __row_count; i++)
	{
		string id_str = __base[i][ID_COL];
		int id_code = atoi(
			id_str.substr(1, id_str.length() - 1).c_str());
		string idb_num_str = ITEMS_DATABASE->get(
			id_code, NAME_NUM);

		int cart_num = atoi(__base[i][NUM_COL].c_str());
		if (cart_num <= 0)
			continue;

		int idb_num = atoi(idb_num_str.c_str());
		char cache[10] = { 0 };
		_itoa(idb_num - cart_num, cache, 10);
		string result_str(cache);

		ITEMS_DATABASE->setItem(id_str, NAME_NUM, result_str);
	}
	return;
}


template <int row_len, int column_len>
void CartDB<row_len, column_len>::__salelistDB_settle(
	SaleListDB<SALELIST_MAX_NUM, SALELIST_COLUMNS>* SALELIST_DATABASE)
{
	for (int i = 0; i < __row_count; i++)
	{
		int cart_num = atoi(__base[i][NUM_COL].c_str());
		if (cart_num <= 0)
			continue;
		string saled[SALELIST_COLUMNS];
		for (int j = 0; j < __column_max; j++)
			saled[j] = __base[i][j];
		saled[SALELIST_COLUMNS - 1] = __user_name;
		SALELIST_DATABASE->addSaled(saled);
	}
	return;
}

template <int row_len, int column_len>
void CartDB<row_len, column_len>::__clear()
{
	string emptyStr = "";
	for (int i = 0; i < __row_count; i++)
		for (int j = 0; j < __column_max; j++)
			__base[i][j] = emptyStr;
	__row_count = 0;
	return;
}


template <int row_len, int column_len>
void CartDB<row_len, column_len>::Save()
{
	FILE *fp = fopen(__db_path.c_str(), "w");
	if (fp == NULL)
	{
		cerr << "CartDB::CartDB: Can not find file.\n";
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