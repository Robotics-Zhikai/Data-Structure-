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
	TreeNode* recur(int rootindex, int left, int right)
	//左闭右开
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
105. 从前序与中序遍历序列构造二叉树
根据一棵树的前序遍历与中序遍历构造二叉树。

注意:
你可以假设树中没有重复的元素。
 
 这个题跟上边剑指offer07重建二叉树是一样的
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
class Solution105 {
public:
    unordered_map<int,int> MAP;
    vector<int> pre;
    vector<int> inord;
    TreeNode* recur(int rootindex,int left,int right){
    //recur的话就是给定根节点在pre中的index，和要构建的以rootindex为根节点的子树在inorder中的索引范围
    //然后递归得到一个构建完成的子树，指向子树的根节点
        if (left==right){//这里容易出错，容易把这个写漏或者退出条件没写对
            return nullptr;
        }//可以这么理解：left等于right意味着构建的子树是一个空树，直接return nullptr即可
        TreeNode* rootnode = new TreeNode(pre[rootindex]);
        rootnode->left = recur(rootindex+1,left,MAP[pre[rootindex]]);
        rootnode->right = recur(rootindex+MAP[pre[rootindex]]-left+1,MAP[pre[rootindex]]+1,right);
        return rootnode;
    }
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        //就用递归实现吧，迭代实现容易出错且不好想
        MAP.clear();
        pre = preorder;
        inord = inorder;
        for (int i = 0;i<inorder.size();i++){
            MAP[inorder[i]] = i;
        }
        return recur(0,0,inorder.size());
    }
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



/*

236. 二叉树的最近公共祖先
给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。

百度百科中最近公共祖先的定义为：“对于有根树 T 的两个节点 p、q，
最近公共祖先表示为一个节点 x，满足 x 是 p、q 的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）。”

*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution236 {
public:
    bool find(TreeNode* root,TreeNode* p){
        if (root==nullptr && p == nullptr){
            return 1;
        }
        else if (root==nullptr && p!=nullptr){
            return 0;
        }
        else if (root == p){
            return 1;
        }
        return (find(root->left,p) || find(root->right,p));
    }
    TreeNode* traverse(TreeNode* root,TreeNode* p,TreeNode* q){
        //这个本质上是一个暴力枚举的解法，时间复杂度在n^2
        if (root==nullptr)
            return nullptr;
        if (p==q)
            return p;
        if (p==root) //当遇到某一结点就是要查找的结点时，就直接返回
            return p; 
        if (q==root)
            return q;
        
        bool leftp = find(root->left,p);
        bool leftq = find(root->left,q);
        if (leftp&&leftq){
            return traverse(root->left,p,q);
        }
        else if (!leftp && !leftq){
            return traverse(root->right,p,q);
        }
        else{ //只有二者分列子树的两侧的时候才是最深的公共结点
            return root;
        }
        return nullptr;
    }
    TreeNode* solveMethod1(TreeNode* root,TreeNode* p,TreeNode* q){
        return traverse(root,p,q);
    }
    
    //https://leetcode-cn.com/problems/lowest-common-ancestor-of-a-binary-tree/solution/236-er-cha-shu-de-zui-jin-gong-gong-zu-xian-hou-xu/
    TreeNode* solveMethod2(TreeNode* root,TreeNode* p,TreeNode* q){
        //递归实现，只扫一遍，是O(N)的复杂度 这个思路要经常复习
        if (root==p || root == q){
            return root;
        }
        if (root == nullptr)
            return nullptr;
        TreeNode* rootleft = solveMethod2(root->left,p,q); //认为这个递归函数返回的就是子问题的解
        TreeNode* rootright = solveMethod2(root->right,p,q);
        if (rootleft!=nullptr && rootright==nullptr){
            return rootleft;
        }
        else if (rootleft==nullptr && rootright!=nullptr){
            return rootright;
        }
        else if (rootleft!=nullptr && rootright!=nullptr){
            return root;
        }
        return nullptr;
    }
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        return solveMethod2(root,p,q);
        return solveMethod1(root,p,q);
    }
};


/*
102. 二叉树的层序遍历
给你一个二叉树，请你返回其按 层序遍历 得到的节点值。 （即逐层地，从左到右访问所有节点）。


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
class Solution102 {
public:
    vector<vector<int>> solveMethod1(TreeNode* root) {
        queue<TreeNode*> que;
        vector<vector<int>> res;
        que.push(root);
        int levelnum = 1;
        while(!que.empty() && que.front()!=nullptr){
            int thisnum = 0;
            vector<int> vec;
            for(int i = 0;i<levelnum;i++){
                if (que.front()->left!=nullptr){
                    que.push(que.front()->left);
                    thisnum++;
                }
                if (que.front()->right!=nullptr){
                    que.push(que.front()->right);
                    thisnum++;
                }
                vec.push_back(que.front()->val);
                que.pop();
            }
            res.push_back(vec);
            levelnum = thisnum;
        }
        return res;
    }
    void recur(vector<vector<int>>& res,TreeNode* root,int depth){
        if (root==nullptr)
            return ;
        if (res.size()<depth+1){
            res.push_back(vector<int>{});
        }
        res[depth].push_back(root->val);
        recur(res,root->left,depth+1);
        recur(res,root->right,depth+1);
    }
    vector<vector<int>> solveMethod2(TreeNode* root) {
        //递归实现，代码简单，运行速度块，但是占据的内存相对较大
        vector<vector<int>> res;
        recur(res,root,0);
        return res;
    }
    vector<vector<int>> levelOrder(TreeNode* root) {
        return solveMethod2(root);
    }
};


/*
538. 把二叉搜索树转换为累加树
给出二叉 搜索 树的根节点，该树的节点值各不相同，请你将其转换为累加树（Greater Sum Tree），
使每个节点 node 的新值等于原树中大于或等于 node.val 的值之和。

提醒一下，二叉搜索树满足下列约束条件：

节点的左子树仅包含键 小于 节点键的节点。
节点的右子树仅包含键 大于 节点键的节点。
左右子树也必须是二叉搜索树。

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
class Solution538 {
public:
    int accumulate;
    void DFS(TreeNode* root)
    //虽然一开始想到了先遍历右边后遍历左边，但是没有想到DFS的作用是找对应子树的所有结点的累加值
    //这个想通了很好写，要多想想
    {
        if (root==nullptr)
            return;
        DFS(root->right);
        root->val += accumulate;
        accumulate = root->val;
        DFS(root->left);
    }
    TreeNode* convertBST(TreeNode* root) {
        accumulate = 0;
        DFS(root);
        return root;
    }
};



/*
98. 验证二叉搜索树
给定一个二叉树，判断其是否是一个有效的二叉搜索树。

假设一个二叉搜索树具有如下特征：

节点的左子树只包含小于当前节点的数。
节点的右子树只包含大于当前节点的数。
所有左子树和右子树自身必须也是二叉搜索树。

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
class Solution98 {
public:
	void DFS(TreeNode* root,vector<int>& res){
		if(root==nullptr)
			return;
		DFS(root->left,res);
		res.push_back(root->val);
		DFS(root->right,res);
	}
	bool solveMethod1(TreeNode* root){
		//用二叉搜索树的性质，如果是二叉搜索树的话，中序遍历后数组应该是有序的，否则数组无序表示不是二叉搜索树
		vector<int> res;
		DFS(root,res);
		for(int i = 0;i<res.size()-1;i++){
			if (res[i+1]<=res[i])
				return false;
		}
		return true;
	}
	bool solveMethod2(TreeNode* root,long int lower,long int upper){
		//这个能抽象到的话很简单，但是问题是抽象不出来带入lower和upper的递归 多看看！！！
		if (root==nullptr)
			return true;
		if (root->val<=lower || root->val>=upper)
			return false;
		return solveMethod2(root->left,lower,root->val) && solveMethod2(root->right,root->val,upper);
	}
	bool isValidBST(TreeNode* root){
		return solveMethod2(root,LONG_MIN,LONG_MAX);
	}
	
    // bool isValidBST(TreeNode* root) {
	// 	if (root==nullptr){
	// 		return true;
	// 	}
	// 	if (root->left!=nullptr){
	// 		if (root->left->val>=root->val)
	// 			return false;
	// 	}
	// 	if (root->right!=nullptr){
	// 		if (root->right->val<=root->val)
	// 			return false;
	// 	}
	// 	return isValidBST(root->left) && isValidBST(root->right);
    // } //不能按照这样来做，这样的话不能分辨[5,4,6,null,null,3,7]这种情况 必须得加lower和upper做一个界限
};




/*
208. 实现 Trie (前缀树)
Trie（发音类似 "try"）或者说 前缀树 是一种树形数据结构，用于高效地存储和检索字符串数据集中的键。
这一数据结构有相当多的应用情景，例如自动补完和拼写检查。

请你实现 Trie 类：

Trie() 初始化前缀树对象。
void insert(String word) 向前缀树中插入字符串 word 。
boolean search(String word) 如果字符串 word 在前缀树中，返回 true（即，在检索之前已经插入）；否则，返回 false 。
boolean startsWith(String prefix) 如果之前已经插入的字符串 word 的前缀之一为 prefix ，返回 true ；否则，返回 false 。

*/

// class Trie {
// public:
//     /** Initialize your data structure here. */
//     Trie() {

//     }
    
//     /** Inserts a word into the trie. */
//     void insert(string word) {
//         for(int i = 0;i<word.size();i++){
//             if (data.size()==i){
//                 data.push_back(map<char,bool>{{word[i],0}});
//             }
//             else{
//                 if (data[i].find(word[i])==data[i].end()){
//                     data[i].insert({word[i],0});
//                 }
//             }
//             if (i==word.size()-1){
//                 data[i][word[i]] = true;
//             }
//         }
//     }
    
//     /** Returns if the word is in the trie. */
//     bool search(string word) {
//         if (data.size()<word.size()){
//             return false;
//         }
//         for (int i = 0;i<word.size();i++){
//             auto found = data[i].find(word[i]);
//             if (found==data[i].end()){
//                 return false;
//             }
//         }
//         int i = word.size()-1;
//         return data[i][word[i]];
//     }
    
//     /** Returns if there is any word in the trie that starts with the given prefix. */
//     bool startsWith(string prefix) {
//         if (data.size()<prefix.size()){
//             return false;
//         }
//         for (int i = 0;i<prefix.size();i++){
//             auto found = data[i].find(prefix[i]);
//             if (found==data[i].end()){
//                 return false;
//             }
//         }
//         // int i = prefix.size()-1;
//         // if (data[i][prefix[i]]==true){
//         //     return false;
//         // }
//         return true;
//     }

// private:
//     vector<map<char,bool>> data;
// };
//上边注释掉的这个是失败的写法，没有把各个节点真正表示成树的数据结构


class Trie {
public:
    /** Initialize your data structure here. */
    Trie():treehead(new node()) {

    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        shared_ptr<node> cur = treehead;
        for(auto &c:word){
            cur = cur->ADDchild(c);
        }
        cur->isfinal = true;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        shared_ptr<node> cur = treehead;
        for(auto &c:word){
            cur = cur->FINDchild(c);
            if (cur==nullptr){
                return false;
            }
        }
        return cur->isfinal;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        shared_ptr<node> cur = treehead;
        for(auto &c:prefix){
            cur = cur->FINDchild(c);
            if (cur==nullptr){
                return false;
            }
        }
        return true;
    }

private:
    class node{
    public:
        node(char cin):c(cin){}
        node() = default;
        shared_ptr<node> ADDchild(char c){
            if (children.find(c)!=children.end()){
                return children[c];
            }
            shared_ptr<node> newchild(new node(c));
            children[c] = newchild;
            return children[c];
        }
        shared_ptr<node> FINDchild(char c){
            if (children.find(c)==children.end()){
                return nullptr;
            }
            return children[c];
        }
        char CHAR(){
            return c;
        }

        bool isfinal = false;
    private:
        char c;
        map<char,shared_ptr<node>> children; //儿子节点
    };
    shared_ptr<node> treehead; //如果不用智能指针，那么执行时间直接减半，占用的空间也减小很多
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */



/*
112. 路径总和
给你二叉树的根节点 root 和一个表示目标和的整数 targetSum ，
判断该树中是否存在 根节点到叶子节点 的路径，这条路径上所有节点值相加等于目标和 targetSum 。

叶子节点 是指没有子节点的节点。

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
class Solution112 {
public:
	bool HAS = false;
	void DFS(TreeNode* root,int & curValue,const int& targetSum){
		if (root==nullptr){
			return;
		}
		curValue+=root->val;
		if (root->left == nullptr && root->right == nullptr){
			if (curValue == targetSum){
				HAS = true;
				return;
			}
		}
		DFS(root->left,curValue,targetSum);
		curValue = root->left==nullptr?curValue:curValue-root->left->val;
		DFS(root->right,curValue,targetSum);
		curValue = root->right==nullptr?curValue:curValue-root->right->val;
	}
    bool hasPathSum(TreeNode* root, int targetSum) {
		//简单题 比较常规
		int curValue = 0;
		DFS(root,curValue,targetSum);
		return HAS;
    }
};



/*
113. 路径总和 II
给你二叉树的根节点 root 和一个整数目标和 targetSum ，找出所有 从根节点到叶子节点 路径总和等于给定目标和的路径。

叶子节点 是指没有子节点的节点。

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
class Solution113 {
public:
	vector<vector<int>> res;
	void DFS(TreeNode* root,const int& targetSum,int& curvalue,vector<int>& path){
		if (root==nullptr){
			return;
		}
		curvalue+=root->val;
		path.push_back(root->val);
		if (root->left==nullptr && root->right==nullptr){
			if (curvalue == targetSum){
				res.push_back(path);
				return;
			}
		}
		DFS(root->left,targetSum,curvalue,path);
		curvalue = root->left==nullptr?curvalue:curvalue-root->left->val;
		if (root->left!=nullptr) //注意这里容易漏掉
			path.pop_back();
		DFS(root->right,targetSum,curvalue,path);
		curvalue = root->right==nullptr?curvalue:curvalue-root->right->val;
		if (root->right!=nullptr)
			path.pop_back();
	}
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
		//还是比较常规的
		res = {};
		int curvalue = 0;
		vector<int> path;
		DFS(root,targetSum,curvalue,path);
		return res;
    }
};



/*
235. 二叉搜索树的最近公共祖先 
给定一个二叉搜索树, 找到该树中两个指定节点的最近公共祖先。

百度百科中最近公共祖先的定义为：“对于有根树 T 的两个结点 p、q，
最近公共祖先表示为一个结点 x，满足 x 是 p、q 的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）。”

例如，给定如下二叉搜索树:  root = [6,2,8,0,4,7,9,null,null,3,5]


*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

//注意充分利用二叉搜索树的性质！！！ 哎 真的很简单啊。。。
class Solution235 {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root==nullptr){
            return nullptr;
        }
        if(root->val<p->val && root->val<q->val){
            return lowestCommonAncestor(root->right,p,q);
        }
        else if (root->val>p->val && root->val>q->val){
            return lowestCommonAncestor(root->left,p,q);
        }
        else{
            return root;
        }
    }
};