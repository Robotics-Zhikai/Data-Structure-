#pragma once
#include "main.h"

/*
剑指 Offer 56 - I. 数组中数字出现的次数
一个整型数组 nums 里除两个数字之外，其他数字都出现了两次。
请写程序找出这两个只出现一次的数字。要求时间复杂度是O(n)，空间复杂度是O(1)。

*/

class SolutionOffer56_I {
public:
    vector<int> singleNumbers(vector<int>& nums) {
        int sum = 0;
        for(auto n:nums){ //两两相同的数异或得到的结果为0，最终只要有某一位为1，则说明参与异或的数中有题目描述的异类
            sum = sum^n;
        }
        
        int index= 1;
        while(index!=0&&((sum&index)==0)){ //这个也是，按位与时要注意运算符优先级
            index = index<<1;
        }//这就找到了第一次出现1的位
        cout<<index<<endl;
        int sum1 = 0;
        int sum2 = 0;
        for(int n : nums){ 
        //找到最低出现1的位后，再扫一遍nums，根据对应的位是否为1来区分成两部分。只有一个的两个数肯定分在了两堆。且
        //有两个的数肯定分在相同堆。
            if ((index&n)!=0){ //注意优先级，不确定优先级的加括号
                sum1 = sum1 ^ n;
            }
            else{
                sum2 = sum2 ^ n;
            }
               
        }
        return {sum1,sum2};
    }
};



/*
剑指 Offer 56 - II. 数组中数字出现的次数 II
在一个数组 nums 中除一个数字只出现一次之外，其他数字都出现了三次。请找出那个只出现一次的数字。

*/

class SolutionOffer56_II {
public:
    int HASHMAPmethod(vector<int> & nums){ //空间复杂度是n，时间复杂度是n
        map<int,int> MAP;
        for(auto n:nums){
            if (MAP.find(n)==MAP.end()){
                MAP[n] = 1;
            }
            else
                MAP[n]++;
        }
        for(auto n:MAP){
            if(n.second == 1){
                return n.first;
            }
        }
        return -1;
    }
    
    int SpaceO1method(vector<int> & nums){ //空间复杂度是1，时间复杂度是n
        vector<int> bitstorage(32,0);
        for(int n:nums){
            unsigned int index = 1; 
            //这个index为int时，当最高位为1时就不能继续左移了 所以设置为unsigned int       
            for(int i = bitstorage.size()-1;i>=0;i--){
                bitstorage[i]+=((n&index)==0?0:1); //这里容易出错，注意统计位的方法,不能直接加(n&index)
                index = index<<1;
            }
        }
        int res = 0;
        for(int i = 0;i<bitstorage.size();i++){
            res = res*2+(bitstorage[i]%3);
        }
        return res;
    }
    int SpaceO1methodLESSSpace(vector<int>& nums) { //更小占用空间的方法
        int ret = 0; //这个代码写的太溜了
        for (int i = 0; i < 32; i++) {
            int temp = 0;
            for (int &num: nums) 
               temp += ((num >> i) & 1);
            ret += ((temp % 3) << i);
        }
        return ret;
    }
    int singleNumber(vector<int>& nums) {
        return SpaceO1methodLESSSpace(nums);
        return SpaceO1method(nums);
        return HASHMAPmethod(nums);
    }
};

/*
剑指 Offer 20. 表示数值的字符串
请实现一个函数用来判断字符串是否表示数值（包括整数和小数）。

数值（按顺序）可以分成以下几个部分：

若干空格
一个 小数 或者 整数
（可选）一个 'e' 或 'E' ，后面跟着一个 整数
若干空格
小数（按顺序）可以分成以下几个部分：

（可选）一个符号字符（'+' 或 '-'）
下述格式之一：
至少一位数字，后面跟着一个点 '.'
至少一位数字，后面跟着一个点 '.' ，后面再跟着至少一位数字
一个点 '.' ，后面跟着至少一位数字
整数（按顺序）可以分成以下几个部分：

（可选）一个符号字符（'+' 或 '-'）
至少一位数字

*/
class SolutionOffer20 {
public:
    bool isNumber(string s) { //题解中用到的是状态机的方法 这个有空要多看看，难点在于归纳各种正确的情况
        //去掉首尾空格
        s.erase(0,s.find_first_not_of(' '));
        s.erase(s.find_last_not_of(' ')+1,s.size());
        if (s.size() == 0) return false;
        
    
        bool numFlag = false;
        bool dotFlag = false;
        bool eFlag = false;
        for (int i = 0; i < s.size(); i++) {
            //判定为数字，则标记numFlag
            if (s[i] >= '0' && s[i] <= '9') {
                numFlag = true;
                //判定为.  需要没出现过.并且没出现过e .最多出现一次，且在e的前边
            } else if (s[i] == '.' && !dotFlag && !eFlag) {
                dotFlag = true;
                //判定为e，需要没出现过e，并且出过数字了 e最多出现一次，且出现前有数字
            } else if ((s[i] == 'e' || s[i] == 'E') && !eFlag && numFlag) {
                eFlag = true;
                numFlag = false;//为了避免123e这种请求，出现e之后就标志为false，因为此时e已经是最后一位了
                //判定为+-符号，只能出现在第一位或者紧接e后面
            } else if ((s[i] == '+' || s[i] == '-') && (i == 0 || s[i-1] == 'e' || s[i-1] == 'E')) {
                //只有在e后边有符号是可接受的
                
            } else {//其他情况，都是非法的
                return false;
            }
        }
        return numFlag;
    }

};

/*
48. 旋转图像
给定一个 n × n 的二维矩阵 matrix 表示一个图像。请你将图像顺时针旋转 90 度。

你必须在 原地 旋转图像，这意味着你需要直接修改输入的二维矩阵。请不要 使用另一个矩阵来旋转图像。


*/
class Solution48 {
public:
    void rotate(vector<vector<int>>& matrix) {
        //先经过列变换，然后再翻折，就得到了顺时针旋转的矩阵
        //也可以先定义一个临时储存的变量，然后再进行挨个的转移赋值
        //https://leetcode-cn.com/problems/rotate-image/solution/xuan-zhuan-tu-xiang-by-leetcode-solution-vu3m/

        if (matrix.empty()){
            return;
        }
        for (int j = 0;j<matrix[0].size()/2;j++){
            for(int i = 0;i<matrix.size();i++){
                swap(matrix[i][j],matrix[i][matrix[0].size()-j-1]);
            }
        }
        for (int i = 0;i<matrix.size();i++){
            for (int j = 0;j<matrix[i].size();j++){
                swap(matrix[i][j],matrix[j][i]);
            }
        }
    }
};
