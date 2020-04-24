//An inorder binary tree traversal can be implemented in a non - recursive way with a stack.For example, suppose that when a 6 - node binary tree(with the keys numbered from 1 to 6) is traversed, the stack operations are : push(1); push(2); push(3); pop(); pop(); push(4); pop(); pop(); push(5); push(6); pop(); pop().Then a unique binary tree(shown in Figure 1) can be generated from this sequence of operations.Your task is to give the postorder traversal sequence of this tree.
//
//
//Figure 1
//Input Specification :
//Each input file contains one test case.For each case, the first line contains a positive integer N(≤30) which is the total number of nodes in a tree(and hence the nodes are numbered from 1 to N).Then 2N lines follow, each describes a stack operation in the format : "Push X" where X is the index of the node being pushed onto the stack; or "Pop" meaning to pop one node from the stack.
//
//Output Specification :
//For each test case, print the postorder traversal sequence of the corresponding tree in one line.A solution is guaranteed to exist.All the numbers must be separated by exactly one space, and there must be no extra space at the end of the line.
//
//Sample Input :
//6
//Push 1
//Push 2
//Push 3
//Pop
//Pop
//Push 4
//Pop
//Pop
//Push 5
//Push 6
//Pop
//Pop
//
//
//
//Sample Output :
//3 4 2 6 5 1

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include<algorithm>
#include<string.h>
using namespace std;

struct TreeNode
{
	int thisNum;
	int left;
	int right;
};

int IsEqual(char * string1,char * string2)
{
	int flag = 0;
	for (int i = 0; string1[i] != '\0'; i++)
	{
		if (string1[i] != string2[i])
		{
			flag = 1;
			break;
		}
	}
	if (flag == 1)
		return 0;
	else
		return 1;
}

vector <TreeNode> CreateTree()
{
	vector <TreeNode> Tree;
	vector <TreeNode> PopStorage; //需要这个来做一个时滞的储存
	vector <TreeNode> Result; //储存最后的结果
	int Allnum;
	char tempchar;
	scanf("%d", &Allnum);
	int flag = 0;
	for (int i = 0; i < 2 * Allnum; i++)
	{
		char tempstring[10];
		int num;
		scanf("%s", tempstring);
		if (IsEqual(tempstring,"Push"))
		{
			scanf("%d", &num);
			TreeNode temp;
			temp.thisNum = num;
			temp.left = -1;
			temp.right = -1;
			
			if (Tree.empty() == 0)
			{
				TreeNode popelement = *(Tree.end() - 1);
				if (popelement.left == -1)
				{
					popelement.left = num;
					Tree.pop_back();
					Tree.push_back(popelement);
				}
				
			}
			if (PopStorage.empty() == 0)
			{
				PopStorage[0].right = num;
				Result.push_back(PopStorage[0]);
				PopStorage.pop_back();
			}
			Tree.push_back(temp);
		}
		else if (IsEqual(tempstring, "Pop"))
		{
			flag = 1;
			TreeNode temp;
			temp = *(Tree.end()-1);
			if (PopStorage.empty() == 0)
			{
				PopStorage[0].right = -1;
				Result.push_back(PopStorage[0]);
				PopStorage.pop_back();
				PopStorage.push_back(temp);
			}
			else
				PopStorage.push_back(temp);
			
			Tree.pop_back();
		}
	}
	if (PopStorage.empty() == 0)
		Result.push_back(PopStorage[0]);
	return Result;
}

int FindRoot(vector <TreeNode> Tree)
{
	vector<int>store;
	for (auto i = Tree.begin(); i != Tree.end(); i++)
	{
		if ((*i).left!=-1)
			store.push_back((*i).left);
		if ((*i).right != -1)
			store.push_back((*i).right);
	}
	for (int j = 1; j <= store.size(); j++)
	{
		int flag = 0;
		for (auto i = store.begin(); i != store.end(); i++)
		{
			if (j == (*i))
			{
				flag = 1;
				break;
			}
		}
		if (flag == 0)
			return j;
	}
	return 0; //找不到根节点
}

TreeNode FindNumTreeNode(vector <TreeNode> Tree,int num)
{
	TreeNode temp;
	temp.thisNum = -1; //如果不初始化的话最后会出现错误
	temp.left = -1;
	temp.right = -1;
	for (int j = 0; j < Tree.size(); j++)
	{
		if (Tree[j].thisNum == num)
		{
			temp = Tree[j];
			return temp;
		}
	}
	return temp;
}

void PostOrderTravesal(vector <TreeNode> Tree,TreeNode Node)
{
	if (Node.thisNum == -1)
		return;
	PostOrderTravesal(Tree, FindNumTreeNode(Tree, Node.left));
	PostOrderTravesal(Tree, FindNumTreeNode(Tree, Node.right));
	printf("%d ", Node.thisNum);
}

int main()
{
	/*
6
Push 1
Push 2
Push 3
Pop
Pop
Push 4
Pop
Pop
Push 5
Push 6
Pop
Pop
*/
	
	vector <TreeNode> Tree = CreateTree();
	int root = FindRoot(Tree);
	PostOrderTravesal(Tree,FindNumTreeNode(Tree,root));
}