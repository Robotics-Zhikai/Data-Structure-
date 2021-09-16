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


	int review(vector<int>& nums,int S){
        //注意要把这个问题转化成一个01背包问题
        int sum = 0;
        for(int e:nums){
            sum+=e;
        }
        vector<vector<int>> dp(nums.size(),vector<int>(sum+1,0));
        if (nums[0]!=0){
            dp[0][nums[0]] = 1; 
            dp[0][0] = 1;
        }
        else{
            dp[0][0] = 2; //要注意这个初始化时候的特殊情况！！！！
        }
        
		//下边这个完全可以去掉，不需要按照这种形式去初始化
        // for(int i = 0;i<nums.size();i++){
        //     if (nums[i]!=0){
        //         dp[i][nums[i]] = 1;
        //         dp[i][0] = 1;
        //     }
        //     else{
        //         dp[i][0] = 2; //要注意这个初始化时候的特殊情况！！！！
        //     }
        // }
        for(int i = 1;i<nums.size();i++){
            for(int j = 0;j<=sum;j++){ //j要从0开始
                if (j<nums[i]){
                    dp[i][j] = dp[i-1][j];
                }
                else{
                    dp[i][j] = dp[i-1][j]+dp[i-1][j-nums[i]];
                }
               // cout<<dp[i][j]<<" ";
            }
            //cout<<endl;
        }
        //a+b = sum
        //a-b = target
        //2a=sum+target
        //a = (sum+target)/2;
        if ((sum+S)%2==1){
            return 0;
        }
        int target = (sum+S)/2;
        if (target>sum || target<0){
            return 0;
        }
        return dp[dp.size()-1][target];
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
    int review(vector<string>& strs,int m,int n){
        vector<vector<vector<int>>> dp(strs.size(),vector<vector<int>>(m+1,vector<int>(n+1,0)));
        int zeroNum = 0;
        int oneNum = 0;
        for(char c:strs[0]){
            if (c=='0'){
                zeroNum++;
            }
            else if (c=='1'){
                oneNum++;
            }
        }
        for(int i = zeroNum;i<=m;i++){
            for (int j = oneNum;j<=n;j++){
                dp[0][i][j] = 1; //一定要注意这个初始化！！！！！！！！！！！！！！！！！
            }
        }
        for(int i = 1;i<strs.size();i++){
            int zeroNum = 0;
            int oneNum = 0;
            for(char c:strs[i]){
                if (c=='0'){
                    zeroNum++;
                }
                else if (c=='1'){
                    oneNum++;
                }
            }

            for(int j = 0;j<=m;j++){
                for(int k = 0;k<=n;k++){
                    if (j>=zeroNum && k>=oneNum) 
                        dp[i][j][k] = max(dp[i-1][j][k],dp[i-1][j-zeroNum][k-oneNum]+1);
                    else
                        dp[i][j][k] = dp[i-1][j][k];
                }
            }
           
        }
        return dp[dp.size()-1][m][n];
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
    int review(vector<vector<int>>& grid){
        vector<vector<int>> dp(grid.size(),vector<int>(grid[0].size(),0));
        dp[0][0] = grid[0][0];
        for(int i = 1;i<grid.size();i++){
            dp[i][0] = dp[i-1][0]+grid[i][0];
        }
        for(int j = 1;j<grid[0].size();j++){
            dp[0][j] = dp[0][j-1]+grid[0][j];
        }
        for(int i = 1;i<grid.size();i++){
            for(int j = 1;j<grid[i].size();j++){
                dp[i][j] = min(dp[i-1][j],dp[i][j-1])+grid[i][j];
            }
        }
        return dp[grid.size()-1][grid[0].size()-1];
    }

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
    int MyselfReview(vector<int>& height){
        int curLeft = 0;
        int splitWater = 0;
        int res = 0;
        for(int i = 1;i<height.size();i++){
            if (height[i]>=height[curLeft]){
                curLeft = i;
                res+=splitWater;
                splitWater = 0;
            }
            else{
                splitWater+=height[curLeft]-height[i];
            }
        }
        if(curLeft!=height.size()-1){
            int storage = curLeft;
            curLeft = height.size()-1;
            splitWater = 0;
            for(int i = curLeft-1;i>=storage;i--){
                if (height[i]>=height[curLeft]){
                    curLeft = i;
                    res+=splitWater;
                    splitWater = 0;
                }
                else{
                    splitWater+=height[curLeft]-height[i];
                }
            }
        }
        return res;
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
    int review(vector<int>& nums){
        vector<int> dp(nums.size(),1);
        dp[0] = 1;
        for(int i = 1;i<nums.size();i++){
            int MAX = INT_MIN;
            for(int j = 0;j<i;j++){
                if (nums[i]>nums[j]){
                    if (dp[j]+1>MAX){
                        MAX = dp[j]+1;
                    }
                }
            }
            if (MAX!=INT_MIN){
                dp[i] = MAX;
            }
        }
        int res = INT_MIN;
        for(int e:dp){
            if (e>res){
                res = e;
            }
        }
        return res;
    }
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
	int rob210712(vector<int>& nums){
		vector<int> dp(nums.size(),0); //[0,i]个房间范围内偷的最大数目
		dp[0] = nums[0];
		for (int i = 1;i<nums.size();i++){
			if (i==1){
				dp[i] = max(nums[0],nums[1]);
			}
			else{
				dp[i] = max(dp[i-2]+nums[i],dp[i-1]);
			}
		}
		return dp[nums.size()-1];
	}
};

/*
213. 打家劫舍 II
你是一个专业的小偷，计划偷窃沿街的房屋，每间房内都藏有一定的现金。
这个地方所有的房屋都 围成一圈 ，这意味着第一个房屋和最后一个房屋是紧挨着的。
同时，相邻的房屋装有相互连通的防盗系统，如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警 。

给定一个代表每个房屋存放金额的非负整数数组，计算你 在不触动警报装置的情况下 ，今晚能够偷窃到的最高金额。

*/
class Solution213 {
public:
   	int rob210712(vector<int>& nums){ //直接调用打家劫舍I的方法即可
           //可以优化成常数的空间复杂度
		if (nums.empty()){
			return 0;
		}
		vector<int> dp(nums.size(),0); //[0,i]个房间范围内偷的最大数目
		dp[0] = nums[0];
		for (int i = 1;i<nums.size();i++){
			if (i==1){
				dp[i] = max(nums[0],nums[1]);
			}
			else{
				dp[i] = max(dp[i-2]+nums[i],dp[i-1]);
			}
		}
		return dp[nums.size()-1];
	}
    int rob(vector<int>& nums) {
        if(nums.size()==1)//这个容易漏掉 
            return nums[0];
		vector<int> nums1;
		vector<int> nums2;
        for(int i = 0;i<nums.size()-1;i++){
			nums1.push_back(nums[i]);
		}
		for(int i = 1;i<nums.size();i++){
			nums2.push_back(nums[i]);
		}
		return max(rob210712(nums1),rob210712(nums2)); //不偷最后一个房间或者不偷第一个房间，然后取最大值即可
    }
};

/*
337. 打家劫舍 III
在上次打劫完一条街道之后和一圈房屋后，小偷又发现了一个新的可行窃的地区。
这个地区只有一个入口，我们称之为“根”。 除了“根”之外，每栋房子有且只有一个“父“房子与之相连。
一番侦察之后，聪明的小偷意识到“这个地方的所有房屋的排列类似于一棵二叉树”。 
如果两个直接相连的房子在同一天晚上被打劫，房屋将自动报警。

计算在不触动警报的情况下，小偷一晚能够盗取的最高金额。
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
class Solution337 {
public:
void DFS(TreeNode* root,map<TreeNode*,int>& dp){
		if (root==nullptr){
			return;
		}
		DFS(root->left,dp);
		DFS(root->right,dp);
		//dp[root] 没有root，只有两个子节点；有root，
		dp[root] = 
				max(dp[root->left]+dp[root->right],
				root->val+
				dp[root->left!=nullptr?root->left->left:nullptr]+dp[root->left!=nullptr?root->left->right:nullptr]+
				dp[root->right!=nullptr?root->right->left:nullptr]+dp[root->right!=nullptr?root->right->right:nullptr]);
				//这个递推式还是比较容易想到的
	}
    int rob(TreeNode* root) {
		//n的空间复杂度和n的时间复杂度 再配合hashmap和后序遍历
		map<TreeNode*,int> dp;
		dp[nullptr] = 0;
		DFS(root,dp);
		return dp[root];
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


/*
152. 乘积最大子数组
给你一个整数数组 nums ，请你找出数组中乘积最大的连续子数组（该子数组中至少包含一个数字），并返回该子数组所对应的乘积。
*/

class Solution152 {
public:
    int solveMethod1(vector<int>& nums){
        //用这种dp就直接超时了，其实就是个暴力
        vector<vector<int>> dp(nums.size(),vector<int>(nums.size(),0)); 
        //dp[i][j]表示[i,j]区间内的连续子数组的乘积
        for (int i = 0;i<nums.size();i++){
            dp[i][i] = nums[i];
        }
        for (int len = 1;len<nums.size();len++){
            for (int i = 0;i<nums.size()-len;i++){
                dp[i][i+len] = dp[i][i+len-1]*nums[i+len];
                dp[i+len][i] = dp[i][i+len];
            }
        }
        int res = INT_MIN;
        for (int i = 0;i<nums.size();i++){
            for (int j = 0;j<nums.size();j++){
                if (dp[i][j]>res){
                    res = dp[i][j];
                }
            }
        }
        return res;
    }
    int solveMethod2(vector<int>& nums){
        //第一次写的时候只弄了一个dp，然后发现是不够的，因为考虑乘积的话可能负负得正会更大，因此MAX和MIN都需要记录
		//尽量把dp数组弄成一维的，也就是抽象成一维的
        vector<int> dpMAX(nums.size(),0); //由于是连续数组，因此考虑dpMAX[i]是包括nums[i]的连续数组最大值
        vector<int> dpMIN(nums.size(),0);  //由于是连续数组，因此考虑dpMIN[i]是包括nums[i]的连续数组最小值
        dpMAX[0] = nums[0];
        for (int i = 1;i<nums.size();i++){
            dpMAX[i] = max(max(dpMAX[i-1]*nums[i],dpMIN[i-1]*nums[i]),nums[i]);
            dpMIN[i] = min(min(dpMAX[i-1]*nums[i],dpMIN[i-1]*nums[i]),nums[i]); //可以根据这个式子优化到常数空间复杂度
        }
        int MAX = INT_MIN;
        for(int i = 0;i<dpMAX.size();i++){
            if (dpMAX[i]>MAX){
                MAX = dpMAX[i];
            }
        }
        return MAX;
    }
    int maxProduct(vector<int>& nums) {
        return solveMethod2(nums);
    }
};



/*
221. 最大正方形
在一个由 '0' 和 '1' 组成的二维矩阵内，找到只包含 '1' 的最大正方形，并返回其面积。

*/

class Solution221 {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        //用动态规划的方法做，时间复杂度是n*n 
        if (matrix.empty()){
            return 0;
        }
        int m = matrix.size();
        int n = matrix[0].size();
        vector<vector<int>> dp(m,vector<int>(n,0)); //dp存储的是边长，dp[i][j]表示以i,j为左下角的最大边长
        for (int j = 0;j<n;j++){
            dp[0][j] = matrix[0][j]-'0';
        }
        for (int i = 0;i<m;i++){
            dp[i][n-1] = matrix[i][n-1]-'0';
        }
        for (int i = 1;i<m;i++){
            for (int j = n-2;j>=0;j--){
                if (matrix[i][j]=='1'){
                    dp[i][j] = min(min(dp[i-1][j],dp[i-1][j+1]),min(dp[i][j+1],dp[i-1][j+1]))+1;
					//主要应该理解这个式子，这里的空间复杂度可以进一步优化
                }   
            }
        }
        int MAX = INT_MIN;
        for (int i = 0;i<dp.size();i++){
            for (int j = 0;j<dp[i].size();j++){
                if (dp[i][j]>MAX){
                    MAX = dp[i][j];
                }
            }
        }
        return MAX*MAX; //返回的应该是面积
    }
};



/*
238. 除自身以外数组的乘积
给你一个长度为 n 的整数数组 nums，其中 n > 1，返回输出数组 output ，
其中 output[i] 等于 nums 中除 nums[i] 之外其余各元素的乘积。

*/

class Solution238 {
public:
    vector<int> solveMethod1(vector<int>& nums){
        //n的时间复杂度，n的空间复杂度
        vector<int> L(nums.size(),1);
        vector<int> R(nums.size(),1);
        for(int i = 1;i<nums.size();i++){
            L[i] = L[i-1]*nums[i-1]; //有点像动态规划了
        }
        for(int i = nums.size()-2;i>=0;i--){
            R[i] = R[i+1]*nums[i+1];
        }
        vector<int> res(nums.size(),0);
        for (int i = 0;i<res.size();i++){
            res[i] = L[i]*R[i];
        }
        return res;
    }
    vector<int> solveMethod2(vector<int>& nums){
        //按照题目中的定义，n的时间复杂度，1的空间复杂度
        //实际上就是先把没有经过空间优化的代码写出来，然后看能不能空间优化一波
        vector<int> R(nums.size(),1);
        for(int i = nums.size()-2;i>=0;i--){
            R[i] = R[i+1]*nums[i+1];
        }
        int LastL = 1;
        R[0] = LastL*R[0];
        for(int i = 1;i<nums.size();i++){
            LastL = LastL*nums[i-1];
            R[i] = R[i]*LastL;
        }
        return R;
    }
    vector<int> productExceptSelf(vector<int>& nums) {
        return solveMethod2(nums);
    }
};

/*
剑指 Offer 66. 构建乘积数组
给定一个数组 A[0,1,…,n-1]，请构建一个数组 B[0,1,…,n-1]，
其中 B[i] 的值是数组 A 中除了下标 i 以外的元素的积, 即 B[i]=A[0]×A[1]×…×A[i-1]×A[i+1]×…×A[n-1]。不能使用除法。

*/
class SolutionOffer66 {
public:
    vector<int> constructArr(vector<int>& a) {
        vector<int> res(a.size(),1);
        for(int i = 1;i<res.size();i++){
            res[i] = res[i-1]*a[i-1];
        }
        int S = 1;
        for(int i = res.size()-2;i>=0;i--){
            S = S*a[i+1];
            res[i] = res[i]*S;
        }
        return res;
    }
};


/*
279. 完全平方数
给定正整数 n，找到若干个完全平方数（比如 1, 4, 9, 16, ...）使得它们的和等于 n。
你需要让组成和的完全平方数的个数最少。

给你一个整数 n ，返回和为 n 的完全平方数的 最少数量 。

完全平方数 是一个整数，其值等于另一个整数的平方；换句话说，其值等于一个整数自乘的积。
例如，1、4、9 和 16 都是完全平方数，而 3 和 11 不是。

*/

class Solution279 {
public:
    bool isTwiceNum(int num){
        double tmp = sqrt(num);
        if (static_cast<double>(static_cast<int>(tmp)) == tmp){
            return true;
        }
        return false;
    }
    int solveMethod1(int n){
        //N^2的时间复杂度
        vector<int> dp(n+1,0);
        dp[1] = 1;
        for (int i = 2;i<=n;i++){
            if (isTwiceNum(i)){
                dp[i] = 1;
            }
            else{
                int MIN = INT_MAX;
                for(int j = 1;j<i/2+1;j++){ //这个逐个遍历，直接超时了
                    if (dp[j]+dp[i-j]<MIN){
                        MIN = dp[j]+dp[i-j];
                    }
                }
                dp[i] = MIN;
            }
        }
        return dp[n];
    }
    int  solveMethod2(int n){
        //n^1.5的时间复杂度
        vector<int> dp(n+1,0);
        dp[1] = 1;
        for (int i = 2;i<=n;i++){
            if (isTwiceNum(i)){
                dp[i] = 1;
            }
            else{
                int MIN = INT_MAX;
                for(int j = 1;j*j<i;j++){ //这个认为最小值肯定是在完全数中去找
                    if (dp[j*j]+dp[i-j*j]<MIN){ 
                        MIN = dp[j*j]+dp[i-j*j];
                    }
                }
                dp[i] = MIN;
            }
        }
        return dp[n];
    }
    int solveMethod3(int n){
        //也可以用BFS做，最先层序遍历到累加值的就是最少数量
        //无论是从时间还是从空间复杂度还是从代码编写的复杂程度相较于动态规划方法没有一丝优势
        //重点是要想通本题是如何抽象到BFS的。本质上其实就是一个树搜索的剪枝回溯
        class node{
        public:
            node(int in,int accu,int level):i(in),accumulate(accu),level(level){}
            int i;
            int accumulate;
            int level;
        };
        queue<node> que;
        que.push(node(0,0,0));
        while(!que.empty()){
            node & tmp = que.front();
            for(int i = 1;;i++){
                int curAcc = tmp.accumulate+i*i;
                if (curAcc<n){
                    que.push(node(i,curAcc,tmp.level+1));
                }
                else if (curAcc==n){
                    return tmp.level+1;
                }
                else {
                    break;
                }
            }
            que.pop();
        }
        return 0;
    }
    int solveMethod3Review(int n){
        vector<int> dp(n+1,0);
        dp[1] = 1;
        for(int i = 2;i<=n;i++){
            int MIN = INT_MAX;
            for(int j = 1;j*j<=i ;j++){
                if (dp[i-j*j]+1<MIN){
                    MIN = dp[i-j*j]+1;
                }
            }
            dp[i] = MIN;
        }
        return dp[n];
    }
    int numSquares(int n) {
        return solveMethod3(n);
        return solveMethod2(n);
    }
};


/*
309. 最佳买卖股票时机含冷冻期
给定一个整数数组，其中第 i 个元素代表了第 i 天的股票价格 。?

设计一个算法计算出最大利润。在满足以下约束条件下，你可以尽可能地完成更多的交易（多次买卖一支股票）:

你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。
卖出股票后，你无法在第二天买入股票 (即冷冻期为 1 天)。

*/
class Solution309 {
public:
    int MAX = INT_MIN;
    bool stateBought = 0;
    int stateSell = -1; 
    void DFS(vector<int>& prices,int index,int& sum){
        if (index == prices.size()){
            if (sum>MAX){
                MAX = sum;
            }
            return;
        }
        int sellstorage;
        bool buystorage;

        if (stateBought){
            DFS(prices,index+1,sum); //可以卖出，也可以什么都不做

            sellstorage = stateSell; //注意保存变量
            buystorage = stateBought;

            sum+=prices[index]; //卖出
            stateSell = index;
            stateBought = 0;
            DFS(prices,index+1,sum);
            sum-=prices[index];

            stateSell = sellstorage;
            stateBought = buystorage;
        }
        else{
            if (stateSell!=-1 && index-stateSell==1){
                DFS(prices,index+1,sum); //冷冻期
            }
            else{
                DFS(prices,index+1,sum);//可以买入，也可以什么都不做

                sellstorage = stateSell;
                buystorage = stateBought;

                sum-=prices[index]; //买入
                stateBought = 1;
                DFS(prices,index+1,sum);
                sum+=prices[index];

                stateSell = sellstorage;
                stateBought = buystorage;
            }
        }
    }
    int solveMethod1(vector<int>& prices){ //用DFS直接超时了，运行是正确的
        int sum = 0;
        DFS(prices,0,sum);
        return MAX;
    }
    int solveMethod2(vector<int>& prices){
        //dp[i][0] 第i天结束后持有股票，此时的最大利润
        //dp[i][1] 第i天结束后不持有股票且进入冷冻期，此时的最大利润
        //dp[i][2] 第i天结束后不持有股票且没有进入冷冻期，此时的最大利润  主要是这三个物理意义不好想
        //dp[i][0] = max(dp[i-1][0],dp[i-1][2]-prices[i]) 把物理意义列出来就很自然能得到这三个递推式了
        //dp[i][1] = dp[i-1][0]+prices[i]
        //dp[i][2] = max(dp[i-1][2],dp[i-1][1])
        //dp[0][0] = 1
        //dp[0][1] = INT_MIN
        //dp[0][2] = INT_MIN
        vector<vector<int>> dp(prices.size(),vector<int>(3,INT_MIN));
        dp[0][0] = -prices[0];
        dp[0][2] = 0;
        //不会出现dp[0][1]的情况
        if (prices.size()>=2){
            dp[1][0] = max(-prices[0],-prices[1]);
            dp[1][1] = -prices[0]+prices[1];
            dp[1][2] = 0;
        }
        for(int i = 2;i<prices.size();i++){
            dp[i][0] = max(dp[i-1][0],dp[i-1][2]-prices[i]);
            dp[i][1] = dp[i-1][0]+prices[i];
            dp[i][2] = max(dp[i-1][2],dp[i-1][1]);
        }
        return max(max(dp[prices.size()-1][0],dp[prices.size()-1][1]),dp[prices.size()-1][2]);
    }
	int solveMethod2Review(vector<int>& prices){
        //dp[i][0] 第i天结束后持有股票的最大利润
        //dp[i][1] 第i天结束后不持有股票且不处于冷冻期的最大利润
        //dp[i][2] 第i天结束后不持有股票且开始进入冷冻期的最大利润
        //dp[i][3] 第i天结束后不持有股票且第i天处于冷冻期的最大利润
        //按这样的理解方式好理解一些
        vector<vector<int>> dp(prices.size(),vector<int>(4,0));
        dp[0][0] = -prices[0];
        dp[0][1] = 0;
        dp[0][2] = 0;
        dp[0][3] = 0;
        for(int i = 1;i<prices.size();i++){
            dp[i][0] = max(max(dp[i-1][0],dp[i-1][1]-prices[i]),dp[i-1][3]-prices[i]);
            dp[i][1] = max(dp[i-1][1],dp[i-1][3]);
            dp[i][2] = dp[i-1][0]+prices[i];
            dp[i][3] = dp[i-1][2];
        }
        int end = prices.size()-1;
        return max(max(dp[end][0],dp[end][1]),max(dp[end][2],dp[end][3]));
    }
    int maxProfit(vector<int>& prices) {
        return solveMethod2(prices);
    }
};


/*
647. 回文子串
给定一个字符串，你的任务是计算这个字符串中有多少个回文子串。

具有不同开始位置或结束位置的子串，即使是由相同的字符组成，也会被视作不同的子串。
*/

class Solution647 {
public:
	void count(int midL,int midR,int& res,const string& s){
		for(int j = 0;midL-j>=0 && midR+j<s.size();j++){
			if (s[midL-j]==s[midR+j]){
				res++;
			}
			else{
				break;
			}
		}
	}
	int solveMethod1(string s){
		//回文子串要不是奇数，要不是偶数，然后中心要不是一个元素，要不就是两个元素
		//因此枚举所有单中心和双中心的回文子串
        //空间复杂度为1 时间复杂度为n^2
        int res = 0;
		int midL,midR;
        for(int i = 0;i<s.size();i++){
			midL = i;
			midR = i; 
            count(midL,midR,res,s);
			if (i!=s.size()-1){
				midL = i;
				midR = midL+1;
				count(midL,midR,res,s);
			}
        }
        return res;
	}
	int solveMethod2(string s){
        //用动态规划的方法做，时间复杂度和空间复杂度均为n^2
		vector<vector<bool>> dp(s.size(),vector<bool>(s.size(),0)); //dp[i][j]表示[i,j]子串是否是回文子串
		for(int i = 0;i<s.size();i++){
			dp[i][i] = 1;
		}
		for (int i = 0;i<s.size()-1;i++){
			if (s[i]==s[i+1]){
				dp[i][i+1] = 1;
			}
		}
		for(int len = 3;len<=s.size();len++){
			for(int i = 0;i<s.size()-len+1;i++){
				if (s[i]==s[i+len-1]&&dp[i+1][i+len-1-1]){
					dp[i][i+len-1] = 1;
				}
			}
		}
		int res = 0;
		for(int i = 0;i<dp.size();i++){
			for(int j = 0;j<dp[i].size();j++){
				if (dp[i][j]){
					res++;
				}
			}
		}
		return res;
	}
	/*
	C语言 动态规划 dp[j]表示从j位置到当前遍历到的字符位置i是否为回文字符串

	int countSubstrings(char * s){
		int len = strlen(s);
		int* dp = (int*)malloc(sizeof(int)*len);
		int cnt= 0;
		
		for(int i = 0; i < len; i++){
			dp[i] = 1;
			cnt++;
			for(int j = 0; j < i; j++){
				if(s[j] == s[i] && dp[j+1] == 1){
					dp[j]= 1;
					cnt++;
				}else{
					dp[j] = 0;
				}
			}
		}
		
		return cnt;
	}

	//另一种动态规划的方法  没太看懂。。。。。。
	*/
    int solveMethod2Review(string s){
        vector<vector<bool>> dp(s.size(),vector<bool>(s.size(),0));
        for(int i = 0;i<s.size();i++){
            dp[i][i] = 1;
        }
        for(int i = 0;i<s.size()-1;i++){
            if (s[i]==s[i+1]){
                dp[i][i+1] = 1;
            }
        }
        for(int len = 3;len<=s.size();len++){
            for(int i = 0;i<s.size()-(len-1);i++){
                if (s[i]==s[i+len-1]&& dp[i+1][i+len-2]){
                    dp[i][i+len-1] = 1;
                }
            }
        }
        int res = 0;
        for(int i = 0;i<dp.size();i++){
            for(int j = 0;j<dp[i].size();j++){
                if (dp[i][j]==1){
                    res++;
                }
            }
        }
        return res;
    }
    int countSubstrings(string s){
        return solveMethod2(s);
    }
};


/*
322. 零钱兑换
给定不同面额的硬币 coins 和一个总金额 amount。
编写一个函数来计算可以凑成总金额所需的最少的硬币个数。
如果没有任何一种硬币组合能组成总金额，返回 -1。

你可以认为每种硬币的数量是无限的。

*/

class Solution322 {
public:
	int solveMethod1(vector<int>& coins, int amount){
		//BFS做，直接超出了限制
		if (amount == 0){
			return 0;
		}
		sort(coins.begin(),coins.end());
		class node{
		public:
			node(int acc,int level):acc(acc),level(level){}
			int acc;
			int level;
		};
		queue<node> que;
		que.push(node(0,0));
		while(!que.empty()){
			node& front = que.front();
			for(auto &c:coins){
				if (front.acc+c<amount){
					que.push(node(front.acc+c,front.level+1));
				}
				else if (front.acc+c>amount){
					break;
				}
				else{
					return front.level+1;
				}
			}
			que.pop();
		}
		return -1;
	}
	int solveMethod2(vector<int>& coins, int amount){
		//这个dp还是超时
		vector<int> dp(amount+1,-1);
		dp[0] = 0;
		for(auto&c:coins){
			if (c<dp.size())
				dp[c] = 1;
		}
		for(int i = 1;i<dp.size();i++){
			if (dp[i]==-1){
				int MIN = INT_MAX;
				for(int j = 1;j<i/2+1;j++){
					int tmp = dp[i-j]+dp[j];
					if (dp[i-j]>=0 && dp[j]>=0 && tmp<MIN){ //注意与method3对应的相同位置处进行对比 是没必要逐个进行计算的
						MIN = tmp;
					}
				}
				if (MIN == INT_MAX){
					dp[i] = -1;
				}
				else{
					dp[i] = MIN;
				}
			}
		}
		return dp[amount];
	}
	int solveMethod3(vector<int>& coins,int amount){
		//这个不超时，直接ac了
		vector<int> dp(amount+1,-1);
		dp[0] = 0;
		for(auto&c:coins){
			if (c<dp.size())
				dp[c] = 1;
		}
		for(int i = 1;i<dp.size();i++){
			if (dp[i]==-1){
				int MIN = INT_MAX;
				for(int j = 0;j<coins.size();j++){
					if (coins[j]<i){
						if (dp[i-coins[j]]>=0 && dp[i-coins[j]]+1<MIN){
							MIN = dp[i-coins[j]]+1;
						}
					}
				}
				if (MIN!=INT_MAX){
					dp[i] = MIN;
				}
			}
		}
		return dp[amount];
	}
    int solveMethod3Review(vector<int>& coins,int amount){
        vector<int> dp(amount+1,-1);
        dp[0] = 0;
        for(int i = 0;i<coins.size();i++){
            if (coins[i]<=amount) //注意这里容易出错
                dp[coins[i]] = 1;
        }
        for(int i = 1;i<=amount;i++){
            int MIN = INT_MAX;
            for(int j = 0;j<coins.size();j++){
                if (i>=coins[j]){
                    if (dp[i-coins[j]]!=-1 && dp[i-coins[j]]+1<MIN){
                        MIN = dp[i-coins[j]]+1;
                    }
                }
            }
            if (MIN == INT_MAX){
                dp[i] = -1;
            }
            else{
                dp[i] = MIN;
            }
        }
        return dp[amount];
    }
    int coinChange(vector<int>& coins, int amount) {
        return solveMethod3(coins,amount);
		return solveMethod2(coins,amount);
    }
};

/*
518. 零钱兑换 II
给你一个整数数组 coins 表示不同面额的硬币，另给一个整数 amount 表示总金额。

请你计算并返回可以凑成总金额的硬币组合数。如果任何硬币组合都无法凑出总金额，返回 0 。

假设每一种面额的硬币有无限个。 

题目数据保证结果符合 32 位带符号整数。
*/
class Solution518 {
public:
    int change(int amount, vector<int>& coins) {
        //https://leetcode-cn.com/problems/coin-change-2/solution/ling-qian-dui-huan-ii-er-wei-zhuan-yi-we-4ywa/
        //用上边的这个方法可以从二维降到一维
        vector<vector<int>> dp(coins.size(),vector<int>(amount+1,0));
        //dp[i][j]表示选前i个硬币，凑出金额为j的组合数量
        for(int i = 0;i<=amount;i++){
            if (i%coins[0]==0)
                dp[0][i] = 1;
        }
        for(int i = 1;i<coins.size();i++){
            for(int j = 0;j<=amount;j++){
                dp[i][j] = dp[i-1][j]; //不选coins[i]
                int selectcoins = coins[i];
                while(j>=selectcoins){
                    dp[i][j]+=dp[i-1][j-selectcoins]; //选大于等于1个coins[i]
                    selectcoins+=coins[i]; //一定要注意这个递推式
                }
               // cout<<"dp["<<i<<"]["<<j<<"]"<<"="<<dp[i][j]<<endl;
            }
        }
        return dp[coins.size()-1][amount];
    }
};

/*
416. 分割等和子集
给你一个 只包含正整数 的 非空 数组 nums 。请你判断是否可以将这个数组分割成两个子集，使得两个子集的元素和相等。
*/
class Solution416 {
public:
	bool solveMethod1Review(vector<int>& nums){
        double sum = 0;
        for(int i = 0;i<nums.size();i++){
            sum+=nums[i];
        }
        if (sum/2!=(int)(sum/2)){
            return false;
        }
        sum = sum/2;
        vector<vector<bool>> dp(nums.size(),vector<bool>(sum+1,0)); //dp[i][j]表示[0,i]元素是否能构成j
        for(int i = 0;i<nums.size();i++){
            dp[i][0] = 1;
            if (nums[i]<=sum)
                dp[i][nums[i]] = 1;
        }
        for(int i = 1;i<nums.size();i++){
            for(int j = 1;j<=sum;j++){
                if (dp[i-1][j]==1){
                    dp[i][j] = 1;
                }
                else if (j>=nums[i] && dp[i-1][j-nums[i]]){
                    dp[i][j] = 1;
                }
                if (j==sum&&dp[i][j]==1){
                    return 1;
                }
            }
        }
        return 0;
    }
    bool canPartition(vector<int>& nums) {
        int SUM = 0;
        for(auto&n:nums){
            SUM+=n;
        }
        if(SUM%2!=0){
            return 0;
        }
        SUM = SUM/2;
		//最重要的还是要确定dp的含义
        vector<vector<bool>> dp(nums.size(),vector<bool>(SUM+1,0));//dp[i][j]表示[0,i]元素是否能构成j
        for(int i = 0;i<dp.size();i++){
            dp[i][0] = 1;
        }
        if (nums[0]<=SUM)
            dp[0][nums[0]] = 1;
        for(int i = 1;i<dp.size();i++){
            for(int j = 0;j<dp[i].size();j++){
                if (j<nums[i]){
                    dp[i][j] = dp[i-1][j];
                }
                else{
                    dp[i][j] = max(dp[i-1][j],dp[i-1][j-nums[i]]);
                }
            }
        }
		//这个能把空间复杂度优化到SUM
		//然后dp优化到一维
        return dp[nums.size()-1][SUM];
    }
};


/*
139. 单词拆分
给定一个非空字符串 s 和一个包含非空单词的列表 wordDict，判定 s 是否可以被空格拆分为一个或多个在字典中出现的单词。

说明：

拆分时可以重复使用字典中的单词。
你可以假设字典中没有重复的单词。

*/

//还是比较建议用动态规划去做
//动态规划跟DFS本质上是一样的原理，只不过动态规划是自底向上的，DFS是自顶向下的
class Solution139 {
public:
    bool solveMethod1(string s,vector<string>& wordDict){
        //用动态规划的方法做 n^2的时间复杂度 n的空间复杂度
        set<string> SET;
        for(auto&str:wordDict){
            SET.insert(str);
        }
        vector<bool> dp(s.size(),0);//dp[i]表示[0,i]区间范围内是否可以符合在字典中出现
        if (SET.find(s.substr(0,1))!=SET.end()){
            dp[0] = 1;
        }
        for(int i = 1;i<s.size();i++){
            if (SET.find(s.substr(0,i+1))!=SET.end()){
                dp[i] = 1;
            }
            else{
                for(int j = 0;j<i;j++){
                    if (dp[j]&& SET.find(s.substr(j+1,i-(j+1)+1))!=SET.end()){
                        dp[i] = 1;
                        break;
                    }
                }
            }
        }
        return dp.back();
    }
    
    bool DFS(set<string>&SET,string&s,int index,vector<int>& memory){
        //基于DFS的记忆化搜索，如果不记忆的话，直接就超出时间限制了
        if (index==s.size()){
            return 1;
        }
        if (memory[index]!=-1){
            return memory[index];
        }
        for(int i = 1;index+i<=s.size();i++){
            if (SET.find(s.substr(index,i))!=SET.end() && DFS(SET,s,index+i,memory)){
                memory[index] = 1;
                return 1;
            }
        }
        memory[index] = 0;
        return 0;
    }
    bool solveMethod2(string s,vector<string>& wordDict){
        set<string> SET;
        for(auto&str:wordDict){
            SET.insert(str);
        }
        vector<int> memory(s.size(),-1);
        return DFS(SET,s,0,memory);
    }
    bool wordBreak(string s, vector<string>& wordDict) {
        return solveMethod2(s,wordDict);

    }
};


/*
剑指 Offer 47. 礼物的最大价值
在一个 m*n 的棋盘的每一格都放有一个礼物，每个礼物都有一定的价值（价值大于 0）。你可以从棋盘的左上角开始拿格子里的礼物，
并每次向右或者向下移动一格、直到到达棋盘的右下角。给定一个棋盘及其上面的礼物的价值，请计算你最多能拿到多少价值的礼物？

*/
class SolutionOffer47 {
public:
    int maxValue(vector<vector<int>>& grid) {
		int m = grid.size();
		int n = grid[0].size();
		vector<vector<int>> dp(m,vector<int>(n,0));
        //空间复杂度可做优化，即直接在grid上修改，这样的话空间复杂度就降到了1
		dp[0][0] = grid[0][0];
		for(int j = 1;j<n;j++){
			dp[0][j] = dp[0][j-1]+grid[0][j];
		}
		for(int i = 1;i<m;i++){
			dp[i][0] = dp[i-1][0]+grid[i][0];
		}
		for (int i = 1;i<m;i++){
			for(int j = 1;j<n;j++){
				dp[i][j] = max(dp[i-1][j],dp[i][j-1])+grid[i][j];
			}
		}
		return dp[m-1][n-1];
    }
};

/*
剑指 Offer 60. n个骰子的点数
把n个骰子扔在地上，所有骰子朝上一面的点数之和为s。输入n，打印出s的所有可能的值出现的概率。

 

你需要用一个浮点数数组返回答案，其中第 i 个元素代表这 n 个骰子所能掷出的点数集合中第 i 小的那个的概率。


*/

class SolutionOffer60 {
public:
    vector<double> dicesProbability(int n) {
        //空间复杂度可以降到n
        //时间复杂度是n^2
        vector<vector<double>> dp(n+1,vector<double>(6*n+1,0));

        for(int i = 1;i<=6;i++){
            dp[1][i] = 1.0/6.0;
        }
        for (int i = 2;i<=n;i++){
            for (int j = i;j<=6*i;j++){
                for (int k = 1;k<=6;k++){
                    if (j-k>=0){
                        dp[i][j]+=dp[i-1][j-k]*(1.0/6.0);
                    }
                }
            }
        }
        return vector<double>(dp[n].begin()+n,dp[n].end());
    }
};


/*
剑指 Offer 63. 股票的最大利润
假设把某股票的价格按照时间先后顺序存储在数组中，请问买卖该股票一次可能获得的最大利润是多少？

*/
class SolutionOffer63 {
public:

    int solveMethod1(vector<int>& prices){
        //动态规划做，时间复杂度是n，空间复杂度可降到1
        if (prices.empty()){
            return 0;
        }
        vector<int> dpMAX(prices.size(),0); //dpMAX[i]表示i之后不包括i的最大值
        vector<int> dpMIN(prices.size(),0); //dpMIN[i]表示i之前包括i的最小值
        dpMIN[0] = prices[0];
        for(int i = 1;i<dpMIN.size();i++){
            if (prices[i]<dpMIN[i-1]){
                dpMIN[i] = prices[i];
            }
            else{
                dpMIN[i] = dpMIN[i-1];
            }
        }
        dpMAX[prices.size()-1] = INT_MIN;
        for(int i = prices.size()-2;i>=0;i--){
            if (prices[i+1]>dpMAX[i+1]){
                dpMAX[i] = prices[i+1];
            }
            else{
                dpMAX[i] = dpMAX[i+1];
            }
        }
        int res = INT_MIN;
        for(int i = 0;i<prices.size()-1;i++){
            if (dpMAX[i]-dpMIN[i]>res){
                res = dpMAX[i]-dpMIN[i];
            }
        }
        return res<0?0:res;
    }   
    int solveMethod2(vector<int>& prices){
        if (prices.empty()){
            return 0;
        }
        int MIN = prices[0]; //MIN表示之前的最小值
        int res = INT_MIN;
        for (int i =1;i<prices.size();i++){
            if (prices[i]-MIN>res){
                res = prices[i]-MIN;
            }
            if (prices[i]<MIN){
                MIN = prices[i];
            }
        }
        return res<0?0:res;
    }
    int maxProfit(vector<int>& prices) {
        return solveMethod2(prices);
    }
};


/*
剑指 Offer 49. 丑数
我们把只包含质因子 2、3 和 5 的数称作丑数（Ugly Number）。求按从小到大的顺序的第 n 个丑数。
*/

class SolutionOffer49 {
public:
    int solveMethod1(int n){
        //用小根堆和去重的set去做
        auto cmp1 = [](long int a,long int b)->bool{return a>b;};
        priority_queue<long int,vector<long int>,decltype(cmp1)> pq(cmp1);
        set<long int> unique;
        pq.push(1);
        unique.insert(1);
        vector<int> factor = {2,3,5};
        long int top;
        for(int i = 1;i<=n;i++){
            top = pq.top();
            for(int f:factor){
                if (unique.find(top*f)==unique.end()){
                    unique.insert(top*f);
                    pq.push(top*f);
                }
            }
            pq.pop();
        }
        return top;
    }
    /*
在已有的丑数序列上每一个数都必须乘2， 乘3， 乘5， 这样才不会漏掉某些丑数。
假设已有的丑数序列为[1, 2, 3, ..., n1, n2], 如果单纯的让每个丑数乘2， 乘3， 乘5顺序排列的话肯定会有问题，
比如如果按照这样的顺序排列下去肯定有问题[1*2, 1*3, 1*5, 2*2, 2*3, 2*5, 3*2, 3*3, 3*5, ... , n1 *2, n1 * 3, n1 * 5, n2 * 2, n3* 3, n2 * 5]，
因为后面乘2的数据可能会比前面乘3乘5的数据要小，那这个乘2的数应该排在他们的前面， 后面乘3的数据也可能比前面乘5的数据要小，那这个乘3的数应该排在他们的前面。
那怎么办呢，每个数都必须乘2， 乘3， 乘5这样才能保证求出所有的丑数，而且还要保证丑数的顺序，这个改如何同时实现呢？
通过观察网上的各个题解，终于找到了办法，那就是记录每个丑数是否已经被乘2， 乘3， 乘5了， 具体的做法是
设置3个索引a, b, c，分别记录前几个数已经被乘2， 乘3， 乘5了，比如a表示前(a-1)个数都已经乘过一次2了，下次应该乘2的是第a个数；
b表示前(b-1)个数都已经乘过一次3了，下次应该乘3的是第b个数；c表示前(c-1)个数都已经乘过一次5了，下次应该乘5的是第c个数；

对于某个状态下的丑数序列，我们知道此时第a个数还没有乘2(有没有乘3或者乘5不知道）， 第b个数还没有乘3(有没有乘2或者乘5不知道），
第c个数还没有乘5(有没有乘2或者乘3不知道), 下一个丑数一定是从第a丑数乘2， 第b个数乘3， 第c个数乘5中获得，他们三者最小的那个就是下个丑数。

求得下个丑数后就得判断这个丑数是谁，是某个数通过乘2得到的，还是某个数乘3得到的，又或是说某个数通过乘5得到的。
我们可以比较一下这个新的丑数等于究竟是等于第a个丑数乘2, 还是第b个数乘3， 还是第c个数乘5， 通过比较我们肯定可以知道这个新的丑数到底是哪个数通过乘哪个数得到的。
假设这个新的丑数是通过第a个数乘2得到的，说明此时第a个数已经通过乘2得到了一个新的丑数，那下个通过乘2得到一个新的丑数的数应该是第(a+1)个数，
此时我们可以说前 a 个数都已经乘过一次2了，下次应该乘2的是第 （a+1） 个数, 所以a++；如果新的丑数是通过第b个数乘3得到的, 
说明此时第 b个数已经通过乘3得到了一个新的丑数，那下个需要通过乘3得到一个新的丑数的数应该是第(b+1)个数，此时我们可以说前 b 个数都已经乘过一次3了，
下次应该乘3的是第 （b+1） 个数, 所以 b++；同理，如果这个这个新的丑数是通过第c个数乘5得到的, 那么c++;

但是注意，如果第a个数乘2后等于第b个数乘3，或者等于第c个数乘5， 说明这个新的丑数是有两种或者三种方式可以得到，
这时应该给得到这个新丑数的组合对应的索引都加一，比如新丑数是第a个数乘2后和第b个数乘3得到的，那么 a 和 b都应该加一， 
因为此时第a个数已经通过乘2得到了一个新的丑数，第b个数已经通过乘3得到了一个新的丑数, 只不过这两个数相等而已。
所以我们给计数器加一的时候不能使用 if else else if， 而应该使用if, if, if, 这样才不会把应该加一的计数器漏掉

经过n次循环，就能得到第n 个丑数了。
*/
    int solveMethod2(int n){
        int a2 = 1;
        int a3 = 1;
        int a5 = 1;
        vector<int> nums(n+1,0);
        nums[1] = 1;
        int curi = 1;
        for(int i = 2;i<nums.size();i++){
            nums[i] = min(nums[a5]*5,min(nums[a2]*2,nums[a3]*3));
            if (nums[i]%2==0){
                a2++;
            }
            if (nums[i]%3==0){
                a3++;
            }
            if (nums[i]%5==0){
                a5++;
            }
        }
        return nums[n];
    }
    int nthUglyNumber(int n) {
        return solveMethod2(n);
    }
};

/*
剑指 Offer 10- II. 青蛙跳台阶问题
一只青蛙一次可以跳上1级台阶，也可以跳上2级台阶。求该青蛙跳上一个 n 级的台阶总共有多少种跳法。

答案需要取模 1e9+7（1000000007），如计算初始结果为：1000000008，请返回 1。

*/
class SolutionOffer10_II {
public:
    int numWays(int n) {
        if (n==0){
            return 1;
        }
        else if (n==1){
            return 1;
        }
        else if (n==2){
            return 2;
        }
        vector<int> dp(n+1,0);
        dp[0] = 0;
        dp[1] = 1;
        dp[2] = 2;
        for(int i = 3;i<=n;i++){
            dp[i] = ((dp[i-1]%1000000007)+(dp[i-2]%1000000007))%1000000007;
        }
        return dp[n];
    }
};


/*
53. 最大子序和
给定一个整数数组 nums ，找到一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。

*/
class Solution53 {
public:
    int review(vector<int>& nums){
        vector<int> dp(nums.size(),0);
        dp[0] = nums[0];
        for(int i = 1;i<nums.size();i++){
            dp[i] = max(nums[i],dp[i-1]+nums[i]);
        }
        int res = INT_MIN;
        for(int e:dp){
            if (e>res){
                res = e;
            }
        }
        return res;
    }
    int maxSubArray(vector<int>& nums) {
        vector<int> dp(nums.size(),0);
        dp[0] = nums[0];
        for(int i = 1;i<nums.size();i++){
            dp[i] = max(dp[i-1]+nums[i],nums[i]);
        }
        int res = INT_MIN;
        for(int i = 0;i<dp.size();i++){
            if (dp[i]>res){
                res = dp[i];
            }
        }
        return res;
    }
};

/*
124. 二叉树中的最大路径和
路径 被定义为一条从树中任意节点出发，沿父节点-子节点连接，达到任意节点的序列。同一个节点在一条路径序列中 至多出现一次 。
该路径 至少包含一个 节点，且不一定经过根节点。

路径和 是路径中各节点值的总和。

给你一个二叉树的根节点 root ，返回其 最大路径和 。

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
class Solution124 {
public:
    int DFSreview(TreeNode* root){
        if (root==nullptr){
            return 0;
        }
        
        int left = DFSreview(root->left);
        int right = DFSreview(root->right);
        int cur = max(max(max(left+right+root->val,root->val),left+root->val),right+root->val);
        MAX = max(cur,MAX);
        return max(max(left,right)+root->val,root->val);
    }
    int review(TreeNode* root){
        DFSreview(root);
        return MAX;
    }
    
    int MAX = INT_MIN;
    void DFS(TreeNode * root){
        //这个可以类比最大子序和的动态规划
        if (root==nullptr){
            return;
        }
        if (root->left == nullptr && root->right == nullptr){
            root->val = root->val;
        }
        DFS(root->left);
        DFS(root->right);
        
        int curMAX = (root->left==nullptr?0:root->left->val)+(root->right==nullptr?0:root->right->val)+root->val;
        if (curMAX>MAX){
            MAX = curMAX;
        }
        root->val=
            max(max(root->val,root->val+(root->left==nullptr?0:root->left->val)),root->val+(root->right==nullptr?0:root->right->val));
            //每次调整root->val，root->val表示以当前节点为起点，以该节点为根节点的子树的路径累计值的最大值
        if (root->val>MAX){ //这个容易漏掉，因为有可能root->val是负值，造成左右侧加起来都不如单侧的
            MAX = root->val;
        }
    }
    int maxPathSum(TreeNode* root) {
        DFS(root);
        return MAX;
    }
};


/*
121. 买卖股票的最佳时机
给定一个数组 prices ，它的第 i 个元素 prices[i] 表示一支给定股票第 i 天的价格。

你只能选择 某一天 买入这只股票，并选择在 未来的某一个不同的日子 卖出该股票。设计一个算法来计算你所能获取的最大利润。

返回你可以从这笔交易中获取的最大利润。如果你不能获取任何利润，返回 0 。

*/

class Solution121 {
public:
    int maxProfit(vector<int>& prices) {
        int MINcur = prices[0];
        int res = INT_MIN;
        for(int i = 1;i<prices.size();i++){
            if (prices[i]-MINcur>res){
                res = prices[i]-MINcur;
            }
            if (prices[i]<MINcur){
                MINcur = prices[i];
            }
        }
        return res<0?0:res;
    }
};


/*
122. 买卖股票的最佳时机 II
给定一个数组 prices ，其中 prices[i] 是一支给定股票第 i 天的价格。

设计一个算法来计算你所能获取的最大利润。你可以尽可能地完成更多的交易（多次买卖一支股票）。

注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。

*/
class Solution122 {
public:
    int maxProfit(vector<int>& prices) {
        vector<int> dpHave(prices.size(),0);//dpHave[i]表示第i天持有股票时的最大利润
        vector<int> dpNothave(prices.size(),0);//dpNothave[i]表示第i天不持有股票时的最大利润
        dpHave[0] = -prices[0];
        dpNothave[0] = 0;
        for(int i = 1;i<prices.size();i++){
            dpHave[i] = max(dpHave[i-1],dpNothave[i-1]-prices[i]);
            dpNothave[i] = max(dpNothave[i-1],dpHave[i-1]+prices[i]);
        }
        return max(*(dpHave.end()-1),*(dpNothave.end()-1));
    }
};


/*
123. 买卖股票的最佳时机 III
给定一个数组，它的第 i 个元素是一支给定的股票在第 i 天的价格。

设计一个算法来计算你所能获取的最大利润。你最多可以完成 两笔 交易。

注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。
*/
//状态dp
class Solution123 {
public:
    int maxProfit(vector<int>& prices) {
        vector<vector<int>> dp(prices.size(),vector<int>(4,0)); 
        //dp[i][0] 第i天第一次持有的最大利润
        //dp[i][1] 第i天第一次持有后不持有的最大利润
        //dp[i][2] 第i天第二次持有的最大利润
        //dp[i][3] 第i天第二次持有后不持有的最大利润
        dp[0][0] = -prices[0];
        dp[0][1] = 0; //dp[0][1] dp[0][2] dp[0][3] 这三个初始值不太好直观理解~只是设置成这几个初始值后，max肯定不会选中这几个没有意义的初始值
        dp[0][2] = -prices[0]; 
        dp[0][3] = 0;
        for(int i = 1;i<prices.size();i++){
            dp[i][0] = max(dp[i-1][0],-prices[i]);
            dp[i][1] = max(dp[i-1][1],dp[i-1][0]+prices[i]);
            dp[i][2] = max(dp[i-1][2],dp[i-1][1]-prices[i]);
            dp[i][3] = max(dp[i-1][3],dp[i-1][2]+prices[i]);

            //cout<<dp[i][0]<<" "<<dp[i][1]<<" "<<dp[i][2]<<" "<<dp[i][3]<<endl;
        }
        int end = prices.size()-1;
        return max(max(dp[end][0],dp[end][1]),max(dp[end][2],dp[end][3]));
    }
};

/*
188. 买卖股票的最佳时机 IV
给定一个整数数组 prices ，它的第 i 个元素 prices[i] 是一支给定的股票在第 i 天的价格。

设计一个算法来计算你所能获取的最大利润。你最多可以完成 k 笔交易。

注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。

*/
class Solution188 {
public:
    int maxProfit(int k, vector<int>& prices) {
        if (prices.empty()){ //防止出现prices为空的情况
            return 0;
        }
        vector<vector<int>> dp(prices.size(),vector<int>(2*k,0));
        //1 2 3 4 5 6 7 8 ... k
        //dp[i][0] 第i天第一次持有的最大利润
        //dp[i][1] 第i天第一次持有后不持有的最大利润
        //dp[i][2] 第i天第二次持有的最大利润
        //dp[i][3] 第i天第二次持有后不持有的最大利润
        //dp[i][4] 第i天第三次持有的最大利润
        //dp[i][5] 第i天第三次持有后不持有的最大利润
        for(int i = 0;i<k;i++){
            dp[0][i*2] = -prices[0];
        }
        for(int i = 1;i<prices.size();i++){
            for(int j = 0;j<2*k;j++){
                if (j==0){
                    dp[i][j] = max(dp[i-1][j],-prices[i]);
                }
                else{
                    if (j%2==1){
                        dp[i][j] = max(dp[i-1][j],dp[i-1][j-1]+prices[i]);
                    }
                    else{
                        dp[i][j] = max(dp[i-1][j],dp[i-1][j-1]-prices[i]);
                    }
                }
            }
        }
        int res = INT_MIN;
        int end = dp.size()-1;
        for(int i = 0;i<dp[end].size();i++){
            if (dp[end][i]>res){
                res = dp[end][i];
            }
        }
        return res<0?0:res; //之所以有这个问号表达式，是为了防止出现k=0的情况
    }
};

/*
1049. 最后一块石头的重量 II
有一堆石头，用整数数组 stones 表示。其中 stones[i] 表示第 i 块石头的重量。

每一回合，从中选出任意两块石头，然后将它们一起粉碎。假设石头的重量分别为 x 和 y，且 x <= y。那么粉碎的可能结果如下：

如果 x == y，那么两块石头都会被完全粉碎；
如果 x != y，那么重量为 x 的石头将会完全粉碎，而重量为 y 的石头新重量为 y-x。
最后，最多只会剩下一块 石头。返回此石头 最小的可能重量 。如果没有石头剩下，就返回 0。

*/
class Solution1049 {
public:
    int lastStoneWeightII(vector<int>& stones) {
        //这个重点是要转化成一个01背包问题，然后确定正确的初始值
        //要返回最小的可能重量，就尽可能的以总重量的一半为约束，重量为最大化的代价
        int half = 0;
        for(int e:stones){
            half+=e;
        }
        int sum = half;
        half = half/2;
        vector<vector<int>> dp(stones.size(),vector<int>(half+1,0));
        for(int j = 0;j<=half;j++){
            if (j>=stones[0])
                dp[0][j] = stones[0];
        }
        for(int i = 0;i<stones.size();i++){
            dp[i][0] = 0;
            if (stones[i]<=half){
                dp[i][stones[i]] = stones[i];
            }
        }

        for(int i = 1;i<stones.size();i++){
            for(int j = 1;j<=half;j++){
                if (j<stones[i]){
                    dp[i][j] = dp[i-1][j];
                }
                else{
                    dp[i][j] = max(dp[i-1][j],dp[i-1][j-stones[i]]+stones[i]);
                }
            }
        }

        //61 57 40 35 32 27 
        return abs(sum-2*dp[dp.size()-1][half]);
    }
};


/*
377. 组合总和 Ⅳ
给你一个由 不同 整数组成的数组 nums ，和一个目标整数 target 。请你从 nums 中找出并返回总和为 target 的元素组合的个数。

题目数据保证答案符合 32 位整数范围。
*/
class Solution377 {
public:
    // int res = 0;
    // void DFS(vector<int>& nums,int index,int target,int&cur){
    //     if (cur>target){
    //         return;
    //     }
    //     if (cur==target){
    //         res++;
    //         return;
    //     }
    //     for(int i = index;i<nums.size();i++){
    //         cur+=nums[i];
    //         DFS(nums,index+1,target,cur);
    //         cur-=nums[i];
    //     }
    // }
    //不能用DFS，因为一个元素可能选择两次
    int combinationSum4(vector<int>& nums, int target) {
        vector<int> dp(target+1,0);//dp[i] 总和为i的元素组合的个数
        dp[0] = 1;

        for(int i = 1;i<=target;i++){
            for(int e:nums){
                if (e<=i){ //考虑是要求一个排列数，那么假设某一个数处于最后一位，枚举所有可能处在最后一位的数
                    dp[i]+=dp[i-e];
                }
            }
        }
        return dp[target];
    }
};


/*
1143. 最长公共子序列
给定两个字符串 text1 和 text2，返回这两个字符串的最长 公共子序列 的长度。如果不存在 公共子序列 ，返回 0 。

一个字符串的 子序列 是指这样一个新的字符串：它是由原字符串在不改变字符的相对顺序的情况下删除某些字符
（也可以不删除任何字符）后组成的新字符串。

例如，"ace" 是 "abcde" 的子序列，但 "aec" 不是 "abcde" 的子序列。
两个字符串的 公共子序列 是这两个字符串所共同拥有的子序列。


*/
class Solution1143 {
public:
    int longestCommonSubsequence(string text1, string text2) {
        vector<vector<int>> dp(text1.size(),vector<int>(text2.size(),0));
        for(int i = 0;i<text1.size();i++){
            if (text1[i]==text2[0]){
                dp[i][0] = 1;
            }
            else{
                if (i>0)
                    dp[i][0] = dp[i-1][0];
            }
        }
        for(int i = 0;i<text2.size();i++){
            if (text1[0]==text2[i]){
                dp[0][i] = 1;
            }
            else{
                if (i>0)
                    dp[0][i] = dp[0][i-1];
            }
        }
        
        for(int i = 1;i<text1.size();i++){
            for(int j = 1;j<text2.size();j++){
                if (text1[i]==text2[j]){
                    dp[i][j] = dp[i-1][j-1]+1;
                }
                else{
                    dp[i][j] = max(dp[i-1][j],dp[i][j-1]);
                }
            }
        }
        return dp[text1.size()-1][text2.size()-1];
    }
};

/*
674. 最长连续递增序列
给定一个未经排序的整数数组，找到最长且 连续递增的子序列，并返回该序列的长度。

连续递增的子序列 可以由两个下标 l 和 r（l < r）确定，如果对于每个 l <= i < r，
都有 nums[i] < nums[i + 1] ，那么子序列 [nums[l], nums[l + 1], ..., nums[r - 1], nums[r]] 就是连续递增子序列。

*/
class Solution674 {
public:
    int findLengthOfLCIS(vector<int>& nums) {
        vector<int> dp(nums.size(),0);
        dp[0] = 1;
        for(int i = 1;i<nums.size();i++){
            if (nums[i]>nums[i-1]){
                dp[i] = dp[i-1]+1;
            }
            else{
                dp[i] = 1;
            }
        }
        int res = INT_MIN;
        for(int i = 0;i<dp.size();i++){
            if (dp[i]>res){
                res = dp[i];
            }
        }
        return res;
    }
};


/*
718. 最长重复子数组
给两个整数数组 A 和 B ，返回两个数组中公共的、长度最长的子数组的长度。
*/
class Solution718 {
public:
    int findLength(vector<int>& nums1, vector<int>& nums2) {
        //dp[i][j]表示nums1的以i结尾和nums2的以j结尾的最长公共子数组长度 注意跟最长公共子序列区分
        vector<vector<int>> dp(nums1.size(),vector<int>(nums2.size(),0));
        for(int i = 0;i<nums1.size();i++){
            if (nums1[i]==nums2[0]){
                dp[i][0] = 1;
            }
        }
        for(int i = 0;i<nums2.size();i++){
            if (nums1[0]==nums2[i]){
                dp[0][i] = 1;
            }
        }
        for(int i = 1;i<nums1.size();i++){
            for(int j = 1;j<nums2.size();j++){
                if (nums1[i]==nums2[j]){
                    dp[i][j] = dp[i-1][j-1]+1;
                }
            }
        }

        int res = INT_MIN;
        for(int i = 0;i<dp.size();i++){
            for(int j = 0;j<dp[i].size();j++){
                if (dp[i][j]>res){
                    res = dp[i][j];
                }
            }
        }
        return res;
    }
};


/*
516. 最长回文子序列
给你一个字符串 s ，找出其中最长的回文子序列，并返回该序列的长度。

子序列定义为：不改变剩余字符顺序的情况下，删除某些字符或者不删除任何字符形成的一个序列。
*/
class Solution516 {
public:
    int longestPalindromeSubseq(string s) {
        vector<vector<int>> dp(s.size(),vector<int>(s.size(),0));
        for(int i = 0;i<s.size();i++){
            dp[i][i] = 1;
        }
        for(int i = 0;i<s.size()-1;i++){
            if (s[i]==s[i+1]){
                dp[i][i+1] = 2;
            }
            else{
                dp[i][i+1] = 1;
            }
        }
        for(int len = 3;len<=s.size();len++){
            for(int i = 0;i<s.size()-(len-1);i++){
                if (s[i]==s[i+len-1]){
                    dp[i][i+len-1] = dp[i+1][i+len-2]+2;
                }
                else{
                    dp[i][i+len-1] = max(dp[i][i+len-2],dp[i+1][i+len-1]);
                }
            }
        }
        int res = INT_MIN;
        for(int i = 0;i<dp.size();i++){
            for(int j = 0;j<dp[i].size();j++){
                if (dp[i][j]>res){
                    res = dp[i][j];
                }
            }
        }
        return res;

    }
};

/*
392. 判断子序列
给定字符串 s 和 t ，判断 s 是否为 t 的子序列。

字符串的一个子序列是原始字符串删除一些（也可以不删除）字符而不改变剩余字符相对位置形成的新字符串。
（例如，"ace"是"abcde"的一个子序列，而"aec"不是）。

进阶：

如果有大量输入的 S，称作 S1, S2, ... , Sk 其中 k >= 10亿，你需要依次检查它们是否为 T 的子序列。
在这种情况下，你会怎样改变代码？

致谢：

特别感谢 @pbrother 添加此问题并且创建所有测试用例。
*/

class Solution392 {
public:
    bool solveMethod1(string s,string t){
        int ptr = 0;
        for(int i = 0;i<t.size();i++){
            if (t[i]==s[ptr]){
                ptr++;
            }
        }
        if (ptr==s.size()){
            return true;
        }
        else{
            return false;
        }
    }
    bool solveMethod2(string s,string t){
        if (t.empty() && !s.empty()){
            return 0;
        }
        if (s.empty()){
            return 1;
        }
        vector<vector<int>> dp(s.size(),vector<int>(t.size(),0));
        //dp[i][j]表示s[0,i]和t[0,j]的最长公共子序列
        for(int i = 0;i<t.size();i++){
            if (s[0]==t[i]){
                dp[0][i] = 1;
            }
            else{
                if (i>0){
                    dp[0][i] = dp[0][i-1];
                }
            }
        }
        for(int i = 0;i<s.size();i++){
            if (s[i]==t[0]){
                dp[i][0] = 1;
            }
            else{
                if (i>0){
                    dp[i][0] = dp[i-1][0];
                }
            }
        }

        for(int i = 1;i<s.size();i++){
            for(int j = 1;j<t.size();j++){
                if (s[i]==t[j]){
                    dp[i][j] = dp[i-1][j-1]+1;
                }
                else{
                    dp[i][j] = max(dp[i-1][j],dp[i][j-1]);
                }
            }
        }
        if (dp[s.size()-1][t.size()-1]==s.size()){
            return true;
        }
        else{
            return false;
        }
    }
    //对于进阶的思考题，可以采用空间换时间的做法，先扫一遍t，然后把t中的每个字符所处的位置
    //映射到链表中，然后每个字符串S都能以length(S)的复杂度去判断了（前提是字符分布均匀）
    bool isSubsequence(string s, string t) {
        return solveMethod2(s,t);
    }
};


/*
583. 两个字符串的删除操作
给定两个单词 word1 和 word2，找到使得 word1 和 word2 相同所需的最小步数，每步可以删除任意一个字符串中的一个字符。
*/
class Solution583 {
public:
    int minDistance(string word1, string word2) {
        string s = word1;
        string t = word2;
        vector<vector<int>> dp(s.size(),vector<int>(t.size(),0));
        //dp[i][j]表示s[0,i]和t[0,j]的最长公共子序列
        for(int i = 0;i<t.size();i++){
            if (s[0]==t[i]){
                dp[0][i] = 1;
            }
            else{
                if (i>0){
                    dp[0][i] = dp[0][i-1];
                }
            }
        }
        for(int i = 0;i<s.size();i++){
            if (s[i]==t[0]){
                dp[i][0] = 1;
            }
            else{
                if (i>0){
                    dp[i][0] = dp[i-1][0];
                }
            }
        }

        for(int i = 1;i<s.size();i++){
            for(int j = 1;j<t.size();j++){
                if (s[i]==t[j]){
                    dp[i][j] = dp[i-1][j-1]+1;
                }
                else{
                    dp[i][j] = max(dp[i-1][j],dp[i][j-1]);
                }
            }
        }
        int LCS = dp[s.size()-1][t.size()-1];
        //关键是如何把原问题转化到最长公共子序列问题上
        return s.size()-LCS+t.size()-LCS;
    }
};


/*
72. 编辑距离
给你两个单词 word1 和 word2，请你计算出将 word1 转换成 word2 所使用的最少操作数 。

你可以对一个单词进行如下三种操作：

插入一个字符
删除一个字符
替换一个字符
*/

class Solution72 {
public:
    int minDistance(string word1, string word2) {
        if (word1.empty() || word2.empty()){
            return abs((int)word1.size()-(int)word2.size());
        }
        vector<vector<int>> dp(word1.size(),vector<int>(word2.size(),0));
        //dp[i][j]表示word1[0,i]和word2[0,j]的最少操作数
        if(word1[0]==word2[0]){
            dp[0][0] = 0;
        }
        else{
            dp[0][0] = 1;
        }

        for(int i = 1;i<word2.size();i++){
            if (word2[i]==word1[0]){ 
                //这里的初始化一定要注意，等于的情况时直接赋值，不应该是dp[0][i] = dp[0][i-1]+1
                dp[0][i] = i; //表示直接把他前边的都删掉
            }
            else{
                dp[0][i] = dp[0][i-1]+1;
            }
        }
        for(int i = 1;i<word1.size();i++){
            if (word1[i]==word2[0]){
                dp[i][0] = i;
            }
            else{
                dp[i][0] = dp[i-1][0]+1;
            }
        }
        for(int i = 1;i<word1.size();i++){
            for(int j = 1;j<word2.size();j++){
                if (word1[i]==word2[j]){
                    //dp[i][j] = dp[i-1][j-1]; //这里的递推式一定要注意，容易出错
                    dp[i][j] = min(min(dp[i-1][j]+1,dp[i][j-1]+1),dp[i-1][j-1]);
                    //包括插入一个字符 删除一个字符 和替换一个字符
                }
                else{
                    dp[i][j] = min(min(dp[i-1][j],dp[i][j-1]),dp[i-1][j-1])+1;
                }
            }
        }
        return dp[word1.size()-1][word2.size()-1];
    }
};
