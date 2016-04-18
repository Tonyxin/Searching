#ifndef STATIC_SEARCH_TABLE_H
#define STATIC_SEARCH_TABLE_H

#include <string.h>
#include <math.h>

enum Status{ Sucess = 1, Error = 0 };

//����ؼ��ֵ�����
//typedef float KeyType;			//�ؼ���Ϊ������
typedef int KeyType;					//�ؼ���Ϊ����
//typedef char* KeyType;			//�ؼ���Ϊ�ַ�����


//Ԫ�����ͣ���һ���ṹ���ʾ
typedef struct ElemType
{
	KeyType key;			//�ؼ�����
	float weight;			//ÿ��Ԫ�ص�Ȩ��
	int position;			//Ԫ���ڱ��е�λ��
	//��������				//Ԫ�ص�������Ϣ
}ElemType;

//��̬��洢
typedef struct SStable 
{
	ElemType * elem;				//��̬��洢�ռ��ַ������ʱ����ʵ�ʳ��ȣ���λ����
	int length;							//��̬���ʵ�ʳ��ȣ����������10����ЧԪ�أ����е�0�����գ�����ӦΪ11��
}SStable;

//�������Ķ�������洢
typedef struct BiTNode
{
	ElemType data;					//�ڵ�����
	struct BiTNode *lchild, *rchild;			//��������
}BiTNode, *BiTree;

//˳�����
int Search_Seq(SStable ST, KeyType key);

//�۰���ң�ֻ�ܲ��������
int Search_Bin(SStable ST, KeyType key);

//���Ų���������
int Search_SecTree(SStable ST, KeyType key);		//�ɴ��Ų������õ�key�ڱ��е�λ��
BiTree SecondOptimal(ElemType *R, float *sw, int low, int high);		//�ݹ����ɴ��Ų�����
void FindSW(float *sw, SStable ST);						//�����ۼ�Ȩ��ֵ
int Compare_Tree(BiTree T, KeyType key);

//�ȽϺ�������ߴ󣬷���1��һ���󣬷���0���ұߴ󣬷���-1
int Compare(int, int);
int Compare(float, float);
int Compare(char*, char*);

#endif