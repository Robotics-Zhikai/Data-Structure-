#pragma once
#include "main.h"

//4. 寻找两个正序数组的中位数
//给定两个大小为 m 和 n 的正序（从小到大）数组 nums1 和 nums2。请你找出并返回这两个正序数组的中位数。
//
//进阶：你能设计一个时间复杂度为 O(log(m + n)) 的算法解决此问题吗？
//https://leetcode-cn.com/problems/median-of-two-sorted-arrays/solution/xun-zhao-liang-ge-you-xu-shu-zu-de-zhong-wei-s-114/
class Solution4 {
public:
	double findMedianSortedArrays_On(vector<int>& nums1, vector<int>& nums2) //O(m+n)复杂度的算法，可以剪枝 但是速度没有本质上的提升
	{
		vector<int> mergevec(nums1.size() + nums2.size());
		auto it1 = nums1.begin();
		auto it2 = nums2.begin();
		auto itmerge = mergevec.begin(); //由于只是找中位数，因此不一定要合并 直接找index就行

		while (it1 != nums1.end() && it2 != nums2.end())
		{
			if (*it1<*it2)
			{
				*itmerge = *it1;
				itmerge++;
				it1++;
			}
			else
			{
				*itmerge = *it2;
				itmerge++;
				it2++;
			}
			//可以在这里剪枝，当运行到一半时推出，但是没有本质上的速度提升
		}
		while (it1 != nums1.end())
		{
			*itmerge = *it1;
			itmerge++;
			it1++;
		}
		while (it2 != nums2.end())
		{
			*itmerge = *it2;
			itmerge++;
			it2++;
		}
		if (mergevec.size() % 2 == 0)
			return (mergevec[(mergevec.size() - 1) / 2] + mergevec[(mergevec.size() - 1) / 2 + 1]) / 2.0;
		else
			return mergevec[(mergevec.size() - 1) / 2];
	}

	int divide(vector<int>& nums1, vector<int>& nums2, int cur1, int cur2, int k) //要找第k小的数 k的起算点是1
	{
		if (cur1 == nums1.size())
			return nums2[cur2 + k - 1];
		else if (cur2 == nums2.size())
			return nums1[cur1 + k - 1];

		if (k == 1)
			return nums1[cur1] <= nums2[cur2] ? nums1[cur1] : nums2[cur2]; //如果不加k=1的情况的话会在k/2-1时出现负数

		int nums1mid = cur1 + k / 2 - 1; //只有每次加k/2-1才能保证能够把不需要的剪枝
		int nums2mid = cur2 + k / 2 - 1;

		if (nums1mid<nums1.size() && nums2mid<nums2.size()) //按正常情况处理
		{
			if (nums1[nums1mid] <= nums2[nums2mid])
				cur1 = nums1mid + 1;
			else
				cur2 = nums2mid + 1;
			return divide(nums1, nums2, cur1, cur2, k - k / 2);
		}
		else //否则有越界，按特殊情况处理 此时不能根据k/2那么剪枝了 
		{
			int ktmp = 0;
			while (cur1 != nums1.size() && cur2 != nums2.size())
			{
				if (nums1[cur1] <= nums2[cur2])
				{
					if (++ktmp == k)
						return nums1[cur1]; //没必要全部合并且没必要记录合并情况，index加到给定位置后就可以return了
					cur1++;
				}
				else
				{
					if (++ktmp == k)
						return nums2[cur2];
					cur2++;
				}
			}
			while (cur1 != nums1.size())
			{
				if (++ktmp == k)
					return nums1[cur1];
				cur1++;
			}
			while (cur2 != nums2.size())
			{
				if (++ktmp == k)
					return nums2[cur2];
				cur2++;
			}
		}
		return -1; //一定不会到这里
	}
	double findMedianSortedArrays_Ologn(vector<int>& nums1, vector<int>& nums2)
	{
		vector<int> midk;
		int mergesize = nums1.size() + nums2.size();
		if (mergesize % 2 == 0)
			midk = { mergesize / 2,mergesize / 2 + 1 };
		else
			midk = { (mergesize + 1) / 2 };

		int sum = 0;
		for (auto it = midk.begin(); it != midk.end(); it++)
			sum += divide(nums1, nums2, 0, 0, *it);

		if (midk.size() == 2)
			return sum / 2.0;
		else
			return sum;
	}
	double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
		// return findMedianSortedArrays_On(nums1, nums2);//28ms 87.3MB 击败98.99% 73.99%
		return findMedianSortedArrays_Ologn(nums1, nums2);//32ms 86.9MB 击败97.36% 85.53% 实现的还是不够简洁 
														  //LeetCode的测试数据不够大规模，体现不出logn算法的优势来
	}

	void test() //检测一下当大规模数据时到底是不是log的算法比线性算法好
	{
		vector<int> vec1;
		for (int i = 0; i < 100000; i++)
			vec1.push_back(rand() % 1000);
		vector<int> vec2;
		for (int i = 0; i < 1000000; i++)
			vec2.push_back(rand() % 10000);

		clock_t begin = clock();
		double onresult = findMedianSortedArrays_On(vec1, vec2);
		clock_t end = clock();
		cout << "findMedianSortedArrays_On花费了" << (double)(end - begin) / CLOCKS_PER_SEC << "秒" << endl; //测试结果为2.817秒

		begin = clock();
		double olognresult = findMedianSortedArrays_Ologn(vec1, vec2);
		end = clock();
		cout << "findMedianSortedArrays_Ologn花费了" << (double)(end - begin) / CLOCKS_PER_SEC << "秒" << endl; //测试结果为0.314秒
																											//速度有明显改进

		if (onresult != olognresult)
			throw exception("实现出错");
	}
};






//240. 搜索二维矩阵 II
//编写一个高效的算法来搜索 m x n 矩阵 matrix 中的一个目标值 target 。该矩阵具有以下特性：
//
//每行的元素从左到右升序排列。
//每列的元素从上到下升序排列。
//https://leetcode-cn.com/problems/search-a-2d-matrix-ii/solution/sou-suo-er-wei-ju-zhen-ii-by-leetcode-2/
class Solution240 {
public:
	bool searchMatrixViolence_search(vector<vector<int>>& matrix, int target) //暴力搜索，N^2的复杂度
	{
		for (int i = 0; i<matrix.size(); i++)
		{
			for (int j = 0; j<matrix[i].size(); j++)
			{
				if (matrix[i][j] == target)
					return 1;
			}
		}
		return 0;
	}
	bool searchMatrixTwoSplit(vector<vector<int>>& matrix, int target) //二分搜索，nlogn的复杂度 但是剪枝不多
	{
		if (matrix.empty())
			return 0;
		int left = 0;
		int right = matrix[0].size();
		int mid = (left + right) / 2;
		while (mid != left)
		{
			if (matrix[0][mid]>target)
				right = mid;
			else if (matrix[0][mid]<target)
				left = mid;
			else
				return 1;
			mid = (left + right) / 2;
		}
		int rightup = left;

		left = 0;
		right = matrix.size();
		mid = (left + right) / 2;
		while (mid != left)
		{
			if (matrix[mid][0]>target)
				right = mid;
			else if (matrix[mid][0]<target)
				left = mid;
			else
				return 1;
			mid = (left + right) / 2;
		}
		int leftdown = left;

		//至此分割出一个可能存在的区域来
		for (int i = 0; i <= leftdown; i++)
		{
			left = 0;
			right = rightup + 1;
			mid = (left + right) / 2;
			while (mid != left)
			{
				if (matrix[i][mid]>target)
					right = mid;
				else if (matrix[i][mid]<target)
					left = mid;
				else
					return 1;
				mid = (left + right) / 2;
			}
			if (matrix[i][left] == target)
				return 1;
		}
		return 0;
	}

	int binarySearch(vector<vector<int>>& matrix, int target, bool vertical, int num, int left, int right) //二分搜索的调用函数
	{
		std::ios::sync_with_stdio(0);
		// int left = 0;
		// int right = vertical?matrix.size():matrix[0].size();
		int mid = (left + right) / 2;
		if (!vertical)
		{
			while (mid != left)
			{
				if (matrix[num][mid]>target)
					right = mid;
				else if (matrix[num][mid]<target)
					left = mid;
				else
					return mid;
				mid = (left + right) / 2;
			}
		}
		else
		{
			while (mid != left)
			{
				if (matrix[mid][num]>target)
					right = mid;
				else if (matrix[mid][num]<target)
					left = mid;
				else
					return mid;
				mid = (left + right) / 2;
			}
		}
		return left;
	}
	bool searchMatrixDivide(vector<vector<int>>& matrix, int target, int leftdownx, int leftdowny, int rightupx, int rightupy) //nlogn 剪枝很多 分治法
																															   //TIPS！！！！:如果leftdown和rightup用vector<int>的话，然后用花括号初始化的话会很慢，远不如直接用四个int来的快，在这个题中直接造成了运行超时
	{
		// std::ios::sync_with_stdio(0); //这个可能与读取速度有关系，是一个trick 
		if (leftdownx == rightupx || leftdowny == rightupy)
			return 0; // 说明矩阵是空的，一定找不到元素

		if (matrix[leftdowny][leftdownx]>target || matrix[rightupy - 1][rightupx - 1]<target) //这也是一个剪枝步
			return 0;
		else if (matrix[leftdowny][leftdownx] == target)
			return 1;
		int locy = binarySearch(matrix, target, 1, (leftdownx + rightupx) / 2, leftdowny, rightupy);
		int locx = (leftdownx + rightupx) / 2;

		if (matrix[locy][locx] == target)
			return 1;
		else
		{
			int tmpx = binarySearch(matrix, target, 0, locy, leftdownx, rightupx);
			if (matrix[locy][tmpx] == target)
				return 1;
		}
		if (searchMatrixDivide(matrix, target, leftdownx, locy + 1, locx, rightupy))
			return 1;
		else if (searchMatrixDivide(matrix, target, locx + 1, leftdowny, rightupx, locy))
			return 1;
		else
			return 0;
	}

	bool searchMatrix_Ncomplexity(vector<vector<int>>& matrix, int target)//O(n^0.5)的复杂度,充分利用矩阵已排序的特性
	{
		std::ios::sync_with_stdio(0);//似乎加上这个后更快了
		if (matrix.empty())
			return 0;
		int row = matrix.size() - 1;//这里一定要减1  不能犯这种低级错误！！ 
									//只能是在一个方向变小，另一个方向变大 如果在左上角或者左下角，那么任意数都比初始数大或小，是有问题的
		int col = 0;
		while (row != -1 && col != matrix[0].size()) //如果高度为m 宽度为n 则复杂度为m+n
		{
			if (matrix[row][col]<target)
				col++;
			else if (matrix[row][col]>target)
				row--;
			else
				return 1;
		}
		return 0;
	}


	bool searchMatrix(vector<vector<int>>& matrix, int target) {
		// return searchMatrixViolence_search(matrix, target); //直接报错超出时间限制
		// return searchMatrixTwoSplit(matrix, target);//用的是二分法，384ms 14.3MB 击败12.27% 67.05% nlogn

		// if (!matrix.empty())
		// 	return searchMatrixDivide(matrix, target,  0,0 ,  (int)matrix[0].size(),(int)matrix.size() ); //192ms 13.7MB 38.59% 71.86% nlogn 但是比单纯二分更好 剪枝更多
		// else
		// 	return 0;

		return searchMatrix_Ncomplexity(matrix, target); //108ms 13.8MB 94.42% 71.72%
	}

	void test()
	{
		vector<vector<int>> matrix = { { 1,4,7,11,15 },{ 2,5,8,12,19 },{ 3,6,9,16,22 },{ 10,13,14,17,24 },{ 18,21,23,26,30 } };
		searchMatrix(matrix, 5);
	}

};

/*
剑指 Offer 04. 二维数组中的查找
在一个 n * m 的二维数组中，每一行都按照从左到右递增的顺序排序，每一列都按照从上到下递增的顺序排序。
请完成一个高效的函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。
跟上边的那个题是一样的
*/
//多刷题还是有好处的，LeetCode240原来刷的时候写的很复杂，现在写的就比较简洁了
class SolutionOffer4 {
public:

    bool binarySearch(vector<int> & array,int target,int L,int R)
    {
        if (L==R)
            return 0;
        int mid = (L+R)/2;
        if (array[mid]==target)
            return 1;
        else if (array[mid]<target)
            return binarySearch(array,target,mid+1,R);
        else if (array[mid]>target)
            return binarySearch(array,target,L,mid);
        return 0;
    }
    bool OMlogN(vector<vector<int>>& matrix, int target) //MlogN复杂度
    {
        for(int i = 0;i<matrix.size();i++){
            if (binarySearch(matrix[i],target,0,matrix[i].size()))
                return 1;
        }
        return 0;
    }
    bool OMplusN(vector<vector<int>>& matrix, int target) //M+N复杂度
    {
        if (matrix.size()==0)
            return 0;
        //从右上角元素开始，当前元素比target小时，下移一格，当前元素比target大时，左移一格
        //https://leetcode-cn.com/problems/er-wei-shu-zu-zhong-de-cha-zhao-lcof/solution/mian-shi-ti-04-er-wei-shu-zu-zhong-de-cha-zhao-zuo/ 把矩阵以左下角为中心，逆时针旋转45度
        int row = 0;
        int col = matrix[0].size()-1;

        while(row<matrix.size()&&col>=0){
            if(matrix[row][col]<target)
                row++;
            else if (matrix[row][col]>target)
                col--;
            else if (matrix[row][col]==target)
                return 1;
        }
        return 0;
    }
    bool findNumberIn2DArray(vector<vector<int>>& matrix, int target) {
        // return OMlogN(matrix,target);
        return OMplusN(matrix,target); //这个运行时间远快与上边那个
    }
};


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
			return merge_TWO_Lists(lists[left], lists[left + 1]);  //这里容易出错


		vector<ListNode*> Listleft(lists.begin(), (lists.begin() + mid));
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

		clock_t begin, end;

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

/*
剑指 Offer 53 - I. 在排序数组中查找数字 I
统计一个数字在排序数组中出现的次数。

直接用分治 剪枝的方法

*/

class Solution53_I
{
public:
    int OnMethod(vector<int>& nums, int target)
    {
        int count = 0;
        for(int i = 0;i<nums.size();i++){
            if (target==nums[i])
                count++;
        }
        return count;
    }

    int countAround(vector<int> & nums,int target,int index)
    {
        int count = 0;
        for(int i = index;i<nums.size();i++){
            if (nums[i]==target)
                count++;
            else
                break;
        }
        for(int i = index-1;i>=0;i--){
            if (nums[i]==target)
                count++;
            else
                break;
        }
        return count;
    }
    int LogNmethod(vector<int>& nums,int L,int R,int target) //[L,R) 前闭后开
    {
        if (L==R) //二分法查找元素只要元素在有序数组中，就肯定能找到，如果L==R就说明找不到
            return 0;
        int mid = (L+R)/2;
        if(target==nums[mid])
            return countAround(nums,target,mid); //常数时间找到重复的元素个数
        else if (target>nums[mid])
            return LogNmethod(nums,mid+1,R,target); //注意这里容易出错 因为分了三路，因此需要mid+1
        else
            return LogNmethod(nums,L,mid,target);
    }
    int search(vector<int>& nums, int target) {
        return LogNmethod(nums,0,nums.size(),target);
    }
};


/*
剑指 Offer 53 - II. 0～n-1中缺失的数字
一个长度为n-1的递增排序数组中的所有数字都是唯一的，并且每个数字都在范围0～n-1之内。
在范围0～n-1内的n个数字中有且只有一个数字不在该数组中，请找出这个数字。
同样是直接用分治法 二分剪枝
*/

class SolutionOffer53_II {
public:
    int recur(vector<int>& nums,int L,int R)
    {
        if(L==R && R==nums.size()) //这个判断条件容易忽略掉
            return L;
        if (L==R)
            return nums[L]-1;
        int mid = (L+R)/2;
        if (mid==nums[mid]) //要利用题中给的0-n-1条件，进而利用索引和索引值之间的关系
            return recur(nums,mid+1,R);
        else 
            return recur(nums,L,mid);
    }

    int missingNumber(vector<int>& nums) {
        return recur(nums,0,nums.size());
    }
};



/*
剑指 Offer 36. 二叉搜索树与双向链表
输入一棵二叉搜索树，将该二叉搜索树转换成一个排序的循环双向链表。要求不能创建任何新的节点，只能调整树中节点指针的指向。
*/
class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node() {}

    Node(int _val) {
        val = _val;
        left = NULL;
        right = NULL;
    }

    Node(int _val, Node* _left, Node* _right) {
        val = _val;
        left = _left;
        right = _right;
    }
};
class SolutionOffer36 {
public:
    Node* treeToDoublyListRecur(Node* root) { //这个就当练手了，面试时不要写这个，容易出错且代码量大
        if (root==nullptr)
            return nullptr;
        if (root->left==nullptr && root->right == nullptr) //叶子结点肯定是以该叶子结点为root的子树的最大结点
            return root;
        Node* maxleft = treeToDoublyListRecur(root->left);
        if (maxleft!=nullptr){
            maxleft->right = root; //将左边的调整后的序列与根节点相连
            root->left = maxleft;
        }

        Node* maxright = treeToDoublyListRecur(root->right);
        if (maxright!=nullptr){ //由于递归函数返回的是子树的最大结点，因此需要以O(n)的复杂度找到最小结点
            Node* minright = maxright;
            while(minright->left!=nullptr){
                if (minright->left!=nullptr)
                    minright = minright->left;
            }
            root->right = minright; //将最小结点与根节点相连
            minright->left = root;
        }
        
        if (root->right == nullptr) //考虑的边界情况，总之要返回以root为根的子树的最大结点
            return root;
        else
            return maxright; //返回以root为根的子树的最大结点
    }
    Node* nlognmethod(Node* root){
        Node* MAX = treeToDoublyListRecur(root);
        if (MAX!=nullptr){
            Node* MIN = MAX;
            while(MIN->left!=nullptr){
                if (MIN->left!=nullptr)
                    MIN = MIN->left;
            }
            MAX->right = MIN;
            MIN->left = MAX;
            return MIN;
        }else{
            return nullptr;
        }
    }

    void DFS(Node* root)
    {
        if (root==nullptr)
            return ;
        DFS(root->left); //这就是个中序遍历

        if (pre==nullptr){ //pre初始化为nullptr,第一个中序遍历到的点就是head
            head = root;
        }else{ //将pre的right设置为当前中序遍历到的点
            pre->right = root;
        }
        root->left = pre;
        pre = root; //pre每次等于中序遍历的结点

        DFS(root->right);
    }

    Node* nmethod(Node* root){ //面试时写这个
        DFS(root);
        if (pre!=nullptr){
            pre->right = head;
            head->left = pre;
            return head;
        }
        return nullptr;
        
    }
    Node* treeToDoublyList(Node* root){
        // return nlognmethod(root);//用的是分治法
        return nmethod(root); //用的是树的中序遍历
        //上下两个在LeetCode的测试集中差距不大，但是当数据量上来后，nmethod具备明显优势，且更简单
        
    }
private:
    Node* pre;
    Node* head;
};



