#ifndef STATIC_SEARCH_TABLE_H
#define STATIC_SEARCH_TABLE_H

#include "Search_DataStruct.h"

//˳�����
int Search_Seq(SStable ST, KeyType key);

//�۰���ң�ֻ�ܲ��������
int Search_Bin(SStable ST, KeyType key);

//���Ų���������
int Search_SecTree(SStable ST, KeyType key);		//�ɴ��Ų������õ�key�ڱ��е�λ��
BiTree SecondOptimal(ElemType *R, float *sw, int low, int high);		//�ݹ����ɴ��Ų�����
void FindSW(float *sw, SStable ST);						//�����ۼ�Ȩ��ֵ
int Compare_Tree(BiTree T, KeyType key);

#endif