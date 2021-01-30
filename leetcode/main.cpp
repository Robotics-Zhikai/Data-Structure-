#include <vector>
#include <algorithm>
#include <random>
#include <time.h>
#include <iostream>
#include <map>
#include <unordered_map>
using namespace std;

void test()
{
	unordered_map<string, int> ag;
	ag["stin"] = 1;
	auto finded = ag.find("stin");
	
}

// using nodetype = pair<char,int> ;
// vector<nodetype> heap;
// int getfather(int index)
// {
//     return index/2;
// }
// int getlchild(int index)
// {
//     return index*2;
// }
// int getrchild(int index)
// {
//     return index*2+1;
// }
// void swap(int l,int r)
// {
//     nodetype tmp = heap[l];
//     heap[l] = heap[r];
//     heap[r] = tmp;
//     if (heap[l].first==heap[r].first)
//     {
//         heap[l].second++;
//         heap[r].second++;
//     }
// }
// void make_heap(const string& in)
// {
//     heap.push_back(make_pair("首元素",0));
//     for(auto it = in.begin();it!=in.end();it++)
//     {
//         heap.push_back(make_pair(*it,0));
//     }
//     //这里不能用堆 但是这里的关于堆的简便写法可以借鉴
// }

//395. 至少有K个重复字符的最长子串
//找到给定字符串（由小写字符组成）中的最长子串 T ， 要求 T 中的每一字符出现次数都不少于 k 。输出 T 的长度。
//https://leetcode-cn.com/problems/longest-substring-with-at-least-k-repeating-characters/solution/duo-lu-fen-zhi-de-di-gui-fang-fa-zhi-xing-he-nei-c/
class Solution395 
{
public:
	int K;
	inline bool isContinue_left(const string & str, int loc, const vector<int>& hash) //应该是单方向判断连续与否
	{
		if (loc - 1 >= 0)
		{
			if (hash[str[loc - 1]] >= K&&hash[str[loc]] >= K)
				return 1;
		}
		return 0;
	}

	inline bool isContinue_right(const string & str, int loc, const vector<int>& hash) //应该是单方向判断连续与否
	{
		if (loc + 1<str.size())
		{
			if (hash[str[loc + 1]] >= K&&hash[str[loc]] >= K)
				return 1;
		}
		return 0;
	}

	inline void move2unique_Iterator_right(const string& str, int& index, const vector<int>& hash)
	{
		while (isContinue_right(str, index++, hash)); //返回的是字串的尾后index
	}
	inline void move2unique_Iterator_left(const string& str, int& index, const vector<int>& hash)
	{
		while (isContinue_left(str, index, hash)) index--; //返回的是字串的尾后index
	}
	inline void getHashmap(const string& str, int left, int right, vector<int>& hash)
	{
		for (int i = left; i != right; i++)
		{
			++hash[str[i]];
		}
	}
	inline void SkipImpossible(const string& str, int left, int right, int& loc, vector<int>& hash)
	{
		for (loc = left; loc != right; loc++)
		{
			if (hash[str[loc]] >= K)
				break;
		}
	}

	int divide(int left, int right, const string& str) //整个应该是nlogn的复杂度 加上剪枝后会更小
	{
		int mid = left + (right - left) / 2.0;

		int l1, l2, m1, m2, r1, r2;
		int upper = mid;
		int lower = mid;

		vector<int> hash(128, 0); //因为给的是英文字母，是有限的，所以可以自己定义一个hash，不用定义UNordered_map，那样会使效率降低
		getHashmap(str, left, right, hash); //O(n)

		move2unique_Iterator_right(str, upper, hash); //O(n)
		move2unique_Iterator_left(str, lower, hash); 

		if (lower <= left&&upper >= right)
		{
			if (upper - lower >= K)
				return upper - lower;
			else
				return 0;
		}

		//如果没有skip步骤的话，每次都要分成三部分，没有让肯定不可能的不进入下一轮，虽然起到了规模减少的作用，但是却没有剪枝
		//有剪枝的话子步骤可能O(n)就完成了，但是没有剪枝的话子步骤一直递归分三部分只能是O(nlogn)的时间，而没有变成O(n)的机会
		l1 = left; l2 = lower;
		m1 = lower; m2 = upper;
		r1 = upper; r2 = right; //下边的这几步，要不是O(n)+3*W(n/3),要不是O(n)+3*O(1);后者是全剪枝，divide只需要O(1)
		SkipImpossible(str, r1, r2, r1, hash);  //O(n) //这是一个剪枝步骤 
		int rightbiggest = divide(r1, r2, str); //W(n/3)
		SkipImpossible(str, l1, l2, l1, hash);
		int leftbiggest = divide(l1, l2, str);  //W(n/3)  //因为是前闭后开，所以需要在lower+1 
		SkipImpossible(str, m1, m2, m1, hash);
		int midbiggest = divide(m1, m2, str);   //W(n/3)

		//这是三个 推广一下就是Solutionzhao里边for循环，效率更高

		vector<int> findmax = { rightbiggest,leftbiggest,midbiggest };
		int maxele = *max_element(findmax.begin(), findmax.end());
		if (maxele >= K)
			return maxele;
		else
			return 0;

	}

	//作者：zhao - 125
	//	链接：https://leetcode-cn.com/problems/longest-substring-with-at-least-k-repeating-characters/solution/duo-lu-fen-zhi-de-di-gui-fang-fa-zhi-xing-he-nei-c/
	//来源：力扣（LeetCode）
	//	著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
	int Solutionzhao(string s, int k) { //内存和运行时间都超过100%
		unordered_map<char, int> umap;
		for (auto c : s) umap[c]++;
		vector<int> split;
		for (int i = 0; i < s.size(); i++) {
			if (umap[s[i]] < k) split.push_back(i); //把绝对不可能的都放进去 如果出现相邻的两个，进入递归后只进行常数步，相当于SkipImpossible
		}											//只不过我的SkipImpossible只在分Str的前半部分跳一次，他这个跳很多次，减少的计算量就更少
													//剪枝剪的更多
		if (split.size() == 0) return s.length();
		int ans = 0, left = 0;
		split.push_back(s.length());
		for (int i = 0; i < split.size(); i++) {
			int len = split[i] - left; //下边的if语句进一步剪枝，把即便是子区间中所有的数量全算上也不会超过目前最大的剪去
			if (len > ans) ans = max(ans, longestSubstring(s.substr(left, len), k)); 
			left = split[i] + 1;
		}
		return ans;
	}


	int SolutionBEST(string s, int k)//题解中某人的方法 借助他的方法的思想，每轮减少一些规模，大大加快了我的程序
	{
		if (k <= 1) return s.size();
		if (s.empty() || s.size() < k) return 0;

		vector<int> hash(128, 0);
		for (char c : s) ++hash[c];

		int i = 0;
		while (i < s.size() && hash[s[i]] >= k) ++i;
		if (i == s.size()) return s.size();

		int l = longestSubstring(s.substr(0, i), k);
		while (i < s.size() && hash[s[i]] < k) ++i; //每次进入下一轮之前都要去掉一些肯定不可能的元素 规模会减小
		int r = longestSubstring(s.substr(i), k);

		return max(l, r);
	}

	int SolutionZK(string s, int k)
	{
		K = k;
		cout << "我的方法" << endl;
		return divide(0, s.size(), s);
	}
	int longestSubstring(string s, int k) {
		// return SolutionBEST(s, k);
		//return Solutionzhao(s, k);
		return SolutionZK(s, k);

	}


};

//215. 数组中的第K个最大元素
//在未排序的数组中找到第 k 个最大的元素。请注意，你需要找的是数组排序后的第 k 个最大的元素，而不是第 k 个不同的元素。
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
		cout << "sort库nlogn花费了" << (double)(end - begin) / CLOCKS_PER_SEC << "秒" << endl;

		begin = clock();
		int a2 = findkbigrecure(testnum, 300); // 算法设计与分析里边是O(n)的复杂度 但是还是比不过库里边的nlogn的算法
		end = clock();
		cout << "分治算法n花费了" << (double)(end - begin) / CLOCKS_PER_SEC << "秒" << endl;

		if (a1 != a2)
			throw exception("出错");
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
		test();

		Solution215 Solution215;
		Solution215.test();
	}
	catch (const std::exception& d)
	{
		cout << d.what() << endl;
	}
	

	system("pause");
}