/*
给定一个插入序列就可以唯一确定一棵二叉搜索树。然而，一棵给定的二叉搜索树却可以由多种不同的插入序列得到。例如分别按照序列{ 2, 1, 3 }和{ 2, 3, 1 }插入初始为空的二叉搜索树，都得到一样的结果。于是对于输入的各种插入序列，你需要判断它们是否能生成一样的二叉搜索树。

输入格式 :
输入包含若干组测试数据。每组数据的第1行给出两个正整数N(≤10)和L，分别是每个序列插入元素的个数和需要检查的序列个数。第2行给出N个以空格分隔的正整数，作为初始插入序列。最后L行，每行给出N个插入的元素，属于L个需要检查的序列。

简单起见，我们保证每个插入序列都是1到N的一个排列。当读到N为0时，标志输入结束，这组数据不要处理。

输出格式 :
对每一组需要检查的序列，如果其生成的二叉搜索树跟对应的初始序列生成的一样，输出“Yes”，否则输出“No”。

输入样例 :
4 2
3 1 4 2
3 4 1 2
3 2 4 1
2 1
2 1
1 2
0



输出样例:
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
		printf("有相同的元素插入\n");
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
		printf("没找到\n");
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


//这是测试基本操作函数的程序
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




//这是判断是否是同一个二叉搜索树的程序
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