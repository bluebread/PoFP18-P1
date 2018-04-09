#include "Database.h"

template <int row_len, int column_len>
Database<row_len, column_len>::Database(
	string* names,
	Type* type_list):
	__column_count(column_len),
	__row_count(row_len),
	__type_list(type_list)
{ 
	__names = new string[column_len];
	for (int i = 0; i < column_len; i++)
	{
		__names[i] = names[i];
	}
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
Database<row_len, column_len>& Database<row_len, column_len>::add()
{
	return;
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