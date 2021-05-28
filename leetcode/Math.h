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



