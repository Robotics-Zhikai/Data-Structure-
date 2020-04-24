/*Given a stack which can keep M numbers at most. Push N numbers in the order of 1, 2, 3, ..., N and pop randomly. You are supposed to tell if a given sequence of numbers is a possible pop sequence of the stack. For example, if M is 5 and N is 7, we can obtain 1, 2, 3, 4, 5, 6, 7 from the stack, but not 3, 2, 1, 7, 5, 6, 4.

Input Specification:
Each input file contains one test case. For each case, the first line contains 3 numbers (all no more than 1000): M (the maximum capacity of the stack), N (the length of push sequence), and K (the number of pop sequences to be checked). Then K lines follow, each contains a pop sequence of N numbers. All the numbers in a line are separated by a space.

Output Specification:
For each pop sequence, print in one line "YES" if it is indeed a possible pop sequence of the stack, or "NO" if not.

Sample Input:
5 7 5
1 2 3 4 5 6 7
3 2 1 7 5 6 4
7 6 5 4 3 2 1
5 6 4 3 7 2 1
1 7 6 5 4 3 2

      
    
Sample Output:
YES
NO
NO
YES
NO*/





#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

typedef struct Node * NodeAddress;
typedef NodeAddress Stack;
typedef struct StackInfo * StackInfoAddress;
struct StackInfo
{
	NodeAddress top;
	NodeAddress Next;
};

struct Node
{
	int Data;
	NodeAddress Next;
};

StackInfoAddress CreatStack(int MaxSize)
{
	if (MaxSize == 0)
	{
		StackInfoAddress Result = (StackInfoAddress)malloc(sizeof(StackInfo));
		Result->Next = NULL;
		Result->top = NULL;
		return Result;
	}
	StackInfoAddress Result = (StackInfoAddress)malloc(sizeof(StackInfo));
	NodeAddress NewNode = (NodeAddress)malloc(sizeof(Node));
	Result->Next = NewNode;
	Result->top = NewNode;
	NewNode->Next = NULL;
	NodeAddress Storage;
	Storage = NewNode;
	for (int i = 1; i < MaxSize; i++)
	{
		NodeAddress NewNode1 = (NodeAddress)malloc(sizeof(Node));
		Storage->Next = NewNode1;
		Storage = NewNode1;
	}
	Storage->Next = NULL;
	return Result;
}

int IsEmpty(StackInfoAddress s)
{
	if ((s->Next == NULL) || (s->Next == s->top))
		return 1;
	else
		return 0;
}

int IsFull(StackInfoAddress s)
{
	if (IsEmpty(s))
		return 0;
	if (s->top == NULL)
		return 1;
	else
		return 0;
}

void Push(StackInfoAddress s, int element)
{
	if (IsFull(s) == 1)
		return;
	else
	{
		s->top->Data = element;
		s->top = s->top->Next;
	}
}

int Pop(StackInfoAddress s)
{
	if (IsEmpty(s) == 1)
	{
		return -1;
	}
	NodeAddress temp = s->Next;
	NodeAddress tempNext = temp->Next;

	while (tempNext != NULL)
	{
		if (s->top == tempNext)
		{
			s->top = temp;
			return s->top->Data;
		}
		tempNext = tempNext->Next;
		temp = temp->Next;
	}
	s->top = temp;
	return s->top->Data;
}

int GetTopStackData(StackInfoAddress stack) // 得到栈顶元素值
{
	if (IsEmpty(stack) == 1) //无法得到栈顶元素值栈为空
		return -1;
	NodeAddress temp;
	temp = stack->Next;
	while (temp != NULL)
	{
		if (temp->Next == stack->top)
			return temp->Data;
		temp = temp->Next;
	}
}

NodeAddress ReadOneline(int maxnumN) //头结点什么都没有
{
	if (maxnumN == 0)
		return NULL;
	NodeAddress FirstNode = (NodeAddress)malloc(sizeof(Node));
	NodeAddress storage = FirstNode;
	for (int i = 0; i < maxnumN; i++)
	{
		NodeAddress NewNode = (NodeAddress)malloc(sizeof(Node));
		int num;
		scanf("%d", &num);
		NewNode->Data = num;
		storage->Next = NewNode;
		storage = NewNode;
	}
	storage->Next = NULL;
	return FirstNode;
}

typedef struct linenode * linenodeAddress;
struct linenode
{
	NodeAddress rownext;
	linenodeAddress verticalnext;
};

linenodeAddress Readmatrix(int linenum,int maxnumN)
{
	if ((linenum == 0)||(maxnumN==0))
		return NULL;
	linenodeAddress First = (linenodeAddress)malloc(sizeof(linenode));
	linenodeAddress Result = First;
	First->rownext = ReadOneline(maxnumN);
	First->verticalnext = NULL;
	for (int i = 1; i < linenum; i++)
	{
		linenodeAddress NewlienNode = (linenodeAddress)malloc(sizeof(linenode));
		NewlienNode->rownext = ReadOneline(maxnumN);
		First->verticalnext = NewlienNode;
		First = First->verticalnext;
	}
	First->verticalnext = NULL;
	return Result;
}

NodeAddress DeleteNode(NodeAddress first, NodeAddress deleteNode)
{
	NodeAddress temp = first->Next;
	NodeAddress NodeStorage = first;
	while (temp != NULL)
	{
		if (temp == deleteNode)
		{
			NodeStorage->Next = temp->Next;
			free(temp);
			break;
		}
		NodeStorage = temp;
		temp = temp->Next;
	}
	return first;
}

NodeAddress GenerateDataOneLine(int maxnumN) //生成1-maxnumN的全排列的其中一个
{
	if (maxnumN == 0)
	{
		NodeAddress temp = (NodeAddress)malloc(sizeof(Node));
		temp->Next = NULL;
		return temp;
	}
	NodeAddress temp = (NodeAddress)malloc(sizeof(Node));
	NodeAddress storage = temp;
	for (int i = 1; i <= maxnumN; i++)
	{
		NodeAddress Newnode = (NodeAddress)malloc(sizeof(Node));
		Newnode->Data = i;
		Newnode->Next = NULL;
		temp->Next = Newnode;
		temp = temp->Next;
	}
	temp = storage->Next;
	NodeAddress Result = (NodeAddress)malloc(sizeof(Node));
	NodeAddress tempResult = Result;
	int randamnum = rand() % maxnumN + 1;
	int num = 0;
	while (temp != NULL)
	{
		num++;
		if (num == randamnum)
		{
			NodeAddress Newnode = (NodeAddress)malloc(sizeof(Node));
			Newnode->Data = temp->Data;
			storage = DeleteNode(storage, temp);
			temp = storage->Next;
			Newnode->Next = NULL;
			tempResult->Next = Newnode;
			tempResult = tempResult->Next;
			maxnumN--;
			num = 0;
			if (maxnumN == 0)
				break;
			randamnum = rand() % maxnumN + 1;
			continue;
		}
		temp = temp->Next;
	}
	return Result;
}

void PrintData(int linenum,int maxnumN)
{
	NodeAddress dispfirst;
	for (int i = 0; i < linenum; i++)
	{
		dispfirst = GenerateDataOneLine(maxnumN);
		NodeAddress temp;
		temp = dispfirst->Next;
		while (temp != NULL)
		{
			printf("%d ", temp->Data);
			temp = temp->Next;
		}
		printf("\n");
	}
}

typedef struct QueueInfo * QueueInfoAddress;
struct QueueInfo
{
	NodeAddress Rear;
	NodeAddress Front;
	NodeAddress HeadNode;
};

QueueInfoAddress CreateQueue(int Maxsize)
{
	if (Maxsize == 0)
	{
		QueueInfoAddress Result;
		Result->Front = NULL;
		Result->Rear = NULL;
		return Result;
	}

	QueueInfoAddress Result = (QueueInfoAddress)malloc(sizeof(QueueInfo));
	NodeAddress HeadNode = (NodeAddress)malloc(sizeof(Node));
	NodeAddress temp = HeadNode;
	int num = 0;
	while (temp != NULL)
	{
		num++;
		NodeAddress NewNode = (NodeAddress)malloc(sizeof(Node));
		temp->Next = NewNode;
		temp = temp->Next;
		if (num == Maxsize)
		{
			temp->Next = HeadNode->Next;
			break;
		}
	}
	Result->HeadNode = HeadNode;
	Result->Front = HeadNode->Next;
	Result->Rear = HeadNode;
	return Result;
}

int IsEmptyQueue(QueueInfoAddress Queue)
{
	if ((Queue->Front == NULL) && (Queue->Rear == NULL))
		return 1;
	if (Queue->Rear == Queue->HeadNode)
		return 1;
	else
		return 0;
}

int IsfullQueue(QueueInfoAddress Queue)
{
	if (IsEmptyQueue(Queue) == 1)
		return 0;
	if (Queue->Front == Queue->Rear)
		return 1;
}

QueueInfoAddress PushQueue(QueueInfoAddress Queue,int data)
{
	if ((Queue->Front == NULL) && (Queue->Rear == NULL)) //说明是空队列 完全没有队列结构
		return Queue;
	if (IsfullQueue(Queue) == 1)
		return Queue;
	if (Queue->Rear == Queue->HeadNode)
	{
		Queue->Front->Data = data;
		Queue->Rear = Queue->HeadNode->Next;
		Queue->Front = Queue->Front->Next;
	}
	else
	{
		Queue->Front->Data = data;
		Queue->Front = Queue->Front->Next;
	}
	return Queue;
}

int PopQueue(QueueInfoAddress Queue)
{
	if (IsEmptyQueue(Queue) == 1)
		return -1;
	if (Queue->Rear->Next == Queue->Front)
	{
		int num;
		num = Queue->Rear->Data;
		Queue->Front = Queue->HeadNode->Next;
		Queue->Rear = Queue->HeadNode;
		return num;
	}
	int num1 = Queue->Rear->Data;
	Queue->Rear = Queue->Rear->Next;
	return num1;
}


int CheckValidSequence(NodeAddress rowdata, StackInfoAddress Stack)
{
	if (rowdata->Next == NULL)
		return -1;
	int num = 0;
	NodeAddress temp = rowdata->Next;
	while (temp != NULL)
	{
		num++;
		temp = temp->Next;
	}
	QueueInfoAddress Queue = CreateQueue(num);
	
	temp = rowdata->Next;
	while (temp != NULL)
	{
		PushQueue(Queue, temp->Data);
		temp = temp->Next;
	}
	for (int i = 1; i <= num; i++)
	{
		Push(Stack, i);
		while (IsEmpty(Stack) == 0 && IsEmptyQueue(Queue) == 0&&( GetTopStackData(Stack) == Queue->Rear->Data))
		{
			Pop(Stack);
			PopQueue(Queue);
		}
	}
	if (IsEmpty(Stack) == 1)
		return 1;
	else
		return 0;







	//似乎不用堆栈队列根本不行
	//temp = rowdata->Next;
	//int num1 = 1;
	//while (temp != NULL)
	//{
	//	for (int i = num1; i <= num; i++)
	//	{
	//		if (i != temp->Data)
	//			Push(Stack, i);
	//		else
	//		{
	//			Push(Stack, i);
	//			PushQueue(Queue, temp->Data);
	//			Pop(Stack);
	//			PopQueue(Queue);
	//			num1 = i + 1;
	//			break;
	//		}
	//	}
	//	temp = temp->Next;
	//}
	//if (IsEmpty(Stack))
	//	return 1;
	//else
	//	return 0;

}
int main()
{
	int maxsize;
	scanf("%d", &maxsize);
	int maxnumN;
	scanf("%d", &maxnumN);
	int linenum;
	scanf("%d", &linenum);
	//printf("%d %d %d\n", maxsize, maxnumN, linenum);
	//PrintData(linenum, maxnumN);
	linenodeAddress StorageMatrix;
	StorageMatrix = Readmatrix(linenum, maxnumN);

	StackInfoAddress Stack = CreatStack(maxsize);

	linenodeAddress tempVertical = StorageMatrix;
	while (tempVertical != NULL)
	{
		Stack = CreatStack(maxsize);
		NodeAddress temp = tempVertical->rownext;
		if (CheckValidSequence(temp,  Stack) == 1)
			printf("YES\n");
		else
			printf("NO\n");
		tempVertical = tempVertical->verticalnext;
	}
}