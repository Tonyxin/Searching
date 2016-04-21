#ifndef DYNAMIC_SEARCH_TABLE_H
#define DYNAMIC_SEARCH_TABLE_H

#include "Search_DataStruct.h"

//��̬��������������
Status SearchBST(BiTree T, KeyType key, BiTree &f, BiTree &p);		//�����еĶ�����������Ѱ�ҹؼ���
/*ע�⣺��ָ����Ϊ�������д���ʱ����������ָ���ָ��ᷢ���仯����Ӧ�������÷�ʽ*/
Status InsertBST(BiTree &T, ElemType e);				//������������в���ڵ�
Status DeleteBST(BiTree &T, ElemType e);			//�������������ɾ��ĳһ���

//ƽ�������
void L_Rotate(BSTtree &T);					//����TΪ���ڵ����ʵ����ת
void R_Rotate(BSTtree &T);					//����TΪ���ڵ����ʵ����ת
void LeftBalance(BSTtree &T);				//���ڵ����+2����ת
void RightBalance(BSTtree &T);				//���ڵ����-2����ת

Status InsertAVL(BSTtree &T, ElemType e, bool &taller);	//��ƽ��������в���ڵ�
#endif 