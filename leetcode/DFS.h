#pragma once
#include "main.h"

/*
剑指 Offer 12. 矩阵中的路径
给定一个 m x n 二维字符网格 board 和一个字符串单词 word 。如果 word 存在于网格中，返回 true ；否则，返回 false 。

单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。
同一个单元格内的字母不允许被重复使用。

*/

class SolutionOffer12
{
public:
	// int rows;
	// int cols;

	// bool exist(vector<vector<char>>& board, string word) {
	//     rows = board.size();
	//     if (!board.empty())
	//         cols = board[0].size();

	//     stack<vector<int>> sta;

	//     vector<vector<bool>> isvisited(board.size(),vector<bool>(board[0].size(),0));
	//     int index = 0;
	//     for(int i = 0;i<board.size();i++){
	//         for(int j = 0;j<board[i].size();j++){
	//             if (isvisited[i][j]==0 && board[i][j]==word[index]){
	//                 sta.push(vector<int>{i,j});
	//                 isvisited[i][j] = 1;
	//             }
	//         }
	//     }
	//     if (sta.empty())
	//         return 0;

	//     index++;
	//     bool flag = 0;
	//     while(!sta.empty())
	//     {
	//         vector<int> chosen = sta.top();
	//         sta.pop();
	//         if (chosen[0]!=0){
	//             if (isvisited[chosen[0]-1][chosen[1]]==0 && board[chosen[0]-1][chosen[1]]==word[index]){
	//                 sta.push(vector<int>{chosen[0]-1,chosen[1]});
	//                 flag = 1;
	//             }
	//         }
	//         if (chosen[0]!=rows-1){
	//             if (isvisited[chosen[0]+1][chosen[1]]==0 && board[chosen[0]+1][chosen[1]]==word[index]){
	//                 sta.push(vector<int>{chosen[0]+1,chosen[1]});
	//                 flag = 1;
	//             }
	//         }
	//         if (chosen[1]!=0){
	//             if (isvisited[chosen[0]][chosen[1]-1]==0 && board[chosen[0]][chosen[1]-1]==word[index]){
	//                 sta.push(vector<int>{chosen[0],chosen[1]-1});
	//                 flag = 1;
	//             }
	//         }
	//         if (chosen[1]!=cols-1){
	//             if (isvisited[chosen[0]][chosen[1]+1]==0 && board[chosen[0]][chosen[1]+1]==word[index]){
	//                 sta.push(vector<int>{chosen[0],chosen[1]+1});
	//                 flag = 1;
	//             }
	//         }

	//         if (flag){
	//             index++;
	//             if (index == word.size())
	//                 return 1;
	//             flag = 0;
	//         }
	//     }
	//     if (index == word.size())
	//         return 1;
	//     return 0 ;

	// }
	//除非面试官要求，否则DFS类的题目不要用迭代实现 迭代实现很容易出错

	bool DFS(vector<vector<bool>>& isvisited, const vector<vector<char>>& board,
		int i, int j, string word, int index)
	{

		if (index == word.size()) {
			return 1;
		}
		if (word.size() == 1 && board[i][j] == word[index])
			return 1;
		bool result = 0;
		if (isvisited[i][j] == 0 && board[i][j] == word[index]) {
			isvisited[i][j] = 1;
			if (i != 0) {
				result = result || DFS(isvisited, board, i - 1, j, word, index + 1);
			}
			if (i != board.size() - 1) {
				result = result || DFS(isvisited, board, i + 1, j, word, index + 1);
			}
			if (j != 0) {
				result = result || DFS(isvisited, board, i, j - 1, word, index + 1);
			}
			if (j != board[0].size() - 1) {
				result = result || DFS(isvisited, board, i, j + 1, word, index + 1);
			}
			isvisited[i][j] = 0;
		}
		return result;
	}

	bool exist(vector<vector<char>>& board, string word)
	{
		if (word.size() == 0)
			return 0;
		if (board.size() == 0)
			return 0;
		vector<vector<bool>> isvisited(board.size(), vector<bool>(board[0].size(), 0));
		for (int i = 0; i<board.size(); i++) {
			for (int j = 0; j<board[i].size(); j++) {
				if (DFS(isvisited, board, i, j, word, 0))
					return 1;
			}
		}
		return 0;
	}

	void test()
	{
		//vector<vector<char>> board = { {'a','a','a','a' }, { 'a','a','a','a' }, { 'a','a','a','a' }, { 'a','a','a','a' } };
		vector<vector<char>> board = { { 'a','a' }, { 'a','a' } };
	
		exist(board, "aaaaa");
	}
};

/*
剑指 Offer 55 - I. 二叉树的深度
输入一棵二叉树的根节点，求该树的深度。从根节点到叶节点依次经过的节点（含根、叶节点）形成树的一条路径，最长路径的长度为树的深度。

*/
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
	
};
class SolutionOffer55_I { //跟动态规划差不多，就是找到优化子结构，然后得到合问题的解
public:
	int maxDepth(TreeNode* root) {
		if (root == nullptr) {
			return 0;
		}
		return max(maxDepth(root->left), maxDepth(root->right)) + 1;
	}
};



/*
剑指 Offer 55 - II. 平衡二叉树
输入一棵二叉树的根节点，判断该树是不是平衡二叉树。如果某二叉树中任意节点的左右子树的深度相差不超过1，那么它就是一棵平衡二叉树。
*/

class SolutionOffer55_II {
public:
	bool isBalancedRecur(TreeNode* root, int* maxdepth) {
		if (root == nullptr) {
			*maxdepth = 0;
			return 1;
		}

		int leftdepth;
		int rightdepth;
		if (isBalancedRecur(root->left, &leftdepth) && isBalancedRecur(root->right, &rightdepth)) { //T(n)=2T(n/2)+O(1) ->O(n)复杂度
			if (abs(leftdepth - rightdepth) <= 1) {
				*maxdepth = max(leftdepth, rightdepth) + 1;
				return 1;
			}
		}
		return 0;
	}
	bool isBalanced(TreeNode* root) {
		int maxdepth;
		return isBalancedRecur(root, &maxdepth);
	}
};

/*
剑指 Offer 13. 机器人的运动范围
地上有一个m行n列的方格，从坐标 [0,0] 到坐标 [m-1,n-1] 。一个机器人从坐标 [0, 0] 的格子开始移动，
它每次可以向左、右、上、下移动一格（不能移动到方格外），
也不能进入行坐标和列坐标的数位之和大于k的格子。例如，当k为18时，机器人能够进入方格 [35, 37] ，因为3+5+3+7=18。
但它不能进入方格 [35, 38]，因为3+5+3+8=19。请问该机器人能够到达多少个格子？

*/

class SolutionOffer13 {
public:
    void DFS(vector<vector<int>>& visit,int m,int n,int k,const int M,const int N){
        visit[m][n] = 1;
        // string row = to_string(m);
        // string col = to_string(n);
        // row = row+col;
        // for(int i = 0;i<row.size();i++){
            // SUM+=row[i]-'0';
        // }

        int SUM = m/10+m%10+n/10+n%10; //直接用这个简单的计算方法即可 可以大幅缩小递归占用空间
        if (SUM<=k)
            Count++;
        else
            return; //如果超过k，就直接剪枝

        if (m<M-1&&visit[m+1][n]==0){ //访问过也剪枝
            DFS(visit,m+1,n,k,M,N);
        }
        if (m>0&&visit[m-1][n]==0){
            DFS(visit,m-1,n,k,M,N);
        }
        if (n>0 && visit[m][n-1]==0){
            DFS(visit,m,n-1,k,M,N);
        }
        if (n<N-1&&visit[m][n+1]==0){
            DFS(visit,m,n+1,k,M,N);
        }
    }
    int movingCount(int m, int n, int k) {
        Count = 0;
        vector<vector<int>> visit(m,vector<int>(n,0));
        DFS(visit,0,0,k,m,n);
        return Count;
    }
private:
    int Count = 0;
};

/*
329. 矩阵中的最长递增路径
给定一个 m x n 整数矩阵 matrix ，找出其中 最长递增路径 的长度。

对于每个单元格，你可以往上，下，左，右四个方向移动。 你 不能 在 对角线 方向上移动或移动到 边界外（即不允许环绕）。
*/
class Solution329 {
public:
    int res = INT_MIN;
    //有了下边的这个lower，很容易编写代码
    int DFS(vector<vector<int>>& storage,vector<vector<int>>& matrix,int i,int j,int lower){
        //DFS返回值的含义就是最长递增路径
        if (i<0 || i>=matrix.size() || j<0 || j>=matrix[0].size()){
            return 0;
        }
        if (matrix[i][j]<=lower){
            return 0;
        }
        int thismax = 0;
        if (storage[i][j]==-1){
            thismax = max(max(DFS(storage,matrix,i+1,j,matrix[i][j]),DFS(storage,matrix,i-1,j,matrix[i][j]))
        ,max(DFS(storage,matrix,i,j+1,matrix[i][j]),DFS(storage,matrix,i,j-1,matrix[i][j])))+1;
            storage[i][j] = thismax;
        }
        else{
            thismax = storage[i][j];
        }
        res = max(res,thismax);
        return thismax;
    }
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        // vector<vector<bool>> isvisit(matrix.size(),vector<int>(matrix[0].size(),0));
        //因为是最长递增路径，所以不可能出现搜索路径交叉的情况
        vector<vector<int>> storage(matrix.size(),vector<int>(matrix[0].size(),-1));//记忆化搜索
        for(int i = 0;i<matrix.size();i++){
            for(int j = 0;j<matrix[i].size();j++){
                if (storage[i][j]==-1){ //这又剪枝了很多
                    DFS(storage,matrix,i,j,INT_MIN);
                }
            }
        }
        return res;
    }
};