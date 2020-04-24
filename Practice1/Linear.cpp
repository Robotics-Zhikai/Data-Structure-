#include "Linear.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
void CopyL(List * L11, List * L33) //复制L3到L1
{
	List L1 = *L11;
	List L3 = *L33;
	//int LengthL3 = Length(L3);
	//int LengthL1 = Length(L1);
	List temp = L1;
	List temp3 = L3;
	if ((temp == NULL) && (temp3 == NULL))
	{
		*L11 = L1;
		return;
	}
	while ((temp != NULL) && (temp3 != NULL))
	{
		temp->Data = temp3->Data;
		temp3 = temp3->Next;
		temp = temp->Next;
	}
	if (temp == NULL)
	{
		temp = temp3;
		while (temp != NULL)
		{
			L1 = Insert(temp->Data, (Length(L1) + 1), L1);
			temp = temp->Next;
		}
	}
	if (temp3 == NULL)
	{
		for (int i = Length(L1); i >= Length(L3) + 1; i--)
		{
			Delete(i, &L1);
		}
	}
	*L11 = L1;
}

ElementType FindKth(int K, List L)//根据位序K，返回相应元素 头结点带数据，位序为1
{
	if (K <= 0)
	{
		cout << "K应该大于0！";
		return -1;
	}
	int Num = 0;
	List temp = L;
	while (temp != NULL)
	{
		Num++;
		if (Num == K)
		{
			return temp->Data;
		}
		temp = temp->Next;
	}
	cout << "K超出数据范围！返回0" << endl;
	return 0;
}

int Find(ElementType X, List L)  //在线性表L中找到第一次出现X的位置
{
	if (L == NULL)
		cout << "链表为空" << endl;
	List temp = L;
	int num = 0;
	while (temp != NULL)
	{
		num++;
		if (temp->Data == X)
			return num;
		temp = temp->Next;
	}
	cout << "在该链表中没有找到该数" << endl;
}

List Insert(ElementType X, int i, List L) //在位序i前插入一个新元素X
{
	if (i < 1)
	{
		cout << "i应该大于1" << endl;
		return L;
	}
	if ((L == NULL) && (i == 1))
	{
		List newNode = (List)malloc(sizeof(Node));
		newNode->Data = X;
		newNode->Next = NULL;
		return newNode;
	}
	if ((L != NULL) && (i == 1))
	{
		List newNode = (List)malloc(sizeof(Node));
		newNode->Data = X;
		newNode->Next = L;
		return newNode;
	}
	int num = 0;
	List temp = L;
	List tempStorage;
	while (temp != NULL)
	{
		num++;
		tempStorage = temp;
		temp = temp->Next;
		if (num == i - 1)
		{
			List malloclist = (List)malloc(sizeof(Node));
			malloclist->Data = X;
			malloclist->Next = temp;
			tempStorage->Next = malloclist;
			break;
		}
	}
	if (num != i - 1)
		cout << "i大于链表的节点数量,插入失败" << endl;
	return L;
}

void Delete(int i, List * L1)//删除指定位序i的元素 删除位序为1的元素时，删除整个链表
{
	List L = *L1;
	if (L == NULL)
	{
		cout << "L为空链表,删除失败" << endl;
		return;
	}
	if (i == 1)
	{
		cout << "i为1时表示删除头结点，相当于把链表删除了" << endl;
		List temp = L;
		for (int a = Length(L); a >1; a--)
		{
			Delete(a, &L);
		}
		free(L);
		*L1 = NULL;
		return;
	}
	List temp;
	int num = 0;
	temp = L;
	while (temp != NULL)
	{
		num++;
		if ((num == i - 1) && (temp->Next != NULL))
		{
			List tempstorage = temp->Next;
			temp->Next = tempstorage->Next;
			free(tempstorage);
			tempstorage = NULL;
			return;
		}
		temp = temp->Next;
	}
	cout << "位序i超过了链表长度，无法删除!" << endl;
}

int Length(List L) //返回线性表的长度
{
	List temp;
	temp = L;
	int num = 0;
	while (temp != NULL)
	{
		num++;
		temp = temp->Next;
	}
	return num;
}

List GetLocation(ElementType i, List L) //返回链表L中位序为i的地址
{
	if (i <= 0)
	{
		cout << "位序应为大于0的数" << endl;
		return 0;
	}
	List temp;
	temp = L;
	int num = 0;
	while (temp != NULL)
	{
		num++;
		if (num == i)
		{
			return temp;
		}
		temp = temp->Next;
	}
	cout << "位序大于链表所有节点的个数了" << endl;
}

void Print(List L)
{
	if (L == NULL)
	{
		cout << "链表为NULL" << endl;
		return;
	}
	List temp = L;
	List tempstorage;
	for (; temp != NULL;)
	{
		tempstorage = temp;
		temp = temp->Next;
		cout << tempstorage->Data << " ";
	}
	cout << endl;
}
