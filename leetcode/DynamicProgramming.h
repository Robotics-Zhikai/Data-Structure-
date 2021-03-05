#pragma once
#include "main.h"

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
			if (!((leftindex + j) != s.size() && (leftindex - j) != -1))
				j--;
			return s.substr(leftindex - j, 2 * j + 1);
		}
		else if (leftindex<rightindex)
		{
			if (s[leftindex] != s[rightindex])
				return string("");
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