#pragma once
#include "main.h"
#include <queue>
/*
剑指 Offer 32 - I. 从上到下打印二叉树
从上到下打印出二叉树的每个节点，同一层的节点按照从左到右的顺序打印。
*/

 //Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class SolutionOffer32_I {
public:
	vector<int> levelOrder(TreeNode* root) {
		queue<TreeNode*> q;
		q.push(root);
		vector<int> result;
		TreeNode * pfr;
		while (q.empty() == 0)
		{
			pfr = q.front();
			if (pfr != nullptr)
			{
				result.push_back(pfr->val);
				TreeNode* l = pfr->left;
				TreeNode* r = pfr->right;
				if (l != nullptr)
					q.push(l);
				if (r != nullptr)
					q.push(r);
			}
			q.pop();
		}
		return result;
	}
};



/*
剑指 Offer 32 - II. 从上到下打印二叉树 II
从上到下按层打印二叉树，同一层的节点按从左到右的顺序打印，每一层打印到一行。
*/
class SolutionOffer32_II {
public:
	vector<vector<int>> levelOrder(TreeNode* root) {
		if (root == nullptr)
			return vector<vector<int>>{};
		queue<TreeNode*> q;
		q.push(root);
		vector<vector<int>> result;
		TreeNode * pf;
		while (!q.empty())
		{
			vector<int> thistmp;
			int qsizecur = q.size();
			for (int i = 0; i<qsizecur; i++)
			{
				pf = q.front();
				q.pop();
				if (pf != nullptr)
				{
					thistmp.push_back(pf->val);
					TreeNode * l = pf->left;
					TreeNode * r = pf->right;
					if (l != nullptr)
						q.push(l);
					if (r != nullptr)
						q.push(r);
				}
			}
			result.push_back(thistmp);
		}
		return result;
	}
};

/*
剑指 Offer 27. 二叉树的镜像
请完成一个函数，输入一个二叉树，该函数输出它的镜像。 翻转二叉树
*/
class SolutionOffer27 {
public:
	TreeNode* mirrorTreeRecur(TreeNode* root)
	{
		if (root == nullptr)
			return root;
		mirrorTree(root->left);
		mirrorTree(root->right);
		TreeNode * mid = root->left;
		root->left = root->right;
		root->right = mid;
		return root;
	}
	TreeNode* mirrorTreeQueue(TreeNode* root)
	{
		queue<TreeNode*> q;
		q.push(root);
		while (q.empty() == 0)
		{
			auto sizes = q.size();
			for (int i = 0; i<sizes; i++)
			{
				TreeNode* q_fr = q.front();
				q.pop();

				if (q_fr != nullptr)
				{
					TreeNode * mid = q_fr->left;
					q_fr->left = q_fr->right;
					q_fr->right = mid;
					q.push(q_fr->left);
					q.push(q_fr->right);
				}
			}
		}
		return root;
	}
	TreeNode* mirrorTree(TreeNode* root) {
		//return mirrorTreeRecur(root);
		return mirrorTreeQueue(root); //用队列的方法时间复杂度与用递归的方法差不多；空间复杂度比递归的方法还大一点
									  //之所以有空间复杂度不一样的问题，是因为递归方法中最大的空间复杂度是O(Clogn)，是树的深度；
									  //而队列方法空间复杂度是O(2^logn)，当然造成了空间复杂度的增加。
	}
};


/*
剑指 Offer 34. 二叉树中和为某一值的路径
输入一棵二叉树和一个整数，打印出二叉树中节点值的和为输入整数的所有路径。
从树的根节点开始往下一直到叶节点所经过的节点形成一条路径。
*/

class SolutionOffer34 {
	//这个题应该反复练习！！！！！！！！！！！！！！！！！！！！！！！！！！！很容易就写错了
public:
	vector<vector<int>> pathSumStack(TreeNode* root, int target)
		//借助栈，先把深度优先遍历树的框架写出来，然后再往进填具体需要的操作
		//没有用递归
		//写非递归的树遍历程序的时候，要借助栈，然后按照脑子中想的遍历顺序去一步一步写，自然就写出来了
	{
		stack<bool> LorR;//记录当前节点的访问情况 0为初次访问，1为第二次访问
		vector<TreeNode*> S;

		TreeNode *curp = root;
		if (root == nullptr)
			return{};
		int curnum = 0;

		vector<vector<int>> result;
		while (1)
		{
			S.push_back(curp);
			LorR.push(0);

			if (curp != nullptr) //深度优先搜索遍历框架之外的操作
			{
				curnum += curp->val;
				if (curnum == target&&curp->left == nullptr&&curp->right == nullptr)
					//这里注意路径的定义：从树的根节点开始往下一直到叶节点所经过的节点形成一条路径。
					//一定要判断找到的点是不是叶节点。只有是叶节点才行
				{
					vector<int> path;
					for (int i = 0; i<S.size(); i++)
						path.push_back(S[i]->val);
					result.push_back(path);
				}
			}

			if (curp == nullptr)
			{
				S.pop_back();
				LorR.pop();
				if (LorR.top() == 0)
				{
					curp = (*(S.end() - 1))->right;
					LorR.top() = 1;
				}
				else
				{
					while (LorR.empty() == 0 && LorR.top() == 1) //LorR.empty()==0容易漏掉
					{
						if (*(S.end() - 1) != nullptr)
							curnum -= (*(S.end() - 1))->val;
						S.pop_back();
						LorR.pop();
					}
					if (S.size() == 0)
						break;
					curp = (*(S.end() - 1))->right;
					LorR.top() = 1; //这句容易漏掉
				}
				continue;
			}
			curp = curp->left;
		}
		return result;
	}


	void traverseRecur(TreeNode* root, int target)
		//以递归的方式实现对树的深度优先遍历，然后在适当位置做出适当操作
	{
		if (root != nullptr)
			path.push_back(root->val);
		else
			path.push_back(-1); //只是一个临时量，最后肯定要弹出去
		if (root != nullptr)
		{
			curnum += root->val;
			if (curnum == target&&root->left == nullptr&&root->right == nullptr)
				res.push_back(path);
		}

		if (root == nullptr)
			return;
		traverseRecur(root->left, target);
		if (root->left != nullptr)
			curnum -= root->left->val;
		path.pop_back();

		traverseRecur(root->right, target);
		if (root->right != nullptr)
			curnum -= root->right->val;
		path.pop_back();

	}
	int curnum = 0;
	vector<int> path;
	vector<vector<int>> res;
	vector<vector<int>> TraverseRecur(TreeNode* root, int target)
	{
		curnum = 0;
		path.clear();
		res.clear();
		traverseRecur(root, target);
		return res;
	}

	vector<vector<int>> pathSum(TreeNode* root, int target)
	{
		//return pathSumStack(root, target); //4ms 19.4MB 97.81% 67.98%
		return TraverseRecur(root, target);//8ms 19.6MB 86.98% 30.63% 这个时间不准 每次运行都不一样 且变化范围很大 
	}
};