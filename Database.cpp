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
Database<row_len, column_len>& Database<row_len, column_len>::search()
{
	return;
}

template <int row_len, int column_len>
Database<row_len, column_len>& Database<row_len, column_len>::print()
{
	return;
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
Database<row_len, column_len>& Database<row_len, column_len>::del()
{
	return;
}


template <int row_len, int column_len>
Database<row_len, column_len>& Database<row_len, column_len>::set()
{
	return;
}