#pragma once
#include "main.h"

//70. 爬楼梯
//假设你正在爬楼梯。需要 n 阶你才能到达楼顶。
//
//每次你可以爬 1 或 2 个台阶。你有多少种不同的方法可以爬到楼顶呢？
//
//注意：给定 n 是一个正整数。
class Solution70 {
public:
	vector<vector<long long>> multiply(vector<vector<long long>> &a, vector<vector<long long>> &b) {
		vector<vector<long long>> c(2, vector<long long>(2));
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 2; j++) {
				c[i][j] = a[i][0] * b[0][j] + a[i][1] * b[1][j];
			}
		}
		return c;
	}
	vector<vector<long long>> matrixPow(vector<vector<long long>> a, int n) {
		vector<vector<long long>> ret = { { 1, 0 },{ 0, 1 } };//ret一开始是个单位矩阵
		while (n > 0) {
			if ((n & 1) == 1) {//这个在草稿纸上算一下就明白了，是一个比较巧的方法
				ret = multiply(ret, a);
			}
			n >>= 1;
			a = multiply(a, a);
		}
		return ret;
	}
	int matrixmultClimbStairs(int n) {
		vector<vector<long long>> ret = { { 1, 1 },{ 1, 0 } };
		vector<vector<long long>> res = matrixPow(ret, n);
		return res[0][0];
	}
	/*
	作者：LeetCode-Solution
	链接：https://leetcode-cn.com/problems/climbing-stairs/solution/pa-lou-ti-by-leetcode-solution/
	来源：力扣（LeetCode）
	著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
	*/


	int iteration_climbStairs(int nin)
		//这样可以本质性的解决备忘录多次访问的问题 从小到大 只访问一次
	{
		if (nin == 0 || nin == 1)
			return 1;
		else if (nin == 2)
			return 2;
		int p = 1;
		int c = 1;
		int n = 2;
		for (int i = 3; i <= nin; i++)
		{
			p = c;
			c = n;
			n = p + c;
		}
		return n;
	}

	int inf = 99999;
	vector<int> Tn;
	int recurclimbStairs(int n)
		//这样直接递归，即便是加上了备忘录，仍存在着一个值被多次访问的情况
		//倘若查询也非常耗时，那么备忘录并不能根本性的解决问题
	{
		if (n == -1)
			return 0;
		else if (n == 0 || n == 1)
		{
			Tn[n] = 1;
			return 1;
		}
		else if (n == 3)
		{
			Tn[n] = 3;
			return 3;
		}
		else
		{
			if (Tn[n] != inf)
				return Tn[n];
			else
			{
				Tn[n] = recurclimbStairs(n - 2) + recurclimbStairs(n - 1);
				return Tn[n];
			}
		}
	}
	int climbStairs(int n) {
		//三种方法
		return iteration_climbStairs(n); //空间复杂度为O(1) 时间复杂度为On，虽然递归式的也是On，但是迭代式的更少

		//Tn = vector<int>(n+1,inf);
		//return recurclimbStairs(n);		//在递归中不要用static，不知何原因不能在递归中写static

		//return matrixmultClimbStairs(n); //低阶方阵的幂乘运算，复杂度是logn
	}

	void test()
	{

		cout << climbStairs(333345) << endl;
	}
};