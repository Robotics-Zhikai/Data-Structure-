#pragma once
#include "main.h"

//二分查找 其实还是一种分治


/*
33. 搜索旋转排序数组
整数数组 nums 按升序排列，数组中的值 互不相同 。

在传递给函数之前，nums 在预先未知的某个下标 k（0 <= k < nums.length）上进行了 旋转，
使数组变为 [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]]（下标 从 0 开始 计数）。
例如， [0,1,2,4,5,6,7] 在下标 3 处经旋转后可能变为 [4,5,6,7,0,1,2] 。

给你 旋转后 的数组 nums 和一个整数 target ，如果 nums 中存在这个目标值 target ，则返回它的下标，否则返回 -1 。

 

示例 1：

输入：nums = [4,5,6,7,0,1,2], target = 0
输出：4
示例 2：

输入：nums = [4,5,6,7,0,1,2], target = 3
输出：-1
示例 3：

输入：nums = [1], target = 0
输出：-1
 

提示：

1 <= nums.length <= 5000
-10^4 <= nums[i] <= 10^4
nums 中的每个值都 独一无二
题目数据保证 nums 在预先未知的某个下标上进行了旋转
-10^4 <= target <= 10^4
 

进阶：你可以设计一个时间复杂度为 O(log n) 的解决方案吗？

*/

class Solution33 {
public:
    int solveMethod1(vector<int>& nums, int target){
        //O(n)复杂度
        for(int i = 0;i<nums.size();i++){
            if (nums[i]==target){
                return i;
            }
        }
        return -1;
    }
    int solveMethod2(vector<int>& nums,int target){
        //logn复杂度
        if (nums.empty()){
            return -1;
        }
        int l = 0;
        int r = nums.size();
        int mid = (l+r)/2;
        int pivot = nums[0]; //下边的二分查找实现都是前闭后开的
        while(1){
            if (nums[mid]>pivot && mid+1<nums.size() && nums[mid]<nums[mid+1]){
                l = mid + 1;
            }
            else if (nums[mid]<pivot){
                r = mid;
            }
            else if (mid+1<nums.size() && nums[mid]>nums[mid+1]){
                break;
            }
            else if (mid == nums.size()-1){
                break;
            }
            mid = (l+r)/2;
        } //首先用二分法找到旋转的index 这里非常难写，但是把握住什么时候应该变l和r，什么时候退出就比较简单了
        
        if (target<pivot){ //然后根据target与pivot的相对大小决定在哪边进行二分查找
            l = mid+1;
            r = nums.size();
        }
        else if (target>=pivot){
            l = 0;
            r = mid+1;
        }
        
        mid = (l+r)/2;
        while(l!=r && mid<nums.size()){ //因为是前闭后开，所以当l=r时，说明搜索不到元素
            if (nums[mid]>target){
                r = mid;
            }
            else if (nums[mid]<target){
                l = mid+1;
            }
            else{
                return mid;
            }
            mid = (l+r)/2;
        }
        
        return -1;
    }
    int search(vector<int>& nums, int target) {
        return solveMethod2(nums,target);
    }
};