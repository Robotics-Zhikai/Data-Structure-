#ifndef STACK_H
#define STACK_H
#define ERROR NULL //����ض�ElementTypeStack�в�ͬ�ķ�������ֵ
#include "Queue.h"
typedef struct NodeStack * NodeStackAddress;
typedef struct StackInfo * StackInfoAddress;

//typedef struct TreeNode * TreeNodeAddress;
//struct TreeNode
//{
//	int NumNode; //���ı��
//	int left;
//	int right;
//};
//typedef struct ListNode * ListNodeAddress;
//struct ListNode
//{
//	TreeNodeAddress TreeNodeAdd;
//	int Root;//������ڵ���
//	ListNodeAddress Next;
//};
typedef ListNodeAddress ElementTypeStack;

struct StackInfo
{
	NodeStackAddress top;
	NodeStackAddress Next;
};

struct NodeStack
{
	ElementTypeStack Data;
	NodeStackAddress Next;
};

StackInfoAddress CreatStack(int MaxSize);

int IsStackEmpty(StackInfoAddress s);

int IsStackFull(StackInfoAddress s);

void StackPush(StackInfoAddress s, ElementTypeStack element);

ElementTypeStack StackPop(StackInfoAddress s);

ElementTypeStack GetTopStackData(StackInfoAddress stack);// �õ�ջ��Ԫ��ֵ

#endif