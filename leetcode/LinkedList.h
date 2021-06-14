#pragma once
#include "main.h"

//leetcode 206. 反转链表
//反转一个单链表。
struct ListNode {
	int val;
	ListNode *next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}
};
class Solution206 {
public:
	ListNode* reverseListIteration(ListNode * head)
	{
		vector<ListNode*>vecptr;
		ListNode * curptr = head;
		while (curptr != nullptr)
		{
			vecptr.push_back(curptr);
			curptr = curptr->next;
		}
		for (int i = vecptr.size() - 1; i >= 1; i--)
		{
			vecptr[i]->next = vecptr[i - 1];
		}
		if (vecptr.empty() == 0)
			vecptr[0]->next = nullptr;
		else
			return nullptr;
		return *(vecptr.end() - 1);
	}
	ListNode* newhead = nullptr;
	ListNode * reverseListRecur(ListNode * cur)
	{

		if (cur->next == nullptr)
		{
			newhead = cur;
			return cur;
		}
		(reverseListRecur(cur->next))->next = cur;
		return cur;
	}
	ListNode * ReverseListRecur(ListNode * head)//包装函数
	{
		if (head == nullptr)
			return nullptr;
		reverseListRecur(head)->next = nullptr;
		return newhead;
	}

	ListNode* reverseList(ListNode* head) {
		//return reverseListIteration(head);
		return ReverseListRecur(head);//递归方法和迭代方法都差不多
	}

	ListNode* createList()
	{
		static ListNode ele3(3);
		static ListNode ele4(4, &ele3);
		return &ele4;
	}

	void test()
	{
		ListNode* head = createList();
		head = reverseList(head);
	}

};


/*
138. 复制带随机指针的链表
给你一个长度为 n 的链表，每个节点包含一个额外增加的随机指针 random ，该指针可以指向链表中的任何节点或空节点。

构造这个链表的 深拷贝。 深拷贝应该正好由 n 个 全新 节点组成，其中每个新节点的值都设为其对应的原节点的值。新节点的 next 指针和 random 指针也都应指向复制链表中的新节点，并使原链表和复制链表中的这些指针能够表示相同的链表状态。复制链表中的指针都不应指向原链表中的节点 。

例如，如果原链表中有 X 和 Y 两个节点，其中 X.random --> Y 。那么在复制链表中对应的两个节点 x 和 y ，同样有 x.random --> y 。

返回复制链表的头节点。

用一个由 n 个节点组成的链表来表示输入/输出中的链表。每个节点用一个 [val, random_index] 表示：

val：一个表示 Node.val 的整数。
random_index：随机指针指向的节点索引（范围从 0 到 n-1）；如果不指向任何节点，则为  null 。
你的代码 只 接受原链表的头节点 head 作为传入参数。
*/


class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
class Solution138 {
public:
    Node* FirstThought(Node * head) //第一眼想到的解决方案 是一个时空复杂度均为O(n)的方法
    {
        Node* cur = head;
        vector<Node*> Newlist;
        map<Node*,int> MAP;
        int index = 0;
        while(cur!=nullptr){ //遍历链表，然后建立映射，并把新创的结点放在vector中
            Node * newnode = new Node(cur->val);
            MAP[cur] = index++;
            newnode->random = cur->random;
            Newlist.push_back(newnode);
            cur = cur->next;
        }
        MAP[nullptr] = Newlist.size();
        Newlist.push_back(nullptr);
        for(int i = 0;i<Newlist.size()-1;i++){
            Newlist[i]->next = Newlist[i+1];
            Newlist[i]->random = Newlist[MAP[Newlist[i]->random]]; //解开映射
        }
        return Newlist[0];
    }
    Node * DFS(Node* node,map<Node*,Node*>& MAP) //直接返回新创建的结点
    { //将复杂链表看成一个图，然后递归的把新new的结点连接
        if (node==nullptr)
            return nullptr;
        if (MAP.find(node)==MAP.end()){
            Node * newnode = new Node(node->val); 
            //如果从未访问过，则新建一个结点，并建立旧地址与新地址的映射，以便之后能直接判断有没有访问过
            MAP[node] = newnode;
        }else{
            return MAP[node]; //如果访问过则直接返回映射的新结点
        }
        
        MAP[node]->next = DFS(node->next,MAP);
        MAP[node]->random = DFS(node->random,MAP);
        return MAP[node]; //返回映射的新节点，这个结点把next和random也在新的结点域中弄好了
    }
    Node* DFSrecur(Node* head)
    {
        map<Node*,Node*> MAP;
        return DFS(head,MAP);
    }

    Node* NoMapMethod(Node * head) //不用映射的方法 
    {
        if (head==nullptr)
            return nullptr;
        Node* cur = head;
        while(cur!=nullptr){
            Node * curnext = cur->next;
            Node* newnode = new Node(cur->val);
            newnode->next = cur->next; //就是把新new的结点插入到旧链表中
            cur->next = newnode;
            cur = curnext;
        }
        cur = head;
        while(cur!=nullptr){
            Node* copyNode = cur->next;
            copyNode->random = nullptr;
            if (cur->random!=nullptr)
                copyNode->random = cur->random->next;
            cur = copyNode->next;
        }
        
        Node* newhead = head->next;
        cur = head;
        int i = 0;
        while(cur!=nullptr){ //把连起来的链表解链
            Node* copyNode = cur->next;
            
            cur->next = copyNode==nullptr?nullptr:copyNode->next;
            copyNode->next = cur->next==nullptr?nullptr:cur->next->next; //注意这个边界条件
            //如果不用冒号表达式的话写起来很复杂
            cur = cur->next;
        }
        return newhead;
    }
    Node* copyRandomList(Node* head) {
        return NoMapMethod(head); //这个空间复杂度是O(1)，时间复杂是O(n)
        return FirstThought(head);//第一眼想到的，最简单的建立一个vector,然后映射
        return DFSrecur(head); //将链表看成图，然后用图的遍历方法新建结点
    }
};
// https://leetcode-cn.com/problems/copy-list-with-random-pointer/solution/fu-zhi-dai-sui-ji-zhi-zhen-de-lian-biao-by-leetcod/


/*
148. 排序链表
给你链表的头结点 head ，请将其按 升序 排列并返回 排序后的链表 。

进阶：

你可以在 O(n log n) 时间复杂度和常数级空间复杂度下，对链表进行排序吗？

*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution148 {
public:
    ListNode* solveMethod1(ListNode* head) {
        //空间复杂度是n
        vector<int> storage;
        ListNode* cur = head;
        while(cur!=nullptr){
            storage.push_back(cur->val);
            cur = cur->next;
        }
        sort(storage.begin(),storage.end());
        cur = head;
        auto it = storage.begin();
        while(cur!=nullptr){
            cur->val = *(it++);
            cur = cur->next;
        }
        return head;
    }
    int lenList(ListNode* head){
        int len = 0;
        ListNode* cur = head;
        while(cur!=nullptr){
            len++;
            cur = cur->next;
        }
        return len;
    }
    ListNode* offsetInt(ListNode* node,int offset){
        if (offset==0)
            return node;
        int i = 0;
        while(node!=nullptr){
            node = node->next;
            i++;
            if (i==offset){
                return node;
            }
        }
        return nullptr;
    }
    ListNode* merge(ListNode* leftsplit,ListNode* rightsplit){ 
        //合并有序链表 常数空间复杂度，直接改链表指针 
        if(leftsplit==nullptr)
            return rightsplit;
        else if (rightsplit == nullptr)
            return leftsplit;

        ListNode* leftcur = leftsplit;
        ListNode* leftend = nullptr;
        ListNode* rightcur = rightsplit;
        ListNode* rightend = nullptr;
        ListNode* mergeCur = nullptr;
        ListNode* mergebegin = mergeCur;
        while(leftcur!=leftend && rightcur!=rightend){
            if (leftcur->val>rightcur->val){
                if (mergebegin==nullptr){
                    mergebegin = rightcur;
                    mergeCur = rightcur;
                }
                else{
                    mergeCur->next = rightcur;
                    mergeCur = mergeCur->next;
                }
                rightcur = rightcur->next;
            }
            else {
                if (mergebegin == nullptr){
                    mergebegin = leftcur;
                    mergeCur = leftcur;
                }
                else{
                    mergeCur->next = leftcur;
                    mergeCur = mergeCur->next;
                }
                leftcur = leftcur->next;
            }
        }

        ListNode* cur;
        if (leftcur==leftend && rightcur!=rightend){
            mergeCur->next = rightcur;
        }
        else if (leftcur!=leftend && rightcur==rightend){
            mergeCur->next = leftcur;
        }
        return mergebegin;
    }
    void couthead(ListNode* head){//用于debug的
        ListNode*cur = head;
        while (cur!=nullptr){
            cout<<cur->val<<" ";
            cur = cur->next;
        }
        cout<<endl;
    }
    ListNode* solveMethod2(ListNode* head){
        //用归并排序，自底向上排，采用迭代的方法 时间复杂度是nlogn，空间复杂度是1
        int N = lenList(head);
        ListNode* cur = head;
        ListNode* newhead = nullptr;
        ListNode* last = nullptr;
        for (int interval = 2;interval<=2*N;interval*=2){//2*n是为了处理归并排序时会多余出来的数
            newhead = nullptr;
            last = nullptr;
            while(cur!=nullptr){
                ListNode* leftsplit = cur;
                ListNode* curnext = offsetInt(cur,interval);
                ListNode* rightsplit = offsetInt(leftsplit,interval/2);

                ListNode* thiscur; //把子链表从总链表中切出来，免得造成循环指，这个地方容易出错
                if ((thiscur = offsetInt(cur,interval-1))!=nullptr)
                    thiscur->next = nullptr;
                if ((thiscur = offsetInt(cur,interval/2-1))!=nullptr)
                    thiscur->next = nullptr;

                ListNode* mergedbegin = merge(leftsplit,rightsplit);
                ListNode* mergedend = offsetInt(mergedbegin,interval-1);
                if (newhead==nullptr){
                    newhead = mergedbegin;
                }
                else{
                    last->next = mergedbegin;
                }
                last = mergedend;
                cur = curnext;
            }
            cur = newhead;//这个地方容易出错，每总的排一次序头结点要变
        }
        return newhead;
    }
    ListNode* solveMethod3(ListNode* head){
    //同样用归并排序，但是用递归的方式实现，实现起来简单，但是空间复杂度就是递归栈的大小也就是logn而不是1了
    //每次找链表的中点时用快慢指针的方法，这样扫一遍就能从慢指针得到中点了
        if (head==nullptr)
            return nullptr;
        else if (head->next==nullptr)
            return head;
        else if (head->next->next==nullptr){
            if(head->val<=head->next->val)
                return head;
            else{
                ListNode* headnext = head->next;
                head->next->next = head;
                head->next = nullptr;
                return headnext;
            }
        }
        ListNode* slow = head;
        ListNode* fast = head;
        while(fast!=nullptr&& fast->next!=nullptr){//注意这个循环条件容易写错 必须保证fast每次移动两格，否则就不能使得fast走完全程后slow走一半了（主要需要考虑到fast->next为nullptr时就不能移动两格了）
            slow = slow->next;
            fast = fast->next!=nullptr?fast->next->next:nullptr;
        } //用快慢指针找链表中点
        ListNode* rightsplit = slow->next;
        slow->next = nullptr; //切断链
        return merge(solveMethod3(head),solveMethod3(rightsplit));
    }
    ListNode* sortList(ListNode* head) {
        return solveMethod3(head); //这种就是用递归的方法不容易出错且代码量少，面试的时候尽量写递归的形式
        return solveMethod2(head);
    }
};



