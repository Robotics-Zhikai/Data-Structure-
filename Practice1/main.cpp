#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Linear.h"
using namespace std;


//本题要求实现一个函数，将两个链表表示的递增整数序列合并为一个非递减的整数序列。
//这里边包含基本的线性表的链表数据结构实现操作，并加上了COPY函数 不是所有函数都经过测试


List Read(); /* 细节在此不表 */


List Merge(List* L1, List* L2);

//List Read()
//{
//	List CreatedList;
//
//	CreatedList = (List)malloc(sizeof(List));
//	ElementType DataThis;
//	cout << "输入此链表的各个数据.以99999结尾"<<endl;
//	//scanf("%d", &DataThis);
//	cin >> DataThis;
//	if (DataThis == 99999)
//	{
//		CreatedList = NULL;
//		cout << "空链表"<<endl;
//		return CreatedList;
//	}
//	CreatedList->Data = DataThis;
//	CreatedList->Next = NULL;
//	for (int i = 0;; i++)
//	{
//		cin >> DataThis;
//		if (DataThis == 99999)
//		{
//			break;
//		}
//		List templist = (List) malloc(sizeof(List));
//		List temp = CreatedList;
//		List tempstorage;
//		for (; temp != NULL; )
//		{
//			tempstorage = temp;
//			temp = temp->Next;
//		}
//		tempstorage->Next = templist;
//		templist->Data = DataThis;
//		templist->Next = NULL;
//	}
//	return CreatedList;
//}

List Read()
{
	List CreatedList;
	ElementType DataThis;
	cout << "输入此链表的各个数据.以99999结尾" << endl;
	cin >> DataThis;
	if (DataThis == 99999)
	{
		CreatedList = NULL;
		cout << "输入了一个空链表"<<endl;
		return CreatedList;
	}
	CreatedList = (List)malloc(sizeof(Node));
	CreatedList->Next = NULL;
	CreatedList->Data = DataThis;
	while (1)
	{
		cin >> DataThis;
		if (DataThis == 99999)
			break;
		CreatedList = Insert(DataThis,(Length(CreatedList) + 1), CreatedList);
	}
	return CreatedList;
}


List Merge(List * L11, List * L22)
{
	List L1 = *L11;
	List L2 = *L22;
	if ((L1 == NULL) && (L2 != NULL))
		return L2;
	if ((L2 == NULL) && (L1 != NULL))
		return L1;
	if ((L1 == NULL) && (L2 == NULL))
		return NULL;
	int num = 1;
	for (int i = 1; i <= Length(L2); i++) //L2往L1里插
	{
		ElementType L2i = FindKth(i, L2);
		for (int j = num; j < Length(L1); j++)
		{
			ElementType L1j = FindKth(j, L1);
			ElementType L1jplus1 = FindKth(j+1, L1);
			if ((L2i>=L1j)&&(L2i<= L1jplus1))
			{
				L1 = Insert(L2i, j + 1, L1);
				num = j;
				break;
			}
			else if ((L2i > L1jplus1) && j == (Length(L1) - 1))
			{
				L1 = Insert(L2i, j + 2, L1);
				num = j;
				break;
			}
		}

	}
	List L3=NULL;
	CopyL(&L3, &L1);
	Delete(1, &L1);
	*L11 = NULL;
	Delete(1, &L2);
	*L22 = NULL;
	return L3;
}


int main()
{
	List L1, L2, L;
	L1 = Read();
	L2 = Read();
	/*CopyL(&L1, &L2);*/

	L = Merge(&L1, &L2);
	Print(L);
	Print(L1);
	Print(L2);
	return 0;
}

/* 你的代码将被嵌在这里 */