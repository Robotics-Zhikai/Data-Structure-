/*Given a tree, you are supposed to list all the leaves in the order of top down, and left to right.

Input Specification :
Each input file contains one test case.For each case, the first line gives a positive integer N(≤10) which is the total number of nodes in the tree-- and hence the nodes are numbered from 0 to N−1.Then N lines follow, each corresponds to a node, and gives the indices of the left and right children of the node.If the child does not exist, a "-" will be put at the position.Any pair of children are separated by a space.

Output Specification :
For each test case, print in one line all the leaves' indices in the order of top down, and left to right. There must be exactly one space between any adjacent numbers, and no extra space at the end of the line.

Sample Input :
8
1 -1
-1 -1
0 -1
2 7
-1 -1
-1 -1
5 -1
4 6



Sample Output :
4 1 5*/
//二叉树
#include <iostream>
#include <stdio.h>
#include<stdlib.h>
#include "Queue.h"
#include "Stack.h"
using namespace std;

int LengthList(ListNodeAddress List)
{
	int num = 0;
	ListNodeAddress temp = List->Next;
	while (temp != NULL)
	{
		num++;
		temp = temp->Next;
	}
	return num;
}

ListNodeAddress FindNumNodeAddress(ListNodeAddress List, int NumNode)
{
	ListNodeAddress temp = List->Next;
	while (temp != NULL)
	{
		if (temp->TreeNodeAdd->NumNode == NumNode)
		{
			return temp;
		}
		temp = temp->Next;
	}
	return NULL;
}

void LevelOrderTraversalQueue(ListNodeAddress list , int TreeNum)//层次遍历用队列非常方便
{
	if (LengthList(list) == 0)
	{
		printf("空树，无法层序遍历!\n");
		return;
	}
	ListNodeAddress temp = list->Next;
	ListNodeAddress NewNodeAddressAddress = FindNumNodeAddress(list, list->Root);
	QueueInfoAddress QueueNew = CreateQueue(TreeNum+5);
	QueueNew = QueuePush(QueueNew, NewNodeAddressAddress);
	while (IsQueueEmpty(QueueNew)==0)
	{
		ElementTypeQueue PopElement = QueuePop(QueueNew);
		/*if ((PopElement->TreeNodeAdd->left ==-1)&&(PopElement->TreeNodeAdd->right == -1))
		{
			printf("%d ", PopElement->TreeNodeAdd->NumNode);
		}*/
		printf("%d ", PopElement->TreeNodeAdd->NumNode);
		if (PopElement->TreeNodeAdd->left != -1)
		{
			QueueNew = QueuePush(QueueNew, FindNumNodeAddress(list, PopElement->TreeNodeAdd->left));
		}
		if (PopElement->TreeNodeAdd->right != -1)
		{
			QueueNew = QueuePush(QueueNew, FindNumNodeAddress(list, PopElement->TreeNodeAdd->right));
		}
	}
}

void PreOrderTraversalStack(ListNodeAddress List, int TrrNum)
{
	StackInfoAddress StackNew = CreatStack(TrrNum);
	ListNodeAddress NumNodeAddress = FindNumNodeAddress(List, List->Root);
	StackPush(StackNew, NumNodeAddress);
	printf("%d ", NumNodeAddress->TreeNodeAdd->NumNode);
	while (IsStackEmpty(StackNew)==0)
	{
		while (NumNodeAddress->TreeNodeAdd->left != -1)
		{
			NumNodeAddress = FindNumNodeAddress(List, NumNodeAddress->TreeNodeAdd->left);
			StackPush(StackNew, NumNodeAddress);
			printf("%d ", NumNodeAddress->TreeNodeAdd->NumNode);
		}
		ElementTypeStack PopElement = StackPop(StackNew);
		NumNodeAddress = FindNumNodeAddress(List, PopElement->TreeNodeAdd->right);
		while ((NumNodeAddress == NULL)&& (IsStackEmpty(StackNew) == 0))
		{
			NumNodeAddress = StackPop(StackNew);
			NumNodeAddress = FindNumNodeAddress(List, NumNodeAddress->TreeNodeAdd->right);
		}
		StackPush(StackNew, NumNodeAddress);
		if (NumNodeAddress!=NULL)
			printf("%d ", NumNodeAddress->TreeNodeAdd->NumNode);
		/*if (PopElement->TreeNodeAdd->right != -1)
		{
			NumNodeAddress = FindNumNodeAddress(List, PopElement->TreeNodeAdd->right);
			StackPush(StackNew, NumNodeAddress);
		}*/
	}
}

void InOrderTraversalStack(ListNodeAddress List, int TrrNum)
{
	StackInfoAddress StackNew = CreatStack(TrrNum);
	ListNodeAddress NumNodeAddress = FindNumNodeAddress(List, List->Root);
	StackPush(StackNew, NumNodeAddress);
	while (IsStackEmpty(StackNew)==0)
	{
		while (NumNodeAddress->TreeNodeAdd->left != -1)
		{
			NumNodeAddress = FindNumNodeAddress(List, NumNodeAddress->TreeNodeAdd->left);
			StackPush(StackNew, NumNodeAddress);
		}
		ElementTypeStack PopElement = StackPop(StackNew);
		printf("%d ", PopElement->TreeNodeAdd->NumNode);
		NumNodeAddress = FindNumNodeAddress(List, PopElement->TreeNodeAdd->right);
		while ((NumNodeAddress == NULL)&& (IsStackEmpty(StackNew) == 0))
		{
			NumNodeAddress = StackPop(StackNew);
			printf("%d ", NumNodeAddress->TreeNodeAdd->NumNode);
			NumNodeAddress = FindNumNodeAddress(List, NumNodeAddress->TreeNodeAdd->right);
		}
		StackPush(StackNew, NumNodeAddress);

		/*if (PopElement->TreeNodeAdd->right != -1)
		{
			NumNodeAddress = FindNumNodeAddress(List, PopElement->TreeNodeAdd->right);
			StackPush(StackNew, NumNodeAddress);
		}*/
	}
}

void PostOrderTraversalStack(ListNodeAddress List, int TrrNum)                                //这个死活不会！！！！！！！搞不了 终于搞定了！！！
{
	StackInfoAddress StackNew = CreatStack(TrrNum);
	ListNodeAddress NumNodeAddress = FindNumNodeAddress(List, List->Root);
	ListNodeAddress Storage;
	ListNodeAddress StorageVisit = NULL;
	while (NumNodeAddress != NULL)
	{
		StackPush(StackNew, NumNodeAddress);
		NumNodeAddress = FindNumNodeAddress(List, NumNodeAddress->TreeNodeAdd->left);
	}
	while ((IsStackEmpty(StackNew) == 0))
	{
		NumNodeAddress = StackPop(StackNew);
		Storage = NumNodeAddress;
		NumNodeAddress = FindNumNodeAddress(List, NumNodeAddress->TreeNodeAdd->right);
		if ((NumNodeAddress == NULL)|| (NumNodeAddress == StorageVisit))
		{
			//ListNodeAddress temp = StackPop(StackNew);
			StorageVisit = Storage;
			printf("%d ", Storage->TreeNodeAdd->NumNode);
			//printf("%d ", Storage->TreeNodeAdd->NumNode);
		}
		else
		{
			StackPush(StackNew, Storage);
			ListNodeAddress temp = NumNodeAddress;
			while (temp != NULL)
			{
				StackPush(StackNew, temp);
				temp = FindNumNodeAddress(List, temp->TreeNodeAdd->left);
			}
			//printf("%d ", Storage->TreeNodeAdd->NumNode);
		}
	}
}

void PreOrderTraversal(ListNodeAddress List,int ListRoot)
{
	ListNodeAddress NumNodeAddress = FindNumNodeAddress(List, ListRoot);
	if (NumNodeAddress == NULL)
		return;
	printf("%d ", ListRoot);
	ListNodeAddress NumNodeAddressleft = FindNumNodeAddress(List, NumNodeAddress->TreeNodeAdd->left);
	if (NumNodeAddressleft == NULL)
		PreOrderTraversal(List, -1);
	else
		PreOrderTraversal(List, NumNodeAddressleft->TreeNodeAdd->NumNode);

	ListNodeAddress NumNodeAddressright = FindNumNodeAddress(List, NumNodeAddress->TreeNodeAdd->right);
	if (NumNodeAddressright == NULL)
		PreOrderTraversal(List, -1);
	else
		PreOrderTraversal(List, NumNodeAddressright->TreeNodeAdd->NumNode);
}

void InOrderTraversal(ListNodeAddress List, int ListRoot)
{
	ListNodeAddress NumNodeAddress = FindNumNodeAddress(List, ListRoot);
	if (NumNodeAddress == NULL)
		return;
	ListNodeAddress NumNodeAddressleft = FindNumNodeAddress(List, NumNodeAddress->TreeNodeAdd->left);
	if (NumNodeAddressleft == NULL)
		InOrderTraversal(List, -1);
	else
		InOrderTraversal(List, NumNodeAddressleft->TreeNodeAdd->NumNode);

	printf("%d ", ListRoot);

	ListNodeAddress NumNodeAddressright = FindNumNodeAddress(List, NumNodeAddress->TreeNodeAdd->right);
	if (NumNodeAddressright == NULL)
		InOrderTraversal(List, -1);
	else
		InOrderTraversal(List, NumNodeAddressright->TreeNodeAdd->NumNode);
}

void PostOrderTraversal(ListNodeAddress List, int ListRoot)
{
	ListNodeAddress NumNodeAddress = FindNumNodeAddress(List, ListRoot);
	if (NumNodeAddress == NULL)
		return;
	ListNodeAddress NumNodeAddressleft = FindNumNodeAddress(List, NumNodeAddress->TreeNodeAdd->left);
	if (NumNodeAddressleft == NULL)
		PostOrderTraversal(List, -1);
	else
		PostOrderTraversal(List, NumNodeAddressleft->TreeNodeAdd->NumNode);

	ListNodeAddress NumNodeAddressright = FindNumNodeAddress(List, NumNodeAddress->TreeNodeAdd->right);
	if (NumNodeAddressright == NULL)
		PostOrderTraversal(List, -1);
	else
		PostOrderTraversal(List, NumNodeAddressright->TreeNodeAdd->NumNode);
	printf("%d ", ListRoot);
}


//用一个线性表储存树结构,并找到根节点
ListNodeAddress CreateTree()
{
	ListNodeAddress Result = (ListNodeAddress)malloc(sizeof(ListNode));
	ListNodeAddress temp = Result;
	int num;
	int Allnum;
	scanf("%d", &Allnum);
	if (Allnum == 0)
		Result->Root = -1;
	for (int i = 0; i < Allnum; i++)
	{
		ListNodeAddress NewNode = (ListNodeAddress)malloc(sizeof(ListNode));
		temp->Next = NewNode;
		TreeNodeAddress NewTreeNode = (TreeNodeAddress)malloc(sizeof(TreeNode));
		NewNode->TreeNodeAdd = NewTreeNode;
		NewTreeNode->NumNode = i;
		scanf("%d", &num);
		NewTreeNode->left = num;
		scanf("%d", &num);
		NewTreeNode->right = num;
		//NewNode->TreeNodeAdd = 
		temp = temp->Next;
	}
	temp->Next = NULL;

	typedef struct Nodetemp * NodetempAddress;
	struct Nodetemp
	{
		int num;
		int flag;
		NodetempAddress Next;
	};
	NodetempAddress tempListNode = (NodetempAddress)malloc(sizeof(Nodetemp));
	NodetempAddress temptemp = tempListNode;
	for (int i = 0; i < Allnum; i++)
	{
		temptemp->Next = (NodetempAddress)malloc(sizeof(Nodetemp));
		temptemp->Next->num = i;
		temptemp->Next->flag = 0;
		temptemp = temptemp->Next;
	}
	temptemp->Next = NULL;

	temp = Result->Next;
	while (temp != NULL)
	{
		temptemp = tempListNode->Next;
		while (temptemp != NULL)
		{
			if (temp->TreeNodeAdd->left == temptemp->num)
			{
				temptemp->flag = 1;
				break;
			}
				temptemp = temptemp->Next;
		}

		temptemp = tempListNode->Next;
		while (temptemp != NULL)
		{
			if (temp->TreeNodeAdd->right == temptemp->num)
			{
				temptemp->flag = 1;
				break;
			}
			temptemp = temptemp->Next;
		}

		temp = temp->Next;
	}

	temptemp = tempListNode->Next;
	while (temptemp != NULL)
	{
		if (temptemp->flag == 0)
		{
			Result->Root = temptemp->num;
			break;
		}
		temptemp = temptemp->Next;
	}

	return Result;
}

int main()
{
	/*
	16
	1 2
	3 4
	5 12
	6 -1
	7 8
	-1 -1
	9 -1
	-1 -1
	-1 -1
	10 11
	-1 -1
	-1 -1
	13 -1
	14 15
	-1 -1
	-1 -1
	
	*/
	ListNodeAddress List = CreateTree();
	int TreeNum = LengthList(List);
	LevelOrderTraversalQueue(List,TreeNum);
	cout << endl;

	PreOrderTraversalStack(List, TreeNum);
	cout << endl;
	PreOrderTraversal(List, List->Root);
	cout << endl;

	InOrderTraversalStack(List, TreeNum);
	cout << endl;
	InOrderTraversal(List, List->Root);
	cout << endl;

	PostOrderTraversalStack(List, TreeNum);
	cout << endl;
	PostOrderTraversal(List, List->Root);
	cout << endl;
}