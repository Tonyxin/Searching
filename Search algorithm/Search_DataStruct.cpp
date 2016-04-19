#include "Search_DataStruct.h"

//比较函数，左边大，返回1；一样大，返回0；右边大，返回-1
int Compare(int i, int j)
{
	if (i > j)		return 1;
	else if (i == j)	return 0;
	else    return -1;
}
int Compare(float i, float j)
{
	if (i > j)		return 1;
	else if (i == j)	return 0;
	else    return -1;
}
int Compare(char* i, char* j)
{
	int tmp = strcmp(i, j);
	if (tmp > 0)		return 1;
	else if (tmp == 0)	return 0;
	else    return -1;
}