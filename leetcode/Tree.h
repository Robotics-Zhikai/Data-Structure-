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
剑指 Offer 32 - III.从上到下打印二叉树 III
请实现一个函数按照之字形顺序打印二叉树，即第一行按照从左到右的顺序打印，
第二层按照从右到左的顺序打印，第三行再按照从左到右的顺序打印，其他行以此类推。
*/
class SolutionOffer32_III {
public:
	vector<vector<int>> levelOrder(TreeNode* root) { //之字形打印
		int level = 0;
		vector<vector<int>> result;
		//时间复杂度为O(n),空间复杂度为O(n)
		//还可以直接用队列，只不过每次把vector push到result中时需要间隔一个reverse一下
		stack<TreeNode*> sta1; //用两个栈来得到不同的遍历顺序
		stack<TreeNode*> sta2;

		sta1.push(root);
		do {
			vector<int> tmp;
			while (!sta1.empty()) {
				if (sta1.top() != nullptr) {
					tmp.push_back(sta1.top()->val);
					sta2.push(sta1.top()->left);
					sta2.push(sta1.top()->right);
				}
				sta1.pop();
			}
			if (!tmp.empty())
				result.push_back(tmp);
			tmp.clear();
			while (!sta2.empty()) {
				if (sta2.top() != nullptr) {
					tmp.push_back(sta2.top()->val);
					sta1.push(sta2.top()->right);
					sta1.push(sta2.top()->left);
				}
				sta2.pop();
			}
			if (!tmp.empty())
				result.push_back(tmp);
		} while (!sta1.empty() || !sta2.empty());
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
		stack<bool> LorR;//记录当前节点的访问情况 0为初次访问，1为已经访问了右子树
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


/*
剑指 Offer 07. 重建二叉树
输入某二叉树的前序遍历和中序遍历的结果，请重建该二叉树。假设输入的前序遍历和中序遍历的结果中都不含重复的数字。
这要好好看看！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
*/

class SolutionOffer07 {
public:
	unordered_map<int, int> mapping;//inorder中数字和index的映射 O(n)的空间存储哈希映射
	vector<int> preo;
	vector<int> ino;
	TreeNode* recur(int rootindex, int left, int right)//左闭右开
													   //输入子树的根节点在preo的索引rootindex，并把子树的所有在ino的索引用[left,right)括起来
													   //然后返回子树的根节点
	{
		if (left >= right)
			return nullptr;
		int rootvalue = preo[rootindex];
		TreeNode* node = new TreeNode(rootvalue);
		node->left = recur(rootindex + 1, left, mapping[rootvalue]);//二叉树的遍历是先遍历左子树，再遍历右子树
																	//所以rootindex+1是左子树的根节点， rootindex+mapping[rootvalue]-left+1是右子树的根节点
		node->right = recur(rootindex + mapping[rootvalue] - left + 1, mapping[rootvalue] + 1, right);
		return node;
	}
	TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
		preo = preorder;//把这个提出去能够提升速度
		ino = inorder;
		for (int i = 0; i<inorder.size(); i++)
			mapping[inorder[i]] = i;
		return recur(0, 0, inorder.size());
	}

/*

前序遍历，从根节点root开始，只要有左子节点，就一直会往左下方走，直到最左下角。 
而中序遍历，是从最左下角往上（示例中的4-5-8-9-3），如果碰到节点有右子节点，则会转向（示例中的8-10）。

因此，代码中的if块是用前序数组一直构建左子树，如果碰到了inorder[inorderIndex]，表示到了左下角，
这时就需要往上走并处理右子树，也就是while代码块。

这是迭代的方法，这跟已知二叉树结构，迭代深度优先遍历二叉树的程序结构是一样的，都是借助栈，从
根节点开始，不断把左子节点压栈，只不过已知树的结构可以直接通过判断左子树是否为null来判断，
而对于已知遍历结果未知树的结构来说，需要从前序遍历的值和中序遍历的值相等来判断左子树为null。

然后就是弹栈，直到弹到右子树出现

class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        if (!preorder.size()) {
            return nullptr;
        }
        TreeNode* root = new TreeNode(preorder[0]);
        stack<TreeNode*> stk;
        stk.push(root);
        int inorderIndex = 0;
        for (int i = 1; i < preorder.size(); ++i) {
            int preorderVal = preorder[i];
            TreeNode* node = stk.top();
            if (node->val != inorder[inorderIndex]) {
                node->left = new TreeNode(preorderVal);
                stk.push(node->left);
            }
            else {
                while (!stk.empty() && stk.top()->val == inorder[inorderIndex]) {
                    node = stk.top();
                    stk.pop();
                    ++inorderIndex;
                }
                node->right = new TreeNode(preorderVal);
                stk.push(node->right);
            }
        }
        return root;
    }
};

作者：LeetCode-Solution
链接：https://leetcode-cn.com/problems/zhong-jian-er-cha-shu-lcof/solution/mian-shi-ti-07-zhong-jian-er-cha-shu-by-leetcode-s/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。



*/
};


/*
剑指 Offer 26. 树的子结构
输入两棵二叉树A和B，判断B是不是A的子结构。(约定空树不是任意一个树的子结构)

B是A的子结构， 即 A中有出现和B相同的结构和节点值。

*/
class SolutionOffer26 {
public:
	bool recur(TreeNode* Aroot, TreeNode* Broot)
	{
		if ((Aroot == Broot &&Broot == nullptr) || (Broot == nullptr&&Aroot != nullptr))
			return 1;
		if (Aroot == nullptr&&Broot != nullptr)
			return 0;

		if (Aroot->val == Broot->val) {
			if (recur(Aroot->left, Broot->left) && recur(Aroot->right, Broot->right)) {
				return 1;
			}
		}
		return 0;
	}

	bool search(TreeNode* root, TreeNode* Broot) //递归的搜索某一节点为根的子结构是否包含在root中
	{ //只有能直接判断root为根的子树都不能或能匹配Broot时，才直接返回
		if (root == nullptr || Broot == nullptr)
			return 0;
		if (root->val == Broot->val) {
			if (recur(root, Broot))
				return 1;
		}

		if (search(root->left, Broot) || search(root->right, Broot))
			return 1;
		return 0;
	}


	bool isSubStructure(TreeNode* A, TreeNode* B) {
		if (B == nullptr&&A != nullptr)
			return 0;

		return search(A, B);
	}
};


/*
114. 二叉树展开为链表
给你二叉树的根结点 root ，请你将它展开为一个单链表：

展开后的单链表应该同样使用 TreeNode ，其中 right 子指针指向链表中下一个结点，而左子指针始终为 null 。
展开后的单链表应该与二叉树 先序遍历 顺序相同。

*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution114 {
public:
    void solveMethod1(TreeNode* root){
        stack<TreeNode*> sta;

        TreeNode* listCur = nullptr;
        if(root!=nullptr)
            sta.push(root);
        while(!sta.empty() && sta.top()!=nullptr){
            TreeNode* popEle = sta.top();
            if (listCur!=nullptr){
                listCur->right = popEle;
                listCur->left = nullptr;
            }
            sta.pop();
            listCur = popEle;
            if (popEle->right!=nullptr){
                sta.push(popEle->right);
            }
            if (popEle->left!=nullptr){
                sta.push(popEle->left);
            }
        }
    }
    TreeNode* solveMethod2(TreeNode* root){ //这个要重点看看
    //这是O(1)的空间复杂度，但是时间复杂度较O(N)的空间复杂度的实现更大些
        if (root==nullptr || (root->left==nullptr && root->right==nullptr)){
            return root;
        }
        TreeNode* leftrecur =  solveMethod2(root->left); //递归实现，认为左子树已经排成链表了，然后返回链表头
        TreeNode* rightrecur = solveMethod2(root->right);

        TreeNode* Cur = leftrecur;
        while(Cur!=nullptr && Cur->right!=nullptr){
            Cur = Cur->right;
        } //到达左子树的链表尾
        if (Cur!=nullptr){
            Cur->right = rightrecur;
            Cur->left = nullptr;
        }
        if (leftrecur!=nullptr){
            root->right = leftrecur;
        }
        else{
            root->right = rightrecur;
        }
        root->left = nullptr;
        return root;
    }
    void flatten(TreeNode* root) {
        solveMethod2(root); //同样的，递归实现代码更简单，而且容易想
    }
};


