#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Linear.h"
using namespace std;


//����Ҫ��ʵ��һ�������������������ʾ�ĵ����������кϲ�Ϊһ���ǵݼ����������С�
//����߰������������Ա���������ݽṹʵ�ֲ�������������COPY���� �������к�������������


List Read(); /* ϸ���ڴ˲��� */


List Merge(List* L1, List* L2);

//List Read()
//{
//	List CreatedList;
//
//	CreatedList = (List)malloc(sizeof(List));
//	ElementType DataThis;
//	cout << "���������ĸ�������.��99999��β"<<endl;
//	//scanf("%d", &DataThis);
//	cin >> DataThis;
//	if (DataThis == 99999)
//	{
//		CreatedList = NULL;
//		cout << "������"<<endl;
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
	cout << "���������ĸ�������.��99999��β" << endl;
	cin >> DataThis;
	if (DataThis == 99999)
	{
		CreatedList = NULL;
		cout << "������һ��������"<<endl;
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
	for (int i = 1; i <= Length(L2); i++) //L2��L1���
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

/* ��Ĵ��뽫��Ƕ������ */