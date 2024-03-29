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
    vector<int> solveMethod1Review(vector<int>& nums, int target){
        vector<vector<int>> numsindex;
        for(int i = 0;i<nums.size();i++){
            numsindex.push_back(vector<int>{nums[i],i});
        }
        sort(numsindex.begin(),numsindex.end(),[](vector<int>&a,vector<int>&b)->bool{return a[0]<b[0];});
        int left = 0;
        int right = nums.size()-1;
        vector<int > res;
        while(left<right){
            if (numsindex[left][0]+numsindex[right][0]<target){
                do{
                    left++;
                }while(left<numsindex.size() && numsindex[left][0]==numsindex[left-1][0]);
            }
            else if (numsindex[left][0]+numsindex[right][0]>target){
                do{
                    right--;
                }while(right>=0 && numsindex[right][0]==numsindex[right+1][0]);
            }
            else{
                res = vector<int>{numsindex[left][1],numsindex[right][1]};
                do{
                    left++;
                }while(left<numsindex.size() && numsindex[left][0]==numsindex[left-1][0]);
                do{
                    right--;
                }while(right>=0 && numsindex[right][0]==numsindex[right+1][0]);
            }
        }

        return res;
    }
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
    vector<int> solveMethod2Review(vector<int>&nums,int target){
        map<int,int> MAP;
        for(int i = 0;i<nums.size();i++){
            MAP[nums[i]] = i;
        }
        for(int i = 0;i<nums.size();i++){
            if (MAP.find(target-nums[i])!=MAP.end() && MAP[target-nums[i]]!=i){
                return vector<int>{i,MAP[target-nums[i]]};
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

/*
438. 找到字符串中所有字母异位词
给定两个字符串 s 和 p，找到 s 中所有 p 的 异位词 的子串，返回这些子串的起始索引。不考虑答案输出的顺序。

异位词 指字母相同，但排列不同的字符串。

*/
class Solution438 {
public:
    bool match(string&s1,string&s2,vector<bool>&isvist,int index2){
        if (index2==s2.size()){
            return 1;
        }
        for(int i = 0;i<s1.size();i++){
            if (s1[i]==s2[index2] && isvist[i]==0){
                isvist[i] = 1;
                if (match(s1,s2,isvist,index2+1)){
                    return 1;
                }
                else{
                    return 0;
                }
            }
        }
        return 0;
    }
    vector<int> solveMethod1(string s,string p){
        //这个直接超时了
        int sum = 0;
        for(char&c:p){
            sum+=(c-'a');
        }
        if (p.empty())
            return {};
        if (s.size()<p.size()){
            return {};
        }
        int init = -1;
        vector<int> res;
        for(int i = 0;i<=s.size()-p.size();i++){
            if (init==-1){
                init = 0;
                for(int j = 0;j<p.size();j++){
                    init+=(s[j]-'a');
                }
            }
            else{
                init = init-(s[i-1]-'a')+(s[i+p.size()-1]-'a');
            }
            if (init==sum){ //不能单纯看加起来的和是否相等
                string windowstr(s.begin()+i,s.begin()+i+p.size());
                vector<bool> isvist(p.size(),0);
                if (match(windowstr,p,isvist,0)){
                    res.push_back(i);
                }
            }
        }
        return res;
    }
    vector<int> solveMethod2(string s,string p){
        vector<int> freqTarget(26,0); //map
        vector<int> freqCur(26,0);
        for(char c:p){
            freqTarget[c-'a']++;
        }
        if (s.size()<p.size()){
            return {};
        }
        vector<int> res;
        for(int i = 0;i<=s.size()-p.size();i++){
            if (i==0){
                for(int j = 0;j<p.size();j++){
                    freqCur[s[j]-'a']++;
                }
            }
            else{
                freqCur[s[i-1]-'a']--;
                freqCur[s[i+p.size()-1]-'a']++; //可以直接用hash表，比用DFS判断是否match效率高多了
            }
            if (freqCur==freqTarget){ //注意这里vector可以直接看是否相等
                res.push_back(i);
            }
        }
        return res;
    }

    vector<int> findAnagrams(string s, string p) {
        return solveMethod2(s,p);
    }
};

/*
49. 字母异位词分组
给定一个字符串数组，将字母异位词组合在一起。可以按任意顺序返回结果列表。

字母异位词指字母相同，但排列不同的字符串。


*/

class Solution49 {
public:
    vector<vector<string>> solveMethod1(vector<string>& strs){
        map<vector<int>,vector<string>> MAP;
        for(auto & str:strs){
            vector<int> tmp(26,0);
            for(char c:str){
                tmp[c-'a']++;
            }
            MAP[tmp].push_back(str);
        }
        vector<vector<string>> res;
        for(auto&pair:MAP){
            res.push_back(pair.second);
        }
        return res;
    }
    vector<vector<string>> solveMethod2(vector<string>& strs){
        map<string,vector<string>> MAP;
        for(auto & str:strs){
            string tmp = str;
            sort(tmp.begin(),tmp.end());
            MAP[tmp].push_back(str);
        }
        vector<vector<string>> res;
        for(auto&pair:MAP){
            res.push_back(pair.second);
        }
        return res;
    }
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        return solveMethod2(strs);
    }
};


/*
面试题3. 数组中重复的数字
找出数组中重复的数字。

在一个长度为 n 的数组 nums 里的所有数字都在 0～n-1 的范围内。
数组中某些数字是重复的，但不知道有几个数字重复了，也不知道每个数字重复了几次。请找出数组中任意一个重复的数字。
*/
class SolutionOffer3 {
public:
    int solveMethod1(vector<int>&nums){
        //n的时间复杂度，n的空间复杂度
        unordered_set<int> SET;
        for(int n:nums){
            if (SET.find(n)==SET.end())
                SET.insert(n);
            else{
                return n;
            }
        }
        return 0;
    }
    int solveMethod2(vector<int>&nums){
        //n的时间复杂度，1的空间复杂度
        //https://leetcode-cn.com/problems/shu-zu-zhong-zhong-fu-de-shu-zi-lcof/solution/mian-shi-ti-03-shu-zu-zhong-zhong-fu-de-shu-zi-yua/
        int i = 0;
        while(i<nums.size()){
            if (i==nums[i]){
                i++;
                continue;
            }
            if (nums[i]==nums[nums[i]]){
                return nums[i];
            }
            swap(nums[i],nums[nums[i]]);
        }
        return 0;
    }
    int findRepeatNumber(vector<int>& nums) {
        return solveMethod2(nums);
    }
};



/*
554. 砖墙
你的面前有一堵矩形的、由 n 行砖块组成的砖墙。
这些砖块高度相同（也就是一个单位高）但是宽度不同。每一行砖块的宽度之和相等。

你现在要画一条 自顶向下 的、穿过 最少 砖块的垂线。如果你画的线只是从砖块的边缘经过，就不算穿过这块砖。
你不能沿着墙的两个垂直边缘之一画线，这样显然是没有穿过一块砖的。

给你一个二维数组 wall ，该数组包含这堵墙的相关信息。其中，wall[i] 是一个代表从左至右每块砖的宽度的数组。
你需要找出怎样画才能使这条线 穿过的砖块数量最少 ，并且返回 穿过的砖块数量 。


*/
class Solution554 {
public:
    int solveMethod1(vector<vector<int>>& wall){
        //直接超时了，应该有剪枝的
        int sumlen = 0;
        for(int e:wall[0]){
            sumlen+=e;
        }
        vector<set<float>> vecSet(wall.size(),set<float>{});
        set<float> bianjie;
        for(int i = 0;i<wall.size();i++){
            set<float> acc;
            float accnum = 0;
            acc.insert(accnum);
            
            for(int j = 0;j<wall[i].size();j++){
                accnum+=wall[i][j];
                acc.insert(accnum);
                bianjie.insert(accnum);
            }
            vecSet[i] = acc;
        }
        int res = INT_MAX;
        for(float j = 0.5;j<sumlen;j=j+0.5){
            int throughCount = 0;
            for(auto & SET:vecSet){
                if (SET.find(j)==SET.end()){
                    throughCount++;
                }
            }
            if (throughCount<res){
                res = throughCount;
            }
        }
        return res;
    }
    int solveMethod2(vector<vector<int>>& wall){
        //间隙最多的就是历经砖块最少的
        unordered_map<int,int> MAP;
        int sumlen = 0;
        for(int e:wall[0]){
            sumlen+=e;
        }
        for(int i = 0;i<wall.size();i++){
            int acc = 0;
            for(int j = 0;j<wall[i].size();j++){
                acc+=wall[i][j];
                if (acc!=sumlen)
                    MAP[acc]++;
            }
        }
        int res = INT_MIN;
        for(auto& ele:MAP){
            if (ele.second>res){
                res = ele.second;
            }
        }
        res = wall.size()-res;
        return res<0?wall.size():res;
    }
    int leastBricks(vector<vector<int>>& wall) {
        return solveMethod2(wall);
    }
};


/*
1094. 拼车
假设你是一位顺风车司机，车上最初有 capacity 个空座位可以用来载客。
由于道路的限制，车 只能 向一个方向行驶（也就是说，不允许掉头或改变方向，你可以将其想象为一个向量）。

这儿有一份乘客行程计划表 trips[][]，其中 trips[i] = [num_passengers, start_location, end_location] 
包含了第 i 组乘客的行程信息：

必须接送的乘客数量；
乘客的上车地点；
以及乘客的下车地点。
这些给出的地点位置是从你的 初始 出发位置向前行驶到这些地点所需的距离（它们一定在你的行驶方向上）。

请你根据给出的行程计划表和车子的座位数，来判断你的车是否可以顺利完成接送所有乘客的任务
（当且仅当你可以在所有给定的行程中接送所有乘客时，返回 true，否则请返回 false）。
*/
class Solution1094 {
public:
    bool carPooling(vector<vector<int>>& trips, int capacity) {
        unordered_map<int,int> upPeaple;
        unordered_map<int,int> downPeaple;
        int endloc = INT_MIN;
        for(int i = 0;i<trips.size();i++){
            endloc = max(endloc,trips[i][2]);
            upPeaple[trips[i][1]]+=trips[i][0];
        }
        for(int i = 0;i<trips.size();i++){
            downPeaple[trips[i][2]]+=trips[i][0];
        }
        int curcap = capacity;
        for(int i = 0;i<=endloc;i++){
            curcap = curcap+downPeaple[i];
            if (curcap<upPeaple[i]){
                return false;
            }
            curcap-=upPeaple[i];
        }
        return true;
    }
};


/*
73. 矩阵置零
给定一个 m x n 的矩阵，如果一个元素为 0 ，则将其所在行和列的所有元素都设为 0 。请使用 原地 算法。

进阶：

一个直观的解决方案是使用  O(mn) 的额外空间，但这并不是一个好的解决方案。
一个简单的改进方案是使用 O(m + n) 的额外空间，但这仍然不是最好的解决方案。
你能想出一个仅使用常量空间的解决方案吗？
*/
class Solution73 {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        bool firstcolZero = 0;
        bool firstrowZero = 0;
        for(int i=0;i<matrix.size();i++){
            if (matrix[i][0]==0){
                firstcolZero = 1;
                break;
            }
        }
        for(int j = 0;j<matrix[0].size();j++){
            if (matrix[0][j]==0){
                firstrowZero = 1;
                break;
            }
        }
        for(int i = 1;i<matrix.size();i++){
            for(int j = 1;j<matrix[i].size();j++){
                if (matrix[i][j]==0){
                    matrix[i][0] = 0;//矩阵的第一行和第一列分别负责标记对应的列和行是否是0
                    matrix[0][j] = 0;
                }
            }
        }
        for(int i=1;i<matrix.size();i++){
            if (matrix[i][0]==0){
                for(int j = 1;j<matrix[i].size();j++){
                    matrix[i][j] = 0;
                }
            }
        }
        for(int j = 1;j<matrix[0].size();j++){
            if (matrix[0][j]==0){
                for(int i = 1;i<matrix.size();i++){
                    matrix[i][j] = 0;
                }
            }
        }
        if (firstcolZero){
            for(int i = 0;i<matrix.size();i++){
                matrix[i][0] = 0;
            }
        }
        if (firstrowZero){
            for(int j = 0;j<matrix[0].size();j++){
                matrix[0][j] = 0;
            }
        }
    }
};