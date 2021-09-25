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

/*
��ָ Offer 13. �����˵��˶���Χ
������һ��m��n�еķ��񣬴����� [0,0] ������ [m-1,n-1] ��һ�������˴����� [0, 0] �ĸ��ӿ�ʼ�ƶ���
��ÿ�ο��������ҡ��ϡ����ƶ�һ�񣨲����ƶ��������⣩��
Ҳ���ܽ�������������������λ֮�ʹ���k�ĸ��ӡ����磬��kΪ18ʱ���������ܹ����뷽�� [35, 37] ����Ϊ3+5+3+7=18��
�������ܽ��뷽�� [35, 38]����Ϊ3+5+3+8=19�����ʸû������ܹ�������ٸ����ӣ�

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

        int SUM = m/10+m%10+n/10+n%10; //ֱ��������򵥵ļ��㷽������ ���Դ����С�ݹ�ռ�ÿռ�
        if (SUM<=k)
            Count++;
        else
            return; //�������k����ֱ�Ӽ�֦

        if (m<M-1&&visit[m+1][n]==0){ //���ʹ�Ҳ��֦
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
329. �����е������·��
����һ�� m x n �������� matrix ���ҳ����� �����·�� �ĳ��ȡ�

����ÿ����Ԫ����������ϣ��£������ĸ������ƶ��� �� ���� �� �Խ��� �������ƶ����ƶ��� �߽��⣨���������ƣ���
*/
class Solution329 {
public:
    int res = INT_MIN;
    //�����±ߵ����lower�������ױ�д����
    int DFS(vector<vector<int>>& storage,vector<vector<int>>& matrix,int i,int j,int lower){
        //DFS����ֵ�ĺ�����������·��
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
        //��Ϊ�������·�������Բ����ܳ�������·����������
        vector<vector<int>> storage(matrix.size(),vector<int>(matrix[0].size(),-1));//���仯����
        for(int i = 0;i<matrix.size();i++){
            for(int j = 0;j<matrix[i].size();j++){
                if (storage[i][j]==-1){ //���ּ�֦�˺ܶ�
                    DFS(storage,matrix,i,j,INT_MIN);
                }
            }
        }
        return res;
    }
};