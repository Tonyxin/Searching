#ifndef DYNAMIC_SEARCH_TABLE_H
#define DYNAMIC_SEARCH_TABLE_H

#include "Search_DataStruct.h"

//动态建立二叉排序树
Status SearchBST(BiTree T, KeyType key, BiTree &f, BiTree &p);		//在现有的二叉排序树中寻找关键字
/*注意：当指针作为参数进行传递时，若函数中指针的指向会发生变化，则应采用引用方式*/
Status InsertBST(BiTree &T, ElemType e);				//向二叉排序树中插入节点
Status DeleteBST(BiTree &T, ElemType e);			//向二叉排序树中删除某一结点

//平衡二叉树
void L_Rotate(BSTtree &T);					//对以T为根节点的树实现左转
void R_Rotate(BSTtree &T);					//对以T为根节点的树实现右转
void LeftBalance(BSTtree &T);				//根节点出现+2，左转
void RightBalance(BSTtree &T);				//根节点出现-2，右转

Status InsertAVL(BSTtree &T, ElemType e, bool &taller);	//在平衡二叉树中插入节点
#endif 