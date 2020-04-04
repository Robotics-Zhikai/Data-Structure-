#include<stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Stack.h"
using namespace std;



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
	NodeStackAddress NewNode = (NodeStackAddress)malloc(sizeof(NodeStack));
	Result->Next = NewNode;
	Result->top = NewNode;
	NewNode->Next = NULL;
	NodeStackAddress Storage;
	Storage = NewNode;
	for (int i = 1; i < MaxSize; i++)
	{
		NodeStackAddress NewNode1 = (NodeStackAddress)malloc(sizeof(NodeStack));
		Storage->Next = NewNode1;
		Storage = NewNode1;
	}
	Storage->Next = NULL;
	return Result;
}

int IsStackEmpty(StackInfoAddress s)
{
	if ((s->Next == NULL) || (s->Next == s->top))
		return 1;
	else
		return 0;
}

int IsStackFull(StackInfoAddress s)
{
	if (IsStackEmpty(s))
		return 0;
	if (s->top == NULL)
		return 1;
	else
		return 0;
}

void StackPush(StackInfoAddress s, ElementTypeStack element)
{
	if (element == ERROR)
		return;
	if (IsStackFull(s) == 1)
		return;
	else
	{
		s->top->Data = element;
		s->top = s->top->Next;
	}
}

ElementTypeStack StackPop(StackInfoAddress s)
{
	if (IsStackEmpty(s) == 1)
	{
		return ERROR;
	}
	NodeStackAddress temp = s->Next;
	NodeStackAddress tempNext = temp->Next;

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

ElementTypeStack GetTopStackData(StackInfoAddress stack) // 得到栈顶元素值
{
	if (IsStackEmpty(stack) == 1) //无法得到栈顶元素值栈为空
		return ERROR;
	NodeStackAddress temp;
	temp = stack->Next;
	while (temp != NULL)
	{
		if (temp->Next == stack->top)
			return temp->Data;
		temp = temp->Next;
	}
}