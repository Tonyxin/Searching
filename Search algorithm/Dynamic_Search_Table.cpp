#include "Dynamic_Search_Table.h"

//-------------------------------------二叉排序树------------------------------------------------
/*二叉排序树：1、若左子树不空，则左子树上所有结点值小于根节点；		
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

//-----------------------------------------------B-树-------------------------------------------------
/*分析：平衡多路查找树，据有以下特点：
*			1、树种每个节点至多有m棵子树（m为B-树的阶次）；
*			2、若根节点不是叶子节点，则至少有两棵子树
*			3、除根之外的所有非终端节点至少有m/2（进一法取值）棵子树；
*			4、所有非终端节点中的数据为{n,A0,K1,A1,K2,A2,...,Kn,An}
*			其中，Ki为关键字，Ai为指向子树根节点的指针，Ai-1子树中的关键字均小于Ki，但均大于Ki-1，n
*			为关键字的个数，取值为m/2（进一法）=1~（m-1）
*/
Status SearchBTree(BTree T, KeyType key, Result &m_result)			//在B-树中寻找目标关键字
{
	/*找得到：返回目标关键字所在的节点指针，关键字序号，标志位
	**找不到：返回应插入的位置（节点指针，后一个关键字序号，标志位）
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
			if (tmp == 0)						//寻找到，返回所在节点的指针，关键字序号，和标志置1
			{
				m_result.pt = T;
				m_result.i = i;
				m_result.flag = 1;
				return Sucess;
			}
			if (tmp > 0)							//该节点找不到，往下一个节点寻找，但保存该节点指针，比要查找关键字稍小的关键字序号，标志置0
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
void SearchBNode(BTree T, KeyType key, Result &m_result)			//在B-树中的某一个节点寻找关键字
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
			if (tmp == 0)						//寻找到，返回所在节点的指针，关键字序号，和标志置1
			{
				m_result.pt = T;
				m_result.i = i;
				m_result.flag = 1;
			}
			if (tmp > 0)							//该节点找不到，比要查找关键字稍大的关键字序号，标志置0
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
Status InsertBTree(BTree &Root, BTree T, KeyType key, int position, BTree T_right, BTree T_left)	//在B-树中插入一个节点
{
	/*Root为根节点，T为要插入的节点，key为要插入的关键字，key要插入在T->key[position]之后，
	**T_right为插入节点后，插入节点的右子树，初始为NULL
	**T_left为插入节点后，插入节点的左子树，初始为NULL
	*/
	if (!T)										//根节点不存在，创建根节点
	{
		T = new BTNode;
		memset(T, 0, sizeof(BTNode)/sizeof(char));
		T->keynum = 1;				//新创造的根节点初始只有1个关键字
		T->key[0] = Minus_Infinity;
		T->key[1] = key;
		T->parent = NULL;			//根节点的父指针为0
		T->ptr[0] = T_left;
		T->ptr[1] = T_right;
		Root = T;
		T_left->parent = Root;
		T_right->parent = Root;
		return Sucess;
	}
	else
	{
		//向节点中插入关键字
		for (int i = T->keynum; i > position; i--)
		{
			T->key[i + 1] = T->key[i];				//顺序存储的关键字与指针向后挪一位
			T->ptr[i + 1] = T->ptr[i];
		}
		T->ptr[position] = T_left;				//将指针指向左右子树
		T->ptr[position + 1] = T_right;
		T->key[position + 1] = key;					//保存关键字
		T->keynum++;									//关键字数增1
		//如果关键字已满，将节点分裂
		if (T->keynum == m)						//因为一个节点至多有m棵子树
		{
			//原节点以关键字key[m/2]分成两个节点，（1~m/2）与（m/2+2~m），关键字key[m/2]拿到上一个节点中
			BTree NewTreeLeft = new BTNode;		
			memset(NewTreeLeft, 0, sizeof(BTNode)/sizeof(char));
			BTree NewTreeRight = new BTNode;			
			memset(NewTreeRight, 0, sizeof(BTNode)/sizeof(char));
			NewTreeLeft->keynum = m / 2;			
			NewTreeLeft->parent = T->parent;				//原节点的父节点称为两个新节点的父节点
			NewTreeLeft->key[0] = Minus_Infinity;
			NewTreeLeft->ptr[0] = T->ptr[0];
			NewTreeRight->keynum = m / 2;
			NewTreeRight->parent = T->parent;
			NewTreeRight->key[0] = Minus_Infinity;
			NewTreeRight->ptr[0] = T->ptr[m / 2 + 1];
			for (int i = 1; i <= m / 2; i++)					
			{
				NewTreeLeft->key[i] = T->key[i];				//为左节点的关键字与指针赋值
				NewTreeLeft->ptr[i] = T->ptr[i];
				NewTreeRight->key[i] = T->key[m / 2 + i + 1];		//为右节点的关键字与指针赋值
				NewTreeRight->ptr[i] = T->ptr[m / 2 + i + 1];
			}
			if (NewTreeLeft->ptr[0])		//分裂的节点不是终端节点，需要其孩子节点回指
			{
				for (int i = 0; i <= m / 2; i++)
				{
					NewTreeLeft->ptr[i]->parent = NewTreeLeft;			//节点指针回指
					NewTreeRight->ptr[i]->parent = NewTreeRight;
				}
			}
			Result m_result;
			SearchBNode(T->parent, T->key[m / 2 + 1], m_result);	//查询key[m/2+1]在父节点中的位置
			BTree parent = T->parent;
			KeyType key = T->key[m / 2 + 1];
			delete T;
			return InsertBTree(Root, parent, key, m_result.i, NewTreeRight, NewTreeLeft);		//将key[m/2]递归插入到上一个节点
		}//if
		else
			return Sucess;
	}//else
}
Status DeleteBTree(BTree &Root, BTree T, int position)				//Root为根节点，在节点T上删除关键字Key[position]
{
	if (T->ptr[position])
	{
		//删除的关键字在非终端节点上，该关键字替换为右孩子最小关键字，递归从右孩子节点删除关键字
		T->key[position] = T->ptr[position]->key[1];
		return DeleteBTree(Root, T->ptr[position], 1);
	}
	else
	{
		//删除的关键字在终端节点上，分三种情况讨论
		/*1、该节点关键字数>=(m+1)/2，直接删除关键字与指针
		**2、该节点关键字数=(m+1)/2，但相邻节点中关键字数足够
		**3、该节点与相邻节点的关键字数都等于(m+1)/2
		*/
		if (T->keynum >= (m + 1) / 2)
		{
			//该节点上有足够多的关键字
			for (int i = position; i < T->keynum; i++)
				T->key[i] = T->key[i + 1];		//该位置之后的关键字与指针向前覆盖，删除该位置处的关键字与指针
			T->key[T->keynum] = 0;
			T->keynum--;		//节点的关键字数减1		
			return Sucess;
		}//if
		else
		{
			Result m_result;
			SearchBNode(T->parent, T->key[position], m_result);				//查询该节点在上一个节点中的位置
			if ((T->parent->ptr[m_result.i+1]) && (T->parent->ptr[m_result.i+1]->keynum >= (m + 1) / 2))
			{
				//该节点关键字不够，但存在相邻的右兄弟，且右兄弟有足够多的关键字
				for (int i = position; i < T->keynum; i++)
					T->key[i] = T->key[i + 1];		//该位置之后的关键字向前覆盖，删除该位置处的关键字
				T->key[T->keynum] = T->parent->key[m_result.i+1];			//在该节点Ai中加入父节点中K(i+1)关键字
				T->parent->key[m_result.i+1] = T->parent->ptr[m_result.i+1]->key[1];		//父节点K(i+1)关键字替换为A(i+1)节点的最小关键字
				return DeleteBTree(Root, T->parent->ptr[m_result.i+1], 1);		//递归删除A(i+1)节点中最小关键字
			}
			else if ((T->parent->ptr[m_result.i - 1]) && (T->parent->ptr[m_result.i - 1]->keynum >= (m + 1) / 2))
			{
				//该节点关键字不够，但存在相邻的左兄弟，且左兄弟有足够多的关键字
				for (int i = position; i > 1; i--)
					T->key[i] = T->key[i - 1];		//该位置之前向后覆盖，删除该位置处的关键字
				T->key[1] = T->parent->key[m_result.i];			//在该节点Ai中加入父节点中Ki关键字
				//父节点Ki关键字替换为A(i-1)节点的最大关键字
				T->parent->key[m_result.i] = T->parent->ptr[m_result.i - 1]->key[T->parent->ptr[m_result.i - 1]->keynum];
				//递归删除A(i-1)节点中最小关键字
				return DeleteBTree(Root, T->parent->ptr[m_result.i - 1], T->parent->ptr[m_result.i - 1]->keynum);
			}//else if
			else
				return DeleteBT_LackKey(Root, T, position, m_result.i);		//左右兄弟均没有足够的关键字
		}//else
	}//else
}
Status DeleteBT_LackKey(BTree &Root, BTree T, int position, int father_position)	//删除节点中一个关键字，但左右兄弟均没有足够关键字
{
	//在节点T中删除关键字
	if (!T->ptr[position - 1])										//如果该关键字做左指针为空，则左指针=右指针
		T->ptr[position - 1] = T->ptr[position];
	for (int i = position; i < T->keynum - 1; i++)
	{
		T->key[i] = T->key[i + 1];
		T->ptr[i] = T->ptr[i + 1];
		T->keynum--;
	}
	if (T->keynum < (m + 1) / 2 - 1)		//节点拥有小于等于（m+1）/2-1个关键字，要查询左右兄弟的情况
	{
		if (T->parent->ptr[father_position+1])						//该节点拥有右兄弟			
		{
			BTree q = T->parent->ptr[father_position+1];		//q为关键字所在节点的右兄弟
			//将右兄弟的关键字与指针向后挪
			for (int i = m - 1; i >= (m + 1) / 2; i--)
			{
				q->key[i] = q->key[i - (m + 1) / 2 + 1];		
				q->ptr[i] = q->ptr[i - (m + 1) / 2 + 1];
			}
			q->ptr[(m + 1) / 2 - 1] = q->ptr[0];
			//将父节点k[father_position+1]关键字移动到右兄弟中
			q->key[(m + 1) / 2 - 1] = q->parent->key[father_position+1];
			//将节点T中剩余关键字与指针(包括A0)移到右兄弟中
			for (int i = 1; i < (m + 1) / 2 - 1; i++)
			{
				q->key[i] = T->key[i];
				q->ptr[i] = T->ptr[i];
				q->ptr[i]->parent = q;			//记得将父指针回指
			}
			q->ptr[0] = T->ptr[0];		
			q->ptr[0]->parent = q;				//记得将父指针回指
			//删除关键字所在节点
			BTree s = T->parent->ptr[father_position];
			T->parent->ptr[father_position] = NULL;
			delete s;			
			//递归删除父节点k[father_position]关键字
			Result m_result;
			SearchBNode(T->parent->parent, T->key[father_position + 1], m_result);	//查询父节点k[father_position]在父父节点中的位置 
			position = father_position + 1;
			father_position = m_result.i;
			return DeleteBT_LackKey(Root, T->parent, position, father_position);		//递归删除
		}//if-该节点存在右兄弟
		else if (T->parent->ptr[father_position - 1])			//该节点存在左兄弟
		{
			BTree q = T->parent->ptr[father_position-1];	//q为关键字所在节点的左兄弟
			//将父节点k[father_position]关键字移动到左兄弟中
			q->key[(m + 1) / 2] = q->parent->key[father_position];
			//将节点T中剩余关键字与指针(包括A0)移到左兄弟中
			q->ptr[(m + 1) / 2] = T->ptr[0];
			q->ptr[(m + 1) / 2]->parent = q;						//父指针回指
			for (int i = 1; i < (m + 1) / 2 - 1; i++)
			{
				q->key[i + (m + 1) / 2] = T->key[i];
				q->ptr[i + (m + 1) / 2] = T->ptr[i];
				q->ptr[i + (m + 1) / 2]->parent = q;			//父指针回指
			}
			//删除关键字所在节点
			BTree s = T->parent->ptr[father_position];
			T->parent->ptr[father_position] = NULL;
			delete s;
			//递归删除父节点k[father_position]关键字
			Result m_result;
			SearchBNode(T->parent->parent, T->key[father_position], m_result);	//查询父节点k[father_position]在父父节点中的位置 
			position = father_position;
			father_position = m_result.i;
			return DeleteBT_LackKey(Root, T->parent, position, father_position);		//递归删除
		}//else if-存在左兄弟
		else      //左右兄弟均不存在，要删除的关键字在根节点上
		{
			if (T->keynum == 0)			//需要删除根节点
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
	}//if-该节点关键字数不够
	else
		return Sucess;
}

