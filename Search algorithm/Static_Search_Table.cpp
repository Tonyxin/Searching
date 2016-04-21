#include "Static_Search_Table.h"

//-------------------------------------------顺序查找-----------------------------------------------
/*分析：适用于任意表的查找，但效率最低
*/
int Search_Seq(SStable ST, KeyType key)
{
	int i;
	ST.elem[0].key = key;			//“哨兵”
	for (i = ST.length; Compare(ST.elem[i].key, key); i--);			//从后往前寻找
	return i;								//返回0，表示表中没有
}

//------------------------------------------折半查找-------------------------------------------------
/*分析：适用于有序表的查找，且查找每个元素的概率相等
**原理：设立搜索区域的边界（low与high），将mid=(low+high)/2指向的元素关键字i与待找关键字j比较，
*			 若i>j，则high=mid-1；若i<j，则low=mid+1；直到得出结果
*/
int Search_Bin(SStable ST, KeyType key)
{
	int low, high, mid;				//表示查找的范围
	low = 1;	high = ST.length;	//初始查找范围
	while (low <= high)
	{
		mid = (low + high) / 2;
		int tmp = Compare(key, ST.elem[mid].key);	//查找范围中间值与关键字比较
		if (tmp == 0)	return mid;	//找到，返回
		else if (tmp > 0)	low = mid + 1;			//未找到，缩小查找范围
		else    high = mid - 1;
	}
	return 0;
}

//--------------------------------------次优查找树---------------------------------------------
/*分析：先建立次优查找树，在根据查找树由根到叶子进行查找，适用于权重元素的有序表查找
**原理：step1：在有序表ST中寻找到这样的点i，该点左边所有点的权值与右边所有点的权值之和
*			            最接近，将改点设为根节点，同时得到（1~i-1）与（i+1~length）两个子序列
*			 step2：根据两个子序列，重复step1，等到两个节点和四个子序列，两个节点分别为根节点
*						 的左右子节点
*			 step3：重复上述步骤，得到次优二叉树
*			 step4：对次优二叉树，从根节点向下，寻找关键字所在的节点
*/
int Search_SecTree(SStable ST, KeyType key)					//根据次优查找树找到key在表中的位置
{
	if (ST.length == 0)		return 0;
	else
	{
		BiTree T;				//次优查找树
		float *sw = new float[ST.length];
		FindSW(sw, ST);					//得到累计权重值
		T = SecondOptimal(ST.elem, sw, 1, ST.length-1);		//递归得到次优二叉树
		delete[] sw;
		return Compare_Tree(T, key);		//查找该关键字在属虚表中的对应位置
	}
}

int Compare_Tree(BiTree T, KeyType key)				//检测关键字是否在次优二叉树中
{
	int i = Compare(T->data.key, key);
	if (i == 0)		return T->data.position;
	else if (i > 0)
	{
		if (T->lchild)			//左子树存在，向左递归
			return Compare_Tree(T->lchild, key);
		else                      //不存在，返回0         
			return 0;
	}
	else
	{
		if (T->rchild)			//右子树存在，向右递归
			return Compare_Tree(T->rchild, key);
		else                      //不存在，返回0
			return 0;
	}
}

BiTree SecondOptimal(ElemType *R, float *sw, int low, int high)				//生成次优查找树的递归过程
{
	//有序表R[low...high]与累计权值表sw（其中sw[0]==0）递归构造次优查找树T
	float dw = sw[high] + sw[low - 1];				//初始化
	float min = abs(sw[high] - sw[low]);			
	int i = low;				//此时abs(dw - sw[low] - sw[low - 1])=min
	for (int j = low + 1; j <= high; j++)
	{
		if (abs(dw - sw[j] - sw[j - 1]) < min)
		{
			i = j;
			min = abs(dw - sw[j] - sw[j - 1]);		//在区间上寻找一点，使得左右两边各点权值之和最接近
		}
	}
	BiTree T = new BiTNode;			//申请一个BiTNode大小的内存空间
	T->data = R[i];									//生成节点
	if (i == low)	T->lchild = NULL;			//生成左子树
	else    T->lchild = SecondOptimal(R, sw, low, i - 1);
	if (i == high)	T->rchild = NULL;		//生成右子树
	else    T->rchild = SecondOptimal(R, sw, i + 1, high);
	return T;
}

void FindSW(float *sw, SStable ST)				//计算累计权重值
{
	sw[0] = 0;
	for (int i = 1; i < ST.length; i++)
		sw[i] = sw[i - 1] + ST.elem[i].weight;
}

