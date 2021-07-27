#pragma once
#include "main.h"

/*

55. 跳跃游戏
给定一个非负整数数组 nums ，你最初位于数组的 第一个下标 。

数组中的每个元素代表你在该位置可以跳跃的最大长度。

判断你是否能够到达最后一个下标。


*/

class Solution55 {
public:
	bool solveMethod1(vector<int>& nums){
		//这个直接超时了，运行的正确性应该是能够保证的
		return DFS(nums,0,nums.size()-1);
	}
    bool DFS(vector<int>& nums,int index,const int& finalindex){
		if (index == finalindex){
			return 1;
		}
		if (index>=nums.size()){
			return 0;
		}
		for(int i = 1;i<=nums[index];i++){
			if (DFS(nums,index+i,finalindex))
				return 1;
		}
		return 0;
	}

	bool solveMethod2(vector<int>& nums){
		//这个也是超时了，因为是n^2的时间复杂度
		vector<bool> dp(nums.size(),0);//dp[i]表示下标i是否可达
		dp[0] = 1;
		for(int i = 1;i<dp.size();i++){
			for(int j = 0;j<i;j++){
				if (dp[j]==1 && (i-j<=nums[j])){
					dp[i] = 1;
					break;
				}
			}
		}
		return dp.back();
	}

	bool solveMethod3(vector<int>& nums){
        //时间复杂度为n 空间复杂度为1 实际上就是一个贪心
		int index = 0;
		int reachable = 0;
		while(index<nums.size() && index<=reachable){
			if (index+nums[index]>reachable){
				reachable = index+nums[index];
			}
			index++;
		}
		if (reachable>=nums.size()-1){
			return 1;
		}
		else
			return 0;
	}

    bool canJump(vector<int>& nums) {
		return solveMethod3(nums);
    }
};

/*
45. 跳跃游戏 II
给你一个非负整数数组 nums ，你最初位于数组的第一个位置。

数组中的每个元素代表你在该位置可以跳跃的最大长度。

你的目标是使用最少的跳跃次数到达数组的最后一个位置。

假设你总是可以到达数组的最后一个位置。

*/

class Solution {
public:
	int solveMethod1(vector<int>&nums){
		//用这个二维dp直接超时了，但是正确性是可以保证的
		//这是n^3的时间复杂度
		vector<vector<int>> dp(nums.size(),vector<int>(nums.size(),INT_MAX)); //dp[i][j]表示从i调到j的最少跳跃次数
		for(int i = 0;i<nums.size();i++){
			dp[i][i] = 0;
		}
		for(int len = 1;len<nums.size();len++){
			for(int i = 0;i<nums.size()-len;i++){
				if (nums[i]>=len){
					dp[i][i+len] = 1;
				}
				else{
					dp[i][i+len] = INT_MAX;
				}
				
				for(int j = i;j<i+len;j++){
					if (dp[i][j]!=INT_MAX && dp[j][i+len]!=INT_MAX){
						dp[i][i+len] = min(dp[i][i+len],dp[i][j]+dp[j][i+len]);
					}
				}
			}
		}
		return dp[0][nums.size()-1];
	}
	int solveMethod2(vector<int>&nums){
		//这是n^2的时间复杂度
		vector<int> dp(nums.size(),INT_MAX);//dp[i]表示从0跳到i的最少跳跃次数
		dp[0] = 0;
		for(int i = 1;i<dp.size();i++){
			for(int j = 0;j<i;j++){
				if (j+nums[j]>=i){
					dp[i] = min(dp[i],dp[j]+1);
				}
			}
		}
		return dp.back();
	}
	int solveMethod3(vector<int>& nums){
		//应该是有n的时间复杂度的贪心算法
        //太难写了！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
		int beginindex = 0;
		int maxindex = 0;
		int upper = 0;
		int res = 0;
		//在遍历数组时，我们不访问最后一个元素，这是因为在访问最后一个元素之前，
		//我们的边界一定大于等于最后一个位置，否则就无法跳到最后一个位置了。
		//如果访问最后一个元素，在边界正好为最后一个位置的情况下，
		//我们会增加一次「不必要的跳跃次数」，因此我们不必访问最后一个元素。
		for(int i = 0;i<nums.size()-1;i++){
			maxindex = max(i+nums[i],maxindex);
			if (i==upper){
				res++;
				upper = maxindex;
			}
		}
		return res;
	}
    int jump(vector<int>& nums) {
		return solveMethod3(nums);
        return solveMethod2(nums);
    }
};