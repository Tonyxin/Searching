#ifndef STATIC_SEARCH_TABLE_H
#define STATIC_SEARCH_TABLE_H

#include "Search_DataStruct.h"

//顺序查找
int Search_Seq(SStable ST, KeyType key);

//折半查找，只能查找有序表
int Search_Bin(SStable ST, KeyType key);

//次优查找树查找
int Search_SecTree(SStable ST, KeyType key);		//由次优查找树得到key在表中的位置
BiTree SecondOptimal(ElemType *R, float *sw, int low, int high);		//递归生成次优查找树
void FindSW(float *sw, SStable ST);						//计算累计权重值
int Compare_Tree(BiTree T, KeyType key);

#endif