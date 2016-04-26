#include "Static_Search_Table.h"
#include "Dynamic_Search_Table.h"
#include <iostream>

using namespace std;

int main()
{
	SStable ST;
	ST.length = 101;
	ST.elem = new ElemType[101];
	for (int i = 0; i < 101; i++)
	{
		ST.elem[i].key = i;
		ST.elem[i].weight = 1;
		ST.elem[i].position = i;
	}
	ST.elem[0].weight = 0;
	/*
	int result1= Search_Seq(ST, 50);
	cout << "˳����ң�" << result1 << endl;
	int result2 = Search_Bin(ST, 50);
	cout << "�۰���ң�" << result2 << endl;
	int result3 = Search_SecTree(ST, 50);
	cout << "���������ң�" << result3 << endl;
	BSTtree T = NULL;		//����������
	bool taller = false;
	for (int i = 1; i < 10; i++)
		InsertAVL(T, ST.elem[i], taller);				//��������������		
	cout << T->data.key << endl;
	cout << T->rchild->data.key << endl;
	cout << T->rchild->rchild->data.key << endl;
	cout << T->lchild->lchild->data.key << endl;
	//DeleteBST(T, ST.elem[3]);
	//cout << T->rchild->rchild->data.key << endl;
	*/

	BTree Root=new BTNode;
	Root->keynum = 1;
	Root->parent = NULL;
	Root->key[0] = 0;
	Root->key[1] = ST.elem[1].key;
	Root->ptr[0] = NULL;
	Root->ptr[1] = NULL;
	for (int i = 2; i < 100; i++)
	{
		Result m_result;
		if (!SearchBTree(Root, ST.elem[i].key, m_result))
			InsertBTree(Root, m_result.pt, ST.elem[i].key, m_result.i, NULL, NULL);
		cout << Root->key[1] << endl;
	}
	

	delete[] ST.elem;
	return 0;
}