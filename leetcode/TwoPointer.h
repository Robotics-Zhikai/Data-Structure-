#pragma once
#include "main.h"

//双指针


/*
141. 环形链表
给定一个链表，判断链表中是否有环。

如果链表中有某个节点，可以通过连续跟踪 next 指针再次到达，则链表中存在环。 为了表示给定链表中的环，
我们使用整数 pos 来表示链表尾连接到链表中的位置（索引从 0 开始）。 
如果 pos 是 -1，则在该链表中没有环。注意：pos 不作为参数进行传递，仅仅是为了标识链表的实际情况。

如果链表中存在环，则返回 true 。 否则，返回 false 。
*/


// Definition for singly-linked list.
struct ListNode {
      int val;
      ListNode *next;
      ListNode(int x) : val(x), next(NULL) {}
};
 
class Solution141 {
public:
    bool solveMethod1(ListNode* head){//32ms 11MB
        set<ListNode*> Unique; //n的空间复杂度
        ListNode* cur = head;
        while(cur!=NULL){
            if (Unique.find(cur)==Unique.end()){
                Unique.insert(cur);
            }
            else
                return 1;
            cur = cur->next;
        }
        return 0;
    }
    bool solveMethod2(ListNode* head){ //8ms 7.9MB
        ListNode* slow = head; //用快慢指针的方法做 如果有环，那么慢指针肯定会被快指针追上
        ListNode* fast = head;

        //慢指针每次移动一个结点，快指针每次移动两个结点
        //如果没有环，那么快指针绝不可能跟在慢指针的后边 但是有环的话就可能跟在了慢指针后边
        while(fast!=NULL){
            slow = slow->next;
            fast = fast->next!=NULL?fast->next->next:NULL;
            if (fast!=NULL && fast->next==slow)
                return 1;
        }
        return 0;
    }
    bool hasCycle(ListNode *head) {
        return solveMethod2(head);
    }
};

/*
142. 环形链表 II
给定一个链表，返回链表开始入环的第一个节点。 如果链表无环，则返回 null。

为了表示给定链表中的环，我们使用整数 pos 来表示链表尾连接到链表中的位置（索引从 0 开始）。 
如果 pos 是 -1，则在该链表中没有环。注意，pos 仅仅是用于标识环的情况，并不会作为参数传递到函数中。

说明：不允许修改给定的链表。

进阶：

你是否可以使用 O(1) 空间解决此题？

*/

class Solution142 { //这个容易忘且不好往出想，要多复习这里用到的快慢指针的方法！！！
public:
    ListNode *detectCycle(ListNode *head) {
    //仍然用快慢指针，只不过要稍加数学推导，
    //见这个链接https://leetcode-cn.com/problems/linked-list-cycle-ii/solution/huan-xing-lian-biao-ii-by-leetcode-solution/
    //同时需要注意的是，在推导过程中有一前提假设，就是慢指针肯定没有绕环形链表完整的一圈过。
    //因为快指针走的速度是慢指针速度的两倍，这样在慢指针走到整个链表长度的一半时就会和快指针相遇
    //因此，快指针走的路程a+n(b+c)+b=2(a+b),也就是等于2倍的慢指针走的路程
    //进而经过变换，得到(n-1)(b+c)+c = a。可以快慢指针相遇的地点为起始点，引入第三个指针找到链表开始入环的第一个结点
        ListNode* slow = head;
        ListNode* fast = head;
        while(fast!=NULL){
            slow = slow->next;
            fast = fast->next!=NULL?fast->next->next:NULL;
            if (slow!=NULL && slow == fast){
                ListNode* ptr = slow;
                slow = head;
                while(slow!=ptr){
                    slow = slow->next;
                    ptr = ptr->next;
                }
                return slow;
            }
        }
        return NULL;
    }
};


/*
287. 寻找重复数
给定一个包含 n + 1 个整数的数组 nums ，其数字都在 1 到 n 之间（包括 1 和 n），可知至少存在一个重复的整数。

假设 nums 只有 一个重复的整数 ，找出 这个重复的数 。

你设计的解决方案必须不修改数组 nums 且只用常量级 O(1) 的额外空间。

*/

class Solution287 {
public:
    int solveMethod1(vector<int>& nums){
        sort(nums.begin(),nums.end());//不能排序，因为题目中要求必须不修改nums
        for (int i = 0;i<nums.size()-1;i++){
            if (nums[i]==nums[i+1])
                return nums[i];
        }
        return 0;
    }
    int solveMethod2(vector<int> & nums){
        //不修改nums，充分利用题目条件：给定一个包含 n + 1 个整数的数组 nums ，其数字都在 1 到 n 之间（包括 1 和 n）
        //用二分法来做，说是二分法，其实就是每趟扫描剪枝掉绝不可能出现重复数的数集合
        //https://leetcode-cn.com/problems/find-the-duplicate-number/solution/er-fen-fa-si-lu-ji-dai-ma-python-by-liweiwei1419/
        int left = 1;
        int right = nums.size()-1; //[left,right]是可能出现重复数的范围
        int mid = (left+right)/2;  
        while(left<right){
            int cnt = 0;
            for(auto num:nums){
                if (num<=mid)
                    cnt++;
            }
            if (cnt>mid){ //意味着在nums中小于等于mid的数的数量比mid还大，那么肯定在[left,mid]区间有重复数
                right = mid; //说明重复数出现在[left,mid]区间
            }
            else{
                left = mid+1;
            }
            mid = (left+right)/2;  
        } //最终的时间复杂度是nlogn,空间复杂度是1
        return right;
    }
    int solveMethod3(vector<int> & nums){ //这个要能根据题中条件想到链表
        //用快慢指针的方法，每个nums的值表示指向的下一个结点的index，当有重复元素时，
        //表明重复元素的值所指向的index有两个元素指向该元素，也就是有一个环，用判断环形链表入口的三指针方法
        //把环形链表入口找到，即可找到重复的整数
        int slow = 0;
        int fast = 0;
        while(fast!=nums.size()){ //肯定有重复元素，这也就造成了这个while循环如果里边不return的话这个函数就不return了
            slow = nums[slow]; //slow指针每次移动一格
            fast = nums[nums[fast]]; //fast指针每次移动两格
            if (fast==slow){
                int ptr= slow;
                slow = 0;
                while(slow!=ptr){
                    slow = nums[slow];
                    ptr = nums[ptr];
                }
                return slow; //返回的是进入环形链表的index，正好是重复的值
            }
        }
        return 0;
    }

    int findDuplicate(vector<int>& nums) {
        return solveMethod3(nums); //时间复杂度是n，空间复杂度是1
        // return solveMethod2(nums);
    }
}; //注意这个不断优化的过程


