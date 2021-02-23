#pragma once
#include "main.h"

//70. ��¥��
//������������¥�ݡ���Ҫ n ������ܵ���¥����
//
//ÿ��������� 1 �� 2 ��̨�ס����ж����ֲ�ͬ�ķ�����������¥���أ�
//
//ע�⣺���� n ��һ����������
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
		vector<vector<long long>> ret = { { 1, 0 },{ 0, 1 } };//retһ��ʼ�Ǹ���λ����
		while (n > 0) {
			if ((n & 1) == 1) {//����ڲݸ�ֽ����һ�¾������ˣ���һ���Ƚ��ɵķ���
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
	���ߣ�LeetCode-Solution
	���ӣ�https://leetcode-cn.com/problems/climbing-stairs/solution/pa-lou-ti-by-leetcode-solution/
	��Դ�����ۣ�LeetCode��
	����Ȩ���������С���ҵת������ϵ���߻����Ȩ������ҵת����ע��������
	*/


	int iteration_climbStairs(int nin)
		//�������Ա����ԵĽ������¼��η��ʵ����� ��С���� ֻ����һ��
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
		//����ֱ�ӵݹ飬�����Ǽ����˱���¼���Դ�����һ��ֵ����η��ʵ����
		//������ѯҲ�ǳ���ʱ����ô����¼�����ܸ����ԵĽ������
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
		//���ַ���
		return iteration_climbStairs(n); //�ռ临�Ӷ�ΪO(1) ʱ�临�Ӷ�ΪOn����Ȼ�ݹ�ʽ��Ҳ��On�����ǵ���ʽ�ĸ���

		//Tn = vector<int>(n+1,inf);
		//return recurclimbStairs(n);		//�ڵݹ��в�Ҫ��static����֪��ԭ�����ڵݹ���дstatic

		//return matrixmultClimbStairs(n); //�ͽ׷�����ݳ����㣬���Ӷ���logn
	}

	void test()
	{

		cout << climbStairs(333345) << endl;
	}
};