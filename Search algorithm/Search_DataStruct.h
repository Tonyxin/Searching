#ifndef SEARCH_DATASTRUCT_H
#define SEARCH_DATASTRUCT_H

#include <math.h>
#include <string.h>

enum Status{ Success = 1, Error = 0, Duplicate = -1 };
enum deplth{ LH = 1, EH = 0, RH = -1 };				//LE��ʾ��������ȱ���������ȶ�2

//����ؼ��ֵ�����
//typedef float KeyType;			//�ؼ���Ϊ������
typedef int KeyType;					//�ؼ���Ϊ����
//typedef char* KeyType;			//�ؼ���Ϊ�ַ�����

//Ԫ�����ͣ���һ���ṹ���ʾ
typedef struct ElemType
{
	KeyType key;			//�ؼ�����
	float weight;			//ÿ��Ԫ�ص�Ȩ��
	int position;			//Ԫ���ڱ��е�λ��
	//��������				//Ԫ�ص�������Ϣ
}ElemType;

//��̬��洢
typedef struct SStable
{
	ElemType * elem;				//��̬��洢�ռ��ַ������ʱ����ʵ�ʳ��ȣ���λ����
	int length;							//��̬���ʵ�ʳ��ȣ����������10����ЧԪ�أ����е�0�����գ�����ӦΪ11��
}SStable;

//�������Ķ�������洢
typedef struct BiTNode
{
	ElemType data;					//�ڵ�����
	struct BiTNode *lchild, *rchild;			//��������
}BiTNode, *BiTree;

//ƽ��������Ĵ洢�ṹ
typedef struct BSTNode
{
	ElemType data;		//�ڵ�����
	deplth bf;				//ƽ������
	struct BSTNode *lchild, *rchild;		//��������
}BSTNode, *BSTtree;


//B-���Ĵ洢�ṹ
#define m 3								//B-���Ľף��ݶ�Ϊ3��ֻ֧��mΪ���������
#define Minus_Infinity -10000	//����key[0]Ϊ������
typedef struct BTNode
{
	int keynum;							//�ڵ��йؼ��ֵĸ���
	struct BTNode *parent;			//ָ��˫�׽ڵ�
	KeyType key[m + 1];				//һ���ڵ��������m-1���ؼ��֣�0�ŵ�Ԫδ��
	struct BTNode *ptr[m + 1];	//����ָ������
}BTNode, *BTree;
typedef struct
{
	BTNode* pt;							//ָ���ҵ��Ľڵ�
	int i;										//1..m���ڽڵ��еĹؼ������
	bool flag;								//���ҽ����1��ʾ�ɹ���0��ʾʧ��
}Result;										//B-�����ҽ������

//��ϣ��Ĵ洢�ṹ
typedef struct LinkNode
{
	LinkNode *last;				//ָ����ָ���������һ�ڵ�
	ElemType elem;				//�����򣬴洢�йؼ���
	LinkNode *next;			//ָ����ָ���������һ�ڵ�
}LinkNode, *LinkList;
#define hashsize 100	//��ϣ��Ĵ洢����
typedef struct
{
	LinkList hash[hashsize];		//�������ӷ������ͻ
}HashTable;


//�ȽϺ�������ߴ󣬷���1��һ���󣬷���0���ұߴ󣬷���-1
int Compare(int, int);
int Compare(float, float);
int Compare(char*, char*);

//��������Ĳ����������ɹ�����Success��ʧ�ܷ���Error
Status SearchNode(LinkList L, KeyType key, LinkList &LResult);			//�������в��ҹؼ������ڵĽڵ�
Status InsertNode(LinkList L, KeyType key);			//�������в���ڵ�
Status DeleteNode(LinkList L, KeyType key);			//��������ɾ���ڵ�

#endif