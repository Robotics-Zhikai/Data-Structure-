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