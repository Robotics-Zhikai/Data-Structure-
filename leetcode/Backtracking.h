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