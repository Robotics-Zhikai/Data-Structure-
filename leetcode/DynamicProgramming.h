#pragma once
#include "main.h"

/*
5. 最长回文子串
给你一个字符串 s，找到 s 中最长的回文子串。
*/
class Solution5 {
public:
	bool isbackStr(const string& str) //判断是否是回文串
	{
		if (str.size() <= 1)
			return 1;
		int left = 0;
		int right = str.size() - 1;
		while (left<right)
		{
			if (str[left++] != str[right--])
				return 0;
		}
		return 1;
	}
	string longestPalindromeDP(string s) //用动态规划的方法
	{
		vector<vector<bool>> dp(s.size(), vector<bool>(s.size(), 0));//前闭后闭，标记字串是否是回文
		if (s.size() == 1)
			return s;
		for (int i = 0; i<s.size(); i++)
			dp[i][i] = 1;  //每个一个长度的字符串肯定是回文字符串
		for (int i = 0; i <= s.size() - 2; i++)
		{
			dp[i][i + 1] = isbackStr(s.substr(i, 2)); //设置长度为2的字串的备忘录
													  //需要注意的是substr不是类似于stl里边的前闭后开的，其参数含义为索引位置和长度！！！！！
													  // cout<<s.substr(i,2)<<" "<<dp[i][i+1]<<endl;
		}

		for (int length = 3; length <= s.size(); length++)
		{
			for (int i = 0; i <= s.size() - length; i++)
			{
				// if (isbackStr(s.substr(i,i+length))) //如果这么搞的话就成了暴力枚举
				// dp[i][i+1] = 1; 
				dp[i][i + length - 1] = (s[i] == s[i + length - 1]) && (dp[i + 1][i + length - 1 - 1]); //很重要的递推式
																										//关键是要想到这个递推式
			}
		}
		for (int i = 0; ; i++)
		{
			for (int row = 0, col = s.size() - 1 - i; row <= i&&col <= s.size() - 1; row++, col++)
			{
				if (dp[row][col] == 1)
				{
					return s.substr(row, col - row + 1);
				}
			}
		}
	}

	string CenterSpan(const string & s, int leftindex, int rightindex) //前闭后闭
																	   //两种扩散的方法，一种是以间隙为中心，一种是以数字为中心
	{

		if (s.size() <= 1)
			return s;

		if (leftindex == rightindex)
		{
			int j;
			if (leftindex == 0)
				return s.substr(0, 1);
			else if (leftindex == s.size() - 1)
				return s.substr(s.size() - 1, 1);
			for (j = 1; (leftindex + j) != s.size() && (leftindex - j) != -1; j++)
			{
				if (s[leftindex + j] != s[leftindex - j])
				{
					j--; //试探性的探出去，如果被打脸了就返回来
					break;
				}
			}
			if (!((leftindex + j) != s.size() && (leftindex - j) != -1))
				j--;
			return s.substr(leftindex - j, 2 * j + 1);
		}
		else if (leftindex<rightindex)
		{
			if (s[leftindex] != s[rightindex])
				return string("");
			if (leftindex == 0 || rightindex == s.size() - 1) //当处于边界时，不扩展
				return s.substr(leftindex, rightindex - leftindex + 1);

			int j;
			for (j = 1; (rightindex + j) != s.size() && (leftindex - j) != -1; j++)
			{
				if (s[rightindex + j] != s[leftindex - j])
				{
					j--;
					break;
				}
			}
			if (!((rightindex + j) != s.size() && (leftindex - j) != -1))
				j--;
			return s.substr(leftindex - j, 2 * j + rightindex - leftindex + 1);
		}
		else
			return "";

	}
	string longestPalindromeMidSpread(string s) //用中心扩散的方法，也是我一开始5分钟内想到的方法
												//但是由于处理边界时不好处理，就没有继续写，转而去写动态规划了
	{

		vector<string> vecHitstr(s.size(), " ");  //恰好是给定数位置的拓展
		vector<string> vecMidstr(s.size() - 1, " "); //间隙扩展

		for (int i = 0; i<s.size(); i++)
			vecHitstr[i] = CenterSpan(s, i, i);
		for (int i = 0; i<s.size() - 1; i++)
			vecMidstr[i] = CenterSpan(s, i, i + 1);

		int Biggest = 0;
		string BigStr = "";
		for (int i = 0; i<vecHitstr.size(); i++)
			if (vecHitstr[i].size()>Biggest)
			{
				Biggest = vecHitstr[i].size();
				BigStr = vecHitstr[i];
			}
		for (int i = 0; i<vecMidstr.size(); i++)
			if (vecMidstr[i].size()>Biggest)
			{
				Biggest = vecMidstr[i].size();
				BigStr = vecMidstr[i];
			}
		return BigStr;
	}
	string longestPalindrome(string s) {
		// return longestPalindromeDP(s); //876ms 29.3MB 20.93% 52.14%
		return longestPalindromeMidSpread(s); //40ms 29.8MB 75.56% 47.71%
	}

	void test()
	{
		longestPalindrome(string("cbbd"));
	}
};


/*
剑指 Offer 14- II. 剪绳子 II
给你一根长度为 n 的绳子，请把绳子剪成整数长度的 m 段（m、n都是整数，n>1并且m>1），
每段绳子的长度记为 k[0],k[1]...k[m - 1] 。请问 k[0]*k[1]*...*k[m - 1] 可能的最大乘积是多少？
例如，当绳子的长度是8时，我们把它剪成长度分别为2、3、3的三段，此时得到的最大乘积是18。

答案需要取模 1e9+7（1000000007），如计算初始结果为：1000000008，请返回 1。
*/

class Solution14_II {
public:

	/*
	int cuttingRope(int n) {
	//如果任旧用剪绳子I中的方法计算，则在中间的计算过程中就会越界 所以在数值有限的情况下不能用这种方法
	n=120;
	vector<long> Tn(n + 1, 0);
	if (n == 0)
	return 0;
	else if (n == 1)
	{
	Tn[1] = 1;
	return 1;
	}
	Tn[1] = 1;

	for (long In = 2; In <= n; In++) //时间复杂度是N^2 空间复杂度是N 有巧妙的方法能降到N  但是估计面试是想不到的
	{
	long maxthis = 0;
	for (long i = 1; i <= In - 1; i++)
	{
	long big = max(max(Tn[i] * (In - i), i*(In - i)), Tn[i] * Tn[In - i]);//注意这个判断容易丢
	//在这里容易出现越界
	//动态规划的核心
	if (big>maxthis)
	{
	maxthis = big;
	}
	}
	Tn[In] = maxthis;
	}
	return Tn[n]%1000000007;
	}
	*/

	long bigmodc(long x, long a, long c) //大数的求余
	{
		//x^a % c = ((x^(a-1)%c)*(x%c))%c
		long xmodc = x%c;
		long result = 1;
		for (int i = 1; i <= a; i++)
		{
			result = ((result%c)*xmodc) % c;
		}
		return result;
	}
	int cuttingRope(int n) //0ms 5.8MB 100% 69.42%
	{
		/*
		先验知识：将绳子尽量等分时得到的乘积最大 再经过推导绳子等分成每段长度为3时长度最长
		对任意长度的绳子，对3取模会余0 1 2
		余0时直接计算就行
		余1时拆分一个3再加上1为2+2
		余2时不拆分，直接乘2即可
		这其实是另一种形式的动态规划。每次的最优值由前一次的最优值递推得到
		递推是常数时间
		(x*y)%c = ((x%c)*(y%c))%c 根据这个式子可以求得大数的模
		*/
		if (n == 0)
			return 0;
		else if (n == 1 || n == 2)
			return 1;
		else if (n == 3)
			return 2;
		int a = n / 3;
		int mod = n % 3;

		long modnum = 1000000007;
		if (mod == 0)
		{
			return bigmodc(3, a, modnum);
		}
		else if (mod == 1)
		{
			//(3^a-1 * 4)%modnum
			return (bigmodc(3, a - 1, modnum) * 4) % modnum;
		}
		else if (mod == 2)
		{
			//(3^a * 2)%modnum
			return (bigmodc(3, a, modnum) * 2) % modnum;
		}
		return -1;
	}
};






/*
剑指 Offer 14- I. 剪绳子
给你一根长度为 n 的绳子，请把绳子剪成整数长度的 m 段（m、n都是整数，n>1并且m>1），
每段绳子的长度记为 k[0],k[1]...k[m-1] 。请问 k[0]*k[1]*...*k[m-1] 可能的最大乘积是多少？
例如，当绳子的长度是8时，我们把它剪成长度分别为2、3、3的三段，此时得到的最大乘积是18。
*/
class SolutionOffer14_I {
public:
	int cuttingRope(int n) {
		vector<int> Tn(n + 1, 0);
		if (n == 0)
			return 0;
		else if (n == 1)
		{
			Tn[1] = 1;
			return 1;
		}
		Tn[1] = 1;

		for (int In = 2; In <= n; In++) //时间复杂度是N^2 空间复杂度是N 有巧妙的方法能降到N  但是估计面试是想不到的
		{
			int maxthis = 0;
			for (int i = 1; i <= In - 1; i++)
			{
				int big = max(max(Tn[i] * (In - i), i*(In - i)), Tn[i] * Tn[In - i]);//注意这个判断容易丢
				//动态规划的核心
				if (big>maxthis)
				{
					maxthis = big;
				}
			}
			Tn[In] = maxthis;
		}
		return Tn[n];
	}
};


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