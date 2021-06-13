#pragma once
#include "main.h"

/*
剑指 Offer 48. 最长不含重复字符的子字符串
请从字符串中找出一个最长的不包含重复字符的子字符串，计算该最长子字符串的长度。

*/
class SolutionOffer48 {
public:
	int lengthOfLongestSubstringUnorderedMap(string s)
	{
		int maxLen = 0;
		int curmaxlen = 0;
		unordered_map<char, int> mapping;
		for (int i = 0; i<s.size(); i++)
		{
			char cur = s[i];
			if (mapping.find(cur) == mapping.end()) //没找到
			{
				mapping[cur] = i;
				curmaxlen++;
			}
			else  //找到了
			{
				if (i - mapping[cur]>curmaxlen)
				{
					curmaxlen++;
				}
				else
				{
					curmaxlen = i - mapping[cur];
				}
				mapping[cur] = i;
			}
			if (curmaxlen>maxLen)
				maxLen = curmaxlen;
		}
		return maxLen;
	}
	int lengthOfLongestSubstringChararray(string s)
		//也用到了点滑动窗口的思想
	{
		int maxLen = 0;
		int curmaxlen = 0;
		int mapping[128]; //ASCII码一共有128个 哈希表主要是用来在常数时间内判断是否当前的最长字串有重复的字母
						  //否则用线性扫描的话就是O(n)的复杂度来判断是否有重复
		memset(mapping, -1, sizeof(mapping));
		for (int i = 0; i<s.size(); i++)
		{
			char cur = s[i];
			if (mapping[cur] == -1) //没找到
			{
				mapping[cur] = i;
				curmaxlen++; //curmaxlen其实就是滑动窗口的大小
			}
			else  //找到了
			{
				if (i - mapping[cur]>curmaxlen)
				{
					curmaxlen++;
				}
				else
				{
					curmaxlen = i - mapping[cur]; //重复元素落在了滑动窗口之内，缩小滑动窗口
				}
				mapping[cur] = i;
			}
			if (curmaxlen>maxLen)
				maxLen = curmaxlen;
		}
		return maxLen;
	}
	int lengthOfLongestSubstring(string s) {
		//return lengthOfLongestSubstringUnorderedMap(s);//12ms 8MB 73.59% 68.24%
		return lengthOfLongestSubstringChararray(s);//用Hash数组代替unorderedmap的话是4ms 7MB 96.97% 80.79% 
													//空间复杂度有改进，时间复杂度相同，都是O(n)
	}
};


/*
1. 两数之和
给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出 和为目标值 target  的那 两个 整数，并返回它们的数组下标。

你可以假设每种输入只会对应一个答案。但是，数组中同一个元素在答案里不能重复出现。

你可以按任意顺序返回答案。

*/
class Solution1 {
public:
    vector<int> solveMethod1(vector<int>& nums, int target){
        //这个是用nlogn的时间复杂度，n的空间复杂度
        //跟三数之和用到的方法差不多
        int left = 0;
        int right = nums.size()-1;
        vector<vector<int>> copynums;
        for (int i = 0;i<nums.size();i++){
            copynums.push_back({i,nums[i]});
        }
        sort(copynums.begin(),copynums.end(),[](vector<int>&a,vector<int>&b){return a[1]<b[1];});
        while(left<right){
            int cur = copynums[left][1]+copynums[right][1];
            if (cur>target){
                do{
                    right--;
                }while(right>=0 && copynums[right][1]==copynums[right+1][1]);
            }
            else if (cur<target){
                do{
                    left++;
                }while(left<copynums.size() && copynums[left][1]==copynums[left-1][1]);
            }
            else{
                return {copynums[left][0],copynums[right][0]};
            }
        }
        return {};
    }
    vector<int> solveMethod2(vector<int>& nums, int target){
        unordered_map<int,int> MAP;
        for(int i = 0;i<nums.size();i++){
            MAP.insert({nums[i],i});
        }
        for(int i = 0;i<nums.size();i++){
            auto right = MAP.find(target-nums[i]);
            if (right != MAP.end() ){
                if (right->second==i)
                    continue;
                return {i,right->second};
            }
        }
        return {};
    }
    vector<int> solveMethod3(vector<int>& nums, int target){
        //两数之和肯定有两个数，按照下边的方法求解
        unordered_map<int,int> MAP;
        for (int i = 0;i<nums.size();i++){
            auto Find = MAP.find(target-nums[i]);
            if (Find!=MAP.end()){
                return {Find->second,i};
            }
            MAP[nums[i]] = i;
        }
        return {};
    }
    //这个HASH的实现贼难写。。要多写！！！！！！
    vector<int> twoSum(vector<int>& nums, int target) {
        return solveMethod3(nums,target);
        return solveMethod2(nums,target);
    }
};