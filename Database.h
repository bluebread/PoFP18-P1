#ifndef __DATABASE_H__
#define __DATABASE_H__
#include <string>
#include "Column.h"
using namespace std;

class Database
{
public:
private:
	int __column_count;
	int __row_count;
	Column *column_head;
};




#endif // !__DATABASE_H__
