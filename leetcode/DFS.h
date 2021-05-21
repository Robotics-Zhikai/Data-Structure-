#pragma once
#include "main.h"

/*
��ָ Offer 12. �����е�·��
����һ�� m x n ��ά�ַ����� board ��һ���ַ������� word ����� word �����������У����� true �����򣬷��� false ��

���ʱ��밴����ĸ˳��ͨ�����ڵĵ�Ԫ���ڵ���ĸ���ɣ����С����ڡ���Ԫ������Щˮƽ���ڻ�ֱ���ڵĵ�Ԫ��
ͬһ����Ԫ���ڵ���ĸ�������ظ�ʹ�á�

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
	//�������Թ�Ҫ�󣬷���DFS�����Ŀ��Ҫ�õ���ʵ�� ����ʵ�ֺ����׳���

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
��ָ Offer 55 - I. �����������
����һ�ö������ĸ��ڵ㣬���������ȡ��Ӹ��ڵ㵽Ҷ�ڵ����ξ����Ľڵ㣨������Ҷ�ڵ㣩�γ�����һ��·�����·���ĳ���Ϊ������ȡ�

*/
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
	
};
class SolutionOffer55_I { //����̬�滮��࣬�����ҵ��Ż��ӽṹ��Ȼ��õ�������Ľ�
public:
	int maxDepth(TreeNode* root) {
		if (root == nullptr) {
			return 0;
		}
		return max(maxDepth(root->left), maxDepth(root->right)) + 1;
	}
};



/*
��ָ Offer 55 - II. ƽ�������
����һ�ö������ĸ��ڵ㣬�жϸ����ǲ���ƽ������������ĳ������������ڵ���������������������1����ô������һ��ƽ���������
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
		if (isBalancedRecur(root->left, &leftdepth) && isBalancedRecur(root->right, &rightdepth)) { //T(n)=2T(n/2)+O(1) ->O(n)���Ӷ�
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