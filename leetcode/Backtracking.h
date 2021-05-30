#pragma once
#include "main.h"

/*
剑指 Offer 38. 字符串的排列
输入一个字符串，打印出该字符串中字符的所有排列。
你可以以任意顺序返回这个字符串数组，但里面不能有重复元素。

题解中有一个swap的方法，速度还挺快的，看不太懂 就暂时先用这种本办法吧
*/

class SolutionOffer38
{
public:
    void recur(const string&str,vector<bool>& isvisited,int index,string& tmp,vector<string>& vecstr)
    {
        isvisited[index] = 1;
        
        tmp.push_back(str[index]);
        if (tmp.size()==str.size())
            vecstr.push_back(tmp);

        set<char> uniqueChar;
        for(int i = 0;i<str.size();i++){
            if (isvisited[i]==0 && uniqueChar.find(str[i])==uniqueChar.end()){ //多了一步剪枝，每层不能有重复元素
                uniqueChar.insert(str[i]);
                recur(str,isvisited,i,tmp,vecstr);
            }
        }
        
        isvisited[index] = 0;
        tmp.pop_back();
    }
    vector<string> permutation(string s) 
    {
        vector<bool> isvisited(s.size(),0);
        string tmp;
        vector<string> vecstr;
        set<char> uniqueChar;
        for (int i = 0;i<s.size();i++){
            if (uniqueChar.find(s[i])==uniqueChar.end()){
                uniqueChar.insert(s[i]);
                recur(s,isvisited,i,tmp,vecstr);
            }
        }
        return vecstr; 
    }

};


/*
46. 全排列
给定一个不含重复数字的数组 nums ，返回其 所有可能的全排列 。你可以 按任意顺序 返回答案。

*/
//跟上边的大同小异 就是做一个DFS而已 挺简单的
class Solution46 {
public:
    vector<vector<int>> res;
    void DFS(vector<int>&nums,vector<bool>& isvisited,int index,vector<int>&storage)
    {
        isvisited[index] = 1;
        storage.push_back(nums[index]);
        if (storage.size()==nums.size()){
            res.push_back(storage);
        }
        else{
            for(int i = 0;i<nums.size();i++){
                if (isvisited[i]==0){
                    DFS(nums,isvisited,i,storage);
                }
            }
        }
        isvisited[index]=0;
        storage.pop_back();
        
    }

    vector<vector<int>> permute(vector<int>& nums) {
        res = {};
        vector<bool> isvisited(nums.size(),0);
        vector<int> storage;
        for(int i = 0;i<nums.size();i++){
            DFS(nums,isvisited,i,storage);
        }
        return res;
    }   
};

/*
47. 全排列 II
给定一个可包含重复数字的序列 nums ，按任意顺序 返回所有不重复的全排列。
*/
class Solution47 {
public:
    void DFS(vector<int>& nums,vector<bool>& isvisited,vector<int>& storage)
    {
        optional<int> lastNum = {};
        for(int i = 0;i<nums.size();i++){

            if (isvisited[i]==0){
                if (!lastNum.has_value()){
                    lastNum = nums[i];
                }
                else if (nums[i]==lastNum){
                    continue;       //这里以常数时间剪枝掉重复的排列
                }
                else
                    lastNum = nums[i]; 

                isvisited[i] = 1; //把这个放在for循环里边的话就不用像46全排列I中在主函数for循环了
                storage.push_back(nums[i]);
                if (storage.size()==nums.size())
                    res.push_back(storage);
                DFS(nums,isvisited,storage); 
                isvisited[i] = 0;
                storage.pop_back();
            }
        }
    }

    vector<vector<int>> permuteUnique(vector<int>& nums) {
        res = {};
        sort(nums.begin(),nums.end()); //排序后在之后的建树过程中就能以常数时间剪掉重复排列的根节点
        //注意理解这个排序 否则如果不排序的话判断同一层的节点是否是重复的只能加一个hash，这样的话代价是很大的
        //保证相同的数字都相邻，然后每次填入的数一定是这个数所在重复数集合中「从左往右第一个未被填过的数字」
        vector<bool>isvisited(nums.size(),0);
        vector<int> storage;
        DFS(nums,isvisited,storage);
        return res;
    }
private:
    vector<vector<int>> res;
};

/*
39. 组合总和
给定一个无重复元素的数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。

candidates 中的数字可以无限制重复被选取。

说明：

所有数字（包括 target）都是正整数。
解集不能包含重复的组合。 (实现这个是难点)

*/

class Solution39 {
public:
    
    void DFS(vector<int>& candidates, int target,int index,int Sum,vector<int>&storage)
    {
        Sum+=candidates[index];
        storage.push_back(candidates[index]);
        
        if (Sum==target){
            result.push_back(storage);
        }     
        for(int i = index;i<candidates.size();i++){ 
            //每次都选其本身和后边的几个作为子节点，否则就会选重（这跟n个数里边挑不重复的两个数的方法类似）
            //这里容易出错，for循环中i的初始值不能是0，应该是index，才能避免元素顺序不同的重复集
            //https://leetcode-cn.com/problems/combination-sum/solution/shou-hua-tu-jie-zu-he-zong-he-combination-sum-by-x/ 可以看这个里边画的图去理解避免重复的原理
            if (Sum+candidates[i]>target)
                continue; //直接剪枝
            else 
                DFS(candidates,target,i,Sum,storage);
        }
        storage.pop_back();
    }

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<int> storage;
        result = {};
        for(int i = 0;i<candidates.size();i++){
            DFS(candidates,target,i,0,storage);
        }
        return result;
    }
private:
    vector<vector<int>> result;
};