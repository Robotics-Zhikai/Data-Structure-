#pragma once
#include "main.h"
#include <queue>
/*
��ָ Offer 32 - I. ���ϵ��´�ӡ������
���ϵ��´�ӡ����������ÿ���ڵ㣬ͬһ��Ľڵ㰴�մ����ҵ�˳���ӡ��
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
��ָ Offer 32 - II. ���ϵ��´�ӡ������ II
���ϵ��°����ӡ��������ͬһ��Ľڵ㰴�����ҵ�˳���ӡ��ÿһ���ӡ��һ�С�
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
��ָ Offer 27. �������ľ���
�����һ������������һ�����������ú���������ľ��� ��ת������
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
		return mirrorTreeQueue(root); //�ö��еķ���ʱ�临�Ӷ����õݹ�ķ�����ࣻ�ռ临�Ӷȱȵݹ�ķ�������һ��
									  //֮�����пռ临�ӶȲ�һ�������⣬����Ϊ�ݹ鷽�������Ŀռ临�Ӷ���O(Clogn)����������ȣ�
									  //�����з����ռ临�Ӷ���O(2^logn)����Ȼ����˿ռ临�Ӷȵ����ӡ�
	}
};


/*
��ָ Offer 34. �������к�Ϊĳһֵ��·��
����һ�ö�������һ����������ӡ���������нڵ�ֵ�ĺ�Ϊ��������������·����
�����ĸ��ڵ㿪ʼ����һֱ��Ҷ�ڵ��������Ľڵ��γ�һ��·����
*/

class SolutionOffer34 {
	//�����Ӧ�÷�����ϰ�����������������������������������������������������������׾�д����
public:
	vector<vector<int>> pathSumStack(TreeNode* root, int target)
		//����ջ���Ȱ�������ȱ������Ŀ��д������Ȼ���������������Ҫ�Ĳ���
		//û���õݹ�
		//д�ǵݹ�������������ʱ��Ҫ����ջ��Ȼ������������ı���˳��ȥһ��һ��д����Ȼ��д������
	{
		stack<bool> LorR;//��¼��ǰ�ڵ�ķ������ 0Ϊ���η��ʣ�1Ϊ�Ѿ�������������
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

			if (curp != nullptr) //������������������֮��Ĳ���
			{
				curnum += curp->val;
				if (curnum == target&&curp->left == nullptr&&curp->right == nullptr)
					//����ע��·���Ķ��壺�����ĸ��ڵ㿪ʼ����һֱ��Ҷ�ڵ��������Ľڵ��γ�һ��·����
					//һ��Ҫ�ж��ҵ��ĵ��ǲ���Ҷ�ڵ㡣ֻ����Ҷ�ڵ����
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
					while (LorR.empty() == 0 && LorR.top() == 1) //LorR.empty()==0����©��
					{
						if (*(S.end() - 1) != nullptr)
							curnum -= (*(S.end() - 1))->val;
						S.pop_back();
						LorR.pop();
					}
					if (S.size() == 0)
						break;
					curp = (*(S.end() - 1))->right;
					LorR.top() = 1; //�������©��
				}
				continue;
			}
			curp = curp->left;
		}
		return result;
	}


	void traverseRecur(TreeNode* root, int target)
		//�Եݹ�ķ�ʽʵ�ֶ�����������ȱ�����Ȼ�����ʵ�λ�������ʵ�����
	{
		if (root != nullptr)
			path.push_back(root->val);
		else
			path.push_back(-1); //ֻ��һ����ʱ�������϶�Ҫ����ȥ
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
		return TraverseRecur(root, target);//8ms 19.6MB 86.98% 30.63% ���ʱ�䲻׼ ÿ�����ж���һ�� �ұ仯��Χ�ܴ� 
	}
};


/*
��ָ Offer 07. �ؽ�������
����ĳ��������ǰ���������������Ľ�������ؽ��ö����������������ǰ���������������Ľ���ж������ظ������֡�
��Ҫ�úÿ���������������������������������������������������������������������������������������������������������������
*/

class SolutionOffer07 {
public:
	unordered_map<int, int> mapping;//inorder�����ֺ�index��ӳ��
	vector<int> preo;
	vector<int> ino;
	TreeNode* recur(int rootindex, int left, int right)//����ҿ�
													   //���������ĸ��ڵ���preo������rootindex������������������ino��������[left,right)������
													   //Ȼ�󷵻������ĸ��ڵ�
	{
		if (left >= right)
			return nullptr;
		int rootvalue = preo[rootindex];
		TreeNode* node = new TreeNode(rootvalue);
		node->left = recur(rootindex + 1, left, mapping[rootvalue]);//�������ı������ȱ������������ٱ���������
																	//����rootindex+1���������ĸ��ڵ㣬 rootindex+mapping[rootvalue]-left+1���������ĸ��ڵ�
		node->right = recur(rootindex + mapping[rootvalue] - left + 1, mapping[rootvalue] + 1, right);
		return node;
	}
	TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
		preo = preorder;//��������ȥ�ܹ������ٶ�
		ino = inorder;
		for (int i = 0; i<inorder.size(); i++)
			mapping[inorder[i]] = i;
		return recur(0, 0, inorder.size());
	}

/*

ǰ��������Ӹ��ڵ�root��ʼ��ֻҪ�����ӽڵ㣬��һֱ�������·��ߣ�ֱ�������½ǡ� 
������������Ǵ������½����ϣ�ʾ���е�4-5-8-9-3������������ڵ������ӽڵ㣬���ת��ʾ���е�8-10����

��ˣ������е�if������ǰ������һֱ���������������������inorder[inorderIndex]����ʾ�������½ǣ�
��ʱ����Ҫ�����߲�������������Ҳ����while����顣

���ǵ����ķ����������֪�������ṹ������������ȱ����������ĳ���ṹ��һ���ģ����ǽ���ջ����
���ڵ㿪ʼ�����ϰ����ӽڵ�ѹջ��ֻ������֪���Ľṹ����ֱ��ͨ���ж��������Ƿ�Ϊnull���жϣ�
��������֪�������δ֪���Ľṹ��˵����Ҫ��ǰ�������ֵ�����������ֵ������ж�������Ϊnull��

Ȼ����ǵ�ջ��ֱ����������������

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

���ߣ�LeetCode-Solution
���ӣ�https://leetcode-cn.com/problems/zhong-jian-er-cha-shu-lcof/solution/mian-shi-ti-07-zhong-jian-er-cha-shu-by-leetcode-s/
��Դ�����ۣ�LeetCode��
����Ȩ���������С���ҵת������ϵ���߻����Ȩ������ҵת����ע��������



*/
};