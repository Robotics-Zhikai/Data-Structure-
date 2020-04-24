/*
����һ���������оͿ���Ψһȷ��һ�ö�����������Ȼ����һ�ø����Ķ���������ȴ�����ɶ��ֲ�ͬ�Ĳ������еõ�������ֱ�������{ 2, 1, 3 }��{ 2, 3, 1 }�����ʼΪ�յĶ��������������õ�һ���Ľ�������Ƕ�������ĸ��ֲ������У�����Ҫ�ж������Ƿ�������һ���Ķ�����������

�����ʽ :
�������������������ݡ�ÿ�����ݵĵ�1�и�������������N(��10)��L���ֱ���ÿ�����в���Ԫ�صĸ�������Ҫ�������и�������2�и���N���Կո�ָ�������������Ϊ��ʼ�������С����L�У�ÿ�и���N�������Ԫ�أ�����L����Ҫ�������С�

����������Ǳ�֤ÿ���������ж���1��N��һ�����С�������NΪ0ʱ����־����������������ݲ�Ҫ����

�����ʽ :
��ÿһ����Ҫ�������У���������ɵĶ�������������Ӧ�ĳ�ʼ�������ɵ�һ���������Yes�������������No����

�������� :
4 2
3 1 4 2
3 4 1 2
3 2 4 1
2 1
2 1
1 2
0



�������:
Yes
No
No
*/

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include<algorithm>
#include<string.h>
using namespace std;

typedef struct TreeNode * TreeNodeAdd;
struct TreeNode
{
	int num;
	TreeNodeAdd lchild;
	TreeNodeAdd rchild;
	TreeNodeAdd thisAdd;
};

TreeNodeAdd InsertElement(TreeNodeAdd head, int Element)
{
	if (head == NULL)
	{
		head = (TreeNodeAdd)malloc(sizeof(TreeNode));
		head->lchild = NULL;
		head->rchild = NULL;
		head->num = Element;
		return head;
	}
	TreeNodeAdd Current = head;
	TreeNodeAdd Last;
	int LorR = -1;
	while (Current != NULL)
	{
		Last = Current;
		LorR = 0;
		if (Element > Current->num)
		{
			Current = Current->rchild;
			LorR = 2;
		}
		else if (Element < Current->num)
		{
			Current = Current->lchild;
			LorR = 1;
		}
		else
			break;
	}
	if (LorR == 0)
	{
		printf("����ͬ��Ԫ�ز���\n");
	}
	else if (LorR == 1)
	{
		Last->lchild = (TreeNodeAdd)malloc(sizeof(TreeNode));
		Last->lchild->num = Element;
		Last->lchild->thisAdd = Last->lchild;
		Last->lchild->lchild = NULL;
		Last->lchild->rchild = NULL;
	}
	else if (LorR == 2)
	{
		Last->rchild = (TreeNodeAdd)malloc(sizeof(TreeNode));
		Last->rchild->num = Element;
		Last->rchild->thisAdd = Last->rchild;
		Last->rchild->lchild = NULL;
		Last->rchild->rchild = NULL;
	}
	else if (LorR == -1)
	{
		head = (TreeNodeAdd)malloc(sizeof(TreeNode));
		head->lchild = NULL;
		head->rchild = NULL;
		head->num = Element;
		head->thisAdd = head;
	}
	return head;

}

TreeNodeAdd Find(TreeNodeAdd head,int Element)
{
	TreeNodeAdd temp = head;
	while (temp != NULL)
	{
		if (Element > temp->num)
		{
			temp = temp->rchild;
		}
		else if (Element < temp->num)
		{
			temp = temp->lchild;
		}
		else
		{
			break;
		}
	}
	return temp;
}

TreeNodeAdd FindMin(TreeNodeAdd head)
{
	TreeNodeAdd temp = head;
	TreeNodeAdd Last = temp;
	while (temp != NULL)
	{
		Last = temp;
		temp = temp->lchild;
	}
	return Last;
}

TreeNodeAdd FindMax(TreeNodeAdd head)
{
	TreeNodeAdd temp = head;
	TreeNodeAdd Last = temp;
	while (temp != NULL)
	{
		Last = temp;
		temp = temp->rchild;
	}
	return Last;
}

TreeNodeAdd Delete(TreeNodeAdd head, int Element)
{
	if (head == NULL)
	{
		printf("û�ҵ�\n");
		return NULL;
	}
	if (Element < head->num)
	{
		TreeNodeAdd Newhead = Delete(head->lchild, Element);
		head->lchild = Newhead;
		return head;
	}
	else if (Element > head->num)
	{
		TreeNodeAdd Newhead = Delete(head->rchild, Element);
		head->rchild = Newhead;
		return head;
	}
	else
	{
		if (head->lchild == NULL&&head->rchild == NULL)
		{
			free(head);
			return NULL;
		}
		else
		{
			if (head->rchild != NULL)
			{
				TreeNodeAdd minest = FindMin(head->rchild);
				int minrecord = minest->num;
				TreeNodeAdd Newhead = Delete(head->rchild, minest->num);
				head->rchild = Newhead;
				head->num = minrecord;
				return head;
			}
			if (head->lchild != NULL)
			{
				TreeNodeAdd maxest = FindMax(head->lchild);
				int maxrecord = maxest->num;
				TreeNodeAdd Newhead = Delete(head->lchild, maxest->num);
				head->lchild = Newhead;
				head->num = maxrecord;
				return head;
			}
		}
	}
}

vector <int> TreeElement;
void PreOrderTraversal(TreeNodeAdd Tree)
{
	if (Tree == NULL)
		return;
	TreeElement.push_back(Tree->num);
	PreOrderTraversal(Tree->lchild);
	PreOrderTraversal(Tree->rchild);
}


//���ǲ��Ի������������ĳ���
int main()
{
	TreeNodeAdd Tree = NULL;
	
	while (1)
	{
		int num;
		scanf("%d", &num);
		if (num == -1)
			break;
		Tree = InsertElement(Tree, num);
	}
	//Delete(Tree, 4);
	Delete(Tree, 12);

}




//�����ж��Ƿ���ͬһ�������������ĳ���
//int main()
//{
//	
//	vector <int> FinalCo;
//	while (1)
//	{
//		int stop;
//		scanf("%d", &stop);
//		if (stop == 0)
//			break;
//		int a[2];
//		a[0] = stop;
//		int num;
//		scanf("%d", &num);
//		a[1] = num;
//		vector <int> initseq;
//		for (int i = 0; i < a[0]; i++)
//		{
//			int num;
//			scanf("%d", &num);
//			initseq.push_back(num);
//		}
//
//		vector <vector<int>> testseqs;
//		for (int i = 0; i < a[1]; i++)
//		{
//			vector <int> seq;
//			for (int j = 0; j < a[0]; j++)
//			{
//				int num;
//				scanf("%d", &num);
//				seq.push_back(num);
//			}
//			testseqs.push_back(seq);
//		}
//
//		TreeNodeAdd InitTree = NULL;
//		for (int i = 0; i < initseq.size(); i++)
//			InitTree = InsertElement(InitTree, initseq[i]);
//
//		for (int i = 0; i < testseqs.size(); i++)
//		{
//			TreeNodeAdd testTree = NULL;
//			for (int j = 0; j < testseqs[i].size(); j++)
//				testTree = InsertElement(testTree, testseqs[i][j]);
//
//			TreeElement.clear();
//			PreOrderTraversal(InitTree);
//			vector <int> store = TreeElement;
//			TreeElement.clear();
//			PreOrderTraversal(testTree);
//			int k;
//			for (k = 0; k < store.size(); k++)
//			{
//				if (store[k] != TreeElement[k])
//					break;
//			}
//			if (k >= store.size())
//				//cout << "YES" << endl;
//				FinalCo.push_back(1);
//			else
//				//cout << "NO" << endl;
//				FinalCo.push_back(0);
//		}
//	}
//	for (int i = 0; i < FinalCo.size(); i++)
//	{
//		if (FinalCo[i] == 1)
//			cout << "Yes" << endl;
//		else
//			cout << "No" << endl;
//	}
//	system("pause");
//
//	
//}