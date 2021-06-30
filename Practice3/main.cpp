/*
02 - 线性结构3 Reversing Linked List(25分)
Given a constant K and a singly linked list L, you are supposed to reverse the links of every K elements on L.For example, given L being 1→2→3→4→5→6, if K = 3, then you must output 3→2→1→6→5→4; if K = 4, you must output 4→3→2→1→5→6.

Input Specification :
Each input file contains one test case.For each case, the first line contains the address of the first node, a positive N(≤10
	​5
	​​) which is the total number of nodes, and a positive K(≤N) which is the length of the sublist to be reversed.The address of a node is a 5 - digit nonnegative integer, and NULL is represented by - 1.

	Then N lines follow, each describes a node in the format :

Address Data Next



where Address is the position of the node, Data is an integer, and Next is the position of the next node.

Output Specification :
For each case, output the resulting ordered linked list.Each node occupies a line, and is printed in the same format as in the input.

Sample Input :
00100 6 4
00000 4 99999
00100 1 12309
68237 6 - 1
33218 3 00000
99999 5 68237
12309 2 33218



Sample Output :
00000 4 33218
33218 3 12309
12309 2 00100
00100 1 99999
99999 5 68237
68237 6 - 1
*/
/*为了训练文件操作，输入输出数据都储存在txt中*/

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

typedef struct Node * NodeAddress;
struct Node
{
	char Address[6];
	int Data;
	char Next[6];
	NodeAddress NextNode;
};

int ValidAddress(char*ch) //判断地址是否合理
{
	if (((ch[5] == '\0') && (ch[4] != '\0'))||(*ch=='-'&&*(ch+1)=='1'))
		return 1;
	else
		return 0;
}

NodeAddress Read()
{
	char ch[7] = { 0 };
	NodeAddress first = (NodeAddress)malloc(sizeof(Node));
	first->NextNode = NULL;
	NodeAddress temp = first;
	int num = 0;
	while (scanf("%s", ch)!=EOF) //假设格式还是对的，只是偶尔有些行出现地址错误的情况
	{
		num++;
		if (!ValidAddress(ch))
		{
			scanf("%s", ch);
			scanf("%s", ch);
			continue;
		}
		NodeAddress newnode = (NodeAddress)malloc(sizeof(Node));
		for (int i = 0; i < 6; i++)
		{
			newnode->Address[i] = ch[i];
		}
		int data;
		if (!scanf("%d", &data))
		{
			scanf("%s", ch);
			scanf("%s", ch);
			continue;
		}
		newnode->Data = data;
		char ch1[6] = { 0 };
		scanf("%s", ch1);
		if (!ValidAddress(ch1))
			continue;
		for (int i = 0; i < 6; i++)
		{
			newnode->Next[i] = ch1[i];
		}
		newnode->NextNode = NULL;
		temp->NextNode = newnode;
		temp = newnode;
		/*if (num == 10)
			break;*/
	}
	return first;
}

void disp(NodeAddress node)
{
	NodeAddress temp = node->NextNode;
	while (temp != NULL)
	{
		printf("%s ", temp->Address);
		printf("%d ", temp->Data);
		printf("%s", temp->Next);
		printf("\n");
		temp = temp->NextNode;
	}
}

void GenerateData(int N)
{
	for (int i = 0; i < N; i++)
	{
		printf("11111 32 22222\n");
	}
}

int isequal(char * char1, char * char2) //对比两字符串是否相等 输入的长度应该相等
{
	int result = 1;
	for (int i = 0; char1[i] != '\0'; i++)
	{
		if (char1[i] != char2[i])
		{
			result = result * 0;
			break;
		}
	}
	return result;
}

NodeAddress FindLocationData(NodeAddress Node1, char*Location) //在链表中找到特定地址下的数据的地址
{
	if ((*Location == '-') && (*(Location + 1) == '1'))
		return NULL;
	NodeAddress temp = Node1->NextNode;
	while (temp != NULL)
	{
		if (isequal(temp->Address, Location))
			return temp;
		temp = temp->NextNode;
	}
	return NULL;//没找到返回NULL
}

int Length(NodeAddress Node,char*firstlocation)
{
	NodeAddress temp = FindLocationData(Node, firstlocation);
	int num = 0;
	while (temp != NULL)
	{
		num++;
		temp = FindLocationData(Node,temp->Next);
	}
	return num;
}

void Copychar2TOchar1(char * char1, char * char2)
{
	int i;
	for (i = 0; char2[i] != '\0'; i++)
	{
		char1[i] = char2[i];
	}
	char1[i] = '\0';
	return;
}

void ReverseList(NodeAddress Node,int K)
{
	if (K > Length(Node,Node->NextNode->Address))
	{
		printf("无法反转，K>N\n");
		return ;
	}
	if (K == 0||K == 1)
	{
		printf("无需反转\n");
		return ;
	}
	if (K < 0)
	{
		printf("K应该大于0\n");
		return ;
	}
	int num = 0;
	NodeAddress temp = Node->NextNode;
	if (temp == NULL)
		return;
	NodeAddress midtemp = temp->NextNode;
	if (midtemp == NULL)
		return;
	NodeAddress tempstorage = temp;
	NodeAddress tempNextStorage = midtemp;
	while (temp != NULL)
	{
		NodeAddress midtempNextStorage = midtemp->NextNode;
		midtemp->NextNode = temp;
		if (num != 0)
		{
			temp->NextNode = tempNextStorage;
			tempNextStorage = midtemp;
		}
		num++;
		if (num == K / 2)
		{
			if (K % 2 == 0)
			{
				Node->NextNode = midtemp;
				tempstorage->NextNode = midtempNextStorage;
				break;
			}
			else
			{
				Node->NextNode = midtempNextStorage;
				tempstorage->NextNode = midtempNextStorage->NextNode;
				midtempNextStorage->NextNode = midtemp;
				break;
			}
		}
		temp = midtempNextStorage;
		midtemp = temp->NextNode;
	}
	temp = Node->NextNode;
	while (temp->NextNode != NULL)
	{
		Copychar2TOchar1(temp->Next, temp->NextNode->Address);
		temp = temp->NextNode;
	}
	Copychar2TOchar1(temp->Next, "-1");
}

void SwapNodeData(NodeAddress swap1, NodeAddress swap2)
{
	int middata;
	NodeAddress tempstorage = swap1;
	NodeAddress temp = swap2;
	middata = temp->Data;
	temp->Data = tempstorage->Data;
	tempstorage->Data = middata;
	int i;
	for (i = 0; i<6 ; i++)
	{
		middata = temp->Next[i];
		temp->Next[i] = tempstorage->Next[i];
		tempstorage->Next[i] = middata;

		middata = temp->Address[i];
		temp->Address[i] = tempstorage->Address[i];
		tempstorage->Address[i] = middata;
	}
}

void ArangeList(NodeAddress Node,char * BeginLocation) //对储存在顺序表中的数据进行顺序修整 链表只是一种实现无限存储的方式
{
	NodeAddress temp = Node->NextNode;
	NodeAddress tempstorage = temp;
	char * Location = BeginLocation;

	while (temp != NULL)
	{
		if (isequal(temp->Address, Location))
		{
			if (temp == tempstorage)
			{
				Location = tempstorage->Next;
				if (isequal("-1", Location))
				{
					tempstorage->NextNode = NULL;
					break;
				}
				temp = tempstorage->NextNode;
				tempstorage = tempstorage->NextNode;
				continue;
			}
			Location = tempstorage->Next;
			SwapNodeData(tempstorage, temp);
			if (isequal("-1", Location))
			{
				tempstorage->NextNode = NULL;
				break;
			}
			temp = tempstorage->NextNode;
			tempstorage = tempstorage->NextNode;
			continue;
		}
		temp = temp->NextNode;
	}
}

void ReverseListMethod2(NodeAddress Node, int K,char*firstLocation)
{
	if (K > Length(Node, firstLocation))
	{
		printf("无法反转，K>N\n");
		return;
	}
	if (K == 0 || K == 1)
	{
		printf("无需反转\n");
		return;
	}
	if (K < 0)
	{
		printf("K应该大于0\n");
		return;
	}

	NodeAddress temp = FindLocationData(Node, firstLocation); //这个用在数组里的话可以对应的转换成数组下标
	if (temp == NULL)
		return;
	NodeAddress firstNodestorage = temp;
	NodeAddress tempNext = FindLocationData(Node, temp->Next);
	if (tempNext == NULL)
		return;
	NodeAddress tempNextNextStorage = FindLocationData(Node, tempNext->Next);

	int num = 0;
	while (1)
	{
		Copychar2TOchar1(tempNext->Next, temp->Address);
		num = num + 1;
		if (num ==(K-(K%2))/2 )
		{
			if (K % 2 == 0)
			{
				if (tempNextNextStorage == NULL)
					Copychar2TOchar1(firstNodestorage->Next, "-1");
				else
					Copychar2TOchar1(firstNodestorage->Next, tempNextNextStorage->Address);
				Copychar2TOchar1(firstLocation, tempNext->Address);
				return;
			}
			else
			{
				NodeAddress tempNextNextNext = FindLocationData(Node, tempNextNextStorage->Next);
				if (tempNextNextNext == NULL)
					Copychar2TOchar1(firstNodestorage->Next, "-1");
				else
					Copychar2TOchar1(firstNodestorage->Next, tempNextNextNext->Address);
				Copychar2TOchar1(tempNextNextStorage->Next, tempNext->Address);
				Copychar2TOchar1(firstLocation, tempNextNextStorage->Address);
				return;
			}
		}
		temp = tempNextNextStorage;
		NodeAddress tempNextstorage = tempNext;
		tempNext = FindLocationData(Node, temp->Next);
		Copychar2TOchar1(temp->Next, tempNextstorage->Address);
		tempNextNextStorage = FindLocationData(Node, tempNext->Next);
	}
}

void dispMethod2(NodeAddress Node,char*firstLocation)
{
	NodeAddress temp = FindLocationData(Node, firstLocation);
	while (temp->Address!=NULL)
	{
		printf("%s ", temp->Address);
		printf("%d ", temp->Data);
		printf("%s\n", temp->Next);
		temp = FindLocationData(Node, temp->Next);
	}
}

#define ChOOSEFUNCTION 1
#ifdef ChOOSEFUNCTION
int main()
{
	NodeAddress first;
	first = Read(); //包括废数据的消去
	ArangeList(first, "33128");
	ReverseList(first, 1);
	disp(first);//将处理后的数据弄到另一个文件里
	//char string1[6] = "33218";
	//ReverseListMethod2(first, 4 ,string1);
	//dispMethod2(first, string1);
	
}
#else
int main()
{
	GenerateData(1000);
}
#endif