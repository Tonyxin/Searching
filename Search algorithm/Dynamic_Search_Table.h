#ifndef DYNAMIC_SEARCH_TABLE_H
#define DYNAMIC_SEARCH_TABLE_H

#include "Search_DataStruct.h"

//��̬��������������
Status SearchBST(BiTree T, KeyType key, BiTree &f, BiTree &p);		//�����еĶ�����������Ѱ�ҹؼ���
/*ע�⣺��ָ����Ϊ�������д���ʱ����������ָ���ָ��ᷢ���仯����Ӧ�������÷�ʽ*/
Status InsertBST(BiTree &T, ElemType e);			//������������в���ڵ�
Status DeleteBST(BiTree &T, ElemType e);			//�������������ɾ��ĳһ���

//ƽ�������
void L_Rotate(BSTtree &T);					//����TΪ���ڵ����ʵ����ת
void R_Rotate(BSTtree &T);					//����TΪ���ڵ����ʵ����ת
void LeftBalance(BSTtree &T);				//���ڵ����+2����ת
void RightBalance(BSTtree &T);				//���ڵ����-2����ת
Status InsertAVL(BSTtree &T, ElemType e, bool &taller);	//��ƽ��������в���ڵ�

//B+����B-��
Status SearchBTree(BTree T, KeyType key, Result &m_result);		//��B-����Ѱ��Ŀ��ؼ���
void SearchBNode(BTree T, KeyType key, Result &m_result);			//��B-���е�ĳһ���ڵ�Ѱ�ҹؼ���
Status InsertBTree(BTree &Root, BTree T, KeyType key, int position, BTree T_right, BTree T_left);	//��B-���в���һ���ڵ�
/*B-����ɾ������δ�������ȷ��*/
Status DeleteBTree(BTree &Root, BTree T, int position);					//RootΪ���ڵ㣬�ڽڵ�T��ɾ���ؼ���Key[position]
Status DeleteBT_LackKey(BTree &Root, BTree T, int position, int father_position);	//ɾ���ڵ���һ���ؼ��֣��������ֵܾ�û���㹻�ؼ���

//��ϣ��
Status SearchHash(HashTable hash_table, ElemType e, int &index);		//���ҹؼ���
Status InsertHash(HashTable hash_table, ElemType e);			//����ؼ���
Status DeleteHash(HashTable hash_table, ElemType e);			//ɾ���ؼ���
#endif 