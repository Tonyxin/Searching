#ifndef SEARCH_DATASTRUCT_H
#define SEARCH_DATASTRUCT_H

#include <math.h>
#include <string.h>

enum Status{ Sucess = 1, Error = 0 };
enum deplth{ LH = 1, EH = 0, RH = -1 };			//LE��ʾ��������ȱ���������ȶ�2

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

//ƽ��������Ĵ洢�ṹ
typedef struct BSTNode
{
	ElemType data;		//�ڵ�����
	deplth bf;				//ƽ������
	struct BSTNode *lchild, *rchild;		//��������
}BSTNode, *BSTtree;

//�ȽϺ�������ߴ󣬷���1��һ���󣬷���0���ұߴ󣬷���-1
int Compare(int, int);
int Compare(float, float);
int Compare(char*, char*);

#endif