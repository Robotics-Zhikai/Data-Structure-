#pragma once
#include "main.h"

/*
494. Ŀ���
����һ���Ǹ��������飬a1, a2, ..., an, ��һ��Ŀ������S������������������ + �� -��
���������е�����һ���������㶼���Դ� + �� -��ѡ��һ�����������ǰ�档

���ؿ���ʹ���������ΪĿ���� S ��������ӷ��ŵķ�������

https://leetcode-cn.com/problems/target-sum/solution/494-mu-biao-he-01bei-bao-xiang-jie-by-ca-1kt5/
*/
class Solution494 {
public:
	int findTargetSumWaysDP1(vector<int>& nums, int S)
	{
		const int n = nums.size();
		int sum = accumulate(nums.begin(), nums.end(), 0);

		if (S>sum) //ȫ������������SС ��ô�Ͳ��ܱ�ʾ
			return 0; //������׶�������������

		//int dp[n][2 * sum + 1]; //dp[i][j]��ʾ[0,i]��������j-sum�ж����ַ���ѡȡ����
		//memset(dp, 0, sizeof(dp)); //��� ����������������������
		//������vs�汾�͵�ԭ����vs2015�в��ܶ�̬�������飬ֻ�����ڱ����ھ�֪�������С�ſ���

		vector<vector<int>> dp(n, vector<int>(2 * sum + 1, 0));

		if (nums[0] == 0) //�������׳������������� ������ȷ���ǳ�ʼ����
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
					first = dp[i - 1][j - nums[i]]; //��ǰ��ֵ���ż�Ϊ+����ô���ַ���
				}
				if (j + nums[i]<2 * sum + 1)
				{
					second = dp[i - 1][j + nums[i]]; //��ǰ��ֵ���ż�Ϊ-����ô���ַ���
				}
				dp[i][j] = first + second; //���Ǻ��ĵĵ��Ʒ��� 
				//���Ǳ߽����ʱ��Ҫ���̫���ӣ����̫���Ӵ�����и��򵥸��ձ��ܴ�����������Ĵ��룡��������������
				//�ͱ����±�ע�͵�����δ��룬���Ǻܶ���������ǻ�����ȫ��ʵ���Ϻܼ򵥵��ϱ���ξͿ��Խ��
				// if (dp[i-1][j]!=0 && nums[i]!=0)
				// {
				//     dp[i][j] = 0;//˵��ǰ�ߵľ������� û��Ҫ���ϻ��ȥ�����������0������
				// }
				// else
				// {

				// }
			}
		}
		return S + sum<2 * sum + 1 ? dp[n - 1][S + sum] : 0;
		//һ��Ҫע�⣡������Ӧ���������ֵ����Ӧ���������һ��ֵ ��Ϊ���е����ֶ���Ҫ�ӷ��ţ�������ĳ�����ֲ��õ����
		// int result = 0;
		// for(int i = 0;i<n;i++)
		// {
		//     if (S+sum<2*sum+1&&dp[i][S+sum]>result)
		//         result = dp[i][S+sum];
		// }
		// return result;
	}
	int findTargetSumWaysDP2(vector<int>& nums, int S)  //�����ռ��Ż��İ汾
	{
		const int n = nums.size();
		int sum = accumulate(nums.begin(), nums.end(), 0);

		if (S>sum) //ȫ������������SС ��ô�Ͳ��ܱ�ʾ
			return 0; //������׶�������������

		// int dp[n][2*sum+1]; //dp[i][j]��ʾ[0,i]��������j-sum�ж����ַ���ѡȡ����
		// memset(dp,0,sizeof(dp)); //��� ����������������������

		//int dp_cur[2 * sum + 1]; //���±ߴ�����Կ���dpiֻ��dpi-1�й�
		//int dp_last[2 * sum + 1];
		//memset(dp_cur, 0, sizeof(dp_cur));
		//memset(dp_last, 0, sizeof(dp_last));
		vector<int> dp_cur(2 * sum + 1, 0);
		vector<int> dp_last(2 * sum + 1, 0);

		auto curdp = dp_cur.begin(); //�����������������������׵�ַ��dp_cur dp_last���޷�������
		auto lastdp = dp_last.begin();

		if (nums[0] == 0) //�������׳������������� ������ȷ���ǳ�ʼ����
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
				//dp[i][j] = first+second; //���Ǻ��ĵĵ��Ʒ��� 
				curdp[j] = first + second;
			}
			swap(lastdp, curdp); //����ָ����������ݣ���������ٶ� 
								 //����������ǰ��dp�ͻ�����last
		}
		return S + sum<2 * sum + 1 ? lastdp[S + sum] : 0;
	}
	int findTargetSumWaysDP3(vector<int>& nums, int S)
	{
		//�������ת������׼��01��������
		//SumΪ������֮�� AΪ����Ϊ+�����ĺ� BΪ����Ϊ-�����ĺ� A+B=Sum A-B=S 
		//�����õ�2A=S+Sum A=(S+Sum)/2 ��S��Sum ������֪�ģ����A��һ���̶�����
		//Ҳ����˵����Ϊ+�����ĺ�Ӧ�õ���Aʱ���ҵ���һ�ֽ�
		//����Ϊ���е�������������Ϊ���������Է���λ+�����ĺͲ�Ӧ����С������˵�(S+Sum)/2��С��ʱҲ�����ҵ���
		const int n = nums.size();
		int sum = accumulate(nums.begin(), nums.end(), 0);
		if (sum<S || (S + sum) % 2 != 0)
			return 0;

		int A = (S + sum) / 2; //DP3ʱ���ٵ���Ҫԭ����һ��ʼ�Ͱ������ģ��������

		//int dp[n][A + 1]; //dp[i][j]��ʾ[0,i]������ѡ�е����ĺ͵���j���ж����ַ���
		//memset(dp, 0, sizeof(dp));
		vector<vector<int>> dp(n, vector<int>(A + 1, 0));

		if (nums[0]<A + 1)
			dp[0][nums[0]] = 1;
		dp[0][0] += 1;
		//ֻ���ǵ�һ���������������ʱ����Ϊ0�ķ������ǲ�ѡ����1������
		//ֻ���ǵ�һ������������Ϊ0ʱ����Ϊ0�ķ�����������ѡ�Ͳ�ѡ 
		for (int i = 1; i<n; i++)
		{
			for (int j = 0; j <= A; j++)
			{
				dp[i][j] = j - nums[i] >= 0 ? dp[i - 1][j - nums[i]] : 0; //ѡ��ǰֵʱ����ô�෽��
				dp[i][j] += dp[i - 1][j]; //��ѡ��ǰֵʱ����ô�෽�� ���߼����������ܵķ�������
				//������Ե�����1ά���� �ȽϺõ����Ͳ�����
			}
		}
		return dp[n - 1][A]; //����ԭ�����Ѿ�ת���ˣ�������S�޹��ˣ�����������
	}
	//Ҳ��һ��01�������⣬����01���������˼·ȥ�룬���ǲ�ͬ��������൱�����е���Ʒ����װ��
	//��˲��ܰ�dp[][]�����ǲ���ʽ��ֻ�ܿ�����ʽ
	//�����ö�̬�滮������������������
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
474. һ����
����һ���������ַ������� strs ���������� m �� n ��

�����ҳ������� strs ������Ӽ��Ĵ�С�����Ӽ��� ��� �� m �� 0 �� n �� 1 ��

��� x ������Ԫ��Ҳ�� y ��Ԫ�أ����� x �Ǽ��� y �� �Ӽ� ��

https://leetcode-cn.com/problems/ones-and-zeroes/solution/dong-tai-gui-hua-zhuan-huan-wei-0-1-bei-bao-wen-ti/
*/
class Solution474 {
public:

	int findMaxFormDP1(vector<string>& strs, int m, int n)
	{
		vector<vector<int>> dp2DLast(m + 1, vector<int>(n + 1, 0));
		vector<vector<int>> dp2D(m + 1, vector<int>(n + 1, 0)); //[0,m] [0,n]
		// vector<vector<vector<int>>> dp(strs.size()+1,dp2D); //��

		//Ū����ά����������Щ dp[i][j][k] ��һά����Ʒ��ѡȡ��Χ��[0,i)���ڶ�ά�������j��0������ά�������k��1
		//Ȼ�󾭹�����������i+1��dp����i��dp�йأ������Ļ��Ϳ�����������ά����Last��Current������
		//����ֱ�ӾͰ��ڴ�������100MB������10MB ����ʱ����480ms������272ms

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
					if (j_count0<0 || k_count1<0) //��ʱ�϶�װ�����µ��ַ���
					//dp[i][j][k] = dp[i-1][j][k];  
					//Ϊ�˸��õĶԱ� ��û�о����������齵ά�ı������� �±�һ�кͱ�����ʵ�ǵȼ۵�
						dp2D[j][k] = dp2DLast[j][k];
					else
						//dp[i][j][k] = max(dp[i-1][j][k],dp[i-1][j_count0][k_count1]+1);//01��������ĺ���
						dp2D[j][k] = max(dp2DLast[j][k], dp2DLast[j_count0][k_count1] + 1);
				}
			}
			dp2DLast = dp2D; //��һ�������Ĺ���
		}
		return dp2D[m][n];
	}

	int findMaxFormDP2(vector<string>& strs, int m, int n)//�����εĸ��ݵ���ʽ���Ż�
	{
		//��Ȼ��findMaxFormDP1������Ӧ��ѹ���������ξ�������vector<vector<int>>����ǰһ���ͺ�һ��ֵ
		//ʵ���Ͽ���ֻ��һ��vector<vector<int>>���Ӻ���ǰ���� 
		//��һ��vector<vector<int>>���ٶ�û�б���������ֻ����ռ�пռ��С��
		vector<vector<int>> dp2D(m+1,vector<int>(n+1,0)); //[0,m] [0,n]

	//	int dp2D[m + 1][n + 1]; //��̬����һ����ά����
	//	memset(dp2D, 0, sizeof(dp2D)); //����dp2Dָ�뿪ʼ��(m+1)*(n+1)�ֽ��ڴ�����ݸ�ֵΪ0
	//����������vector<vector<int>> ʱֱ����268ms 9.5MB ������60ms 8.5MB �ٶ����˱�������

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
					if (j_count0<0 || k_count1<0) //��ʱ�϶�װ�����µ��ַ���
												  //dp2D[j][k] = dp2DLast[j][k]; 
						dp2D[j][k] = dp2D[j][k];
					else
						//dp2D[j][k] = max(dp2DLast[j][k],dp2DLast[j_count0][k_count1]+1);
						dp2D[j][k] = max(dp2D[j][k], dp2D[j_count0][k_count1] + 1);
					//�����ǴӺ���ǰ����������С��jk��dp2D��û�и���
				}
			}
			//dp2DLast = dp2D; //��һ�������Ĺ���
		}
		return dp2D[m][n];
	}

	//����һ��01�������� �ַ��������е�ÿһ���ַ����Ƿ����
	//�ͻ�����01��������������Ǳ���������Լ����������˳�ʼ���������ά
	//�����ñ�����⣬ö�����п����ԣ����Ӷ���c*2^n��n=strs.size() 
	int findMaxForm(vector<string>& strs, int m, int n) {
		//return findMaxFormDP1(strs,m,n);
		return findMaxFormDP2(strs, m, n); //�������������������ڵķ�����һ���ģ�����ʵ�ַ�ʽ������ DP2����Ч
	}
};


/*
64. ��С·����
����һ�������Ǹ������� m x n ���� grid �����ҳ�һ�������Ͻǵ����½ǵ�·����ʹ��·���ϵ������ܺ�Ϊ��С��

˵����ÿ��ֻ�����»��������ƶ�һ����
*/
//�����ֻ�����»��������ƶ�һ�� ��һ���Ƚ����ԵĶ�̬�滮 ���ǵ��������Ҷ����ƶ�ʱ���Ͳ��ÿ��ɶ�̬�滮�� ������̰��
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
		//ʵ���Ͽ��Բ�Ҫ���dp��ֱ����grid���޸�ֵ ��Ϊ����˳��Ļ�ԭ�����ֵֻ��Ҫ��һ��
		//�����Ϳ��԰ѿռ临�ӶȽ���1
		dp[0][0] = grid[0][0];
		for (int j = 1; j<n; j++)
		{
			int col = j;
			int row = 0;
			while (col != -1 && row != m) //������whileѭ�����ظ������ݣ����Է�װ��һ��������
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
96. ��ͬ�Ķ���������
����һ������ n������ 1 ... n Ϊ�ڵ���ɵĶ����������ж����֣�
�Ѷ��е�
*/
class Solution96 {
public:
	//��DP�ķ���һ��ͨ�� 0ms 6MB 100% 63.4%
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
5. ������Ӵ�
����һ���ַ��� s���ҵ� s ����Ļ����Ӵ���
*/
class Solution5 {
public:
	bool isbackStr(const string& str) //�ж��Ƿ��ǻ��Ĵ�
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
	string longestPalindromeDP(string s) //�ö�̬�滮�ķ���
	{
		vector<vector<bool>> dp(s.size(), vector<bool>(s.size(), 0));//ǰ�պ�գ�����ִ��Ƿ��ǻ���
		if (s.size() == 1)
			return s;
		for (int i = 0; i<s.size(); i++)
			dp[i][i] = 1;  //ÿ��һ�����ȵ��ַ����϶��ǻ����ַ���
		for (int i = 0; i <= s.size() - 2; i++)
		{
			dp[i][i + 1] = isbackStr(s.substr(i, 2)); //���ó���Ϊ2���ִ��ı���¼
				//��Ҫע�����substr����������stl��ߵ�ǰ�պ󿪵ģ����������Ϊ����λ�úͳ��ȣ���������
				// cout<<s.substr(i,2)<<" "<<dp[i][i+1]<<endl;
		}

		for (int length = 3; length <= s.size(); length++)
		{
			for (int i = 0; i <= s.size() - length; i++)
			{
				// if (isbackStr(s.substr(i,i+length))) //�����ô��Ļ��ͳ��˱���ö��
				// dp[i][i+1] = 1; 
				dp[i][i + length - 1] = (s[i] == s[i + length - 1]) && (dp[i + 1][i + length - 1 - 1]); //����Ҫ�ĵ���ʽ
																										//�ؼ���Ҫ�뵽�������ʽ
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

	string CenterSpan(const string & s, int leftindex, int rightindex) //ǰ�պ��
		//������ɢ�ķ�����һ�����Լ�϶Ϊ���ģ�һ����������Ϊ����
		//�Ƚ���д����������������������� ��Ҫ�ܹ��뵽�Լ�϶Ϊ������չ��������Ϊ������չ
		//�������ʵ��������м�ֵ���Լ��ٳ�ʼ���Ĳ��� ������������˼��
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
					j--; //��̽�Ե�̽��ȥ������������˾ͷ�����
					break;
				}
			}
			if (!((leftindex + j) != s.size() && (leftindex - j) != -1)) //����Ҳ�ǲ�̫����ע�⵽�ĵ�
				j--;
			return s.substr(leftindex - j, 2 * j + 1);
		}
		else if (leftindex<rightindex)
		{
			if (s[leftindex] != s[rightindex]) //����Ҳ���״��
				return string("");  //���ü�϶ʱ�������϶���˵����ֲ���ȣ�������Ȼ�ľͲ��ǻ��Ĵ�
			if (leftindex == 0 || rightindex == s.size() - 1) //�����ڱ߽�ʱ������չ
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
	string longestPalindromeMidSpread(string s) //��������ɢ�ķ�����Ҳ����һ��ʼ5�������뵽�ķ���
												//�������ڴ���߽�ʱ���ô�����û�м���д��ת��ȥд��̬�滮��
												//���Ѽ�϶Ҳ���ǽ���������չʱ�ͺô�����
	{

		vector<string> vecHitstr(s.size(), " ");  //ǡ���Ǹ�����λ�õ���չ
		vector<string> vecMidstr(s.size() - 1, " "); //��϶��չ

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

	//��̬�滮��Ҫö�����б߽磬��N^2��
	//������ɢ������Ҫö��N^2�ı߽磬��2N��
	//��Ȼ���߶���N^2�ĸ��Ӷȣ�������Ȼ���߸�ʵ��Щ
	//��̬�滮�������˲��ǻ��Ĵ��Ĳ��֣���������ɢ��һ�����ǻ��Ĵ���Ҳû���� ������Ȼ�ĺ���ʱ�����
	}

	void test()
	{
		longestPalindrome(string("cbbd"));
	}
};


/*
��ָ Offer 14- II. ������ II
����һ������Ϊ n �����ӣ�������Ӽ����������ȵ� m �Σ�m��n����������n>1����m>1����
ÿ�����ӵĳ��ȼ�Ϊ k[0],k[1]...k[m - 1] ������ k[0]*k[1]*...*k[m - 1] ���ܵ����˻��Ƕ��٣�
���磬�����ӵĳ�����8ʱ�����ǰ������ɳ��ȷֱ�Ϊ2��3��3�����Σ���ʱ�õ������˻���18��

����Ҫȡģ 1e9+7��1000000007����������ʼ���Ϊ��1000000008���뷵�� 1��
*/

class Solution14_II {
public:

	/*
	int cuttingRope(int n) {
	//����ξ��ü�����I�еķ������㣬�����м�ļ�������оͻ�Խ�� ��������ֵ���޵�����²��������ַ���
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

	for (long In = 2; In <= n; In++) //ʱ�临�Ӷ���N^2 �ռ临�Ӷ���N ������ķ����ܽ���N  ���ǹ����������벻����
	{
	long maxthis = 0;
	for (long i = 1; i <= In - 1; i++)
	{
	long big = max(max(Tn[i] * (In - i), i*(In - i)), Tn[i] * Tn[In - i]);//ע������ж����׶�
	//���������׳���Խ��
	//��̬�滮�ĺ���
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

	long bigmodc(long x, long a, long c) //����������
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
		����֪ʶ�������Ӿ����ȷ�ʱ�õ��ĳ˻���� �پ����Ƶ����ӵȷֳ�ÿ�γ���Ϊ3ʱ�����
		�����ⳤ�ȵ����ӣ���3ȡģ����0 1 2
		��0ʱֱ�Ӽ������
		��1ʱ���һ��3�ټ���1Ϊ2+2
		��2ʱ����֣�ֱ�ӳ�2����
		����ʵ����һ����ʽ�Ķ�̬�滮��ÿ�ε�����ֵ��ǰһ�ε�����ֵ���Ƶõ�
		�����ǳ���ʱ��
		(x*y)%c = ((x%c)*(y%c))%c �������ʽ�ӿ�����ô�����ģ
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
��ָ Offer 14- I. ������
����һ������Ϊ n �����ӣ�������Ӽ����������ȵ� m �Σ�m��n����������n>1����m>1����
ÿ�����ӵĳ��ȼ�Ϊ k[0],k[1]...k[m-1] ������ k[0]*k[1]*...*k[m-1] ���ܵ����˻��Ƕ��٣�
���磬�����ӵĳ�����8ʱ�����ǰ������ɳ��ȷֱ�Ϊ2��3��3�����Σ���ʱ�õ������˻���18��
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

		for (int In = 2; In <= n; In++) //ʱ�临�Ӷ���N^2 �ռ临�Ӷ���N ������ķ����ܽ���N  ���ǹ����������벻����
		{
			int maxthis = 0;
			for (int i = 1; i <= In - 1; i++)
			{
				int big = max(max(Tn[i] * (In - i), i*(In - i)), Tn[i] * Tn[In - i]);//ע������ж����׶�
				//��̬�滮�ĺ���
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

/*
42. ����ˮ
���� n ���Ǹ�������ʾÿ�����Ϊ 1 �����ӵĸ߶�ͼ�����㰴�����е����ӣ�����֮���ܽӶ�����ˮ��

*/
//������ö�̬�滮�ȽϺ��룬����ʱ��Ҳ�����뵽 Ҳ��д

class Solution42 {
public:
    int DP(vector<int>& height) //����ȽϺ����Ҳ��д
    {
        if(height.empty())
            return 0;
        vector<int> LeftMax(height.size(),0); //leftmax[i]��ʾi��i��ߵ����ӵ����ֵ
        vector<int> RightMax(height.size(),0); //rightmax[i]��ʾi��i�ұߵ����ӵ����ֵ
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
    int Myself(vector<int>& height) //�����Ȼ���Լ�д�ģ��������׳����Ҵ�������ɨ�������Դ�˷�
    {
        if (height.empty())
            return 0;
        int Left = numeric_limits<int>::min();
        int Leftindex = -1;
        int sum = 0;
        int oldsum = 0;
        for(int i = 0;i<height.size();i++){ //�ȴ�������ɨ,��һ��̰��˼�룬�������ߵĵ���ʱ��֮ǰ���޹�
            if (height[i]<Left)
                sum+=Left-height[i];
            else{
                oldsum = sum;
                Left = height[i];
                Leftindex = i;
            }
        }
        int leftstroe = Leftindex; ///���leftindex�������һ����˵����LeftΪ�߶ȵ�left������װ�º��ʵ�ˮ���ͻ��˵�oldsum
        if (Leftindex!=height.size()-1){ //�ٴ�������ɨ
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
    int Twoptr(vector<int>& height) //˫ָ��ķ���
    {
        int ans = 0;
        int left = 0, right = height.size() - 1;
        int leftMax = 0, rightMax = 0;
        while (left < right) {
            leftMax = max(leftMax, height[left]); //�洢left��left��ߵ����ֵ
            rightMax = max(rightMax, height[right]); //�洢right��right�ұߵ����ֵ
            if (height[left] < height[right]) { //left�ұߵ�ʵ�����heightֵֻ�ܱ�height[right]����ǰrightmax���������� ����ʵ�Ͷ�̬�滮�����һ����һ����
                ans += leftMax - height[left]; //ÿ��ȷ����϶��Ľ���ˮ���� ÿ��iֻ�ܽ�min(leftmax,rightmax)-height[i]
                ++left;
            } else { //ͬ���ģ�right��ߵ�ʵ�����ֵֻ�ܱ�height[left]����ǰleftmax����������
                ans += rightMax - height[right];  //ÿ��ȷ����϶��Ľ���ˮ����
                --right;
            }
        }
        return ans;
        // ���ߣ�LeetCode-Solution
        // ���ӣ�https://leetcode-cn.com/problems/trapping-rain-water/solution/jie-yu-shui-by-leetcode-solution-tuvc/
        // ��Դ�����ۣ�LeetCode��
        // ����Ȩ���������С���ҵת������ϵ���߻����Ȩ������ҵת����ע��������
    }

    int trap(vector<int>& height) {
        // return DP(height); //����O(n)ʱ�临�Ӷȣ�O(n)�ռ临�Ӷ�
        // return Myself(height); //����O(n)ʱ�临�Ӷȣ�O��1���ռ临�Ӷ�
        return Twoptr(height); //����O(n)ʱ�临�Ӷȣ�O��1���ռ临�Ӷ�
    }
};



/*
��ָ Offer 46. �����ַ�����ַ���
����һ�����֣����ǰ������¹����������Ϊ�ַ�����0 ����� ��a�� ��1 ����� ��b����������11 ����� ��l����������25 ����� ��z����
һ�����ֿ����ж�����롣����ʵ��һ����������������һ�������ж����ֲ�ͬ�ķ��뷽����
*/

class SolutionOffer46 {
public:
    int translateNum(int num) {
        string numstr = to_string(num);
        vector<vector<int>> dp(numstr.size(),vector<int>(numstr.size(),1));
        //dp[i][j]��ʾ������[i,j]�ڵ�string�ж����ֲ�ͬ�ķ��뷽��
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
                dp[i][i+len-1] = dp[i][i+len-2]+((merge<=25&&merge!=self)?dp[i][i+len-3]:0); //merge!=self��06 6�����ȥ��
                //�¼�����ַ���ǰһ�������������ټ����¼�����ַ�����ǰһ�����������룬�ܵ������ľ����µ�dp
            }
        }
        //�ϱ�������for��ȫ���Ժϲ���Ȼ���ù�������ѿռ临�ӶȽ���O(1)
        return dp[0][numstr.size()-1];

    }
};

/*
300. �����������
����һ���������� nums ���ҵ�������ϸ���������еĳ��ȡ�

���������������������������У�ɾ������ɾ���������е�Ԫ�ض����ı�����Ԫ�ص�˳��
���磬[3,6,2,7] ������ [0,3,1,6,2,2,7] �������С�


*/
//��nlogn�Ľⷨ��ʱ��������ʱ�Ȳ���

class Solution300 {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> dp(nums.size(),0); //�������iλ��Ԫ�ص�iλ�ü�֮ǰԪ�ص���ϸ���������г��� 
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
198. ��ҽ���
����һ��רҵ��С͵���ƻ�͵���ؽֵķ��ݡ�ÿ�䷿�ڶ�����һ�����ֽ�
Ӱ����͵�Ե�Ψһ��Լ���ؾ������ڵķ���װ���໥��ͨ�ķ���ϵͳ������������ڵķ�����ͬһ���ϱ�С͵���룬ϵͳ���Զ�������

����һ������ÿ�����ݴ�Ž��ķǸ��������飬������ ����������װ�õ������ ��һҹ֮���ܹ�͵�Ե�����߽�

*/

class Solution198 {
public:
    int rob(vector<int>& nums) {
        vector<int> dp(nums.size(),0); //���Ϊi��i֮ǰ����߽��
        if (nums.size()==1)
            return nums[0];
        dp[0] = nums[0];
        dp[1] = max(nums[0],nums[1]);
        for(int i = 2;i<nums.size();i++){
            dp[i] = max(dp[i-2]+nums[i],dp[i-1]);
            //Ҫ��͵��i�ң������dp[i-2]+nums[i]��Ҫ����͵��i�ң������dp[i-1]
            //�����ϱߵĵݹ�ʽ�����԰ѿռ临�Ӷ��Ż���O(1).�����ʵ�ַ���������������index��ÿ��ѭ��(index++)%3
        }
        return dp[nums.size()-1];
    }
	int rob210712(vector<int>& nums){
		vector<int> dp(nums.size(),0); //[0,i]�����䷶Χ��͵�������Ŀ
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
213. ��ҽ��� II
����һ��רҵ��С͵���ƻ�͵���ؽֵķ��ݣ�ÿ�䷿�ڶ�����һ�����ֽ�
����ط����еķ��ݶ� Χ��һȦ ������ζ�ŵ�һ�����ݺ����һ�������ǽ����ŵġ�
ͬʱ�����ڵķ���װ���໥��ͨ�ķ���ϵͳ������������ڵķ�����ͬһ���ϱ�С͵���룬ϵͳ���Զ����� ��

����һ������ÿ�����ݴ�Ž��ķǸ��������飬������ �ڲ���������װ�õ������ �������ܹ�͵�Ե�����߽�

*/
class Solution213 {
public:
   	int rob210712(vector<int>& nums){ //ֱ�ӵ��ô�ҽ���I�ķ�������
           //�����Ż��ɳ����Ŀռ临�Ӷ�
		if (nums.empty()){
			return 0;
		}
		vector<int> dp(nums.size(),0); //[0,i]�����䷶Χ��͵�������Ŀ
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
        if(nums.size()==1)//�������©�� 
            return nums[0];
		vector<int> nums1;
		vector<int> nums2;
        for(int i = 0;i<nums.size()-1;i++){
			nums1.push_back(nums[i]);
		}
		for(int i = 1;i<nums.size();i++){
			nums2.push_back(nums[i]);
		}
		return max(rob210712(nums1),rob210712(nums2)); //��͵���һ��������߲�͵��һ�����䣬Ȼ��ȡ���ֵ����
    }
};

/*
337. ��ҽ��� III
���ϴδ����һ���ֵ�֮���һȦ���ݺ�С͵�ַ�����һ���µĿ����Եĵ�����
�������ֻ��һ����ڣ����ǳ�֮Ϊ�������� ���ˡ�����֮�⣬ÿ����������ֻ��һ��������������֮������
һ�����֮�󣬴�����С͵��ʶ��������ط������з��ݵ�����������һ�ö��������� 
�������ֱ�������ķ�����ͬһ�����ϱ���٣����ݽ��Զ�������

�����ڲ���������������£�С͵һ���ܹ���ȡ����߽�
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
		//dp[root] û��root��ֻ�������ӽڵ㣻��root��
		dp[root] = 
				max(dp[root->left]+dp[root->right],
				root->val+
				dp[root->left!=nullptr?root->left->left:nullptr]+dp[root->left!=nullptr?root->left->right:nullptr]+
				dp[root->right!=nullptr?root->right->left:nullptr]+dp[root->right!=nullptr?root->right->right:nullptr]);
				//�������ʽ���ǱȽ������뵽��
	}
    int rob(TreeNode* root) {
		//n�Ŀռ临�ӶȺ�n��ʱ�临�Ӷ� �����hashmap�ͺ������
		map<TreeNode*,int> dp;
		dp[nullptr] = 0;
		DFS(root,dp);
		return dp[root];
    }
};


/*
62. ��ͬ·��
һ��������λ��һ�� m x n ��������Ͻ� ����ʼ������ͼ�б��Ϊ ��Start�� ����

������ÿ��ֻ�����»��������ƶ�һ������������ͼ�ﵽ��������½ǣ�����ͼ�б��Ϊ ��Finish�� ����

���ܹ��ж�������ͬ��·����

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
    int solveMethod1(int m, int n){ //��DFS�ķ�������Ҫ�����ظ��ģ��ܵ�Ч���Դ��ģ��ֱ�ӳ�ʱ
        vector<vector<int>> isvist(m,vector<int>(n,0));
		count = 0;
		DFS(isvist,0,0);
		return count;
    }

    int solveMethod2(int m,int n){
        //�ö�̬�滮�ķ������Ͳ���ʱ��
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
    //�������������ѧ�ķ�ʽ�����Ǹ�����ѧ

    int uniquePaths(int m, int n) {
        return solveMethod2(m,n);
    }
};


/*
152. �˻����������
����һ���������� nums �������ҳ������г˻��������������飨�������������ٰ���һ�����֣��������ظ�����������Ӧ�ĳ˻���
*/

class Solution152 {
public:
    int solveMethod1(vector<int>& nums){
        //������dp��ֱ�ӳ�ʱ�ˣ���ʵ���Ǹ�����
        vector<vector<int>> dp(nums.size(),vector<int>(nums.size(),0)); 
        //dp[i][j]��ʾ[i,j]�����ڵ�����������ĳ˻�
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
        //��һ��д��ʱ��ֻŪ��һ��dp��Ȼ�����ǲ����ģ���Ϊ���ǳ˻��Ļ����ܸ���������������MAX��MIN����Ҫ��¼
		//������dp����Ū��һά�ģ�Ҳ���ǳ����һά��
        vector<int> dpMAX(nums.size(),0); //�������������飬��˿���dpMAX[i]�ǰ���nums[i]�������������ֵ
        vector<int> dpMIN(nums.size(),0);  //�������������飬��˿���dpMIN[i]�ǰ���nums[i]������������Сֵ
        dpMAX[0] = nums[0];
        for (int i = 1;i<nums.size();i++){
            dpMAX[i] = max(max(dpMAX[i-1]*nums[i],dpMIN[i-1]*nums[i]),nums[i]);
            dpMIN[i] = min(min(dpMAX[i-1]*nums[i],dpMIN[i-1]*nums[i]),nums[i]); //���Ը������ʽ���Ż��������ռ临�Ӷ�
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
221. ���������
��һ���� '0' �� '1' ��ɵĶ�ά�����ڣ��ҵ�ֻ���� '1' ����������Σ��������������

*/

class Solution221 {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        //�ö�̬�滮�ķ�������ʱ�临�Ӷ���n*n 
        if (matrix.empty()){
            return 0;
        }
        int m = matrix.size();
        int n = matrix[0].size();
        vector<vector<int>> dp(m,vector<int>(n,0)); //dp�洢���Ǳ߳���dp[i][j]��ʾ��i,jΪ���½ǵ����߳�
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
					//��ҪӦ��������ʽ�ӣ�����Ŀռ临�Ӷȿ��Խ�һ���Ż�
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
        return MAX*MAX; //���ص�Ӧ�������
    }
};



/*
238. ��������������ĳ˻�
����һ������Ϊ n ���������� nums������ n > 1������������� output ��
���� output[i] ���� nums �г� nums[i] ֮�������Ԫ�صĳ˻���

*/

class Solution238 {
public:
    vector<int> solveMethod1(vector<int>& nums){
        //n��ʱ�临�Ӷȣ�n�Ŀռ临�Ӷ�
        vector<int> L(nums.size(),1);
        vector<int> R(nums.size(),1);
        for(int i = 1;i<nums.size();i++){
            L[i] = L[i-1]*nums[i-1]; //�е���̬�滮��
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
        //������Ŀ�еĶ��壬n��ʱ�临�Ӷȣ�1�Ŀռ临�Ӷ�
        //ʵ���Ͼ����Ȱ�û�о����ռ��Ż��Ĵ���д������Ȼ���ܲ��ܿռ��Ż�һ��
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
279. ��ȫƽ����
���������� n���ҵ����ɸ���ȫƽ���������� 1, 4, 9, 16, ...��ʹ�����ǵĺ͵��� n��
����Ҫ����ɺ͵���ȫƽ�����ĸ������١�

����һ������ n �����غ�Ϊ n ����ȫƽ������ �������� ��

��ȫƽ���� ��һ����������ֵ������һ��������ƽ�������仰˵����ֵ����һ�������Գ˵Ļ���
���磬1��4��9 �� 16 ������ȫƽ�������� 3 �� 11 ���ǡ�

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
        //N^2��ʱ�临�Ӷ�
        vector<int> dp(n+1,0);
        dp[1] = 1;
        for (int i = 2;i<=n;i++){
            if (isTwiceNum(i)){
                dp[i] = 1;
            }
            else{
                int MIN = INT_MAX;
                for(int j = 1;j<i/2+1;j++){ //������������ֱ�ӳ�ʱ��
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
        //n^1.5��ʱ�临�Ӷ�
        vector<int> dp(n+1,0);
        dp[1] = 1;
        for (int i = 2;i<=n;i++){
            if (isTwiceNum(i)){
                dp[i] = 1;
            }
            else{
                int MIN = INT_MAX;
                for(int j = 1;j*j<i;j++){ //�����Ϊ��Сֵ�϶�������ȫ����ȥ��
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
        //Ҳ������BFS�������Ȳ���������ۼ�ֵ�ľ�����������
        //�����Ǵ�ʱ�仹�Ǵӿռ临�ӶȻ��ǴӴ����д�ĸ��ӳ̶�����ڶ�̬�滮����û��һ˿����
        //�ص���Ҫ��ͨ��������γ���BFS�ġ���������ʵ����һ���������ļ�֦����
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
    int numSquares(int n) {
        return solveMethod3(n);
        return solveMethod2(n);
    }
};


/*
309. ���������Ʊʱ�����䶳��
����һ���������飬���е� i ��Ԫ�ش����˵� i ��Ĺ�Ʊ�۸� ��?

���һ���㷨����������������������Լ�������£�����Ծ����ܵ���ɸ���Ľ��ף��������һ֧��Ʊ��:

�㲻��ͬʱ�����ʽ��ף���������ٴι���ǰ���۵�֮ǰ�Ĺ�Ʊ����
������Ʊ�����޷��ڵڶ��������Ʊ (���䶳��Ϊ 1 ��)��

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
            DFS(prices,index+1,sum); //����������Ҳ����ʲô������

            sellstorage = stateSell; //ע�Ᵽ�����
            buystorage = stateBought;

            sum+=prices[index]; //����
            stateSell = index;
            stateBought = 0;
            DFS(prices,index+1,sum);
            sum-=prices[index];

            stateSell = sellstorage;
            stateBought = buystorage;
        }
        else{
            if (stateSell!=-1 && index-stateSell==1){
                DFS(prices,index+1,sum); //�䶳��
            }
            else{
                DFS(prices,index+1,sum);//�������룬Ҳ����ʲô������

                sellstorage = stateSell;
                buystorage = stateBought;

                sum-=prices[index]; //����
                stateBought = 1;
                DFS(prices,index+1,sum);
                sum+=prices[index];

                stateSell = sellstorage;
                stateBought = buystorage;
            }
        }
    }
    int solveMethod1(vector<int>& prices){ //��DFSֱ�ӳ�ʱ�ˣ���������ȷ��
        int sum = 0;
        DFS(prices,0,sum);
        return MAX;
    }
    int solveMethod2(vector<int>& prices){
        //dp[i][0] ��i���������й�Ʊ����ʱ���������
        //dp[i][1] ��i������󲻳��й�Ʊ�ҽ����䶳�ڣ���ʱ���������
        //dp[i][2] ��i������󲻳��й�Ʊ��û�н����䶳�ڣ���ʱ���������  ��Ҫ���������������岻����
        //dp[i][0] = max(dp[i-1][0],dp[i-1][2]-prices[i]) �����������г����ͺ���Ȼ�ܵõ�����������ʽ��
        //dp[i][1] = dp[i-1][0]+prices[i]
        //dp[i][2] = max(dp[i-1][2],dp[i-1][1])
        //dp[0][0] = 1
        //dp[0][1] = INT_MIN
        //dp[0][2] = INT_MIN
        vector<vector<int>> dp(prices.size(),vector<int>(3,INT_MIN));
        dp[0][0] = -prices[0];
        dp[0][2] = 0;
        //�������dp[0][1]�����
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
    int maxProfit(vector<int>& prices) {
        return solveMethod2(prices);
    }
};


/*
647. �����Ӵ�
����һ���ַ�������������Ǽ�������ַ������ж��ٸ������Ӵ���

���в�ͬ��ʼλ�û����λ�õ��Ӵ�����ʹ������ͬ���ַ���ɣ�Ҳ�ᱻ������ͬ���Ӵ���
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
		//�����Ӵ�Ҫ����������Ҫ����ż����Ȼ������Ҫ����һ��Ԫ�أ�Ҫ����������Ԫ��
		//���ö�����е����ĺ�˫���ĵĻ����Ӵ�
        //�ռ临�Ӷ�Ϊ1 ʱ�临�Ӷ�Ϊn^2
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
        //�ö�̬�滮�ķ�������ʱ�临�ӶȺͿռ临�ӶȾ�Ϊn^2
		vector<vector<bool>> dp(s.size(),vector<bool>(s.size(),0)); //dp[i][j]��ʾ[i,j]�Ӵ��Ƿ��ǻ����Ӵ�
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
	C���� ��̬�滮 dp[j]��ʾ��jλ�õ���ǰ���������ַ�λ��i�Ƿ�Ϊ�����ַ���

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

	//��һ�ֶ�̬�滮�ķ���  û̫����������������
	*/

    int countSubstrings(string s){
        return solveMethod2(s);
    }
};


/*
322. ��Ǯ�һ�
������ͬ����Ӳ�� coins ��һ���ܽ�� amount��
��дһ��������������Դճ��ܽ����������ٵ�Ӳ�Ҹ�����
���û���κ�һ��Ӳ�����������ܽ����� -1��

�������Ϊÿ��Ӳ�ҵ����������޵ġ�

*/

class Solution322 {
public:
	int solveMethod1(vector<int>& coins, int amount){
		//BFS����ֱ�ӳ���������
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
		//���dp���ǳ�ʱ
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
					if (dp[i-j]>=0 && dp[j]>=0 && tmp<MIN){ //ע����method3��Ӧ����ͬλ�ô����жԱ� ��û��Ҫ������м����
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
		//�������ʱ��ֱ��ac��
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
    int coinChange(vector<int>& coins, int amount) {
        return solveMethod3(coins,amount);
		return solveMethod2(coins,amount);
    }
};



/*
416. �ָ�Ⱥ��Ӽ�
����һ�� ֻ���������� �� �ǿ� ���� nums �������ж��Ƿ���Խ��������ָ�������Ӽ���ʹ�������Ӽ���Ԫ�غ���ȡ�
*/
class Solution416 {
public:
    bool canPartition(vector<int>& nums) {
        int SUM = 0;
        for(auto&n:nums){
            SUM+=n;
        }
        if(SUM%2!=0){
            return 0;
        }
        SUM = SUM/2;
		//����Ҫ�Ļ���Ҫȷ��dp�ĺ���
        vector<vector<bool>> dp(nums.size(),vector<bool>(SUM+1,0));//dp[i][j]��ʾ[0,i]Ԫ���Ƿ��ܹ���j
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
		//����ܰѿռ临�Ӷ��Ż���SUM
		//Ȼ��dp�Ż���һά
        return dp[nums.size()-1][SUM];
    }
};


/*
139. ���ʲ��
����һ���ǿ��ַ��� s ��һ�������ǿյ��ʵ��б� wordDict���ж� s �Ƿ���Ա��ո���Ϊһ���������ֵ��г��ֵĵ��ʡ�

˵����

���ʱ�����ظ�ʹ���ֵ��еĵ��ʡ�
����Լ����ֵ���û���ظ��ĵ��ʡ�

*/

//���ǱȽϽ����ö�̬�滮ȥ��
//��̬�滮��DFS��������һ����ԭ��ֻ������̬�滮���Ե����ϵģ�DFS���Զ����µ�
class Solution139 {
public:
    bool solveMethod1(string s,vector<string>& wordDict){
        //�ö�̬�滮�ķ����� n^2��ʱ�临�Ӷ� n�Ŀռ临�Ӷ�
        set<string> SET;
        for(auto&str:wordDict){
            SET.insert(str);
        }
        vector<bool> dp(s.size(),0);//dp[i]��ʾ[0,i]���䷶Χ���Ƿ���Է������ֵ��г���
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
        //����DFS�ļ��仯���������������Ļ���ֱ�Ӿͳ���ʱ��������
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
��ָ Offer 47. ���������ֵ
��һ�� m*n �����̵�ÿһ�񶼷���һ�����ÿ�����ﶼ��һ���ļ�ֵ����ֵ���� 0��������Դ����̵����Ͻǿ�ʼ�ø���������
��ÿ�����һ��������ƶ�һ��ֱ���������̵����½ǡ�����һ�����̼������������ļ�ֵ���������������õ����ټ�ֵ�����

*/
class SolutionOffer47 {
public:
    int maxValue(vector<vector<int>>& grid) {
		int m = grid.size();
		int n = grid[0].size();
		vector<vector<int>> dp(m,vector<int>(n,0));
        //�ռ临�Ӷȿ����Ż�����ֱ����grid���޸ģ������Ļ��ռ临�ӶȾͽ�����1
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
��ָ Offer 60. n�����ӵĵ���
��n���������ڵ��ϣ��������ӳ���һ��ĵ���֮��Ϊs������n����ӡ��s�����п��ܵ�ֵ���ֵĸ��ʡ�

 

����Ҫ��һ�����������鷵�ش𰸣����е� i ��Ԫ�ش����� n ���������������ĵ��������е� i С���Ǹ��ĸ��ʡ�


*/

class SolutionOffer60 {
public:
    vector<double> dicesProbability(int n) {
        //�ռ临�Ӷȿ��Խ���n
        //ʱ�临�Ӷ���n^2
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