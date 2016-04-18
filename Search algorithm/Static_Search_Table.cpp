#include "Static_Search_Table.h"

//�ȽϺ�������ߴ󣬷���1��һ���󣬷���0���ұߴ󣬷���-1
int Compare(int i, int j)
{
	if (i > j)		return 1;
	else if (i == j)	return 0;
	else    return -1;
}
int Compare(float i, float j)
{
	if (i > j)		return 1;
	else if (i == j)	return 0;
	else    return -1;
}
int Compare(char* i, char* j)
{
	int tmp = strcmp(i, j);
	if (tmp > 0)		return 1;
	else if (tmp == 0)	return 0;
	else    return -1;
}


//-------------------------------------------˳�����-----------------------------------------------
/*�����������������Ĳ��ң���Ч�����
*/
int Search_Seq(SStable ST, KeyType key)
{
	int i;
	ST.elem[0].key = key;			//���ڱ���
	for (i = ST.length; Compare(ST.elem[i].key, key); i--);			//�Ӻ���ǰѰ��
	return i;								//����0����ʾ����û��
}

//------------------------------------------�۰����-------------------------------------------------
/*�����������������Ĳ��ң��Ҳ���ÿ��Ԫ�صĸ������
*/
int Search_Bin(SStable ST, KeyType key)
{
	int low, high, mid;				//��ʾ���ҵķ�Χ
	low = 1;	high = ST.length;	//��ʼ���ҷ�Χ
	while (low <= high)
	{
		mid = (low + high) / 2;
		int tmp = Compare(key, ST.elem[mid].key);	//���ҷ�Χ�м�ֵ��ؼ��ֱȽ�
		if (tmp == 0)	return mid;	//�ҵ�������
		else if (tmp > 0)	low = mid + 1;			//δ�ҵ�����С���ҷ�Χ
		else    high = mid - 1;
	}
	return 0;
}

//--------------------------------------���Ų�����---------------------------------------------
/*�������Ƚ������Ų��������ڸ��ݲ������ɸ���Ҷ�ӽ��в��ң�������Ȩ��Ԫ�ص���������
*/
int Search_SecTree(SStable ST, KeyType key)					//���ݴ��Ų������ҵ�key�ڱ��е�λ��
{
	if (ST.length == 0)		return 0;
	else
	{
		BiTree T;				//���Ų�����
		float *sw = new float[ST.length];
		FindSW(sw, ST);					//�õ��ۼ�Ȩ��ֵ
		T = SecondOptimal(ST.elem, sw, 1, ST.length-1);		//�ݹ�õ����Ŷ�����
		delete[] sw;
		return Compare_Tree(T, key);		//���Ҹùؼ�����������еĶ�Ӧλ��
	}
}

int Compare_Tree(BiTree T, KeyType key)				//���ؼ����Ƿ��ڴ��Ŷ�������
{
	int i = Compare(T->data.key, key);
	if (i == 0)		return T->data.position;
	else if (i > 0)
	{
		if (T->lchild)			//���������ڣ�����ݹ�
			return Compare_Tree(T->lchild, key);
		else                      //�����ڣ�����0         
			return 0;
	}
	else
	{
		if (T->rchild)			//���������ڣ����ҵݹ�
			return Compare_Tree(T->rchild, key);
		else                      //�����ڣ�����0
			return 0;
	}
}

BiTree SecondOptimal(ElemType *R, float *sw, int low, int high)				//���ɴ��Ų������ĵݹ����
{
	//�����R[low...high]���ۼ�Ȩֵ��sw������sw[0]==0���ݹ鹹����Ų�����T
	float dw = sw[high] + sw[low - 1];				//��ʼ��
	float min = abs(sw[high] - sw[low]);			
	int i = low;				//��ʱabs(dw - sw[low] - sw[low - 1])=min
	for (int j = low + 1; j <= high; j++)
	{
		if (abs(dw - sw[j] - sw[j - 1]) < min)
		{
			i = j;
			min = abs(dw - sw[j] - sw[j - 1]);		//��������Ѱ��һ�㣬ʹ���������߸���Ȩֵ֮����ӽ�
		}
	}
	BiTree T = new BiTNode;			//����һ��BiTNode��С���ڴ�ռ�
	T->data = R[i];									//���ɽڵ�
	if (i == low)	T->lchild = NULL;			//����������
	else    T->lchild = SecondOptimal(R, sw, low, i - 1);
	if (i == high)	T->rchild = NULL;		//����������
	else    T->rchild = SecondOptimal(R, sw, i + 1, high);
	return T;
}

void FindSW(float *sw, SStable ST)				//�����ۼ�Ȩ��ֵ
{
	sw[0] = 0;
	for (int i = 1; i < ST.length; i++)
		sw[i] = sw[i - 1] + ST.elem[i].weight;
}

