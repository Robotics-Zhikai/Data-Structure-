#include <vector>
#include <algorithm>
#include <random>
#include <time.h>
#include <iostream>
using namespace std;


//215. �����еĵ�K�����Ԫ��
//��δ������������ҵ��� k ������Ԫ�ء���ע�⣬����Ҫ�ҵ������������ĵ� k ������Ԫ�أ������ǵ� k ����ͬ��Ԫ�ء�
//https://leetcode-cn.com/problems/kth-largest-element-in-an-array/
class Solution215 {
public:
	void test()
	{
		
		vector<int> testnum(100001);
		for (int i = 0; i < testnum.size(); i++)
			testnum[i] = rand() % 1000 + 1;

		clock_t begin,end ;

		begin = clock();
		int a1 = findkbig(testnum, 300);
		end = clock();
		cout << "sort��nlogn������" << (double)(end - begin) / CLOCKS_PER_SEC << "��" << endl;

		begin = clock();
		int a2 = findkbigrecure(testnum, 300); // �㷨�������������O(n)�ĸ��Ӷ� ���ǻ��ǱȲ�������ߵ�nlogn���㷨
		end = clock();
		cout << "�����㷨n������" << (double)(end - begin) / CLOCKS_PER_SEC << "��" << endl;

		if (a1 != a2)
			throw exception("����");
	} 

	int findKthLargest(vector<int>& nums, int k) {

		// return findkbigrecure(nums,k);
		return findkbig(nums, k);

	}

	int findkbig(vector<int> &num, int k)
	{
		sort(num.begin(), num.end(), [](int a, int b) {return a>b; });
		return num[k - 1];
	}
	int basenum = 5;
	void addbig_small_elements(const vector<int>::iterator& beginit, const vector<int>::iterator& endit, int ele, vector<int>& bigvec, vector<int>& smallvec)
	{
		for (vector<int>::iterator it = beginit; it != endit; it++)
		{
			if (*it >= ele)
				bigvec.push_back(*it);
			else
				smallvec.push_back(*it);
		}
	}

	int findkbigrecure(vector<int>& S, int k)
	{
		if (k == S.size())
			return *min_element(S.begin(), S.end());
		int dividgroup = 0;
		if (S.size() % basenum == 0)
			dividgroup = S.size() / basenum;
		else
			dividgroup = S.size() / basenum + 1;

		vector<int> midle(dividgroup);
		for (size_t i = 0; i<S.size(); i = i + basenum)
		{
			if (i + basenum >= S.size())
			{
				sort(S.begin() + i, S.end(), [](int a, int b) {return a>b; });
				*(midle.end() - 1) = S[i];
			}
			else
			{
				sort(S.begin() + i, S.begin() + i + basenum, [](int a, int b) {return a>b; });
				midle[i / basenum] = S[i + (basenum - 1) / 2];
			}
		}

		int midnum = findkbigrecure(midle, ceil(midle.size() / 2.0));


		vector<int> NextsmallS;
		vector<int> NextbigS;
		addbig_small_elements(S.begin(), S.end(), midnum, NextbigS, NextsmallS);
		NextbigS.erase(find(NextbigS.begin(), NextbigS.end(), midnum));
		if (k - 1 == NextbigS.size())
			return midnum;
		else
		{
			if (k - 1<NextbigS.size())
				return findkbigrecure(NextbigS, k);
			else
				return findkbigrecure(NextsmallS, k - NextbigS.size() - 1);
		}

	}
};


int main()
{
	try
	{

		Solution215 Solution215;
		Solution215.test();
	}
	catch (const std::exception& d)
	{
		cout << d.what() << endl;
	}
	

	system("pause");
}