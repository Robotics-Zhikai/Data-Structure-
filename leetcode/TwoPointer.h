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
