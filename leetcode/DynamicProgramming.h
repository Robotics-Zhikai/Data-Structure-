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