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
	cout << "Ë³Ðò²éÕÒ£º" << result1 << endl;
	int result2 = Search_Bin(ST, 50);
	cout << "ÕÛ°ë²éÕÒ£º" << result2 << endl;
	int result3 = Search_SecTree(ST, 50);
	cout << "´ÎÓÅÊ÷²éÕÒ£º" << result3 << endl;
	*/
	BSTtree T = NULL;		//¶þ²æÅÅÐòÊ÷
	bool taller = false;
	for (int i = 1; i < 10; i++)
		InsertAVL(T, ST.elem[i], taller);				//¹¹½¨¶þ²æÅÅÐòÊ÷		
	cout << T->data.key << endl;
	cout << T->rchild->data.key << endl;
	cout << T->rchild->rchild->data.key << endl;
	cout << T->lchild->lchild->data.key << endl;

	//DeleteBST(T, ST.elem[3]);
	//cout << T->rchild->rchild->data.key << endl;

	delete[] ST.elem;
	return 0;
}