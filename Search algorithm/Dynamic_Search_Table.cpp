#include "Dynamic_Search_Table.h"

//-------------------------------------����������------------------------------------------------
/*������������1�������������գ��������������н��ֵС�ڸ��ڵ㣻		
*					 2�������������գ��������������н��ֵ���ڸ��ڵ㣻
*					 3����������Ҳ�ֱ�Ϊ����������
*PS���ڽ������Ų�����ʱ����������Ǵ�С�������У������Ĵ��Ų�����Ҳ�Ƕ���������
*���̣������д��ڸý�㣬�򷵻أ��������ڣ�����룬�����Ҳһ��ΪҶ�ӽ��
*/
Status SearchBST(BiTree T, KeyType key, BiTree &f, BiTree &p)		//�����еĶ�����������Ѱ�ҹؼ���
{
	/*Tָ����ڵ㣬keyΪ�ؼ��֣�fָ��T��˫�ף���ʼΪNULL��
	*�����ҳɹ���pָ���йؼ��ֵ�Ԫ�ؽڵ㣻�����Ҳ��ɹ���pָ�����·���ϵ����һ���ڵ�
	*/
	if (!T)			//���ڵ㲻���ڣ�����ʧ�ܣ�pָ��f		
	{
		p = f;
		return Error;
	}
	else
	{
		int tmp = Compare(T->data.key, key);
		if (tmp == 0)					//���ڵ�ؼ��ֵ���Ŀ��ؼ��֣�pָ��T������Success
		{
			p = T;
			return Sucess;
		}
		else if (tmp > 0)				//���ڵ�ؼ��ִ���Ŀ��ؼ��֣��ݹ鵽���������в���
		{
			f = T;
			return SearchBST(f->lchild, key, f, p);
		}
		else                                  //���ڵ�ؼ���С��Ŀ��ؼ��֣��ݹ鵽���������в���
		{
			f = T;
			return SearchBST(f->rchild, key, f, p);
		}
	}
}
Status InsertBST(BiTree &T, ElemType e)				//������������в���ڵ�
{
	BiTree p, f;				//pָ���йؼ��ֵĽڵ㣨���ҳɹ���������ָ�����·�������һ���ڵ㣨����ʧ�ܣ�
	p = NULL;
	f = NULL;					//fΪp�ĸ��ڵ�
	if (SearchBST(T, e.key, f, p))		//�ڶ��������ҵ��˸ùؼ��֣������룬����ʧ��
		return Error;
	else						//��������û���ҵ��ùؼ��֣�����Ԫ�ز��뵽��������
	{
		BiTree NewNode = new BiTNode;
		NewNode->data = e;
		NewNode->lchild = NULL;
		NewNode->rchild = NULL;
		if (!T)				//ԭ���Ͳ����ڶ�����						
			T = NewNode;
		else
		{
			int tmp = Compare(p->data.key, e.key);
			if (tmp > 0)
				p->lchild = NewNode;					//���ڵ�ؼ��ִ���Ŀ��ؼ��֣���Ϊ����
			else
				p->rchild = NewNode;					//���ڵ�ؼ���С��Ŀ��ؼ��֣���Ϊ�Һ���
		}
		return Sucess;
	}
}
Status DeleteBST(BiTree &T, ElemType e)		//�������������ɾ��ĳһ���
{
	BiTree p,f;				//pָ���йؼ��ֵĽڵ㣬fΪp�ĸ��ڵ�
	p = NULL;
	f = NULL;
	if (SearchBST(T, e.key, f, p))		//���ҳɹ�
	{
		BiTree q=NULL;
		if (!p->lchild)			//p��������Ϊ��
			q = p->rchild;
		else if (!p->rchild)	//p��������Ϊ��
			q = p->lchild;
		else                          //p��������������Ϊ��
		{
			q = p->lchild;		//p�����ӳ�Ϊ�ýڵ㣬p����������Ϊ����������������
			BiTree s = p->lchild;
			while (s->rchild)	s = s->rchild;
			s->rchild = p->rchild;
		}
		if (!f)			//pΪ���ڵ�
			T = q;
		else if ((f->lchild)&&(f->lchild->data.key == p->data.key))			//pΪf������
			f->lchild = q;
		else                                 //pΪf���Һ���
			f->rchild = q;
		delete p;
		return Sucess;
	}
	else
		return Error;				//û�в��ҵ��ùؼ��֣�����Error
}

//---------------------------------------ƽ�����������---------------------------------------------
/*�������ڶ����������Ͻ����Ż�������һ���ڵ㣬���������������֮��ᳬ��1����ֹ��һ�������
*			 ������ʱ�򣬳������нڵ�ֻ��������������ʱ�˻�Ϊ˳�����
**������Ϊÿһ���������ƽ������bf��bf=|���������-���������|��ÿ�β���һ���ڵ㣬�͸���ƽ����
*			 �ӣ��������ϳ���bf>1���͵������Ľṹ
*/
void L_Rotate(BSTtree& T)					//����TΪ���ڵ����ʵ����ת
{
	BSTtree p = T;
	BSTtree q = p->rchild;
	if (q->lchild)				//���q������������p��Ϊq����������q��ԭ��������Ϊp��������
	{
		BSTtree s = q->lchild;
		q->lchild = p;
		p->rchild = s;
	}
	else                          //���q��������������pֱ�ӳ�Ϊq��������
	{
		q->lchild = p;
		p->rchild = NULL;
	}
	T = q;
}
void R_Rotate(BSTtree& T)					//����TΪ���ڵ����ʵ����ת
{
	BSTtree p = T;
	BSTtree q = p->lchild;
	if (q->rchild)				//���q������������p��Ϊq����������q��ԭ��������Ϊp��������
	{
		BSTtree s = q->rchild;
		q->rchild = p;
		p->lchild = s;
	}
	else                          //���q��������������pֱ�ӳ�Ϊq��������
	{
		q->rchild = p;
		p->lchild = NULL;
	}
	T = q;
}
void LeftBalance(BSTtree &T)			//ƽ��������
{
	switch (T->lchild->bf)
	{
	case LH:															//			              (a)o                ֱ����a����ת
		T->bf = T->lchild->bf = EH;						//		           	  o              o
		R_Rotate(T);													//		       o	     o
		break;															// 	o	
	case RH:
		switch (T->lchild->rchild->bf)
		{
		case LH:														//						          (a)o         �ȶ�b����ת���ٶ�a����ת        
			T->bf = RH;												//					   (b)o	                o
			T->lchild->bf = EH;								    //  	        o		     o
			T->lchild->rchild->bf = EH;						//						   o					
			break;																		 
		case RH:														//						           (a)o			�ȶ�b����ת���ٶ�a����ת
			T->bf = EH;												//					   (b)o	                 o
			T->lchild->bf = LH;									//			  o	         o
			T->lchild->rchild->bf = EH;						//                            o
			break;
		}
		L_Rotate(T->lchild);		//��������ת
		R_Rotate(T);					//�ٶԸ��ڵ���ת
		break;
	}
}
void RightBalance(BSTtree &T)				//ƽ��������
{
	switch (T->rchild->bf)
	{
	case RH:															//									 (a)o							ֱ�Ӷ�a����ת						
		T->bf = EH;													//								o				o
		T->rchild->bf = EH;										//											 o  	o
		L_Rotate(T);													//	                                                   o
		break;
	case LH:
		switch (T->rchild->lchild->bf)						
		{
		case RH:														//									(a)o					�ȶ�b��ת���ٶ�a��ת
			T->bf = LH;												//								o			(b)o
			T->rchild->bf = EH;									//							                 o          o
			T->rchild->lchild->bf = EH;						//                                             o
			break;
		case LH:														//									(a)o					�ȶ�b��ת���ٶ�a��ת							
			T->bf = EH;												//								o			(b)o
			T->rchild->bf = RH;									//                                          o			o
			T->rchild->lchild->bf = EH;						//                                        o
			break;
		}
		R_Rotate(T->rchild);			//�ȶ��Һ�����ת
		L_Rotate(T);						//�ٶԸ��ڵ���ת
		break;
	}
}
Status InsertAVL(BSTtree &T, ElemType e, bool &taller)		//��ƽ��������в���ڵ�
{
	if (!T)		//���TΪ�գ���������
	{
		T = new BSTNode;
		T->data = e;
		T->bf = EH;
		T->lchild = T->rchild = NULL;
		taller = true;					//true��ʾ����
	}
	else
	{
		int tmp = Compare(T->data.key, e.key);
		if (tmp == 0)		//������е����д��ڸùؼ��֣����ش���
		{
			taller = false;		//�������Ϸ���Taller��Ϣ
			return Error;
		}	
		else if (tmp < 0)
		{
			if (!InsertAVL(T->rchild, e, taller))	//�������ʧ�ܣ����Ϸ��ز���ʧ����Ϣ
				return Error;
			if (taller)		//�������
			{
				switch (T->bf)
				{
				case RH:
					RightBalance(T);				//������֧
					taller = false;					//�������ϼ�������
					break;
				case EH:
					T->bf = RH;						//����ƽ������
					taller = true;					//Ҫ�������Ϸ���������Ϣ
					break;
				case LH:
					T->bf = EH;						//����ƽ������
					taller = false;					//�������Ϸ���������Ϣ
					break;
				}//switch
			}//if
		}//else if
		else
		{
			if (!InsertAVL(T->lchild, e, taller))	//�������ʧ�ܣ����Ϸ��ز���ʧ����Ϣ
				return Error;
			if (taller)		//�������
			{
				switch (T->bf)
				{
				case LH:
					LeftBalance(T);				//������֧
					taller = false;				//�������ϼ�������
					break;
				case EH:
					T->bf = LH;					//����ƽ������
					taller = true;				//Ҫ�������Ϸ���������Ϣ
					break;
				case RH:
					T->bf = EH;					//����ƽ������
					taller = false;				//�������Ϸ���������Ϣ
					break;
				}//switch
			}//if
		}//else
	}//else 
	return Sucess;
}

//-----------------------------------------------B-��-------------------------------------------------
/*������ƽ���·�����������������ص㣺
*			1������ÿ���ڵ�������m��������mΪB-���Ľ״Σ���
*			2�������ڵ㲻��Ҷ�ӽڵ㣬����������������
*			3������֮������з��ն˽ڵ�������m/2����һ��ȡֵ����������
*			4�����з��ն˽ڵ��е�����Ϊ{n,A0,K1,A1,K2,A2,...,Kn,An}
*			���У�KiΪ�ؼ��֣�AiΪָ���������ڵ��ָ�룬Ai-1�����еĹؼ��־�С��Ki����������Ki-1��n
*			Ϊ�ؼ��ֵĸ�����ȡֵΪm/2����һ����=1~��m-1��
*/
Status SearchBTree(BTree T, KeyType key, Result &m_result)			//��B-����Ѱ��Ŀ��ؼ���
{
	/*�ҵõ�������Ŀ��ؼ������ڵĽڵ�ָ�룬�ؼ�����ţ���־λ
	**�Ҳ���������Ӧ�����λ�ã��ڵ�ָ�룬��һ���ؼ�����ţ���־λ��
	*/
	if (!T)
	{
		m_result.flag = 0;
		return Error;
	}
	else
	{
		for (int i = 1; i <= T->keynum; i++)
		{
			int tmp = Compare(T->key[i], key);
			if (tmp == 0)						//Ѱ�ҵ����������ڽڵ��ָ�룬�ؼ�����ţ��ͱ�־��1
			{
				m_result.pt = T;
				m_result.i = i;
				m_result.flag = 1;
				return Sucess;
			}
			if (tmp > 0)							//�ýڵ��Ҳ���������һ���ڵ�Ѱ�ң�������ýڵ�ָ�룬��Ҫ���ҹؼ�����С�Ĺؼ�����ţ���־��0
			{
				m_result.pt = T;
				m_result.i = i-1;
				m_result.flag = 0;
				return SearchBTree(T->ptr[i - 1], key, m_result);
			}
			else
			{
				if (i == T->keynum)
				{
					m_result.pt = T;
					m_result.i = i;
					m_result.flag = 0;
					return SearchBTree(T->ptr[i], key, m_result);
				}
			}
		}//for
	}//else
}
void SearchBNode(BTree T, KeyType key, Result &m_result)			//��B-���е�ĳһ���ڵ�Ѱ�ҹؼ���
{
	if (!T)
	{
		m_result.flag = 0;
	}
	else
	{
		for (int i = 1; i <= T->keynum; i++)
		{
			int tmp = Compare(T->key[i], key);
			if (tmp == 0)						//Ѱ�ҵ����������ڽڵ��ָ�룬�ؼ�����ţ��ͱ�־��1
			{
				m_result.pt = T;
				m_result.i = i;
				m_result.flag = 1;
			}
			if (tmp > 0)							//�ýڵ��Ҳ�������Ҫ���ҹؼ����Դ�Ĺؼ�����ţ���־��0
			{
				m_result.pt = T;
				m_result.i = i-1;
				m_result.flag = 0;
			}
			else
			{
				if (i == T->keynum)
				{
					m_result.pt = T;
					m_result.i = i;
					m_result.flag = 0;
				}
			}
		}//for
	}//else
}
Status InsertBTree(BTree &Root, BTree T, KeyType key, int position, BTree T_right, BTree T_left)	//��B-���в���һ���ڵ�
{
	/*RootΪ���ڵ㣬TΪҪ����Ľڵ㣬keyΪҪ����Ĺؼ��֣�keyҪ������T->key[position]֮��
	**T_rightΪ����ڵ�󣬲���ڵ������������ʼΪNULL
	**T_leftΪ����ڵ�󣬲���ڵ������������ʼΪNULL
	*/
	if (!T)										//���ڵ㲻���ڣ��������ڵ�
	{
		T = new BTNode;
		memset(T, 0, sizeof(BTNode)/sizeof(char));
		T->keynum = 1;				//�´���ĸ��ڵ��ʼֻ��1���ؼ���
		T->key[0] = Minus_Infinity;
		T->key[1] = key;
		T->parent = NULL;			//���ڵ�ĸ�ָ��Ϊ0
		T->ptr[0] = T_left;
		T->ptr[1] = T_right;
		Root = T;
		T_left->parent = Root;
		T_right->parent = Root;
		return Sucess;
	}
	else
	{
		//��ڵ��в���ؼ���
		for (int i = T->keynum; i > position; i--)
		{
			T->key[i + 1] = T->key[i];				//˳��洢�Ĺؼ�����ָ�����Ųһλ
			T->ptr[i + 1] = T->ptr[i];
		}
		T->ptr[position] = T_left;				//��ָ��ָ����������
		T->ptr[position + 1] = T_right;
		T->key[position + 1] = key;					//����ؼ���
		T->keynum++;									//�ؼ�������1
		//����ؼ������������ڵ����
		if (T->keynum == m)						//��Ϊһ���ڵ�������m������
		{
			//ԭ�ڵ��Թؼ���key[m/2]�ֳ������ڵ㣬��1~m/2���루m/2+2~m�����ؼ���key[m/2]�õ���һ���ڵ���
			BTree NewTreeLeft = new BTNode;		
			memset(NewTreeLeft, 0, sizeof(BTNode)/sizeof(char));
			BTree NewTreeRight = new BTNode;			
			memset(NewTreeRight, 0, sizeof(BTNode)/sizeof(char));
			NewTreeLeft->keynum = m / 2;			
			NewTreeLeft->parent = T->parent;				//ԭ�ڵ�ĸ��ڵ��Ϊ�����½ڵ�ĸ��ڵ�
			NewTreeLeft->key[0] = Minus_Infinity;
			NewTreeLeft->ptr[0] = T->ptr[0];
			NewTreeRight->keynum = m / 2;
			NewTreeRight->parent = T->parent;
			NewTreeRight->key[0] = Minus_Infinity;
			NewTreeRight->ptr[0] = T->ptr[m / 2 + 1];
			for (int i = 1; i <= m / 2; i++)					
			{
				NewTreeLeft->key[i] = T->key[i];				//Ϊ��ڵ�Ĺؼ�����ָ�븳ֵ
				NewTreeLeft->ptr[i] = T->ptr[i];
				NewTreeRight->key[i] = T->key[m / 2 + i + 1];		//Ϊ�ҽڵ�Ĺؼ�����ָ�븳ֵ
				NewTreeRight->ptr[i] = T->ptr[m / 2 + i + 1];
			}
			if (NewTreeLeft->ptr[0])		//���ѵĽڵ㲻���ն˽ڵ㣬��Ҫ�亢�ӽڵ��ָ
			{
				for (int i = 0; i <= m / 2; i++)
				{
					NewTreeLeft->ptr[i]->parent = NewTreeLeft;			//�ڵ�ָ���ָ
					NewTreeRight->ptr[i]->parent = NewTreeRight;
				}
			}
			Result m_result;
			SearchBNode(T->parent, T->key[m / 2 + 1], m_result);	//��ѯkey[m/2+1]�ڸ��ڵ��е�λ��
			BTree parent = T->parent;
			KeyType key = T->key[m / 2 + 1];
			delete T;
			return InsertBTree(Root, parent, key, m_result.i, NewTreeRight, NewTreeLeft);		//��key[m/2]�ݹ���뵽��һ���ڵ�
		}//if
		else
			return Sucess;
	}//else
}
Status DeleteBTree(BTree &Root, BTree T, int position)				//RootΪ���ڵ㣬�ڽڵ�T��ɾ���ؼ���Key[position]
{
	if (T->ptr[position])
	{
		//ɾ���Ĺؼ����ڷ��ն˽ڵ��ϣ��ùؼ����滻Ϊ�Һ�����С�ؼ��֣��ݹ���Һ��ӽڵ�ɾ���ؼ���
		T->key[position] = T->ptr[position]->key[1];
		return DeleteBTree(Root, T->ptr[position], 1);
	}
	else
	{
		//ɾ���Ĺؼ������ն˽ڵ��ϣ��������������
		/*1���ýڵ�ؼ�����>=(m+1)/2��ֱ��ɾ���ؼ�����ָ��
		**2���ýڵ�ؼ�����=(m+1)/2�������ڽڵ��йؼ������㹻
		**3���ýڵ������ڽڵ�Ĺؼ�����������(m+1)/2
		*/
		if (T->keynum >= (m + 1) / 2)
		{
			//�ýڵ������㹻��Ĺؼ���
			for (int i = position; i < T->keynum; i++)
				T->key[i] = T->key[i + 1];		//��λ��֮��Ĺؼ�����ָ����ǰ���ǣ�ɾ����λ�ô��Ĺؼ�����ָ��
			T->key[T->keynum] = 0;
			T->keynum--;		//�ڵ�Ĺؼ�������1		
			return Sucess;
		}//if
		else
		{
			Result m_result;
			SearchBNode(T->parent, T->key[position], m_result);				//��ѯ�ýڵ�����һ���ڵ��е�λ��
			if ((T->parent->ptr[m_result.i+1]) && (T->parent->ptr[m_result.i+1]->keynum >= (m + 1) / 2))
			{
				//�ýڵ�ؼ��ֲ��������������ڵ����ֵܣ������ֵ����㹻��Ĺؼ���
				for (int i = position; i < T->keynum; i++)
					T->key[i] = T->key[i + 1];		//��λ��֮��Ĺؼ�����ǰ���ǣ�ɾ����λ�ô��Ĺؼ���
				T->key[T->keynum] = T->parent->key[m_result.i+1];			//�ڸýڵ�Ai�м��븸�ڵ���K(i+1)�ؼ���
				T->parent->key[m_result.i+1] = T->parent->ptr[m_result.i+1]->key[1];		//���ڵ�K(i+1)�ؼ����滻ΪA(i+1)�ڵ����С�ؼ���
				return DeleteBTree(Root, T->parent->ptr[m_result.i+1], 1);		//�ݹ�ɾ��A(i+1)�ڵ�����С�ؼ���
			}
			else if ((T->parent->ptr[m_result.i - 1]) && (T->parent->ptr[m_result.i - 1]->keynum >= (m + 1) / 2))
			{
				//�ýڵ�ؼ��ֲ��������������ڵ����ֵܣ������ֵ����㹻��Ĺؼ���
				for (int i = position; i > 1; i--)
					T->key[i] = T->key[i - 1];		//��λ��֮ǰ��󸲸ǣ�ɾ����λ�ô��Ĺؼ���
				T->key[1] = T->parent->key[m_result.i];			//�ڸýڵ�Ai�м��븸�ڵ���Ki�ؼ���
				//���ڵ�Ki�ؼ����滻ΪA(i-1)�ڵ�����ؼ���
				T->parent->key[m_result.i] = T->parent->ptr[m_result.i - 1]->key[T->parent->ptr[m_result.i - 1]->keynum];
				//�ݹ�ɾ��A(i-1)�ڵ�����С�ؼ���
				return DeleteBTree(Root, T->parent->ptr[m_result.i - 1], T->parent->ptr[m_result.i - 1]->keynum);
			}//else if
			else
				return DeleteBT_LackKey(Root, T, position, m_result.i);		//�����ֵܾ�û���㹻�Ĺؼ���
		}//else
	}//else
}
Status DeleteBT_LackKey(BTree &Root, BTree T, int position, int father_position)	//ɾ���ڵ���һ���ؼ��֣��������ֵܾ�û���㹻�ؼ���
{
	//�ڽڵ�T��ɾ���ؼ���
	if (!T->ptr[position - 1])										//����ùؼ�������ָ��Ϊ�գ�����ָ��=��ָ��
		T->ptr[position - 1] = T->ptr[position];
	for (int i = position; i < T->keynum - 1; i++)
	{
		T->key[i] = T->key[i + 1];
		T->ptr[i] = T->ptr[i + 1];
		T->keynum--;
	}
	if (T->keynum < (m + 1) / 2 - 1)		//�ڵ�ӵ��С�ڵ��ڣ�m+1��/2-1���ؼ��֣�Ҫ��ѯ�����ֵܵ����
	{
		if (T->parent->ptr[father_position+1])						//�ýڵ�ӵ�����ֵ�			
		{
			BTree q = T->parent->ptr[father_position+1];		//qΪ�ؼ������ڽڵ�����ֵ�
			//�����ֵܵĹؼ�����ָ�����Ų
			for (int i = m - 1; i >= (m + 1) / 2; i--)
			{
				q->key[i] = q->key[i - (m + 1) / 2 + 1];		
				q->ptr[i] = q->ptr[i - (m + 1) / 2 + 1];
			}
			q->ptr[(m + 1) / 2 - 1] = q->ptr[0];
			//�����ڵ�k[father_position+1]�ؼ����ƶ������ֵ���
			q->key[(m + 1) / 2 - 1] = q->parent->key[father_position+1];
			//���ڵ�T��ʣ��ؼ�����ָ��(����A0)�Ƶ����ֵ���
			for (int i = 1; i < (m + 1) / 2 - 1; i++)
			{
				q->key[i] = T->key[i];
				q->ptr[i] = T->ptr[i];
				q->ptr[i]->parent = q;			//�ǵý���ָ���ָ
			}
			q->ptr[0] = T->ptr[0];		
			q->ptr[0]->parent = q;				//�ǵý���ָ���ָ
			//ɾ���ؼ������ڽڵ�
			BTree s = T->parent->ptr[father_position];
			T->parent->ptr[father_position] = NULL;
			delete s;			
			//�ݹ�ɾ�����ڵ�k[father_position]�ؼ���
			Result m_result;
			SearchBNode(T->parent->parent, T->key[father_position + 1], m_result);	//��ѯ���ڵ�k[father_position]�ڸ����ڵ��е�λ�� 
			position = father_position + 1;
			father_position = m_result.i;
			return DeleteBT_LackKey(Root, T->parent, position, father_position);		//�ݹ�ɾ��
		}//if-�ýڵ�������ֵ�
		else if (T->parent->ptr[father_position - 1])			//�ýڵ�������ֵ�
		{
			BTree q = T->parent->ptr[father_position-1];	//qΪ�ؼ������ڽڵ�����ֵ�
			//�����ڵ�k[father_position]�ؼ����ƶ������ֵ���
			q->key[(m + 1) / 2] = q->parent->key[father_position];
			//���ڵ�T��ʣ��ؼ�����ָ��(����A0)�Ƶ����ֵ���
			q->ptr[(m + 1) / 2] = T->ptr[0];
			q->ptr[(m + 1) / 2]->parent = q;						//��ָ���ָ
			for (int i = 1; i < (m + 1) / 2 - 1; i++)
			{
				q->key[i + (m + 1) / 2] = T->key[i];
				q->ptr[i + (m + 1) / 2] = T->ptr[i];
				q->ptr[i + (m + 1) / 2]->parent = q;			//��ָ���ָ
			}
			//ɾ���ؼ������ڽڵ�
			BTree s = T->parent->ptr[father_position];
			T->parent->ptr[father_position] = NULL;
			delete s;
			//�ݹ�ɾ�����ڵ�k[father_position]�ؼ���
			Result m_result;
			SearchBNode(T->parent->parent, T->key[father_position], m_result);	//��ѯ���ڵ�k[father_position]�ڸ����ڵ��е�λ�� 
			position = father_position;
			father_position = m_result.i;
			return DeleteBT_LackKey(Root, T->parent, position, father_position);		//�ݹ�ɾ��
		}//else if-�������ֵ�
		else      //�����ֵܾ������ڣ�Ҫɾ���Ĺؼ����ڸ��ڵ���
		{
			if (T->keynum == 0)			//��Ҫɾ�����ڵ�
			{
				if (T->ptr[0])
				{
					Root = T->ptr[0];
					Root->parent = NULL;
				}
				else
				{
					Root = T->ptr[1];
					Root->parent = NULL;
				}
				delete T;
			}
			return Sucess;
		}
	}//if-�ýڵ�ؼ���������
	else
		return Sucess;
}

