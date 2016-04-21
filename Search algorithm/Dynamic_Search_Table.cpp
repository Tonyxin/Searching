#include "Dynamic_Search_Table.h"

/*-------------------------------------����������------------------------------------------------
*������������1�������������գ��������������н��ֵС�ڸ��ڵ㣻		
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