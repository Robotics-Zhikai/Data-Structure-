#include "Linear.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
void CopyL(List * L11, List * L33) //����L3��L1
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

ElementType FindKth(int K, List L)//����λ��K��������ӦԪ�� ͷ�������ݣ�λ��Ϊ1
{
	if (K <= 0)
	{
		cout << "KӦ�ô���0��";
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
	cout << "K�������ݷ�Χ������0" << endl;
	return 0;
}

int Find(ElementType X, List L)  //�����Ա�L���ҵ���һ�γ���X��λ��
{
	if (L == NULL)
		cout << "����Ϊ��" << endl;
	List temp = L;
	int num = 0;
	while (temp != NULL)
	{
		num++;
		if (temp->Data == X)
			return num;
		temp = temp->Next;
	}
	cout << "�ڸ�������û���ҵ�����" << endl;
}

List Insert(ElementType X, int i, List L) //��λ��iǰ����һ����Ԫ��X
{
	if (i < 1)
	{
		cout << "iӦ�ô���1" << endl;
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
		cout << "i��������Ľڵ�����,����ʧ��" << endl;
	return L;
}

void Delete(int i, List * L1)//ɾ��ָ��λ��i��Ԫ�� ɾ��λ��Ϊ1��Ԫ��ʱ��ɾ����������
{
	List L = *L1;
	if (L == NULL)
	{
		cout << "LΪ������,ɾ��ʧ��" << endl;
		return;
	}
	if (i == 1)
	{
		cout << "iΪ1ʱ��ʾɾ��ͷ��㣬�൱�ڰ�����ɾ����" << endl;
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
	cout << "λ��i�����������ȣ��޷�ɾ��!" << endl;
}

int Length(List L) //�������Ա�ĳ���
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

List GetLocation(ElementType i, List L) //��������L��λ��Ϊi�ĵ�ַ
{
	if (i <= 0)
	{
		cout << "λ��ӦΪ����0����" << endl;
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
	cout << "λ������������нڵ�ĸ�����" << endl;
}

void Print(List L)
{
	if (L == NULL)
	{
		cout << "����ΪNULL" << endl;
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
