#pragma once
#include "main.h"

//4. Ѱ�����������������λ��
//����������СΪ m �� n �����򣨴�С�������� nums1 �� nums2�������ҳ������������������������λ����
//
//���ף��������һ��ʱ�临�Ӷ�Ϊ O(log(m + n)) ���㷨�����������
//https://leetcode-cn.com/problems/median-of-two-sorted-arrays/solution/xun-zhao-liang-ge-you-xu-shu-zu-de-zhong-wei-s-114/
class Solution4 {
public:
	double findMedianSortedArrays_On(vector<int>& nums1, vector<int>& nums2) //O(m+n)���Ӷȵ��㷨�����Լ�֦ �����ٶ�û�б����ϵ�����
	{
		vector<int> mergevec(nums1.size() + nums2.size());
		auto it1 = nums1.begin();
		auto it2 = nums2.begin();
		auto itmerge = mergevec.begin(); //����ֻ������λ������˲�һ��Ҫ�ϲ� ֱ����index����

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
			//�����������֦�������е�һ��ʱ�Ƴ�������û�б����ϵ��ٶ�����
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

	int divide(vector<int>& nums1, vector<int>& nums2, int cur1, int cur2, int k) //Ҫ�ҵ�kС���� k���������1
	{
		if (cur1 == nums1.size())
			return nums2[cur2 + k - 1];
		else if (cur2 == nums2.size())
			return nums1[cur1 + k - 1];

		if (k == 1)
			return nums1[cur1] <= nums2[cur2] ? nums1[cur1] : nums2[cur2]; //�������k=1������Ļ�����k/2-1ʱ���ָ���

		int nums1mid = cur1 + k / 2 - 1; //ֻ��ÿ�μ�k/2-1���ܱ�֤�ܹ��Ѳ���Ҫ�ļ�֦
		int nums2mid = cur2 + k / 2 - 1;

		if (nums1mid<nums1.size() && nums2mid<nums2.size()) //�������������
		{
			if (nums1[nums1mid] <= nums2[nums2mid])
				cur1 = nums1mid + 1;
			else
				cur2 = nums2mid + 1;
			return divide(nums1, nums2, cur1, cur2, k - k / 2);
		}
		else //������Խ�磬������������� ��ʱ���ܸ���k/2��ô��֦�� 
		{
			int ktmp = 0;
			while (cur1 != nums1.size() && cur2 != nums2.size())
			{
				if (nums1[cur1] <= nums2[cur2])
				{
					if (++ktmp == k)
						return nums1[cur1]; //û��Ҫȫ���ϲ���û��Ҫ��¼�ϲ������index�ӵ�����λ�ú�Ϳ���return��
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
		return -1; //һ�����ᵽ����
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
		// return findMedianSortedArrays_On(nums1, nums2);//28ms 87.3MB ����98.99% 73.99%
		return findMedianSortedArrays_Ologn(nums1, nums2);//32ms 86.9MB ����97.36% 85.53% ʵ�ֵĻ��ǲ������ 
														  //LeetCode�Ĳ������ݲ������ģ�����ֲ���logn�㷨��������
	}

	void test() //���һ�µ����ģ����ʱ�����ǲ���log���㷨�������㷨��
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
		cout << "findMedianSortedArrays_On������" << (double)(end - begin) / CLOCKS_PER_SEC << "��" << endl; //���Խ��Ϊ2.817��

		begin = clock();
		double olognresult = findMedianSortedArrays_Ologn(vec1, vec2);
		end = clock();
		cout << "findMedianSortedArrays_Ologn������" << (double)(end - begin) / CLOCKS_PER_SEC << "��" << endl; //���Խ��Ϊ0.314��
																											//�ٶ������ԸĽ�

		if (onresult != olognresult)
			throw exception("ʵ�ֳ���");
	}
};






//240. ������ά���� II
//��дһ����Ч���㷨������ m x n ���� matrix �е�һ��Ŀ��ֵ target ���þ�������������ԣ�
//
//ÿ�е�Ԫ�ش������������С�
//ÿ�е�Ԫ�ش��ϵ����������С�
//https://leetcode-cn.com/problems/search-a-2d-matrix-ii/solution/sou-suo-er-wei-ju-zhen-ii-by-leetcode-2/
class Solution240 {
public:
	bool searchMatrixViolence_search(vector<vector<int>>& matrix, int target) //����������N^2�ĸ��Ӷ�
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
	bool searchMatrixTwoSplit(vector<vector<int>>& matrix, int target) //����������nlogn�ĸ��Ӷ� ���Ǽ�֦����
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

		//���˷ָ��һ�����ܴ��ڵ�������
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

	int binarySearch(vector<vector<int>>& matrix, int target, bool vertical, int num, int left, int right) //���������ĵ��ú���
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
	bool searchMatrixDivide(vector<vector<int>>& matrix, int target, int leftdownx, int leftdowny, int rightupx, int rightupy) //nlogn ��֦�ܶ� ���η�
																															   //TIPS��������:���leftdown��rightup��vector<int>�Ļ���Ȼ���û����ų�ʼ���Ļ��������Զ����ֱ�����ĸ�int���Ŀ죬���������ֱ����������г�ʱ
	{
		// std::ios::sync_with_stdio(0); //����������ȡ�ٶ��й�ϵ����һ��trick 
		if (leftdownx == rightupx || leftdowny == rightupy)
			return 0; // ˵�������ǿյģ�һ���Ҳ���Ԫ��

		if (matrix[leftdowny][leftdownx]>target || matrix[rightupy - 1][rightupx - 1]<target) //��Ҳ��һ����֦��
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

	bool searchMatrix_Ncomplexity(vector<vector<int>>& matrix, int target)//O(n^0.5)�ĸ��Ӷ�,������þ��������������
	{
		std::ios::sync_with_stdio(0);//�ƺ���������������
		if (matrix.empty())
			return 0;
		int row = matrix.size() - 1;//����һ��Ҫ��1  ���ܷ����ֵͼ����󣡣� 
									//ֻ������һ�������С����һ�������� ��������Ͻǻ������½ǣ���ô���������ȳ�ʼ�����С�����������
		int col = 0;
		while (row != -1 && col != matrix[0].size()) //����߶�Ϊm ���Ϊn ���Ӷ�Ϊm+n
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
		// return searchMatrixViolence_search(matrix, target); //ֱ�ӱ�����ʱ������
		// return searchMatrixTwoSplit(matrix, target);//�õ��Ƕ��ַ���384ms 14.3MB ����12.27% 67.05% nlogn

		// if (!matrix.empty())
		// 	return searchMatrixDivide(matrix, target,  0,0 ,  (int)matrix[0].size(),(int)matrix.size() ); //192ms 13.7MB 38.59% 71.86% nlogn ���Ǳȵ������ָ��� ��֦����
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
��ָ Offer 04. ��ά�����еĲ���
��һ�� n * m �Ķ�ά�����У�ÿһ�ж����մ����ҵ�����˳������ÿһ�ж����մ��ϵ��µ�����˳������
�����һ����Ч�ĺ���������������һ����ά�����һ���������ж��������Ƿ��и�������
���ϱߵ��Ǹ�����һ����
*/
//��ˢ�⻹���кô��ģ�LeetCode240ԭ��ˢ��ʱ��д�ĺܸ��ӣ�����д�ľͱȽϼ����
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
    bool OMlogN(vector<vector<int>>& matrix, int target) //MlogN���Ӷ�
    {
        for(int i = 0;i<matrix.size();i++){
            if (binarySearch(matrix[i],target,0,matrix[i].size()))
                return 1;
        }
        return 0;
    }
    bool OMplusN(vector<vector<int>>& matrix, int target) //M+N���Ӷ�
    {
        if (matrix.size()==0)
            return 0;
        //�����Ͻ�Ԫ�ؿ�ʼ����ǰԪ�ر�targetСʱ������һ�񣬵�ǰԪ�ر�target��ʱ������һ��
        //https://leetcode-cn.com/problems/er-wei-shu-zu-zhong-de-cha-zhao-lcof/solution/mian-shi-ti-04-er-wei-shu-zu-zhong-de-cha-zhao-zuo/ �Ѿ��������½�Ϊ���ģ���ʱ����ת45��
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
        return OMplusN(matrix,target); //�������ʱ��Զ�����ϱ��Ǹ�
    }
};


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
			return merge_TWO_Lists(lists[left], lists[left + 1]);  //�������׳���


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

		clock_t begin, end;

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

/*
��ָ Offer 53 - I. �����������в������� I
ͳ��һ�����������������г��ֵĴ�����

ֱ���÷��� ��֦�ķ���

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
    int LogNmethod(vector<int>& nums,int L,int R,int target) //[L,R) ǰ�պ�
    {
        if (L==R) //���ַ�����Ԫ��ֻҪԪ�������������У��Ϳ϶����ҵ������L==R��˵���Ҳ���
            return 0;
        int mid = (L+R)/2;
        if(target==nums[mid])
            return countAround(nums,target,mid); //����ʱ���ҵ��ظ���Ԫ�ظ���
        else if (target>nums[mid])
            return LogNmethod(nums,mid+1,R,target); //ע���������׳��� ��Ϊ������·�������Ҫmid+1
        else
            return LogNmethod(nums,L,mid,target);
    }
    int search(vector<int>& nums, int target) {
        return LogNmethod(nums,0,nums.size(),target);
    }
};


/*
��ָ Offer 53 - II. 0��n-1��ȱʧ������
һ������Ϊn-1�ĵ������������е��������ֶ���Ψһ�ģ�����ÿ�����ֶ��ڷ�Χ0��n-1֮�ڡ�
�ڷ�Χ0��n-1�ڵ�n������������ֻ��һ�����ֲ��ڸ������У����ҳ�������֡�
ͬ����ֱ���÷��η� ���ּ�֦
*/

class SolutionOffer53_II {
public:
    int recur(vector<int>& nums,int L,int R)
    {
        if(L==R && R==nums.size()) //����ж��������׺��Ե�
            return L;
        if (L==R)
            return nums[L]-1;
        int mid = (L+R)/2;
        if (mid==nums[mid]) //Ҫ�������и���0-n-1������������������������ֵ֮��Ĺ�ϵ
            return recur(nums,mid+1,R);
        else 
            return recur(nums,L,mid);
    }

    int missingNumber(vector<int>& nums) {
        return recur(nums,0,nums.size());
    }
};



/*
��ָ Offer 36. ������������˫������
����һ�ö��������������ö���������ת����һ�������ѭ��˫������Ҫ���ܴ����κ��µĽڵ㣬ֻ�ܵ������нڵ�ָ���ָ��
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
    Node* treeToDoublyListRecur(Node* root) { //����͵������ˣ�����ʱ��Ҫд��������׳����Ҵ�������
        if (root==nullptr)
            return nullptr;
        if (root->left==nullptr && root->right == nullptr) //Ҷ�ӽ��϶����Ը�Ҷ�ӽ��Ϊroot�������������
            return root;
        Node* maxleft = treeToDoublyListRecur(root->left);
        if (maxleft!=nullptr){
            maxleft->right = root; //����ߵĵ��������������ڵ�����
            root->left = maxleft;
        }

        Node* maxright = treeToDoublyListRecur(root->right);
        if (maxright!=nullptr){ //���ڵݹ麯�����ص�������������㣬�����Ҫ��O(n)�ĸ��Ӷ��ҵ���С���
            Node* minright = maxright;
            while(minright->left!=nullptr){
                if (minright->left!=nullptr)
                    minright = minright->left;
            }
            root->right = minright; //����С�������ڵ�����
            minright->left = root;
        }
        
        if (root->right == nullptr) //���ǵı߽��������֮Ҫ������rootΪ���������������
            return root;
        else
            return maxright; //������rootΪ���������������
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
        DFS(root->left); //����Ǹ��������

        if (pre==nullptr){ //pre��ʼ��Ϊnullptr,��һ������������ĵ����head
            head = root;
        }else{ //��pre��right����Ϊ��ǰ����������ĵ�
            pre->right = root;
        }
        root->left = pre;
        pre = root; //preÿ�ε�����������Ľ��

        DFS(root->right);
    }

    Node* nmethod(Node* root){ //����ʱд���
        DFS(root);
        if (pre!=nullptr){
            pre->right = head;
            head->left = pre;
            return head;
        }
        return nullptr;
        
    }
    Node* treeToDoublyList(Node* root){
        // return nlognmethod(root);//�õ��Ƿ��η�
        return nmethod(root); //�õ��������������
        //����������LeetCode�Ĳ��Լ��в�಻�󣬵��ǵ�������������nmethod�߱��������ƣ��Ҹ���
        
    }
private:
    Node* pre;
    Node* head;
};



