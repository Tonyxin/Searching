#ifndef DYNAMIC_SEARCH_TABLE_H
#define DYNAMIC_SEARCH_TABLE_H

#include "Search_DataStruct.h"

//动态建立二叉排序树
Status SearchBST(BiTree T, KeyType key, BiTree &f, BiTree &p);		//在现有的二叉排序树中寻找关键字
/*注意：当指针作为参数进行传递时，若函数中指针的指向会发生变化，则应采用引用方式*/
Status InsertBST(BiTree &T, ElemType e);			//向二叉排序树中插入节点
Status DeleteBST(BiTree &T, ElemType e);			//向二叉排序树中删除某一结点

//平衡二叉树
void L_Rotate(BSTtree &T);					//对以T为根节点的树实现左转
void R_Rotate(BSTtree &T);					//对以T为根节点的树实现右转
void LeftBalance(BSTtree &T);				//根节点出现+2，左转
void RightBalance(BSTtree &T);				//根节点出现-2，右转
Status InsertAVL(BSTtree &T, ElemType e, bool &taller);	//在平衡二叉树中插入节点

//B+树与B-树
Status SearchBTree(BTree T, KeyType key, Result &m_result);		//在B-树中寻找目标关键字
void SearchBNode(BTree T, KeyType key, Result &m_result);			//在B-树中的某一个节点寻找关键字
Status InsertBTree(BTree &Root, BTree T, KeyType key, int position, BTree T_right, BTree T_left);	//在B-树中插入一个节点
/*B-树的删除操作未检测其正确性*/
Status DeleteBTree(BTree &Root, BTree T, int position);					//Root为根节点，在节点T上删除关键字Key[position]
Status DeleteBT_LackKey(BTree &Root, BTree T, int position, int father_position);	//删除节点中一个关键字，但左右兄弟均没有足够关键字

//哈希表
Status SearchHash(HashTable hash_table, ElemType e, int &index);		//查找关键字
Status InsertHash(HashTable hash_table, ElemType e);			//插入关键字
Status DeleteHash(HashTable hash_table, ElemType e);			//删除关键字
#endif 