#pragma once
#include "main.h"
#include <queue> //priority_queue
/*
��ָ Offer 40. ��С��k����
������������ arr ���ҳ�������С�� k ���������磬����4��5��1��6��2��7��3��8��8�����֣�����С��4��������1��2��3��4��
*/
class SolutionOffer40 {
public:
	vector<int> getLeastNumbersOriginal(vector<int>& arr, int k)//�����O(nlogn)����
	{
		sort(arr.begin(), arr.end(), [](int a, int b)->bool {return a<b; });
		return vector<int>(arr.begin(), arr.begin() + k);
	}
	int getLeastNumbersDivideandConqure(vector<int>& arr, int l, int r, int k)
	{
		if (arr.empty())
			return 0;
		if (k == 0) //�������׺���
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
		if (right == k - 1) //�±ߵ���Щ�����׺����׳�����������
							//return vector<int>(arr.begin(),arr.begin()+right+1);
			return right + 1; //���������Ĵ�����ٶ����˼������������Ϊÿ�β���Ҫ����vector<int>��
		else if (right<k - 1)
			return getLeastNumbersDivideandConqure(arr, right + 1, r, k);
		else if (right>k - 1)
			return getLeastNumbersDivideandConqure(arr, l, right, k);
		return 0;
	}
	vector<int> GetLeastNumbersDivideandConqure(vector<int>& arr, int l, int r, int k)//��װ����
	{
		int num = getLeastNumbersDivideandConqure(arr, l, r, k);
		return vector<int>(arr.begin(), arr.begin() + num);//���Ӷ����������ÿ�ΰ��ʱ��O(n)�����O��n^2�� 
	}

	vector<int> getLeastNumbersPriorityQueue(vector<int>& arr, int k) //��������Ƚ����׽����
	{
		if (k == 0)
			return vector<int>();
		auto f = [](int a, int b)->bool {return a <= b; }; //ά��һ�������
		priority_queue<int, vector<int>, decltype(f)> q(f);
		for (int i = 0; i<arr.size(); i++)
		{
			//ÿ�εĲ������Ӷ���O(logk)
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
		return getLeastNumbersPriorityQueue(arr, k);//�öѲ����÷��ο� ��Ϊ�������м�֦ ���ѵĻ�������O(n)
	}
};


/*
347. ǰ K ����ƵԪ��
����һ���������� nums ��һ������ k �����㷵�����г���Ƶ��ǰ k �ߵ�Ԫ�ء�����԰� ����˳�� ���ش𰸡�
*/

class Solution347 {
public:
	//Ҳ���ÿ�������ķ�����ÿɨһ�μ�֦һ��ķ�ʽ���д���
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int,int> freq;
        for (int i = 0;i<nums.size();i++){
            if (freq.find(nums[i])==freq.end()){
                freq[nums[i]] = 0;
            }
            else{
                freq[nums[i]]++;
            }
        }
        
        auto lambda = [](pair<int,int>& a,pair<int,int>& b)->bool{return a.second>b.second;};
        //���ںŽ���С���ѣ�С�ںŽ��������
		priority_queue<pair<int,int>,vector<pair<int,int>>,decltype(lambda)> PriQue(lambda);
        for(auto&m:freq){
            if (PriQue.size()<k){ //����С����
                PriQue.push(m);
            }
            else{
                if (m.second>=PriQue.top().second){ //Ȼ�����ͷ���ֵ����pop��push
                    PriQue.pop();
                    PriQue.push(m);
                }
            }
        } //ʱ�临�Ӷ���nlogk����k�ǳ�Сʱʱ�临�Ӷ�����n
        vector<int> res;
        for(int i = 0;i<k;i++){ //���յõ�ǰk�����ֵ
            res.push_back(PriQue.top().first);
            PriQue.pop();
        }
        return res;
    }
};