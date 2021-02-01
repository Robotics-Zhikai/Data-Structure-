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
	swap(*hafg.begin(), *(hafg.begin() + 1)); //����Ԫ��ʱ�������������
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
//     heap.push_back(make_pair("��Ԫ��",0));
//     for(auto it = in.begin();it!=in.end();it++)
//     {
//         heap.push_back(make_pair(*it,0));
//     }
//     //���ﲻ���ö� ��������Ĺ��ڶѵļ��д�����Խ��
// }



//973. ��ӽ�ԭ��� K ����
//������һ����ƽ���ϵĵ���ɵ��б� points����Ҫ�����ҳ� K ������ԭ��(0, 0) ����ĵ㡣
//
//�����ƽ��������֮��ľ�����ŷ����¾��롣��
//
//����԰��κ�˳�򷵻ش𰸡����˵������˳��֮�⣬��ȷ����Ψһ�ġ�
//https://leetcode-cn.com/problems/k-closest-points-to-origin/solution/zui-jie-jin-yuan-dian-de-k-ge-dian-by-leetcode-sol/
class Solution973 {

	///////////////////////////////////////////////////////////////////////////////////
	//�����ķ��η�
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
		// [left, i-1] ��С�ڵ��� pivot, [i+1, right] ������ pivot
		if (K < i - left + 1) {
			random_select(points, left, i - 1, K);
		}
		else if (K > i - left + 1) {
			random_select(points, i + 1, right, K - (i - left + 1));
		}
		//��������˵�K=i-left+1ʱreturn
	}

	vector<vector<int>> kClosest_TiJie(vector<vector<int>>& points, int K) {
		int n = points.size();
		random_select(points, 0, n - 1, K);
		return{ points.begin(), points.begin() + K };

	}
	///////////////////////////////////////////////////////////////////////////////////

public:
	vector<vector<int>> kClosestHeapPop(vector<vector<int>>& points, int K)//�����ǽ��Ѻ�pop�ѣ����Ӷ���n+klogn
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

	vector<vector<int>> kClosestTopK(vector<vector<int>>& points, int K) //������topk ���Ӷ���k+nlogk
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
	//Ҫ�Ҿ��������K���㣬��ô�������뵽�����㷨���е�̶���Ͳ��������ֲ���
	//���ж��ֵ�˼��
	int quickdivid(vector<vector<int>>& points, int left, int right) //������ŵķ��η���������O(n)�ĸ��Ӷ�
																	 //����ֻҪ�ǳ���return����ֱ��ȫ������
	{
		static auto lambdaless = [](const vector<int> &p1, const vector<int>& p2) {return (pow(p1[0], 2) + pow(p1[1], 2))<(pow(p2[0], 2) + pow(p2[1], 2)); };
		//�������׳���
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
			//���µ�������������䶼����Ҫ
			if (left == K_num)
				return left;
			else if (left + 1 == K_num)
				return left + 1;
			else
				return right;
		}
		//�ϱߵ��⼸��return�����൱�ڶ������������������ˣ���ֱ��return

		// vector<int> mid = points[left]; //����ڵݹ��Ϻܺ��ڴ棬�ķ���2MB
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
		swap(points[indexR], points[left]); //�������Swap������ٶ��д��������
		// points.insert(points.begin()+indexL,points[left]);//��Ϊ������������ƾ�������һ�κ�Ԫ�ؾͲ�����
		// points.erase(points.begin()+left);               //��erase��insert�Ľ�ϲ�û�����ֳ�������

		//�������׳���
		//���µ�if else��������һ����֦
		if (indexL - 1 == K_num) //���м�����պ��ܹ���������ʱ��return��ֻҪreturn�͵õ����ս����indexL-1�����м�ֵ������
			return indexL - 1;
		else if (indexL - 1>K_num) //���ж�Ϊ�����Ӽ�ʱ���������Ӽ�
			return quickdivid(points, left, indexL - 1);
		else  //����������Ӽ��������԰����м���Ǹ�ֵ
			return quickdivid(points, indexL - 1 + 1, right);

	}
	vector<vector<int>> kClosestQuickSort(vector<vector<int>>& points, int K)//����������򣬷��ν��
	{
		int mid = quickdivid(points, 0, points.size());

		return{ points.begin(),points.begin() + mid };
	}

	vector<vector<int>> kClosest(vector<vector<int>>& points, int K) {
		K_num = K;
		// return kClosestHeapPop(points, K);//256ms 40.5MB ����91.22 61.04
		// return kClosestTopK(points, K); //176ms 38MB ���� 99.6 99.75
		return kClosestQuickSort(points, K); //124ms 38.1MB ����99.97 99.63 ���Լ��ķ���ʵ��
		// return kClosest_TiJie(points,K); //���ķ���ʵ�� 136ms��37.9MB ����99.93 99.85
	}
};



//23. �ϲ�K����������
//����һ���������飬ÿ�������Ѿ����������С�
//
//���㽫��������ϲ���һ�����������У����غϲ��������
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


	
	inline ListNode* merge_TWO_Lists(ListNode* L, ListNode* R)//�ϲ������������� ����鲢�����ʵ��˼·
	{
		ListNode* Lcurrent = L;
		ListNode* Rcurrent = R;

		ListNode* mergeCurrent = nullptr;
		if (Lcurrent != nullptr&&Rcurrent != nullptr) //�������׳���
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

	inline ListNode* divide(vector<ListNode*>& lists) //���η���ʱ�临�Ӷ���Lnlogn n�����������L��ÿ�������ƽ������
		//���������ȼ����еķ���������ûʲô������������priority queue�Ļ�
	{
		int left = 0;
		int right = lists.size();
		int mid = (left + right) / 2;

		if (left == right)
			return nullptr;
		else if (right - 1 == left)
			return *lists.begin();
		else if (right - left == 2)
			return merge_TWO_Lists(lists[left], lists[left+1]);  //�������׳���


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


//395. ������K���ظ��ַ�����Ӵ�
//�ҵ������ַ�������Сд�ַ���ɣ��е���Ӵ� T �� Ҫ�� T �е�ÿһ�ַ����ִ����������� k ����� T �ĳ��ȡ�
//https://leetcode-cn.com/problems/longest-substring-with-at-least-k-repeating-characters/solution/duo-lu-fen-zhi-de-di-gui-fang-fa-zhi-xing-he-nei-c/
class Solution395 
{
public:
	int K;
	inline bool isContinue_left(const string & str, int loc, const vector<int>& hash) //Ӧ���ǵ������ж��������
	{
		if (loc - 1 >= 0)
		{
			if (hash[str[loc - 1]] >= K&&hash[str[loc]] >= K)
				return 1;
		}
		return 0;
	}

	inline bool isContinue_right(const string & str, int loc, const vector<int>& hash) //Ӧ���ǵ������ж��������
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
		while (isContinue_right(str, index++, hash)); //���ص����ִ���β��index
	}
	inline void move2unique_Iterator_left(const string& str, int& index, const vector<int>& hash)
	{
		while (isContinue_left(str, index, hash)) index--; //���ص����ִ���β��index
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

	int divide(int left, int right, const string& str) //����Ӧ����nlogn�ĸ��Ӷ� ���ϼ�֦����С
	{
		int mid = left + (right - left) / 2.0;

		int l1, l2, m1, m2, r1, r2;
		int upper = mid;
		int lower = mid;

		vector<int> hash(128, 0); //��Ϊ������Ӣ����ĸ�������޵ģ����Կ����Լ�����һ��hash�����ö���UNordered_map��������ʹЧ�ʽ���
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

		//���û��skip����Ļ���ÿ�ζ�Ҫ�ֳ������֣�û���ÿ϶������ܵĲ�������һ�֣���Ȼ���˹�ģ���ٵ����ã�����ȴû�м�֦
		//�м�֦�Ļ��Ӳ������O(n)������ˣ�����û�м�֦�Ļ��Ӳ���һֱ�ݹ��������ֻ����O(nlogn)��ʱ�䣬��û�б��O(n)�Ļ���
		l1 = left; l2 = lower;
		m1 = lower; m2 = upper;
		r1 = upper; r2 = right; //�±ߵ��⼸����Ҫ����O(n)+3*W(n/3),Ҫ����O(n)+3*O(1);������ȫ��֦��divideֻ��ҪO(1)
		SkipImpossible(str, r1, r2, r1, hash);  //O(n) //����һ����֦���� 
		int rightbiggest = divide(r1, r2, str); //W(n/3)
		SkipImpossible(str, l1, l2, l1, hash);
		int leftbiggest = divide(l1, l2, str);  //W(n/3)  //��Ϊ��ǰ�պ󿪣�������Ҫ��lower+1 
		SkipImpossible(str, m1, m2, m1, hash);
		int midbiggest = divide(m1, m2, str);   //W(n/3)

		//�������� �ƹ�һ�¾���Solutionzhao���forѭ����Ч�ʸ���

		vector<int> findmax = { rightbiggest,leftbiggest,midbiggest };
		int maxele = *max_element(findmax.begin(), findmax.end());
		if (maxele >= K)
			return maxele;
		else
			return 0;

	}

	//���ߣ�zhao - 125
	//	���ӣ�https://leetcode-cn.com/problems/longest-substring-with-at-least-k-repeating-characters/solution/duo-lu-fen-zhi-de-di-gui-fang-fa-zhi-xing-he-nei-c/
	//��Դ�����ۣ�LeetCode��
	//	����Ȩ���������С���ҵת������ϵ���߻����Ȩ������ҵת����ע��������
	int Solutionzhao(string s, int k) { //�ڴ������ʱ�䶼����100%
		unordered_map<char, int> umap;
		for (auto c : s) umap[c]++;
		vector<int> split;
		for (int i = 0; i < s.size(); i++) {
			if (umap[s[i]] < k) split.push_back(i); //�Ѿ��Բ����ܵĶ��Ž�ȥ ����������ڵ�����������ݹ��ֻ���г��������൱��SkipImpossible
		}											//ֻ�����ҵ�SkipImpossibleֻ�ڷ�Str��ǰ�벿����һ�Σ���������ܶ�Σ����ٵļ������͸���
													//��֦���ĸ���
		if (split.size() == 0) return s.length();
		int ans = 0, left = 0;
		split.push_back(s.length());
		for (int i = 0; i < split.size(); i++) {
			int len = split[i] - left; //�±ߵ�if����һ����֦���Ѽ����������������е�����ȫ����Ҳ���ᳬ��Ŀǰ���ļ�ȥ
			if (len > ans) ans = max(ans, longestSubstring(s.substr(left, len), k)); 
			left = split[i] + 1;
		}
		return ans;
	}


	int SolutionBEST(string s, int k)//�����ĳ�˵ķ��� �������ķ�����˼�룬ÿ�ּ���һЩ��ģ�����ӿ����ҵĳ���
	{
		if (k <= 1) return s.size();
		if (s.empty() || s.size() < k) return 0;

		vector<int> hash(128, 0);
		for (char c : s) ++hash[c];

		int i = 0;
		while (i < s.size() && hash[s[i]] >= k) ++i;
		if (i == s.size()) return s.size();

		int l = longestSubstring(s.substr(0, i), k);
		while (i < s.size() && hash[s[i]] < k) ++i; //ÿ�ν�����һ��֮ǰ��Ҫȥ��һЩ�϶������ܵ�Ԫ�� ��ģ���С
		int r = longestSubstring(s.substr(i), k);

		return max(l, r);
	}

	int SolutionZK(string s, int k)
	{
		K = k;
		cout << "�ҵķ���" << endl;
		return divide(0, s.size(), s);
	}
	int longestSubstring(string s, int k) {
		// return SolutionBEST(s, k);
		//return Solutionzhao(s, k);
		return SolutionZK(s, k);

	}


};

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
			dividgroup = S.size() / basenum; //�ֳɶ��С�飬ÿ��С����basenum����
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