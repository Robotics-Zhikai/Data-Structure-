#pragma once
#include "main.h"

//二分查找 其实还是一种分治


/*
33. 搜索旋转排序数组
整数数组 nums 按升序排列，数组中的值 互不相同 。

在传递给函数之前，nums 在预先未知的某个下标 k（0 <= k < nums.length）上进行了 旋转，
使数组变为 [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]]
（下标 从 0 开始 计数）。
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

    int review(vector<int>& nums, int target) {
        //逐一枚举就行 注意要利用nums中各元素互不相同这一条件
        int left = 0;
        int right = nums.size()-1;
        while(left<=right){
            int mid = (left+right)/2;
            if (nums[mid] == target){
                return mid;
            }
            else if (nums[mid]>=nums[0] && nums[mid]<target){
                left = mid + 1;
            }
            else if (nums[mid]>target && target>=nums[0]){
                right = mid - 1;
            }
            else if (nums[mid]<nums[0] && target>=nums[0]){
                right = mid - 1;
            }
            else if (target<nums[0] && nums[mid]<target){
                left = mid + 1;
            }
            else if (target<nums[0] && nums[mid]>=nums[0]){
                left = mid + 1;
            }
            else if (target<nums[0] && nums[mid]>target){
                right = mid - 1;
            }
        }
        return -1;
    }

    int search(vector<int>& nums, int target) {
        return solveMethod2(nums,target);
    }
};



/*
剑指 Offer 11. 旋转数组的最小数字
把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。
输入一个递增排序的数组的一个旋转，输出旋转数组的最小元素。
例如，数组 [3,4,5,1,2] 为 [1,2,3,4,5] 的一个旋转，该数组的最小值为1。  
*/
class SolutionOffer11 {
public:
    int review(vector<int>& numbers){
        int left = 0;
        int right = numbers.size()-1;
        int mid = (left+right)/2;
        while(left<right){
            if (numbers[mid]>numbers[right]){
                left = mid+1;
            }
            else if (numbers[mid]<numbers[right]){
                right = mid;
            }
            else {
                right--; //注意这个等于情况的处理
            }
            mid = (left+right)/2;
        }
        
        return numbers[left];
    }
    int minArray(vector<int>& numbers) {
        return review(numbers);
        for (int i = 0;i<numbers.size()-1;i++){
            if (numbers[i]>numbers[i+1]){
                return numbers[i+1];
            }
        }
        return numbers[0];
    }
};

/*
34. 在排序数组中查找元素的第一个和最后一个位置
给定一个按照升序排列的整数数组 nums，和一个目标值 target。找出给定目标值在数组中的开始位置和结束位置。

如果数组中不存在目标值 target，返回 [-1, -1]。

进阶：

你可以设计并实现时间复杂度为 O(log n) 的算法解决此问题吗？

*/

class Solution34 {
public:
    vector<int> solveMethod1(vector<int>& nums,int target){
        int l = 0;
        int r = nums.size(); //仍然是前闭后开
        int mid = (l+r)/2;
        while(l!=r){
            if (nums[mid]>target){
                r = mid;
            }
            else if (nums[mid]<target){
                l = mid+1;
            }
            else{
                break;
            }
            mid = (l+r)/2;
        }
        if (l==r){ 
            //l意味着target必然在>=l的地方，r意味着target必然在<r的地方，然后如果l=r说明就肯定没有
            return vector<int>{-1,-1};
        }
        int low = 0;
        int high = nums.size()-1;
        for(int i = mid;i>=0;i--){
            if (nums[i]!=target){
                low = i+1;
                break;
            }
        }
        for (int i = mid;i<nums.size();i++){
            if (nums[i]!=target){
                high = i-1;
                break;
            }
        }
        return vector<int>{low,high};
    }
    vector<int> solveMethod2(vector<int>& nums,int target){
        if (nums.empty()){
            return vector<int>{-1,-1};
        }
        int l = 0;
        int r = nums.size()-1; //这里看成是前闭后闭的不容易出错
        int mid = (l+r)/2;
        int low ,high;
        while(l!=r){ //还是这里二分容易出错 这里是寻找target的第一个值
            if (nums[mid]<target){
                l = mid+1;
            }
            else if (nums[mid]>=target){
                r = mid;
            }
            mid = (l+r)/2;
        }
        if (l>=nums.size() || nums[l]!=target){
            return vector<int>{-1,-1};
        }
        low = l;
        
        l = 0;
        r = nums.size(); //但是这里就不能看成是前闭后闭，因为看成前闭后开就很好写
        mid = (l+r)/2;
        while(l!=r){ //这里是寻找第一个比target大的索引
            if (nums[mid]>target){
                r = mid;
            }
            else if (nums[mid]<=target){
                l = mid + 1;
            }
            mid = (l+r)/2;
        }
        high = l-1;

        return vector<int>{low,high};
    }
    vector<int> searchRange(vector<int>& nums, int target) {
        return solveMethod2(nums,target);
    }
};