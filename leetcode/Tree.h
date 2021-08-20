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
	TreeNode* recur(int rootindex, int left, int right)
	//����ҿ�
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
105. ��ǰ��������������й��������
����һ������ǰ�������������������������

ע��:
����Լ�������û���ظ���Ԫ�ء�
 
 �������ϱ߽�ָoffer07�ؽ���������һ����
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
    //recur�Ļ����Ǹ������ڵ���pre�е�index����Ҫ��������rootindexΪ���ڵ��������inorder�е�������Χ
    //Ȼ��ݹ�õ�һ��������ɵ�������ָ�������ĸ��ڵ�
        if (left==right){//�������׳������װ����д©�����˳�����ûд��
            return nullptr;
        }//������ô��⣺left����right��ζ�Ź�����������һ��������ֱ��return nullptr����
        TreeNode* rootnode = new TreeNode(pre[rootindex]);
        rootnode->left = recur(rootindex+1,left,MAP[pre[rootindex]]);
        rootnode->right = recur(rootindex+MAP[pre[rootindex]]-left+1,MAP[pre[rootindex]]+1,right);
        return rootnode;
    }
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        //���õݹ�ʵ�ְɣ�����ʵ�����׳����Ҳ�����
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



/*

236. �������������������
����һ��������, �ҵ�����������ָ���ڵ������������ȡ�

�ٶȰٿ�������������ȵĶ���Ϊ���������и��� T �������ڵ� p��q��
����������ȱ�ʾΪһ���ڵ� x������ x �� p��q �������� x ����Ⱦ����ܴ�һ���ڵ�Ҳ���������Լ������ȣ�����

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
        //�����������һ������ö�ٵĽⷨ��ʱ�临�Ӷ���n^2
        if (root==nullptr)
            return nullptr;
        if (p==q)
            return p;
        if (p==root) //������ĳһ������Ҫ���ҵĽ��ʱ����ֱ�ӷ���
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
        else{ //ֻ�ж��߷��������������ʱ���������Ĺ������
            return root;
        }
        return nullptr;
    }
    TreeNode* solveMethod1(TreeNode* root,TreeNode* p,TreeNode* q){
        return traverse(root,p,q);
    }
    
    //https://leetcode-cn.com/problems/lowest-common-ancestor-of-a-binary-tree/solution/236-er-cha-shu-de-zui-jin-gong-gong-zu-xian-hou-xu/
    TreeNode* solveMethod2(TreeNode* root,TreeNode* p,TreeNode* q){
        //�ݹ�ʵ�֣�ֻɨһ�飬��O(N)�ĸ��Ӷ� ���˼·Ҫ������ϰ
        if (root==p || root == q){
            return root;
        }
        if (root == nullptr)
            return nullptr;
        TreeNode* rootleft = solveMethod2(root->left,p,q); //��Ϊ����ݹ麯�����صľ���������Ľ�
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
102. �������Ĳ������
����һ�������������㷵���䰴 ������� �õ��Ľڵ�ֵ�� �������أ������ҷ������нڵ㣩��


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
        //�ݹ�ʵ�֣�����򵥣������ٶȿ飬����ռ�ݵ��ڴ���Խϴ�
        vector<vector<int>> res;
        recur(res,root,0);
        return res;
    }
    vector<vector<int>> levelOrder(TreeNode* root) {
        return solveMethod2(root);
    }
};


/*
538. �Ѷ���������ת��Ϊ�ۼ���
�������� ���� ���ĸ��ڵ㣬�����Ľڵ�ֵ������ͬ�����㽫��ת��Ϊ�ۼ�����Greater Sum Tree����
ʹÿ���ڵ� node ����ֵ����ԭ���д��ڻ���� node.val ��ֵ֮�͡�

����һ�£�������������������Լ��������

�ڵ���������������� С�� �ڵ���Ľڵ㡣
�ڵ���������������� ���� �ڵ���Ľڵ㡣
��������Ҳ�����Ƕ�����������

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
    //��Ȼһ��ʼ�뵽���ȱ����ұߺ������ߣ�����û���뵽DFS���������Ҷ�Ӧ���������н����ۼ�ֵ
    //�����ͨ�˺ܺ�д��Ҫ������
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
98. ��֤����������
����һ�����������ж����Ƿ���һ����Ч�Ķ�����������

����һ��������������������������

�ڵ��������ֻ����С�ڵ�ǰ�ڵ������
�ڵ��������ֻ�������ڵ�ǰ�ڵ������
�������������������������Ҳ�Ƕ�����������

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
		//�ö��������������ʣ�����Ƕ����������Ļ����������������Ӧ��������ģ��������������ʾ���Ƕ���������
		vector<int> res;
		DFS(root,res);
		for(int i = 0;i<res.size()-1;i++){
			if (res[i+1]<=res[i])
				return false;
		}
		return true;
	}
	bool solveMethod2(TreeNode* root,long int lower,long int upper){
		//����ܳ��󵽵Ļ��ܼ򵥣����������ǳ��󲻳�������lower��upper�ĵݹ� �࿴��������
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
    // } //���ܰ������������������Ļ����ֱܷ�[5,4,6,null,null,3,7]������� ����ü�lower��upper��һ������
};




/*
208. ʵ�� Trie (ǰ׺��)
Trie���������� "try"������˵ ǰ׺�� ��һ���������ݽṹ�����ڸ�Ч�ش洢�ͼ����ַ������ݼ��еļ���
��һ���ݽṹ���൱���Ӧ���龰�������Զ������ƴд��顣

����ʵ�� Trie �ࣺ

Trie() ��ʼ��ǰ׺������
void insert(String word) ��ǰ׺���в����ַ��� word ��
boolean search(String word) ����ַ��� word ��ǰ׺���У����� true�������ڼ���֮ǰ�Ѿ����룩�����򣬷��� false ��
boolean startsWith(String prefix) ���֮ǰ�Ѿ�������ַ��� word ��ǰ׺֮һΪ prefix ������ true �����򣬷��� false ��

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
//�ϱ�ע�͵��������ʧ�ܵ�д����û�аѸ����ڵ�������ʾ���������ݽṹ


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
        map<char,shared_ptr<node>> children; //���ӽڵ�
    };
    shared_ptr<node> treehead; //�����������ָ�룬��ôִ��ʱ��ֱ�Ӽ��룬ռ�õĿռ�Ҳ��С�ܶ�
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */



/*
112. ·���ܺ�
����������ĸ��ڵ� root ��һ����ʾĿ��͵����� targetSum ��
�жϸ������Ƿ���� ���ڵ㵽Ҷ�ӽڵ� ��·��������·�������нڵ�ֵ��ӵ���Ŀ��� targetSum ��

Ҷ�ӽڵ� ��ָû���ӽڵ�Ľڵ㡣

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
		//���� �Ƚϳ���
		int curValue = 0;
		DFS(root,curValue,targetSum);
		return HAS;
    }
};



/*
113. ·���ܺ� II
����������ĸ��ڵ� root ��һ������Ŀ��� targetSum ���ҳ����� �Ӹ��ڵ㵽Ҷ�ӽڵ� ·���ܺ͵��ڸ���Ŀ��͵�·����

Ҷ�ӽڵ� ��ָû���ӽڵ�Ľڵ㡣

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
		if (root->left!=nullptr) //ע����������©��
			path.pop_back();
		DFS(root->right,targetSum,curvalue,path);
		curvalue = root->right==nullptr?curvalue:curvalue-root->right->val;
		if (root->right!=nullptr)
			path.pop_back();
	}
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
		//���ǱȽϳ����
		res = {};
		int curvalue = 0;
		vector<int> path;
		DFS(root,targetSum,curvalue,path);
		return res;
    }
};



/*
235. ����������������������� 
����һ������������, �ҵ�����������ָ���ڵ������������ȡ�

�ٶȰٿ�������������ȵĶ���Ϊ���������и��� T ��������� p��q��
����������ȱ�ʾΪһ����� x������ x �� p��q �������� x ����Ⱦ����ܴ�һ���ڵ�Ҳ���������Լ������ȣ�����

���磬�������¶���������:  root = [6,2,8,0,4,7,9,null,null,3,5]


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

//ע�������ö��������������ʣ����� �� ��ĺܼ򵥰�������
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