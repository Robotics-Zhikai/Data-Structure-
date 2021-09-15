#pragma once
#include "main.h"

/*
剑指 Offer 45. 把数组排成最小的数
输入一个非负整数数组，把数组里所有数字拼接起来排成一个数，打印能拼接出的所有数字中最小的一个。
https://leetcode-cn.com/problems/ba-shu-zu-pai-cheng-zui-xiao-de-shu-lcof/solution/tu-jie-wo-men-zhi-qian-ke-neng-mei-you-g-gcr3/
这有一个详细的证明
大致是用了传递性和反证法
AB<BA BC<CB 则AC<CA 由这个传递性，可知所有非从小到大顺序排列的字符串都比顺序排列的字符串代表的数大
*/
class SolutionOffer45 {
public:
	bool compareSmaller(string stra, string strb)
	{
		//string stra = to_string(a); //数字转字符串
		//string strb = to_string(b);
		string apb = stra + strb;
		string bpa = strb + stra;
		//unsigned long numapb = stoul(apb); //字符串转数字
		//unsigned long numbpa = stoul(bpa);
		if (apb<bpa) //字典序进行比较
			return 1;
		else
			return 0;
	}
	string minNumber(vector<int>& nums) //总体思路就是新定义一个比较大小的机制
	{
		vector<string> numsStr;
		for (int i = 0; i<nums.size(); i++)
			numsStr.push_back(to_string(nums[i]));
		sort(numsStr.begin(), numsStr.end(),
			[this](string a, string b)->bool {return compareSmaller(a, b); });
		//注意lambda中要捕获this  否则就需要把compareSmaller设置成static
		string result = "";
		for (int i = 0; i<numsStr.size(); i++)
			result += numsStr[i];
		return result;
	}
};

/*
406. 根据身高重建队列
假设有打乱顺序的一群人站成一个队列，数组 people 表示队列中一些人的属性（不一定按顺序）。
每个 people[i] = [hi, ki] 表示第 i 个人的身高为 hi ，前面 正好 有 ki 个身高大于或等于 hi 的人。

请你重新构造并返回输入数组 people 所表示的队列。
返回的队列应该格式化为数组 queue ，其中 queue[j] = [hj, kj] 是队列中第 j 个人的属性（queue[0] 是排在队列前面的人）。

*/

//涉及到这种排序题，需要注意要往按照多个关键字顺序进行排序的方向进行思考
class Solution406 {
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        sort(people.begin(),people.end(),[](vector<int>&a,vector<int>&b)->bool
        {
            return a[0]>b[0] || (a[0]==b[0]&&a[1]<b[1]);
        }); 
        //一定要注意当a[0]==b[0]时，k小的放在前边
        //在身高一样，k不一样的时候，譬如[5,2]和[5,3], 对于最后排完的数组，
		//[5,2]必然在[5,3]的前面。所以如果遍历的时候[5,3]在前面，等它先插入完，
		//这个时候它前面会有3个大于等于它的数组对，遍历到[5,2]的时候，
		//它必然又会插入[5,3]前面（因为它会插入链表索引为2的地方），这个时候[5,3]前面就会有4个大于等于它的数组对了，这样就会出错。
        vector<vector<int>> res;
        for(auto&person:people){
            res.insert(res.begin()+person[1],person); //由此可见insert不一定非要在有连续元素的时候插入
        } //然后依次插入就可以
        return res;
    }
};


/*
56. 合并区间
以数组 intervals 表示若干个区间的集合，其中单个区间为 intervals[i] = [starti, endi] 。
请你合并所有重叠的区间，并返回一个不重叠的区间数组，该数组需恰好覆盖输入中的所有区间。

*/
class Solution56 {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        sort(intervals.begin(),intervals.end(),[](vector<int>&a,vector<int>&b)->bool{return a[0]<b[0];});
        //先按照左端点对区间进行排序，然后依次输入区间merge
        //最终的时间复杂度是nlogn
        //经过排序后，只要当前的区间不能与前一个区间merge，那么之后的区间也肯定不能与前一个区间merge 算是一种贪心
        vector<vector<int>> res;
        for(auto& vec:intervals){
            if (res.empty()){
                res.push_back(vec);
            }
            else{
                vector<int>& tmp = res.back();
                if (vec[0]>=tmp[0] && vec[0]<=tmp[1]){
                    vector<int> merged = {min(vec[0],tmp[0]),max(vec[1],tmp[1])};
                    res.pop_back();
                    res.push_back(merged);
                }
                else{
                    res.push_back(vec);
                }
            }
        }
        return res;

    }
};


/*
912. 排序数组
给你一个整数数组 nums，请你将该数组升序排列。

快速排序
*/
class Solution912 {
public:
    void sortsub(vector<int>& nums,int L,int R){
        if (L==R){
            return;
        }
        int pivot = nums[L];
        int left = L+1;
        int right = R-1;
        while(left<=right){
            if (nums[left]>pivot){
                swap(nums[left],nums[right]);
                right--;
            }
            else if (nums[left]<=pivot){
                left++;
            }
            else if (nums[right]<pivot){
                swap(nums[left],nums[right]);
                left++;
            }
            else if (nums[right]>=pivot){
                right--;
            }
        }
        swap(nums[L],nums[right]);
        sortsub(nums,L,right);
        sortsub(nums,right+1,R);
    }
    vector<int> sortArray(vector<int>& nums) {
        sortsub(nums,0,nums.size());
        return nums;
    }
};