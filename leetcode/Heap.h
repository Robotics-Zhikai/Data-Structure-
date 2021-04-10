#pragma once
#include "main.h"
#include <queue> //priority_queue
/*
剑指 Offer 40. 最小的k个数
输入整数数组 arr ，找出其中最小的 k 个数。例如，输入4、5、1、6、2、7、3、8这8个数字，则最小的4个数字是1、2、3、4。
*/
class SolutionOffer40 {
public:
	vector<int> getLeastNumbersOriginal(vector<int>& arr, int k)//常规的O(nlogn)方法
	{
		sort(arr.begin(), arr.end(), [](int a, int b)->bool {return a<b; });
		return vector<int>(arr.begin(), arr.begin() + k);
	}
	int getLeastNumbersDivideandConqure(vector<int>& arr, int l, int r, int k)
	{
		if (arr.empty())
			return 0;
		if (k == 0) //这里容易忽略
			return 0;

		int selected = l;
		int left = selected + 1;
		int right = r - 1;
		while (1)
		{
			while (left != arr.size() && arr[left] <= arr[selected])
				left++;
			while (right != selected && arr[right]>arr[selected])
				right--;
			if (left>right)
				break;
			swap(arr[left], arr[right]);
		}
		swap(arr[selected], arr[right]);
		if (right == k - 1) //下边的这些很容易很容易出错！！！！！
							//return vector<int>(arr.begin(),arr.begin()+right+1);
			return right + 1; //经过这样的处理后，速度有了极大的提升，因为每次不需要拷贝vector<int>了
		else if (right<k - 1)
			return getLeastNumbersDivideandConqure(arr, right + 1, r, k);
		else if (right>k - 1)
			return getLeastNumbersDivideandConqure(arr, l, right, k);
		return 0;
	}
	vector<int> GetLeastNumbersDivideandConqure(vector<int>& arr, int l, int r, int k)//包装函数
	{
		int num = getLeastNumbersDivideandConqure(arr, l, r, k);
		return vector<int>(arr.begin(), arr.begin() + num);//复杂度理想情况下每次半分时是O(n)，最坏是O（n^2） 
	}

	vector<int> getLeastNumbersPriorityQueue(vector<int>& arr, int k) //这个做法比较容易借鉴到
	{
		if (k == 0)
			return vector<int>();
		auto f = [](int a, int b)->bool {return a <= b; }; //维护一个大根堆
		priority_queue<int, vector<int>, decltype(f)> q(f);
		for (int i = 0; i<arr.size(); i++)
		{
			//每次的操作复杂度是O(logk)
			if (q.size()<k)
				q.push(arr[i]);
			else
			{
				if (arr[i]<q.top())
				{
					q.pop();
					q.push(arr[i]);
				}
			}
		}
		vector<int> result;
		while (q.empty() == 0)
		{
			result.push_back(q.top());
			q.pop();
		}
		return result;
	}

	vector<int> getLeastNumbers(vector<int>& arr, int k) {
		//return getLeastNumbersOriginal(arr,k);
		// return GetLeastNumbersDivideandConqure(arr,0,arr.size(), k);
		return getLeastNumbersPriorityQueue(arr, k);//用堆不如用分治快 因为分治里有剪枝 而堆的话经常是O(n)
	}
};