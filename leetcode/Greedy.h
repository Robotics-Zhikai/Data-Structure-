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