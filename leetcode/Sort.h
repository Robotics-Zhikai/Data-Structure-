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