//创建一个普遍的树，即其儿子不一定只有两个，并遍历 n叉树

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include<algorithm>
using namespace std;
/*


*/
typedef struct Node * NodeAddress;
struct Node //储存n叉树的一个节点的下一个节点集合
{
	int NumData;
	NodeAddress Next;
};

typedef struct TreeNode* TreeNodeAddress;
struct TreeNode
{
	int TreeNodeNumData;
	NodeAddress Next;
};

typedef struct TreeListNode * TreeNodeListAdd;
struct TreeListNode
{
	TreeNodeAddress This;
	TreeNodeListAdd Next;
	int RootNum;
};

void AddNode2List(NodeAddress List,int NumData) //往链表的尾端添加数据
{
	NodeAddress temp = List->Next;
	NodeAddress templast = List;
	while (temp != NULL)
	{
		templast = temp;
		temp = temp->Next;
	}
	NodeAddress NewNode = (NodeAddress)malloc(sizeof(Node));
	NewNode->NumData = NumData;
	NewNode->Next = NULL;
	templast->Next = NewNode;
}

TreeNodeListAdd CreateStorageTreeList()
{
	printf("输入待存储的树的数据\n");
	int NumAll;
	scanf("%d", &NumAll);
	TreeNodeListAdd TreeNodeListNew = (TreeNodeListAdd)malloc(sizeof(TreeNodeListAdd));
	TreeNodeListAdd Result = TreeNodeListNew;
	TreeNodeListNew->Next = NULL;
	for (int i = 0; i < NumAll; i++)
	{
		TreeNodeListAdd temp = (TreeNodeListAdd)malloc(sizeof(TreeNodeListAdd));
		temp->This = (TreeNodeAddress)malloc(sizeof(TreeNode));

		temp->This->TreeNodeNumData = i;

		temp->This->Next = (NodeAddress)malloc(sizeof(Node));
		temp->This->Next->Next = NULL;
		int num;
		scanf("%d", &num);
		AddNode2List(temp->This->Next, num);
		while (num != -1)
		{
			scanf("%d", &num);
			AddNode2List(temp->This->Next, num);
		}

		TreeNodeListNew->Next = temp;
		TreeNodeListNew = temp;
	}
	TreeNodeListNew->Next = NULL;

	vector <int> StorageNumCode;
	
	TreeNodeListAdd Temp = Result->Next;
	while (Temp != NULL)
	{
		NodeAddress tempthis = Temp->This->Next;
		while (tempthis != NULL)
		{
			StorageNumCode.push_back(tempthis->NumData);
			tempthis = tempthis->Next;
		}
		Temp = Temp->Next;
	}
	sort(StorageNumCode.begin(), StorageNumCode.end());

	int num = 0;
	for (auto i = StorageNumCode.begin(); i != StorageNumCode.end(); i++)
	{
		if ((*i) == num)
			num++; 
	}
	if (num == NumAll)
	{
		Result->RootNum = -99999;
		printf("树没有根节点\n");
	}
	else
		Result->RootNum = num;
	return Result;
}

TreeNodeListAdd FindNumNodeAddress(TreeNodeListAdd List,int num)
{
	//int root = List->RootNum;
	if (num == -1)
		return NULL;
	TreeNodeListAdd temp = List->Next;
	while (temp != NULL)
	{
		if (temp->This->TreeNodeNumData == num)
			return temp;
		temp = temp->Next;
	}
	return NULL;
}

vector <NodeAddress> GetNodechildrenAdd(TreeNodeListAdd List,int NumNode)
{
	vector <NodeAddress> Result;
	TreeNodeListAdd Add = FindNumNodeAddress(List, NumNode);
	if (Add == NULL)
		return Result;
	NodeAddress temp = Add->This->Next->Next;
	while (temp != NULL)
	{
		Result.push_back(temp);
		temp = temp->Next;
	}
	return Result;
}

NodeAddress GetNodeFirstChildAdd(TreeNodeListAdd List, int NumNode)
{
	TreeNodeListAdd Add = FindNumNodeAddress(List, NumNode);
	if (Add == NULL)
		return NULL;
	NodeAddress temp = Add->This->Next->Next;
	if (temp->NumData == -1)
		return NULL;
	else
		return temp;
}

void PostOrderTraversalOrdinaryStack(TreeNodeListAdd List)                    //这个非递归遍历非常好，容易理解，且后序遍历非常方便
{
	vector <NodeAddress> Stack; //用vector来模拟堆栈
	TreeNodeListAdd temp = FindNumNodeAddress(List, List->RootNum);
	if (temp == NULL)
		return;
	NodeAddress RootNode = (NodeAddress)malloc(sizeof(Node));
	RootNode->NumData = List->RootNum;
	RootNode->Next = NULL;
	Stack.push_back(RootNode);

	NodeAddress tempNodeAddress = temp->This->Next->Next;
	while (Stack.empty() == 0)
	{
		while (tempNodeAddress != NULL)
		{
			Stack.push_back(tempNodeAddress);
			tempNodeAddress = GetNodeFirstChildAdd(List, tempNodeAddress->NumData);
		}
		int flag = 0;
		while (Stack.empty() == 0)
		{
			NodeAddress PopElement = *(Stack.end() - 1);
			Stack.pop_back();
			printf("%d ", PopElement->NumData);
			tempNodeAddress = PopElement->Next;
			while ((tempNodeAddress!=NULL)&&(tempNodeAddress->NumData != -1))
			{
				Stack.push_back(tempNodeAddress);
				NodeAddress tempthis = GetNodeFirstChildAdd(List, tempNodeAddress->NumData);
				if (tempthis != NULL)
				{
					tempNodeAddress = tempthis;
					flag = 1;
					break;
				}
				else
				{
					PopElement = *(Stack.end() - 1);
					Stack.pop_back();
					printf("%d ", PopElement->NumData);
				}

				tempNodeAddress = tempNodeAddress->Next;
			}
			if (flag == 1)
				break;
		}
	}
}

void PreOrderTraversalOrdinaryStack(TreeNodeListAdd List)
{
	vector <NodeAddress> Stack; //用vector来模拟堆栈
	TreeNodeListAdd temp = FindNumNodeAddress(List, List->RootNum);
	if (temp == NULL)
		return;
	NodeAddress RootNode = (NodeAddress)malloc(sizeof(Node));
	RootNode->NumData = List->RootNum;
	RootNode->Next = NULL;
	Stack.push_back(RootNode);
	printf("%d ", RootNode->NumData);

	NodeAddress tempNodeAddress = temp->This->Next->Next;
	while (Stack.empty() == 0)
	{
		while (tempNodeAddress != NULL)
		{
			Stack.push_back(tempNodeAddress);
			printf("%d ", tempNodeAddress->NumData);
			tempNodeAddress = GetNodeFirstChildAdd(List, tempNodeAddress->NumData);
		}
		int flag = 0;
		while (Stack.empty() == 0)
		{
			NodeAddress PopElement = *(Stack.end() - 1);
			Stack.pop_back();
			tempNodeAddress = PopElement->Next;
			while ((tempNodeAddress != NULL) && (tempNodeAddress->NumData != -1))
			{
				Stack.push_back(tempNodeAddress);
				printf("%d ", tempNodeAddress->NumData);
				NodeAddress tempthis = GetNodeFirstChildAdd(List, tempNodeAddress->NumData);
				if (tempthis != NULL)
				{
					tempNodeAddress = tempthis;
					flag = 1;
					break;
				}
				else
				{
					PopElement = *(Stack.end() - 1);
					Stack.pop_back();
				}

				tempNodeAddress = tempNodeAddress->Next;
			}
			if (flag == 1)
				break;
		}
	}

}


void PreOrderTraversalOrdinary(TreeNodeListAdd List,int NumNode)//用递归法遍历
{
	if (NumNode == -1)
		return;
	printf("%d ",NumNode);
	vector <NodeAddress> NodeList = GetNodechildrenAdd(List,NumNode);
	for (auto i = NodeList.begin(); i != NodeList.end(); i++)
	{
		PreOrderTraversalOrdinary(List, (*i)->NumData);
	}
}

void PostOrderTraversalOrdinary(TreeNodeListAdd List, int NumNode)//后序遍历，先访问子节点，后访问根节点
{
	if (NumNode == -1)
		return;
	vector <NodeAddress> NodeList = GetNodechildrenAdd(List, NumNode);
	for (auto i = NodeList.begin(); i != NodeList.end(); i++)
	{
		PostOrderTraversalOrdinary(List, (*i)->NumData);
	}
	printf("%d ", NumNode);
}

int main()
{
	/*
46
1 2 3 -1 
4 5 6 7 -1 
8 -1 
9 10 11 -1 
12 13 -1 
14 -1 
15 -1 
16 17 -1 
18 19 -1 
20 21 -1 
-1
22 23 -1 
24 25 26 27 -1 
-1
-1
-1
-1
-1
28 29 30 31 32 -1 
-1 
-1
-1
-1
-1
-1
-1
34 35 -1
-1
-1
-1
-1
-1
-1
0 -1
-1 
36 -1
37 -1
38 -1
39 -1
40 -1
41 -1
42 -1
43 -1
44 45 -1
-1 
-1 
*/


	TreeNodeListAdd temp = CreateStorageTreeList();

	PreOrderTraversalOrdinary(temp, temp->RootNum);
	cout << endl;
	PreOrderTraversalOrdinaryStack(temp);
	cout << endl;

	PostOrderTraversalOrdinary(temp, temp->RootNum);
	cout << endl;
	PostOrderTraversalOrdinaryStack(temp);
}