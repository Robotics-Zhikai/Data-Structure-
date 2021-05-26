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