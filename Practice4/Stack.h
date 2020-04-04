#ifndef STACK_H
#define STACK_H
#define ERROR NULL //针对特定ElementTypeStack有不同的返回特殊值
#include "Queue.h"
typedef struct NodeStack * NodeStackAddress;
typedef struct StackInfo * StackInfoAddress;

//typedef struct TreeNode * TreeNodeAddress;
//struct TreeNode
//{
//	int NumNode; //树的编号
//	int left;
//	int right;
//};
//typedef struct ListNode * ListNodeAddress;
//struct ListNode
//{
//	TreeNodeAddress TreeNodeAdd;
//	int Root;//储存根节点编号
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

ElementTypeStack GetTopStackData(StackInfoAddress stack);// 得到栈顶元素值

#endif