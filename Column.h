#ifndef __COLUMN_H__
#define __COLUMN_H__
#include <string>
using namespace std;

enum Type { INT_T, FLOAT_T, STRING_T };

template <class T, int size>
class Column
{
public:
	Column(Type, string);
	int length();
	string name();
	T get(int);
	int search(T);
	Column& add(T);
	Column& del(int);
	Column& insert(T, int);
	Column& set(int);
private:
	Type __type;
	T __items[size];
	int __len;
	string __name;
};



#endif // !__COLUMN_H__
