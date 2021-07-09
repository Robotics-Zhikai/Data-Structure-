#pragma once
#include "main.h"

/*
494. 目标和
给定一个非负整数数组，a1, a2, ..., an, 和一个目标数，S。现在你有两个符号 + 和 -。
对于数组中的任意一个整数，你都可以从 + 或 -中选择一个符号添加在前面。

返回可以使最终数组和为目标数 S 的所有添加符号的方法数。

https://leetcode-cn.com/problems/target-sum/solution/494-mu-biao-he-01bei-bao-xiang-jie-by-ca-1kt5/
*/
class Solution494 {
public:
	int findTargetSumWaysDP1(vector<int>& nums, int S)
	{
		const int n = nums.size();
		int sum = accumulate(nums.begin(), nums.end(), 0);

		if (S>sum) //全部加起来还比S小 那么就不能表示
			return 0; //这个容易丢！！！！！！

		//int dp[n][2 * sum + 1]; //dp[i][j]表示[0,i]的数等于j-sum有多少种符号选取方法
		//memset(dp, 0, sizeof(dp)); //后闭 ！！！！！！！！！！！
		//可能是vs版本低的原因，在vs2015中不能动态分配数组，只能是在编译期就知道数组大小才可以

		vector<vector<int>> dp(n, vector<int>(2 * sum + 1, 0));

		if (nums[0] == 0) //这里容易出错！！！！！！ 必须正确考虑初始条件
			dp[0][0 + sum] = 2;
		else
		{
			dp[0][-nums[0] + sum] = 1;
			dp[0][nums[0] + sum] = 1;
		}

		for (int i = 1; i<n; i++)
		{
			for (int j = 0; j<2 * sum + 1; j++)
			{
				int first = 0;
				int second = 0;
				if (j - nums[i] >= 0)
				{
					first = dp[i - 1][j - nums[i]]; //当前数值符号记为+有这么多种方法
				}
				if (j + nums[i]<2 * sum + 1)
				{
					second = dp[i - 1][j + nums[i]]; //当前数值符号记为-有这么多种方法
				}
				dp[i][j] = first + second; //这是核心的递推方程 
				//考虑边界情况时不要想得太复杂，如果太复杂大概率有更简单更普遍能代表所有情况的代码！！！！！！！！
				//就比如下边注释掉的这段代码，考虑很多情况，涵盖还不完全，实际上很简单的上边这段就可以解决
				// if (dp[i-1][j]!=0 && nums[i]!=0)
				// {
				//     dp[i][j] = 0;//说明前边的就能满足 没必要加上或减去现在这个大于0的数字
				// }
				// else
				// {

				// }
			}
		}
		return S + sum<2 * sum + 1 ? dp[n - 1][S + sum] : 0;
		//一定要注意！！！不应该是找最大值，而应该是找最后一个值 因为所有的数字都需要加符号，不存在某个数字不用的情况
		// int result = 0;
		// for(int i = 0;i<n;i++)
		// {
		//     if (S+sum<2*sum+1&&dp[i][S+sum]>result)
		//         result = dp[i][S+sum];
		// }
		// return result;
	}
	int findTargetSumWaysDP2(vector<int>& nums, int S)  //经过空间优化的版本
	{
		const int n = nums.size();
		int sum = accumulate(nums.begin(), nums.end(), 0);

		if (S>sum) //全部加起来还比S小 那么就不能表示
			return 0; //这个容易丢！！！！！！

		// int dp[n][2*sum+1]; //dp[i][j]表示[0,i]的数等于j-sum有多少种符号选取方法
		// memset(dp,0,sizeof(dp)); //后闭 ！！！！！！！！！！！

		//int dp_cur[2 * sum + 1]; //从下边代码可以看到dpi只与dpi-1有关
		//int dp_last[2 * sum + 1];
		//memset(dp_cur, 0, sizeof(dp_cur));
		//memset(dp_last, 0, sizeof(dp_last));
		vector<int> dp_cur(2 * sum + 1, 0);
		vector<int> dp_last(2 * sum + 1, 0);

		auto curdp = dp_cur.begin(); //必须有这个，否则代表数组首地址的dp_cur dp_last是无法交换的
		auto lastdp = dp_last.begin();

		if (nums[0] == 0) //这里容易出错！！！！！！ 必须正确考虑初始条件
						  //dp[0][0+sum] = 2;
			lastdp[0 + sum] = 2;
		else
		{
			// dp[0][-nums[0]+sum] = 1;
			// dp[0][nums[0]+sum] = 1;
			lastdp[-nums[0] + sum] = 1;
			lastdp[nums[0] + sum] = 1;
		}

		int * mid = 0;
		for (int i = 1; i<n; i++)
		{
			for (int j = 0; j<2 * sum + 1; j++)
			{
				int first = 0;
				int second = 0;
				if (j - nums[i] >= 0)
				{
					//first = dp[i-1][j-nums[i]];
					first = lastdp[j - nums[i]];
				}
				if (j + nums[i]<2 * sum + 1)
				{
					//second = dp[i-1][j+nums[i]];
					second = lastdp[j + nums[i]];
				}
				//dp[i][j] = first+second; //这是核心的递推方程 
				curdp[j] = first + second;
			}
			swap(lastdp, curdp); //交换指针而不是数据，可以提高速度 
								 //经过交换后当前的dp就换到了last
		}
		return S + sum<2 * sum + 1 ? lastdp[S + sum] : 0;
	}
	int findTargetSumWaysDP3(vector<int>& nums, int S)
	{
		//这道题能转换到标准的01背包问题
		//Sum为所有数之和 A为符号为+的数的和 B为符号为-的数的和 A+B=Sum A-B=S 
		//联立得到2A=S+Sum A=(S+Sum)/2 而S、Sum 都是已知的，因此A是一个固定的数
		//也就是说符号为+的数的和应该等于A时就找到了一种解
		//又因为所有的输入数的序列为整数，所以符号位+的数的和不应该有小数，因此当(S+Sum)/2是小数时也不能找到解
		const int n = nums.size();
		int sum = accumulate(nums.begin(), nums.end(), 0);
		if (sum<S || (S + sum) % 2 != 0)
			return 0;

		int A = (S + sum) / 2; //DP3时间少的主要原因是一开始就把问题规模降下来了

		//int dp[n][A + 1]; //dp[i][j]表示[0,i]的数中选中的数的和等于j的有多少种方法
		//memset(dp, 0, sizeof(dp));
		vector<vector<int>> dp(n, vector<int>(A + 1, 0));

		if (nums[0]<A + 1)
			dp[0][nums[0]] = 1;
		dp[0][0] += 1;
		//只考虑第一个数，当首项非零时，和为0的方法就是不选，有1个方法
		//只考虑第一个数，当首项为0时，和为0的方法有两个，选和不选 
		for (int i = 1; i<n; i++)
		{
			for (int j = 0; j <= A; j++)
			{
				dp[i][j] = j - nums[i] >= 0 ? dp[i - 1][j - nums[i]] : 0; //选当前值时有这么多方法
				dp[i][j] += dp[i - 1][j]; //不选当前值时有这么多方法 二者加起来就是总的方法数量
				//这个可以调整成1维逆序 比较好调，就不调了
			}
		}
		return dp[n - 1][A]; //由于原问题已经转化了，所以与S无关了！！！！！！
	}
	//也是一个01背包问题，按照01背包问题的思路去想，但是不同的是这个相当于所有的物品都得装，
	//因此不能把dp[][]看做是不等式，只能看做等式
	//除了用动态规划，还可以用其他方法
	int findTargetSumWays(vector<int>& nums, int S) {
		//return findTargetSumWaysDP1(nums,S); //48ms 8.9MB 55.05% 77.19%
		//return findTargetSumWaysDP2(nums,S); //48ms 8.7MB 55.05 88.84
		return findTargetSumWaysDP3(nums, S); //8ms 8.6MB 92.48% 98.29%
	}

	void test()
	{
		findTargetSumWays(vector<int>{2, 107, 109, 113, 127, 131, 137, 3, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 47, 53}, 2147483647);
	}
};


/*
474. 一和零
给你一个二进制字符串数组 strs 和两个整数 m 和 n 。

请你找出并返回 strs 的最大子集的大小，该子集中 最多 有 m 个 0 和 n 个 1 。

如果 x 的所有元素也是 y 的元素，集合 x 是集合 y 的 子集 。

https://leetcode-cn.com/problems/ones-and-zeroes/solution/dong-tai-gui-hua-zhuan-huan-wei-0-1-bei-bao-wen-ti/
*/
class Solution474 {
public:

	int findMaxFormDP1(vector<string>& strs, int m, int n)
	{
		vector<vector<int>> dp2DLast(m + 1, vector<int>(n + 1, 0));
		vector<vector<int>> dp2D(m + 1, vector<int>(n + 1, 0)); //[0,m] [0,n]
		// vector<vector<vector<int>>> dp(strs.size()+1,dp2D); //后开

		//弄成三维数组更好理解些 dp[i][j][k] 第一维是物品的选取范围是[0,i)，第二维是最多有j个0，第三维是最多有k个1
		//然后经过分析，发现i+1的dp仅和i的dp有关，这样的话就可以用两个二维矩阵Last和Current来代替
		//这样直接就把内存消耗由100MB降到了10MB 运行时间由480ms降到了272ms

		for (int i = 1; i <= strs.size(); i++)
		{
			int count0 = count(strs[i - 1].begin(), strs[i - 1].end(), '0');
			int count1 = count(strs[i - 1].begin(), strs[i - 1].end(), '1');
			for (int j = 0; j <= m; j++)
			{
				for (int k = 0; k <= n; k++)
				{
					int j_count0 = j - count0;
					int k_count1 = k - count1;
					if (j_count0<0 || k_count1<0) //此时肯定装不进新的字符串
					//dp[i][j][k] = dp[i-1][j][k];  
					//为了更好的对比 把没有经过滚动数组降维的保留下来 下边一行和本行其实是等价的
						dp2D[j][k] = dp2DLast[j][k];
					else
						//dp[i][j][k] = max(dp[i-1][j][k],dp[i-1][j_count0][k_count1]+1);//01背包问题的核心
						dp2D[j][k] = max(dp2DLast[j][k], dp2DLast[j_count0][k_count1] + 1);
				}
			}
			dp2DLast = dp2D; //有一个滚动的过程
		}
		return dp2D[m][n];
	}

	int findMaxFormDP2(vector<string>& strs, int m, int n)//更深层次的根据递推式的优化
	{
		//虽然在findMaxFormDP1中有相应的压缩，但是任旧有两个vector<vector<int>>储存前一个和后一个值
		//实际上可以只用一个vector<vector<int>>，从后往前更新 
		//用一个vector<vector<int>>对速度没有本质提升，只是让占有空间更小了
		vector<vector<int>> dp2D(m+1,vector<int>(n+1,0)); //[0,m] [0,n]

	//	int dp2D[m + 1][n + 1]; //动态创建一个二维数组
	//	memset(dp2D, 0, sizeof(dp2D)); //将以dp2D指针开始的(m+1)*(n+1)字节内存的数据赋值为0
	//当用这个替代vector<vector<int>> 时直接由268ms 9.5MB 降到了60ms 8.5MB 速度有了本质提升

		for (int i = 1; i <= strs.size(); i++)
		{
			int count0 = count(strs[i - 1].begin(), strs[i - 1].end(), '0');
			int count1 = count(strs[i - 1].begin(), strs[i - 1].end(), '1');
			//for(int j = 0;j<=m;j++)
			for (int j = m; j >= 0; j--)
			{
				//for(int k=0;k<=n;k++)
				for (int k = n; k >= 0; k--)
				{
					int j_count0 = j - count0;
					int k_count1 = k - count1;
					if (j_count0<0 || k_count1<0) //此时肯定装不进新的字符串
												  //dp2D[j][k] = dp2DLast[j][k]; 
						dp2D[j][k] = dp2D[j][k];
					else
						//dp2D[j][k] = max(dp2DLast[j][k],dp2DLast[j_count0][k_count1]+1);
						dp2D[j][k] = max(dp2D[j][k], dp2D[j_count0][k_count1] + 1);
					//由于是从后往前，所以所有小于jk的dp2D都没有更新
				}
			}
			//dp2DLast = dp2D; //有一个滚动的过程
		}
		return dp2D[m][n];
	}

	//这是一个01背包问题 字符串集合中的每一个字符串是否放入
	//和基本的01背包问题的区别是本题有两个约束条件，因此初始情况下有三维
	//可以用暴力求解，枚举所有可能性，复杂度是c*2^n，n=strs.size() 
	int findMaxForm(vector<string>& strs, int m, int n) {
		//return findMaxFormDP1(strs,m,n);
		return findMaxFormDP2(strs, m, n); //本质上这两个函数基于的方法是一样的，但是实现方式有区别 DP2更高效
	}
};


/*
64. 最小路径和
给定一个包含非负整数的 m x n 网格 grid ，请找出一条从左上角到右下角的路径，使得路径上的数字总和为最小。

说明：每次只能向下或者向右移动一步。
*/
//这道题只能向下或者向右移动一步 是一个比较明显的动态规划 但是当上下左右都能移动时，就不好看成动态规划了 可能是贪心
class Solution64 {
public:
	int inf = 99999;
	int minPathSum(vector<vector<int>>& grid) {
		if (grid.empty())
			return 0;
		if (grid.size() == 1)
			return accumulate(grid[0].begin(), grid[0].end(), 0);
		int m = grid.size();
		int n = grid[0].size();
		vector<vector<int>> dp(m, vector<int>(n, inf));
		//实际上可以不要这个dp，直接在grid上修改值 因为按照顺序的话原矩阵的值只需要用一次
		//这样就可以把空间复杂度降到1
		dp[0][0] = grid[0][0];
		for (int j = 1; j<n; j++)
		{
			int col = j;
			int row = 0;
			while (col != -1 && row != m) //这两个while循环是重复的内容，可以封装到一个函数中
			{
				if (row == 0)
					dp[row][col] = dp[row][col - 1] + grid[row][col];
				else if (col == 0)
					dp[row][col] = dp[row - 1][col] + grid[row][col];
				else
				{
					int uptodown = dp[row - 1][col] + grid[row][col];
					int lefttoright = dp[row][col - 1] + grid[row][col];
					if (uptodown<lefttoright)
						dp[row][col] = uptodown;
					else
						dp[row][col] = lefttoright;
				}
				row++;
				col--;
			}
		}
		for (int i = 1; i<m; i++)
		{
			int col = n - 1;
			int row = i;
			while (col != -1 && row != m)
			{
				if (row == 0)
					dp[row][col] = dp[row][col - 1] + grid[row][col];
				else if (col == 0)
					dp[row][col] = dp[row - 1][col] + grid[row][col];
				else
				{
					int uptodown = dp[row - 1][col] + grid[row][col];
					int lefttoright = dp[row][col - 1] + grid[row][col];
					if (uptodown<lefttoright)
						dp[row][col] = uptodown;
					else
						dp[row][col] = lefttoright;
				}
				row++;
				col--;
			}
		}
		return dp[m - 1][n - 1];
	}
};

/*
96. 不同的二叉搜索树
给定一个整数 n，求以 1 ... n 为节点组成的二叉搜索树有多少种？
难度中等
*/
class Solution96 {
public:
	//用DP的方法一次通过 0ms 6MB 100% 63.4%
	int numTrees(int n) {
		vector<int> vecnum(n + 1, 0);
		if (n == 0)
			return 1;
		else if (n == 1)
			return 1;
		else if (n == 2)
			return 2;
		vecnum[0] = 1;
		vecnum[1] = 1;
		vecnum[2] = 2;
		for (int i = 3; i <= n; i++)
		{
			int currentnum = 0;
			for (int index = 0; index<i; index++)
			{
				currentnum += vecnum[index] * vecnum[i - index - 1];
			}
			vecnum[i] = currentnum;
		}
		return vecnum[n];
	}
};


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
		//比较难写的是这个函数！！！！！！ 需要能够想到以间隙为中心扩展和以数字为中心扩展
		//体现了适当的增加中间值可以减少初始化的步骤 这个问题增加了间隔
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
			if (!((leftindex + j) != s.size() && (leftindex - j) != -1)) //这里也是不太容易注意到的点
				j--;
			return s.substr(leftindex - j, 2 * j + 1);
		}
		else if (leftindex<rightindex)
		{
			if (s[leftindex] != s[rightindex]) //这里也是易错点
				return string("");  //当用间隙时，如果间隙两端的数字不相等，理所当然的就不是回文串
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
												//当把间隙也考虑进来进行拓展时就好处理了
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

	//动态规划法要枚举所有边界，是N^2的
	//中心扩散法不需要枚举N^2的边界，是2N的
	//虽然二者都是N^2的复杂度，但是显然后者更实惠些
	//动态规划法多算了不是回文串的部分，而中心扩散法一个不是回文串的也没有算 理所当然的后者时间更短
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

/*
42. 接雨水
给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。

*/
//这道题用动态规划比较好想，面试时候也容易想到 也好写

class Solution42 {
public:
    int DP(vector<int>& height) //这个比较好理解也好写
    {
        if(height.empty())
            return 0;
        vector<int> LeftMax(height.size(),0); //leftmax[i]表示i及i左边的柱子的最高值
        vector<int> RightMax(height.size(),0); //rightmax[i]表示i及i右边的柱子的最高值
        LeftMax[0] = height[0];
        RightMax[height.size()-1] = height[height.size()-1];
        for(int i = 1;i<height.size();i++){
            LeftMax[i] = max(height[i],LeftMax[i-1]);
        }
        for(int i = height.size()-2;i>=0;i--){
            RightMax[i] = max(height[i],RightMax[i+1]);
        }
        int sum = 0;
        for(int i = 0;i<height.size();i++){
            sum += min(LeftMax[i],RightMax[i])-height[i]; 
        }
        return sum;
    }
    int Myself(vector<int>& height) //这个虽然是自己写的，但是容易出错，且从左往右扫会造成资源浪费
    {
        if (height.empty())
            return 0;
        int Left = numeric_limits<int>::min();
        int Leftindex = -1;
        int sum = 0;
        int oldsum = 0;
        for(int i = 0;i<height.size();i++){ //先从左往右扫,是一种贪心思想，遇到更高的挡板时与之前的无关
            if (height[i]<Left)
                sum+=Left-height[i];
            else{
                oldsum = sum;
                Left = height[i];
                Leftindex = i;
            }
        }
        int leftstroe = Leftindex; ///如果leftindex不是最后一个，说明以Left为高度的left并不能装下合适的水，就回退到oldsum
        if (Leftindex!=height.size()-1){ //再从右往左扫
            sum = oldsum;
            Left = numeric_limits<int>::min();
            for(int i = height.size()-1;i>=leftstroe;i--){
                if(height[i]<Left)
                    sum+=Left-height[i];
                else{
                    Left = height[i];
                }
            }
        }
        return sum;
    }
    int Twoptr(vector<int>& height) //双指针的方法
    {
        int ans = 0;
        int left = 0, right = height.size() - 1;
        int leftMax = 0, rightMax = 0;
        while (left < right) {
            leftMax = max(leftMax, height[left]); //存储left及left左边的最大值
            rightMax = max(rightMax, height[right]); //存储right及right右边的最大值
            if (height[left] < height[right]) { //left右边的实际最大height值只能比height[right]（当前rightmax）更大或相等 这其实和动态规划的最后一步是一样的
                ans += leftMax - height[left]; //每次确定最肯定的接雨水容量 每个i只能接min(leftmax,rightmax)-height[i]
                ++left;
            } else { //同样的，right左边的实际最大值只能比height[left]（当前leftmax）更大或相等
                ans += rightMax - height[right];  //每次确定最肯定的接雨水容量
                --right;
            }
        }
        return ans;
        // 作者：LeetCode-Solution
        // 链接：https://leetcode-cn.com/problems/trapping-rain-water/solution/jie-yu-shui-by-leetcode-solution-tuvc/
        // 来源：力扣（LeetCode）
        // 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
    }

    int trap(vector<int>& height) {
        // return DP(height); //这是O(n)时间复杂度，O(n)空间复杂度
        // return Myself(height); //这是O(n)时间复杂度，O（1）空间复杂度
        return Twoptr(height); //这是O(n)时间复杂度，O（1）空间复杂度
    }
};



/*
剑指 Offer 46. 把数字翻译成字符串
给定一个数字，我们按照如下规则把它翻译为字符串：0 翻译成 “a” ，1 翻译成 “b”，……，11 翻译成 “l”，……，25 翻译成 “z”。
一个数字可能有多个翻译。请编程实现一个函数，用来计算一个数字有多少种不同的翻译方法。
*/

class SolutionOffer46 {
public:
    int translateNum(int num) {
        string numstr = to_string(num);
        vector<vector<int>> dp(numstr.size(),vector<int>(numstr.size(),1));
        //dp[i][j]表示在区间[i,j]内的string有多少种不同的翻译方法
        for (int i = 0;i<numstr.size()-1;i++){
            if (stoi(string(numstr.begin()+i,numstr.begin()+i+2))<=25)
                dp[i][i+1] = 2;
            else
                dp[i][i+1] = 1;
        }
        
        for(int len = 3;len<=numstr.size();len++){
            for(int i = 0;i<numstr.size()-len+1;i++){
                int self = numstr[i+len-1]-'0';
                int merge = stoi(string(numstr.begin()+i+len-2,numstr.begin()+i+len));
                dp[i][i+len-1] = dp[i][i+len-2]+((merge<=25&&merge!=self)?dp[i][i+len-3]:0); //merge!=self把06 6的情况去掉
                //新加入的字符与前一个连起来翻译再加上新加入的字符不与前一个连起来翻译，总的数量的就是新的dp
            }
        }
        //上边这两个for完全可以合并，然后用滚动数组把空间复杂度降到O(1)
        return dp[0][numstr.size()-1];

    }
};

/*
300. 最长递增子序列
给你一个整数数组 nums ，找到其中最长严格递增子序列的长度。

子序列是由数组派生而来的序列，删除（或不删除）数组中的元素而不改变其余元素的顺序。
例如，[3,6,2,7] 是数组 [0,3,1,6,2,2,7] 的子序列。


*/
//有nlogn的解法，时间有限暂时先不看

class Solution300 {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> dp(nums.size(),0); //储存包含i位置元素的i位置及之前元素的最长严格递增子序列长度 
        dp[0] = 1;
        for(int i = 1;i<nums.size();i++){
            int MAX = INT_MIN;
            for (int j = 0;j<i;j++){
                if (nums[i]>nums[j]){
                    if (dp[j]>MAX){
                        MAX = dp[j];
                    }
                }
            }
            if (MAX==INT_MIN){
                dp[i] = 1;
            }
            else
                dp[i] = MAX+1;
        }
        return *max_element(dp.begin(),dp.end());
    }
};


/*
198. 打家劫舍
你是一个专业的小偷，计划偷窃沿街的房屋。每间房内都藏有一定的现金，
影响你偷窃的唯一制约因素就是相邻的房屋装有相互连通的防盗系统，如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警。

给定一个代表每个房屋存放金额的非负整数数组，计算你 不触动警报装置的情况下 ，一夜之内能够偷窃到的最高金额。

*/

class Solution198 {
public:
    int rob(vector<int>& nums) {
        vector<int> dp(nums.size(),0); //标号为i及i之前的最高金额
        if (nums.size()==1)
            return nums[0];
        dp[0] = nums[0];
        dp[1] = max(nums[0],nums[1]);
        for(int i = 2;i<nums.size();i++){
            dp[i] = max(dp[i-2]+nums[i],dp[i-1]);
            //要不偷第i家，结果是dp[i-2]+nums[i]；要不不偷第i家，结果是dp[i-1]
            //考虑上边的递归式，可以把空间复杂度优化到O(1).具体的实现方法就是设置两个index，每轮循环(index++)%3
        }
        return dp[nums.size()-1];
    }
};


/*
62. 不同路径
一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为 “Start” ）。

机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为 “Finish” ）。

问总共有多少条不同的路径？

*/
class Solution62 {
public:
	int count = 0;
    
    void DFS(vector<vector<int>>& isvist,int i,int j){
		if (i==isvist.size()-1 && !isvist.empty() && j==isvist[0].size()-1){
			count++;
		}
		isvist[i][j] = 1;
		if (i<isvist.size()-1){
            if (isvist[i+1][j]==0)
			    DFS(isvist,i+1,j);
		}
		if (!isvist.empty() && j<isvist[0].size()-1){
			if (isvist[i][j+1]==0)
                DFS(isvist,i,j+1);
		}
		isvist[i][j] = 0;
	}
    int solveMethod1(int m, int n){ //用DFS的方法，需要计算重复的，很低效，对大规模的直接超时
        vector<vector<int>> isvist(m,vector<int>(n,0));
		count = 0;
		DFS(isvist,0,0);
		return count;
    }

    int solveMethod2(int m,int n){
        //用动态规划的方法做就不超时了
        vector<vector<int>> dp(m,vector<int>(n,0));
        dp[m-1][n-1] = 1;
        for (int j = n-2;j>=0;j--){
            dp[m-1][j] = dp[m-1][j+1]; 
        }
        for (int i = m-2;i>=0;i--){
            dp[i][n-1] = 1;
        }
        for (int i = m-2;i>=0;i--){
            for (int j = n-2;j>=0;j--){
                dp[i][j] = dp[i+1][j]+dp[i][j+1];
            }
        }
        return dp[0][0];
    }
    //还可以用组合数学的方式，就是高中数学

    int uniquePaths(int m, int n) {
        return solveMethod2(m,n);
    }
};