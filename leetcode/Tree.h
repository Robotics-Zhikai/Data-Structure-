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
��ָ Offer 32 - III.���ϵ��´�ӡ������ III
��ʵ��һ����������֮����˳���ӡ������������һ�а��մ����ҵ�˳���ӡ��
�ڶ��㰴�մ��ҵ����˳���ӡ���������ٰ��մ����ҵ�˳���ӡ���������Դ����ơ�
*/
class SolutionOffer32_III {
public:
	vector<vector<int>> levelOrder(TreeNode* root) { //֮���δ�ӡ
		int level = 0;
		vector<vector<int>> result;
		//ʱ�临�Ӷ�ΪO(n),�ռ临�Ӷ�ΪO(n)
		//������ֱ���ö��У�ֻ����ÿ�ΰ�vector push��result��ʱ��Ҫ���һ��reverseһ��
		stack<TreeNode*> sta1; //������ջ���õ���ͬ�ı���˳��
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
	unordered_map<int, int> mapping;//inorder�����ֺ�index��ӳ�� O(n)�Ŀռ�洢��ϣӳ��
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


/*
��ָ Offer 26. �����ӽṹ
�������ö�����A��B���ж�B�ǲ���A���ӽṹ��(Լ��������������һ�������ӽṹ)

B��A���ӽṹ�� �� A���г��ֺ�B��ͬ�Ľṹ�ͽڵ�ֵ��

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

	bool search(TreeNode* root, TreeNode* Broot) //�ݹ������ĳһ�ڵ�Ϊ�����ӽṹ�Ƿ������root��
	{ //ֻ����ֱ���ж�rootΪ�������������ܻ���ƥ��Brootʱ����ֱ�ӷ���
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
114. ������չ��Ϊ����
����������ĸ���� root �����㽫��չ��Ϊһ��������

չ����ĵ�����Ӧ��ͬ��ʹ�� TreeNode ������ right ��ָ��ָ����������һ����㣬������ָ��ʼ��Ϊ null ��
չ����ĵ�����Ӧ��������� ������� ˳����ͬ��

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
    TreeNode* solveMethod2(TreeNode* root){ //���Ҫ�ص㿴��
    //����O(1)�Ŀռ临�Ӷȣ�����ʱ�临�ӶȽ�O(N)�Ŀռ临�Ӷȵ�ʵ�ָ���Щ
        if (root==nullptr || (root->left==nullptr && root->right==nullptr)){
            return root;
        }
        TreeNode* leftrecur =  solveMethod2(root->left); //�ݹ�ʵ�֣���Ϊ�������Ѿ��ų������ˣ�Ȼ�󷵻�����ͷ
        TreeNode* rightrecur = solveMethod2(root->right);

        TreeNode* Cur = leftrecur;
        while(Cur!=nullptr && Cur->right!=nullptr){
            Cur = Cur->right;
        } //����������������β
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
        solveMethod2(root); //ͬ���ģ��ݹ�ʵ�ִ�����򵥣�����������
    }
};


