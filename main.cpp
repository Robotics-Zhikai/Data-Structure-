/*本项目用来练习文件操作*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

typedef struct Node * NodeAddress;
struct Node
{
	int Data;
	NodeAddress Next;
};
int main()
{
	int ch;
	int ch1;
	NodeAddress First = (NodeAddress)malloc(sizeof(Node));
	First->Next = NULL;
	NodeAddress temp = First;
	while ((ch=getchar())!=EOF)
	{
		NodeAddress newNode = (NodeAddress)malloc(sizeof(Node));
		temp->Next = newNode;
	
		newNode->Data = ch;
		newNode->Next = NULL;
		temp = newNode;
	} 
	temp = First->Next;
	int num = 0;
	#define NUM 10
	int storage[10];
	NodeAddress storageAddress[NUM];
	while (temp != NULL)
	{
		storage[num] = temp->Data;
		storageAddress[num] = temp;
		num++;
		putchar(temp->Data);
		if (num == NUM)
		{
			num = 0;
			printf("\n");
			for (int i = 0; i < 10; i++)
			{
				printf("%d  ", storage[i]);
			}
			printf("\n");
		}
		temp = temp->Next;
	}
	printf("\n");
	for (int i = 0; i < num; i++)
	{
		printf("%d  ", storageAddress[i]->Data);
	}
	printf("\n");
	
}