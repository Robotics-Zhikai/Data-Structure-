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




