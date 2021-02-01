#include <vector>
#include <algorithm>
#include <random>
#include <time.h>
#include <iostream>
#include <map>
#include <unordered_map>
#include <iterator>

using namespace std;

void test()
{
	
	vector<int > hafg{ 1,2,3,4 };
	hafg.erase(hafg.begin());
	hafg.insert(hafg.begin() + 1,8);
	vector<int > hafg1 = { hafg.begin(),hafg.end() };
	swap(*hafg.begin(), *(hafg.begin() + 1)); //交换元素时输入参数是引用
	auto lambdaf = [](int a, int b) {return a > b; };
	vector<int> testheap{ 1,2,3,4 };
	make_heap(testheap.begin(), testheap.end());
	if (int(-20))
		cout << "int(-20)" << endl;
	int * tmp = nullptr;
	if (tmp == nullptr)
		cout << "s" << endl;
	vector<int> vectmp = { 1,2,3,4 };
	vector<int> hahaffg(vectmp.begin(), vectmp.begin() + 1);
	list<int> sagg = {1,2,3,4};
	list<int> sgahah(sagg.begin(), sagg.end());
	
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



//973. 最接近原点的 K 个点
//我们有一个由平面上的点组成的列表 points。需要从中找出 K 个距离原点(0, 0) 最近的点。
//
//（这里，平面上两点之间的距离是欧几里德距离。）
//
//你可以按任何顺序返回答案。除了点坐标的顺序之外，答案确保是唯一的。
//https://leetcode-cn.com/problems/k-closest-points-to-origin/solution/zui-jie-jin-yuan-dian-de-k-ge-dian-by-leetcode-sol/
class Solution973 {

	///////////////////////////////////////////////////////////////////////////////////
	//题解给的分治法
private:
	mt19937 gen{ random_device{}() };

public:
	void random_select(vector<vector<int>>& points, int left, int right, int K) {
		int pivot_id = uniform_int_distribution<int>{ left, right }(gen);
		int pivot = points[pivot_id][0] * points[pivot_id][0] + points[pivot_id][1] * points[pivot_id][1];
		swap(points[right], points[pivot_id]);
		int i = left - 1;
		for (int j = left; j < right; ++j) {
			int dist = points[j][0] * points[j][0] + points[j][1] * points[j][1];
			if (dist <= pivot) {
				++i;
				swap(points[i], points[j]);
			}
		}
		++i;
		swap(points[i], points[right]);
		// [left, i-1] 都小于等于 pivot, [i+1, right] 都大于 pivot
		if (K < i - left + 1) {
			random_select(points, left, i - 1, K);
		}
		else if (K > i - left + 1) {
			random_select(points, i + 1, right, K - (i - left + 1));
		}
		//这就隐含了当K=i-left+1时return
	}

	vector<vector<int>> kClosest_TiJie(vector<vector<int>>& points, int K) {
		int n = points.size();
		random_select(points, 0, n - 1, K);
		return{ points.begin(), points.begin() + K };

	}
	///////////////////////////////////////////////////////////////////////////////////

public:
	vector<vector<int>> kClosestHeapPop(vector<vector<int>>& points, int K)//方法是建堆和pop堆，复杂度是n+klogn
	{
		auto lambdaf = [](const vector<int> &p1, const vector<int>& p2) {return (pow(p1[0], 2) + pow(p1[1], 2))>(pow(p2[0], 2) + pow(p2[1], 2)); };
		vector<vector<int>> result;
		make_heap(points.begin(), points.end(), lambdaf);
		while (!points.empty() && result.size()<K)
		{
			pop_heap(points.begin(), points.end(), lambdaf);
			result.push_back(points.back());
			points.pop_back();
		}
		return result;
	}

	vector<vector<int>> kClosestTopK(vector<vector<int>>& points, int K) //方法是topk 复杂度是k+nlogk
	{
		auto lambdaf = [](const vector<int> &p1, const vector<int>& p2) {return (pow(p1[0], 2) + pow(p1[1], 2))<(pow(p2[0], 2) + pow(p2[1], 2)); };
		vector<vector<int>> result;
		make_heap(points.begin(), points.begin() + K, lambdaf);
		if (K != 0)
		{
			for (auto it = points.begin() + K; it != points.end(); it++)
			{
				if (!lambdaf(points[0], *it))
				{
					pop_heap(points.begin(), points.begin() + K, lambdaf);
					*(points.begin() + K - 1) = *it;
					push_heap(points.begin(), points.begin() + K, lambdaf);
				}
			}
			result = { points.begin(),points.begin() + K };
		}
		return result;
	}

	int K_num;
	//要找距离最近的K个点，那么就能联想到快排算法中中点固定后就不动了这种操作
	//还有二分的思想
	int quickdivid(vector<vector<int>>& points, int left, int right) //借鉴快排的分治方法，这是O(n)的复杂度
																	 //底下只要是出现return，就直接全部返回
	{
		static auto lambdaless = [](const vector<int> &p1, const vector<int>& p2) {return (pow(p1[0], 2) + pow(p1[1], 2))<(pow(p2[0], 2) + pow(p2[1], 2)); };
		//这里容易出错
		if (left == right)
			return left;
		if (right - left == 1)
		{
			if (left == K_num)
				return left;
			else
				return left + 1;
		}
		if (right - left == 2)
		{
			if (!lambdaless(points[left], points[left + 1]))
				swap(points[left], points[left + 1]);
			//以下的这三个条件语句都很重要
			if (left == K_num)
				return left;
			else if (left + 1 == K_num)
				return left + 1;
			else
				return right;
		}
		//上边的这几个return就是相当于二分搜索搜索到那里了，就直接return

		// vector<int> mid = points[left]; //这个在递归上很耗内存，耗费了2MB
		int indexL = left + 1;
		int indexR = right - 1;
		while (indexL<indexR)
		{
			while (indexL<right && lambdaless(points[indexL], points[left]))
				indexL++;
			while (indexR>left && !lambdaless(points[indexR], points[left]))
				indexR--;
			if (indexL<indexR)
				swap(points[indexL], points[indexR]);
		}
		swap(points[indexR], points[left]); //把这个用Swap代替后速度有大幅度提升
		// points.insert(points.begin()+indexL,points[left]);//因为快速排序的优势就在于排一次后元素就不动了
		// points.erase(points.begin()+left);               //而erase和insert的结合并没有体现出该优势

		//这里容易出错
		//底下的if else就是做的一个剪枝
		if (indexL - 1 == K_num) //当中间的数刚好能够满足题意时，return，只要return就得到最终结果。indexL-1就是中间值的索引
			return indexL - 1;
		else if (indexL - 1>K_num) //当判断为在左子集时，进入左子集
			return quickdivid(points, left, indexL - 1);
		else  //否则进入右子集，不可以包括中间的那个值
			return quickdivid(points, indexL - 1 + 1, right);

	}
	vector<vector<int>> kClosestQuickSort(vector<vector<int>>& points, int K)//借鉴快速排序，分治解决
	{
		int mid = quickdivid(points, 0, points.size());

		return{ points.begin(),points.begin() + mid };
	}

	vector<vector<int>> kClosest(vector<vector<int>>& points, int K) {
		K_num = K;
		// return kClosestHeapPop(points, K);//256ms 40.5MB 击败91.22 61.04
		// return kClosestTopK(points, K); //176ms 38MB 击败 99.6 99.75
		return kClosestQuickSort(points, K); //124ms 38.1MB 击败99.97 99.63 我自己的分治实现
		// return kClosest_TiJie(points,K); //题解的分治实现 136ms，37.9MB 击败99.93 99.85
	}
};



//23. 合并K个升序链表
//给你一个链表数组，每个链表都已经按升序排列。
//
//请你将所有链表合并到一个升序链表中，返回合并后的链表。
//https://leetcode-cn.com/problems/merge-k-sorted-lists/solution/he-bing-kge-pai-xu-lian-biao-by-leetcode-solutio-2/
class Solution23 {
public:
	// Definition for singly-linked list.
	struct ListNode {
		int val;
		ListNode *next;
		ListNode() : val(0), next(nullptr) {}
		ListNode(int x) : val(x), next(nullptr) {}
		ListNode(int x, ListNode *next) : val(x), next(next) {}
	};

	ListNode * transvec2listnodeptr(vector<int> num)
	{
		if (num.size() == 0)
			return nullptr;
		//vector<int> num = { -10,-9,-9,-3,-1,-1,0 };
		ListNode * tmp = new ListNode[num.size()];
		int i;
		for (i = 0; i < num.size() - 1; i++)
		{
			tmp[i] = ListNode(num[i], tmp + i + 1);
		}
		tmp[i] = ListNode(num[i], nullptr);
		return tmp;
	}
	void test()
	{

		ListNode * first0 = transvec2listnodeptr(vector<int>{-10, -9, -9, -3, -1, -1, 0 });
		ListNode * first1 = transvec2listnodeptr(vector<int>{-5 });
		ListNode * first2 = transvec2listnodeptr(vector<int>{4 });
		ListNode * first3 = transvec2listnodeptr(vector<int>{-8 });
		ListNode * first4 = transvec2listnodeptr(vector<int>{});
		ListNode * first5 = transvec2listnodeptr(vector<int>{-9, -6, -5, -4, -2, 2, 3 });
		ListNode * first6 = transvec2listnodeptr(vector<int>{-3, -3, -2, -1, 0 });
		


	

		vector<ListNode*> lists = { first0,first1 ,first2,first3, first4 ,first5,first6 };
		mergeKLists(lists);
	}


	
	inline ListNode* merge_TWO_Lists(ListNode* L, ListNode* R)//合并两个有序链表 借鉴归并排序的实现思路
	{
		ListNode* Lcurrent = L;
		ListNode* Rcurrent = R;

		ListNode* mergeCurrent = nullptr;
		if (Lcurrent != nullptr&&Rcurrent != nullptr) //这里容易出错
		{
			if (Lcurrent->val <= Rcurrent->val)
			{
				mergeCurrent = Lcurrent;
				Lcurrent = Lcurrent->next;
			}
			else
			{
				mergeCurrent = Rcurrent;
				Rcurrent = Rcurrent->next;
			}
		}
		else if (Lcurrent != nullptr)
		{
			mergeCurrent = Lcurrent;
			Lcurrent = Lcurrent->next;
		}
		else if (Rcurrent != nullptr)
		{
			mergeCurrent = Rcurrent;
			Rcurrent = Rcurrent->next;
		}
		else
			return mergeCurrent;

		ListNode* mergebegin = mergeCurrent;
		while (Lcurrent != nullptr && Rcurrent != nullptr)
		{
			if ((Lcurrent->val) <= (Rcurrent->val))
			{
				mergeCurrent->next = Lcurrent;
				mergeCurrent = mergeCurrent->next;
				Lcurrent = Lcurrent->next;
			}
			else
			{
				mergeCurrent->next = Rcurrent;
				mergeCurrent = mergeCurrent->next;
				Rcurrent = Rcurrent->next;
			}
		}

		if (Lcurrent != nullptr)
			mergeCurrent->next = Lcurrent;
		else if (Rcurrent != nullptr)
			mergeCurrent->next = Rcurrent;
		else
			mergeCurrent->next = nullptr;

		return mergebegin;
	}

	inline ListNode* divide(vector<ListNode*>& lists) //分治法，时间复杂度是Lnlogn n是链表个数，L是每个链表的平均长度
		//还有用优先级队列的方法，但是没什么技术含量，用priority queue的话
	{
		int left = 0;
		int right = lists.size();
		int mid = (left + right) / 2;

		if (left == right)
			return nullptr;
		else if (right - 1 == left)
			return *lists.begin();
		else if (right - left == 2)
			return merge_TWO_Lists(lists[left], lists[left+1]);  //这里容易出错


		vector<ListNode*> Listleft(lists.begin(), (lists.begin()+mid));
		vector<ListNode*> Listright((lists.begin() + mid), lists.end());

		ListNode* leftnodeptr = divide(Listleft);
		ListNode* rightnodeptr = divide(Listright);

		return merge_TWO_Lists(leftnodeptr, rightnodeptr);
	}
	ListNode* mergeKLists(vector<ListNode*>& lists) {

		return divide(lists);
	}
};


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
			dividgroup = S.size() / basenum; //分成多个小组，每个小组有basenum个数
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
		Solution23 Solution23;
		Solution23.test();
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