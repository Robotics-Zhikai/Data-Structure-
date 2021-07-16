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



/*
560. 和为K的子数组
给定一个整数数组和一个整数 k，你需要找到该数组中和为 k 的连续的子数组的个数。

示例 1 :

输入:nums = [1,1,1], k = 2
输出: 2 , [1,1] 与 [1,1] 为两种不同的情况。
说明 :

数组的长度为 [1, 20,000]。
数组中元素的范围是 [-1000, 1000] ，且整数 k 的范围是 [-1e7, 1e7]。


*/

class Solution560 {
public:
    // int subarraySum(vector<int>& nums, int k) { //这里的双指针解法只有在nums肯定有序的时候才可行
	// 	sort(nums.begin(),nums.end());
	// 	int Lindex = 0;
	// 	int Rindex = 0;
	// 	int cur = 0;
	// 	int res = 0;

	// 	do{
	// 		while(Rindex<nums.size()){
	// 			cur+=nums[Rindex++];
	// 			if (cur>=k){
	// 				break;
	// 			}
	// 		}
	// 		if (cur==k){
	// 			res++;
	// 		}
	// 		while(Lindex<Rindex){
	// 			cur-=nums[Lindex++];
	// 			if (cur<=k){
	// 				break;
	// 			}
	// 		}
	// 		if (cur==k){
	// 			res++;
	// 		}
	// 	}while(Rindex!=nums.size());
	// 	return res;
    // }
	int solveMethod1(vector<int>& nums,int k){
		//n^2的时间复杂度 又超时了
		vector<int> acc(nums.size()+1,0); //后开
		acc[0] = 0;
		for(int i = 1;i<acc.size();i++){
			acc[i] = acc[i-1]+nums[i-1];
		}
		int res = 0;
		for(int i = 0;i<=nums.size();i++){
			for(int j = i+1;j<=nums.size();j++){
				if (acc[j]-acc[i]==k){
					res++;
				}
			}
		}
		return res;
	}
	int solveMethod2(vector<int>& nums,int k){
		//这个也太难写了。。。。。。。。。
		int acc = 0;
		map<int,int> MAP; //表示对应于某一键值的组合数有多少种
		int res = 0;
		for (int i = 0;i<nums.size();i++){
			acc += nums[i];
			if (acc==k){
				res++;
			}

            if (MAP.find(acc-k)!=MAP.end()){
                res+=MAP[acc-k];
            } //这两个if非常难写
			
			MAP[acc]++;
		}
		return res;
	}
	int subarraySum(vector<int>& nums, int k) {
		return solveMethod2(nums,k);
	}
};


//437跟上边的560是差不多的
/*
437. 路径总和 III
给定一个二叉树，它的每个结点都存放着一个整数值。

找出路径和等于给定数值的路径总数。

路径不需要从根节点开始，也不需要在叶子节点结束，但是路径方向必须是向下的（只能从父节点到子节点）。

二叉树不超过1000个节点，且节点数值范围是 [-1000000,1000000] 的整数。

*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution437 {
public:
    void DFS(TreeNode* root,int& targetSum,int & curSum){
		if (root==nullptr){
			return ;
		}
		curSum += root->val;
        if (curSum == targetSum){
            res++;
        }
		DFS(root->left,targetSum,curSum);
        curSum -= root->left==nullptr?0:root->left->val;
		DFS(root->right,targetSum,curSum);
        curSum -= root->right==nullptr?0:root->right->val;
	}
	int res = 0;
    int solveMethod1(TreeNode* root,int targetSum){
        //这个是O(n^2)的复杂度
        if(root == nullptr){
            return 0;
        }
        int curSum = 0;
		DFS(root,targetSum,curSum);
        pathSum(root->left,targetSum);
		pathSum(root->right,targetSum);
		return res;
    }
    void DFS(map<int,int>&MAP,TreeNode* root,int targetSum,int& curSum){
        if (root==nullptr){
            return;
        }

        curSum+=root->val;
        if (curSum == targetSum){
            res++;
        }
		if (MAP.find(curSum-targetSum)!=MAP.end()){
			res+=MAP[curSum-targetSum];
		}
        MAP[curSum]++;
        DFS(MAP,root->left,targetSum,curSum);
        if (root->left!=nullptr)
            MAP[curSum]--;
        curSum -= root->left==nullptr?0:root->left->val;
		
        DFS(MAP,root->right,targetSum,curSum);
        if (root->right!=nullptr)
            MAP[curSum]--;
        curSum -= root->right==nullptr?0:root->right->val;
		

    }
    int solveMethod2(TreeNode* root,int targetSum){
        //还是前缀和，跟在数组上进行前缀和是一样的
        //这样的话就直接降到了N的复杂度
		map<int,int> MAP;
		int curSum = 0;
		DFS(MAP,root,targetSum,curSum);
		return res;
    }
    int pathSum(TreeNode* root, int targetSum) {
        return solveMethod2(root,targetSum);
    }
};