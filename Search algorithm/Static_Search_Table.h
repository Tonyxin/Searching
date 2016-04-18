#ifndef STATIC_SEARCH_TABLE_H
#define STATIC_SEARCH_TABLE_H

#include <string.h>
#include <math.h>

enum Status{ Sucess = 1, Error = 0 };

//定义关键字的类型
//typedef float KeyType;			//关键字为浮点数
typedef int KeyType;					//关键字为整型
//typedef char* KeyType;			//关键字为字符串型


//元素类型，用一个结构体表示
typedef struct ElemType
{
	KeyType key;			//关键字域
	float weight;			//每个元素的权重
	int position;			//元素在表中的位置
	//…………				//元素的其他信息
}ElemType;

//静态表存储
typedef struct SStable 
{
	ElemType * elem;				//静态表存储空间基址，建表时按照实际长度，首位留空
	int length;							//静态表的实际长度（如果表中有10个有效元素，还有第0个留空，长度应为11）
}SStable;

//二叉树的二叉链表存储
typedef struct BiTNode
{
	ElemType data;					//节点数据
	struct BiTNode *lchild, *rchild;			//左右子树
}BiTNode, *BiTree;

//顺序查找
int Search_Seq(SStable ST, KeyType key);

//折半查找，只能查找有序表
int Search_Bin(SStable ST, KeyType key);

//次优查找树查找
int Search_SecTree(SStable ST, KeyType key);		//由次优查找树得到key在表中的位置
BiTree SecondOptimal(ElemType *R, float *sw, int low, int high);		//递归生成次优查找树
void FindSW(float *sw, SStable ST);						//计算累计权重值
int Compare_Tree(BiTree T, KeyType key);

//比较函数，左边大，返回1；一样大，返回0；右边大，返回-1
int Compare(int, int);
int Compare(float, float);
int Compare(char*, char*);

#endif