#include "Search_DataStruct.h"

//比较函数，左边大，返回1；一样大，返回0；右边大，返回-1
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

Status SearchNode(LinkList L, KeyType key, LinkList & LResult)				//在链表中查找关键字所在的节点
{
	/*L：指向被查找的链表，key：被查找的关键字，LResult：指向含有目标关键字的节点
	**查找成功，返回Success；查找失败，返回Error
	*/
	LResult = L;			//初始LResult应指向链表头
	LinkList L_tmp = L->next;
	Status result = Error;
	while (L_tmp)
	{
		LResult = L_tmp;
		int tmp = Compare(L_tmp->elem.key, key);
		if (tmp == 0)
		{
			result = Success;
			break;
		}
		L_tmp = L_tmp->next;
	}
	return result;
}

Status InsertNode(LinkList L, KeyType key)			//在链表中插入节点
{
	/*L：指向要插入的链表，key：要插入的关键字
	**插入成功，返回Success；插入失败（链表中已有该节点），返回Error
	*/
	LinkList LPosition = NULL;
	if (SearchNode(L, key, LPosition))		//已有该关键字，插入失败
		return Error;
	else
	{
		LinkList NewNode = new LinkNode;
		NewNode->elem.key = key;
		NewNode->next = NULL;
		NewNode->last = LPosition;
		LPosition->next = NewNode;		//将含有关键字的节点插入末尾
		return Success;
	}
}

Status DeleteNode(LinkList L, KeyType key)			//在链表中删除节点
{
	/*L：指向要删除的链表，key：要删除的关键字
	**删除成功，返回Success；删除失败（链表中已有该节点），返回Error
	*/
	LinkList LPosition = NULL;
	if (!SearchNode(L, key, LPosition))		//未找到该关键字，删除失败
		return Error;
	else
	{
		if (LPosition->next)		//含有关键字的节点还有下一个节点
		{
			LPosition->last->next = LPosition->next;			//调整指针
			LPosition->next->last = LPosition->last;
		}
		else
			LPosition->last->next = NULL;			//调整指针
		delete LPosition;		//释放节点
		return Success;
	}
}
