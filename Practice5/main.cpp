/*给定两棵树T1和T2。如果T1可以通过若干次左右孩子互换就变成T2，则我们称两棵树是“同构”的。例如图1给出的两棵树就是同构的，因为我们把其中一棵树的结点A、B、G的左右孩子互换后，就得到另外一棵树。而图2就不是同构的。


图1



图2

现给定两棵树，请你判断它们是否是同构的。
输入格式 :
输入给出2棵二叉树树的信息。对于每棵树，首先在一行中给出一个非负整数N(≤10)，即该树的结点数（此时假设结点从0到N−1编号）；随后N行，第i行对应编号第i个结点，给出该结点中存储的1个英文大写字母、其左孩子结点的编号、右孩子结点的编号。如果孩子结点为空，则在相应位置上给出“ - ”。给出的数据间用一个空格分隔。注意：题目保证每个结点中存储的字母是不同的。

输出格式 :
如果两棵树是同构的，输出“Yes”，否则输出“No”。

输入样例1（对应图1）：
8
A 1 2
B 3 4
C 5 -1
D -1 -1
E 6 -1
G 7 -1
F -1 -1
H -1 -1
8
G -1 4
B 7 6
F -1 -1
A 5 1
H -1 -1
C 0 -1
D -1 -1
E 2 -1



输出样例1:
Yes



输入样例2（对应图2）：
8
B 5 7
F -1 -1
A 0 3
C 6 -1
H -1 -1
D -1 -1
G 4 -1
E 1 -1
8
D 6 -1
B 5 -1
E -1 -1
H -1 -1
C 0 2
G -1 3
F -1 -1
A 1 4



输出样例2:
No*/

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
using namespace std;

struct TreeNode
{
	char Character;
	int left;
	int right;
	int thisnum;
	int Treeroot;
};

vector <TreeNode> Tree;

vector <TreeNode> CreateTree()
{
	vector <TreeNode> Tree; //Tree的第一个节点的信息存储Treeroot的编号
	TreeNode temp;
	Tree.push_back(temp);
	/*printf("输入数据\n");*/
	int Allnum;
	char nimabi;
	scanf("%d%c", &Allnum,&nimabi);
	for (int i = 0; i < Allnum; i++)
	{
		scanf("%c %d %d%c", &temp.Character, &temp.left, &temp.right,&nimabi);
		temp.thisnum = i;
		Tree.push_back(temp);
	}
	vector <int> Storage;
	for (auto i = Tree.begin()+1; i != Tree.end(); i++)
	{
		if(i->left!=-1)
			Storage.push_back(i->left);
		if(i->right!=-1)
			Storage.push_back(i->right);
	}
	for (int i = 0; i < Allnum; i++)
	{
		int flag = 0;
		for (auto j = Storage.begin(); j != Storage.end(); j++)
		{
			if (i == *j)
			{
				flag = 1;
				break;
			}
		}
		if (flag == 0)
		{
			Tree[0].Treeroot = i;
			break;
		}
	}
	return Tree;
}

int Isomorphic(vector <TreeNode> Tree1,TreeNode TreeNode1, vector <TreeNode> Tree2,TreeNode TreeNode2)
{
	if (TreeNode1.left == -1 && TreeNode1.right == -1 && TreeNode2.left == -1 && TreeNode2.right == -1)
		return 1;
	if (TreeNode1.left == -1 && TreeNode1.right == -1 && (TreeNode2.left != -1 || TreeNode2.right != -1))
		return 0;
	if (TreeNode2.left == -1 && TreeNode2.right == -1 && (TreeNode1.left != -1 || TreeNode1.right != -1))
		return 0;

	if (TreeNode1.left == -1 && TreeNode1.right != -1 && (TreeNode2.left == -1 && TreeNode2.right != -1))
	{
		if (Tree1[TreeNode1.right+1].Character != Tree2[TreeNode2.right+1].Character)
			return 0;
		else
			return Isomorphic(Tree1, Tree1[TreeNode1.right + 1], Tree2, Tree2[TreeNode2.right + 1]);
	}
		
	if (TreeNode1.left == -1 && TreeNode1.right != -1 && (TreeNode2.right == -1 && TreeNode2.left != -1))
	{
		if (Tree1[TreeNode1.right + 1].Character != Tree2[TreeNode2.left + 1].Character)
			return 0;
		else
			return Isomorphic(Tree1, Tree1[TreeNode1.right + 1], Tree2, Tree2[TreeNode2.left + 1]);
	}
		
	if (TreeNode1.left != -1 && TreeNode1.right == -1 && (TreeNode2.right == -1 && TreeNode2.left != -1))
	{
		if (Tree1[TreeNode1.left + 1].Character != Tree2[TreeNode2.left + 1].Character)
			return 0;
		else
			return Isomorphic(Tree1, Tree1[TreeNode1.left + 1], Tree2, Tree2[TreeNode2.left + 1]);
	}
		
	if (TreeNode1.left != -1 && TreeNode1.right == -1 && (TreeNode2.left == -1 && TreeNode2.right != -1))
	{
		if (Tree1[TreeNode1.left + 1].Character != Tree2[TreeNode2.right + 1].Character)
			return 0;
		else
			return Isomorphic(Tree1, Tree1[TreeNode1.left + 1], Tree2, Tree2[TreeNode2.right + 1]);
	}
		
	if (TreeNode1.left != -1 && TreeNode1.right != -1 && (TreeNode2.left != -1 && TreeNode2.right != -1))
	{
		char A1 = Tree1[TreeNode1.left + 1].Character;
		char A2 = Tree1[TreeNode1.right + 1].Character;
		char B1 = Tree2[TreeNode2.left + 1].Character;
		char B2 = Tree2[TreeNode2.right + 1].Character;

		if (A1 == B1&&A2 != B2)
			return 0;
		if (A1 == B2&&A2 != B1)
			return 0;
		if (A2 == B1&&A1 != B2)
			return 0;
		if (A2 == B2&&A1 != B1)
			return 0;
		int num = 0;
		if (A1 == B1)
			num = num + Isomorphic(Tree1, Tree1[TreeNode1.left + 1], Tree2, Tree2[TreeNode2.left + 1]);
		if (A1 == B2)
			num = num + Isomorphic(Tree1, Tree1[TreeNode1.left + 1], Tree2, Tree2[TreeNode2.right + 1]);
		if(A2 == B1)
			num = num + Isomorphic(Tree1, Tree1[TreeNode1.right + 1], Tree2, Tree2[TreeNode2.left + 1]);
		if(A2 == B2)
			num = num + Isomorphic(Tree1, Tree1[TreeNode1.right + 1], Tree2, Tree2[TreeNode2.right + 1]);
		if (num == 2)
			return 1;
		else
			return 0;
	}
}

int main()
{
//输入样例1（对应图1）：
	/*
8
A 1 2
B 3 4
C 5 -1
D -1 -1
E 6 -1
G 7 -1
F -1 -1
H -1 -1
8
G -1 4
B 7 6
F -1 -1
A 5 1
H -1 -1
C 0 -1
D -1 -1
E 2 -1


8
B 5 7
F -1 -1
A 0 3
C 6 -1
H -1 -1
D -1 -1
G 4 -1
E 1 -1
8
D 6 -1
B 5 -1
E -1 -1
H -1 -1
C 0 2
G -1 3
F -1 -1
A 1 4
*/

	vector <TreeNode> Tree1;
	Tree1 = CreateTree();
	vector <TreeNode> Tree2;
	Tree2 = CreateTree();
	int Result = Isomorphic(Tree1, Tree1[Tree1[0].Treeroot+1],Tree2, Tree2[Tree2[0].Treeroot+1]);
}






















//typedef struct TreeNode * TreeNodeAddress;
//struct TreeNode
//{
//	int NumNode; //树的编号
//	int left;
//	int right;
//};
//
//typedef struct ListNode * ListNodeAddress;
//struct ListNode
//{
//	TreeNodeAddress TreeNodeAdd;
//	int Root;//储存根节点编号
//	ListNodeAddress Next;
//};
//
////用一个线性表储存树结构,并找到根节点
//ListNodeAddress CreateTree()
//{
//	ListNodeAddress Result = (ListNodeAddress)malloc(sizeof(ListNode));
//	ListNodeAddress temp = Result;
//	int num;
//	int Allnum;
//	scanf("%d", &Allnum);
//	if (Allnum == 0)
//		Result->Root = -1;
//	for (int i = 0; i < Allnum; i++)
//	{
//		ListNodeAddress NewNode = (ListNodeAddress)malloc(sizeof(ListNode));
//		temp->Next = NewNode;
//		TreeNodeAddress NewTreeNode = (TreeNodeAddress)malloc(sizeof(TreeNode));
//		NewNode->TreeNodeAdd = NewTreeNode;
//		NewTreeNode->NumNode = i;
//		scanf("%d", &num);
//		NewTreeNode->left = num;
//		scanf("%d", &num);
//		NewTreeNode->right = num;
//		//NewNode->TreeNodeAdd = 
//		temp = temp->Next;
//	}
//	temp->Next = NULL;
//
//	typedef struct Nodetemp * NodetempAddress;
//	struct Nodetemp
//	{
//		int num;
//		int flag;
//		NodetempAddress Next;
//	};
//	NodetempAddress tempListNode = (NodetempAddress)malloc(sizeof(Nodetemp));
//	NodetempAddress temptemp = tempListNode;
//	for (int i = 0; i < Allnum; i++)
//	{
//		temptemp->Next = (NodetempAddress)malloc(sizeof(Nodetemp));
//		temptemp->Next->num = i;
//		temptemp->Next->flag = 0;
//		temptemp = temptemp->Next;
//	}
//	temptemp->Next = NULL;
//
//	temp = Result->Next;
//	while (temp != NULL)
//	{
//		temptemp = tempListNode->Next;
//		while (temptemp != NULL)
//		{
//			if (temp->TreeNodeAdd->left == temptemp->num)
//			{
//				temptemp->flag = 1;
//				break;
//			}
//			temptemp = temptemp->Next;
//		}
//
//		temptemp = tempListNode->Next;
//		while (temptemp != NULL)
//		{
//			if (temp->TreeNodeAdd->right == temptemp->num)
//			{
//				temptemp->flag = 1;
//				break;
//			}
//			temptemp = temptemp->Next;
//		}
//
//		temp = temp->Next;
//	}
//
//	temptemp = tempListNode->Next;
//	while (temptemp != NULL)
//	{
//		if (temptemp->flag == 0)
//		{
//			Result->Root = temptemp->num;
//			break;
//		}
//		temptemp = temptemp->Next;
//	}
//
//	return Result;
//}
//
//int main()
//{
//	CreateTree();
//}