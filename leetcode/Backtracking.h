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


/*
22. 括号生成
数字 n 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 有效的 括号组合。
*/
//这种回溯都有固定的套路
class Solution22 {
public:

    void DFS(string & str,vector<bool>& isvisit,string& storage)
    {
        optional<char> lastchar;
        for(int i = 0;i<str.size();i++){
            if (isvisit[i]==0){
                if (!lastchar.has_value()){
                    lastchar = str[i];
                }
                else if (lastchar==str[i])
                    continue;
                else
                    lastchar = str[i]; //用来去重的
                isvisit[i] = 1;

                storage.push_back(str[i]);

                if (str[i]=='(') //用来辅助剪枝
                    leftNum++;
                else if (str[i]==')')
                    rightNum++;
                bool Clip = 0;
                // https://leetcode-cn.com/problems/generate-parentheses/solution/hui-su-suan-fa-by-liweiwei1419/
                if (leftNum<rightNum) //当前加入到storage中使用的右括号数大于使用的左括号数则剪枝 因为右括号代表终止，右括号更多说明前边没有与之相匹配的左括号了，之后不管再怎么加括号都不能保证匹配
                    Clip = 1;
                if (storage[0]==')') //遇到这种情况直接剪枝 能节省不少计算量 这种情况实际上已经包含在了上边的if中
                    Clip = 1;
                if(Clip){ 

                }
                else{
                    // Valid.push_back(str[i]);
                    // int flag = 0;
                    // if (Valid.size()>=2 && *(Valid.end()-1)==')' && *(Valid.end()-2)=='('){
                    //     Valid.pop_back();
                    //     Valid.pop_back();
                    //     flag = 1;
                    // } //不能用辅助栈边递归边判断是否正确，用辅助栈的话很有可能把本不应该pop 的pop出去了
                    if (storage.size()==str.size()){
                        // vector<char> Valid ;
                        // for(int i = 0;i<storage.size();i++){
                        //     Valid.push_back(storage[i]);
                        //     if (Valid.size()>=2 && *(Valid.end()-1)==')' && *(Valid.end()-2)=='('){
                        //         Valid.pop_back();
                        //         Valid.pop_back();
                        //     }
                        // }
                        // if (Valid.empty()) //加上if (leftNum<rightNum)的剪枝后直接这个也不用判断
                            res.push_back(storage);
                    }
                    
                    DFS(str,isvisit,storage);
                }
                
                isvisit[i] = 0;
                if (*(storage.end()-1)=='('){
                    leftNum--;
                }
                else if (*(storage.end()-1)==')'){
                    rightNum--;
                } //用来辅助剪枝
                storage.pop_back();
                
            }
        }

    }

    vector<string> generateParenthesis(int n) {
        //整个程序的编写过程先是写DFS，按照生成有重复元素序列的全排列的方法来写 
        //然后在此基础上进行剪枝，最后写记录res的if语句 
        //按这个顺序或者说框架来一步一步写是不会出错的
        string str;
        for(int i = 0;i<n;i++){
            str.push_back('(');
        }
        for(int i = 0;i<n;i++){
            str.push_back(')');
        } //需要先排好序
        vector<bool> isvisit(2*n,0);
        string storage;
        leftNum = 0;
        rightNum = 0;
        DFS(str,isvisit,storage);
        return res;
    }
private:
    vector<string> res;
    int leftNum;
    int rightNum;
};