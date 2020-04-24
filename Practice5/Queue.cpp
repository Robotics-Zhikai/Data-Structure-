#include<stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Queue.h"

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
	NodeQueueAddress HeadNode = (NodeQueueAddress)malloc(sizeof(NodeQueue));
	NodeQueueAddress temp = HeadNode;
	int num = 0;
	while (temp != NULL)
	{
		num++;
		NodeQueueAddress NewNode = (NodeQueueAddress)malloc(sizeof(NodeQueue));
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

int IsQueueEmpty(QueueInfoAddress Queue)
{
	if ((Queue->Front == NULL) && (Queue->Rear == NULL))
		return 1;
	if (Queue->Rear == Queue->HeadNode)
		return 1;
	else
		return 0;
}

int IsQueuefull(QueueInfoAddress Queue)
{
	if (IsQueueEmpty(Queue) == 1)
		return 0;
	if (Queue->Front == Queue->Rear)
		return 1;
}

QueueInfoAddress QueuePush(QueueInfoAddress Queue, ElementTypeQueue data)
{
	if ((Queue->Front == NULL) && (Queue->Rear == NULL)) //说明是空队列 完全没有队列结构
		return Queue;
	if (IsQueuefull(Queue) == 1)
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

ElementTypeQueue QueuePop(QueueInfoAddress Queue)
{
	if (IsQueueEmpty(Queue) == 1)
		return ERROR;
	if (Queue->Rear->Next == Queue->Front)
	{
		ElementTypeQueue num;
		num = Queue->Rear->Data;
		Queue->Front = Queue->HeadNode->Next;
		Queue->Rear = Queue->HeadNode;
		return num;
	}
	ElementTypeQueue num1 = Queue->Rear->Data;
	Queue->Rear = Queue->Rear->Next;
	return num1;
}
