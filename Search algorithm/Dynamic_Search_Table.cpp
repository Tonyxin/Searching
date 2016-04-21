#include "Dynamic_Search_Table.h"

/*-------------------------------------二叉排序树------------------------------------------------
*二叉排序树：1、若左子树不空，则左子树上所有结点值小于根节点；		
*					 2、若右子树不空，则右子树上所有结点值大于根节点；
*					 3、左右子树也分别为二叉排序树
*PS：在建立次优查找树时，若有序表是从小到大排列，建立的次优查找树也是二叉排序树
*过程：若树中存在该结点，则返回；若不存在，则插入，插入的也一定为叶子结点
*/
Status SearchBST(BiTree T, KeyType key, BiTree &f, BiTree &p)		//在现有的二叉排序树中寻找关键字
{
	/*T指向根节点，key为关键字，f指向T的双亲，初始为NULL；
	*若查找成功，p指向含有关键字的元素节点；若查找不成功，p指向查找路径上的最后一个节点
	*/
	if (!T)			//根节点不存在，查找失败，p指向f		
	{
		p = f;
		return Error;
	}
	else
	{
		int tmp = Compare(T->data.key, key);
		if (tmp == 0)					//根节点关键字等于目标关键字，p指向T，返回Success
		{
			p = T;
			return Sucess;
		}
		else if (tmp > 0)				//根节点关键字大于目标关键字，递归到左子树进行查找
		{
			f = T;
			return SearchBST(f->lchild, key, f, p);
		}
		else                                  //根节点关键字小于目标关键字，递归到右子树进行查找
		{
			f = T;
			return SearchBST(f->rchild, key, f, p);
		}
	}
}
Status InsertBST(BiTree &T, ElemType e)				//向二叉排序树中插入节点
{
	BiTree p, f;				//p指向含有关键字的节点（查找成功），或者指向查找路径的最后一个节点（查找失败）
	p = NULL;
	f = NULL;					//f为p的父节点
	if (SearchBST(T, e.key, f, p))		//在二叉树中找到了该关键字，不插入，返回失败
		return Error;
	else						//二叉树中没有找到该关键字，将该元素插入到二叉树中
	{
		BiTree NewNode = new BiTNode;
		NewNode->data = e;
		NewNode->lchild = NULL;
		NewNode->rchild = NULL;
		if (!T)				//原本就不存在二叉树						
			T = NewNode;
		else
		{
			int tmp = Compare(p->data.key, e.key);
			if (tmp > 0)
				p->lchild = NewNode;					//根节点关键字大于目标关键字，称为左孩子
			else
				p->rchild = NewNode;					//根节点关键字小于目标关键字，称为右孩子
		}
		return Sucess;
	}
}
Status DeleteBST(BiTree &T, ElemType e)		//向二叉排序树中删除某一结点
{
	BiTree p,f;				//p指向含有关键字的节点，f为p的父节点
	p = NULL;
	f = NULL;
	if (SearchBST(T, e.key, f, p))		//查找成功
	{
		BiTree q=NULL;
		if (!p->lchild)			//p的左子树为空
			q = p->rchild;
		else if (!p->rchild)	//p的右子树为空
			q = p->lchild;
		else                          //p的左右子树均不为空
		{
			q = p->lchild;		//p的左孩子成为该节点，p的右子树称为左子树的最右子树
			BiTree s = p->lchild;
			while (s->rchild)	s = s->rchild;
			s->rchild = p->rchild;
		}
		if (!f)			//p为根节点
			T = q;
		else if ((f->lchild)&&(f->lchild->data.key == p->data.key))			//p为f的左孩子
			f->lchild = q;
		else                                 //p为f的右孩子
			f->rchild = q;
		delete p;
		return Sucess;
	}
	else
		return Error;				//没有查找到该关键字，返回Error
}

//---------------------------------------平衡二叉排序树---------------------------------------------
/*分析：在二叉排序树上进行优化，任意一个节点，其左右子树的深度之差不会超过1，防止对一个有序表
*			 建树的时候，出现所有节点只有右子树，查找时退化为顺序查找
**方法：为每一个结点设置平衡因子bf，bf=|左子树深度-右子树深度|，每次插入一个节点，就更改平衡因
*			 子，整个树上出现bf>1，就调整树的结构
*/
void L_Rotate(BSTtree& T)					//对以T为根节点的树实现左转
{
	BSTtree p = T;
	BSTtree q = p->rchild;
	if (q->lchild)				//如果q存在左子树，p称为q的左子树后，q的原左子树称为p的右子树
	{
		BSTtree s = q->lchild;
		q->lchild = p;
		p->rchild = s;
	}
	else                          //如果q不存在左子树，p直接称为q的左子树
	{
		q->lchild = p;
		p->rchild = NULL;
	}
	T = q;
}
void R_Rotate(BSTtree& T)					//对以T为根节点的树实现右转
{
	BSTtree p = T;
	BSTtree q = p->lchild;
	if (q->rchild)				//如果q存在右子树，p称为q的右子树后，q的原右子树称为p的左子树
	{
		BSTtree s = q->rchild;
		q->rchild = p;
		p->lchild = s;
	}
	else                          //如果q不存在右子树，p直接称为q的右子树
	{
		q->rchild = p;
		p->lchild = NULL;
	}
	T = q;
}
void LeftBalance(BSTtree &T)			//平衡左子树
{
	switch (T->lchild->bf)
	{
	case LH:															//			              (a)o                直接在a点左转
		T->bf = T->lchild->bf = EH;						//		           	  o              o
		R_Rotate(T);													//		       o	     o
		break;															// 	o	
	case RH:
		switch (T->lchild->rchild->bf)
		{
		case LH:														//						          (a)o         先对b点左转，再对a点右转        
			T->bf = RH;												//					   (b)o	                o
			T->lchild->bf = EH;								    //  	        o		     o
			T->lchild->rchild->bf = EH;						//						   o					
			break;																		 
		case RH:														//						           (a)o			先对b点左转，再对a点右转
			T->bf = EH;												//					   (b)o	                 o
			T->lchild->bf = LH;									//			  o	         o
			T->lchild->rchild->bf = EH;						//                            o
			break;
		}
		L_Rotate(T->lchild);		//对左孩子左转
		R_Rotate(T);					//再对根节点右转
		break;
	}
}
void RightBalance(BSTtree &T)				//平衡右子树
{
	switch (T->rchild->bf)
	{
	case RH:															//									 (a)o							直接对a点左转						
		T->bf = EH;													//								o				o
		T->rchild->bf = EH;										//											 o  	o
		L_Rotate(T);													//	                                                   o
		break;
	case LH:
		switch (T->rchild->lchild->bf)						
		{
		case RH:														//									(a)o					先对b右转，再对a左转
			T->bf = LH;												//								o			(b)o
			T->rchild->bf = EH;									//							                 o          o
			T->rchild->lchild->bf = EH;						//                                             o
			break;
		case LH:														//									(a)o					先对b右转，再对a左转							
			T->bf = EH;												//								o			(b)o
			T->rchild->bf = RH;									//                                          o			o
			T->rchild->lchild->bf = EH;						//                                        o
			break;
		}
		R_Rotate(T->rchild);			//先对右孩子右转
		L_Rotate(T);						//再对根节点左转
		break;
	}
}
Status InsertAVL(BSTtree &T, ElemType e, bool &taller)		//在平衡二叉树中插入节点
{
	if (!T)		//如果T为空，插入数据
	{
		T = new BSTNode;
		T->data = e;
		T->bf = EH;
		T->lchild = T->rchild = NULL;
		taller = true;					//true表示长高
	}
	else
	{
		int tmp = Compare(T->data.key, e.key);
		if (tmp == 0)		//如果现有的树中存在该关键字，返回错误
		{
			taller = false;		//不再向上返回Taller信息
			return Error;
		}	
		else if (tmp < 0)
		{
			if (!InsertAVL(T->rchild, e, taller))	//如果插入失败，向上返回插入失败消息
				return Error;
			if (taller)		//如果长高
			{
				switch (T->bf)
				{
				case RH:
					RightBalance(T);				//调整右支
					taller = false;					//不再向上继续调整
					break;
				case EH:
					T->bf = RH;						//更改平衡因子
					taller = true;					//要继续向上反馈长高信息
					break;
				case LH:
					T->bf = EH;						//更改平衡因子
					taller = false;					//不再向上反馈长高信息
					break;
				}//switch
			}//if
		}//else if
		else
		{
			if (!InsertAVL(T->lchild, e, taller))	//如果插入失败，向上返回插入失败消息
				return Error;
			if (taller)		//如果长高
			{
				switch (T->bf)
				{
				case LH:
					LeftBalance(T);				//调整左支
					taller = false;				//不再向上继续调整
					break;
				case EH:
					T->bf = LH;					//更改平衡因子
					taller = true;				//要继续向上反馈长高信息
					break;
				case RH:
					T->bf = EH;					//更改平衡因子
					taller = false;				//不再向上反馈长高信息
					break;
				}//switch
			}//if
		}//else
	}//else 
	return Sucess;
}