#pragma once
#include "main.h"

/*
剑指 Offer 67. 把字符串转换成整数
写一个函数 StrToInt，实现把字符串转换成整数这个功能。不能使用 atoi 或者其他类似的库函数。
首先，该函数会根据需要丢弃无用的开头空格字符，直到寻找到第一个非空格的字符为止。

当我们寻找到的第一个非空字符为正或者负号时，则将该符号与之后面尽可能多的连续数字组合起来，作为该整数的正负号；
假如第一个非空字符是数字，则直接将其与之后连续的数字字符组合起来，形成整数。
该字符串除了有效的整数部分之后也可能会存在多余的字符，这些字符可以被忽略，它们对于函数不应该造成影响。
注意：假如该字符串中的第一个非空格字符不是一个有效整数字符、字符串为空或字符串仅包含空白字符时，
则你的函数不需要进行转换。
在任何情况下，若函数不能进行有效的转换时，请返回 0。
说明：
假设我们的环境只能存储 32 位大小的有符号整数，那么其数值范围为 [−231,  231 − 1]。
如果数值超过这个范围，请返回  INT_MAX (231 − 1) 或 INT_MIN (−231) 。

*/
//一定不要基于case编程，那样编出来的代码想起来复杂，且鲁棒性差。一定要想一个固定的模式

class SolutionOffer67 {
public:
    int strToInt(string str) {
        optional<int> sigh = {};
        long int num = 0; //判断溢出的算法在面试时不太好想，就先用long替代吧
        for (int i = 0;i<str.size();i++){
        //核心思路是先判断字符串的正负，判断成功后就按照既定的计算十进制数的方法，一旦碰到不符的情况，就退出
            if (sigh.has_value()==0&&str[i]==' '){
                continue;
            }
            else if (sigh.has_value()==0&&str[i]=='+'){
                sigh = 1;
            }
            else if (sigh.has_value()==0&&str[i]=='-'){
                sigh = -1;
            }
            else if (sigh.has_value()==0&&str[i]>='0'&&str[i]<='9'){
                sigh = 1;
                num = num*10 + (str[i]-'0');
                if(num>INT_MAX)
                    return INT_MAX;
                else if (num<INT_MIN)
                    return INT_MIN;
            }
            else if (sigh.has_value()&&str[i]>='0'&&str[i]<='9'){
                num = num*10 + (str[i]-'0');
                if(num>INT_MAX){
                    if (sigh==1)
                        return INT_MAX;
                    else
                        return INT_MIN;
                }
                    
                else if (num<INT_MIN){
                    if(sigh==1)
                        return INT_MIN;
                    else
                        return INT_MAX;
                }
            }
            else if(num!=0) //这里容易出错，是经过一连串数后来了个空格或者字母
                break;
            else
                return 0;
        }
        if (sigh.has_value()==0)
            return 0;
        return sigh.value()*num;
    }
};

/*
剑指 Offer 50. 第一个只出现一次的字符
在字符串 s 中找出第一个只出现一次的字符。如果没有，返回一个单空格。 s 只包含小写字母。

*/
class SolutionOffer50 {
public:
    char firstUniqChar(string s) {
        vector<int> MAP(26,0);
        for(char c:s){
            MAP[c-'a']++;
        }
        for(char c:s){
            if(MAP[c-'a']==1){
                return c;
            }
        }
        return ' ';
    }
};


/*
14. 最长公共前缀
编写一个函数来查找字符串数组中的最长公共前缀。

如果不存在公共前缀，返回空字符串 ""。
*/
class Solution14 {
public:
    string longestCommonPrefix(vector<string>& strs) {
        if (strs.empty()){
            return "";
        }
        if (strs.size()==1){
            return strs[0];
        }
        int index = 0;
        while(1){
            int i = 1;
            for(;i<strs.size();i++){
                if (index>=strs[i].size() || strs[i][index]!=strs[i-1][index]){
                    break;
                }
            }
            if (i!=strs.size()){
                return strs[0].substr(0,index);
            }
            index++;
        }
    }
};