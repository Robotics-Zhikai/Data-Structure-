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
剑指 Offer 35. 复杂链表的复制
请实现 copyRandomList 函数，复制一个复杂链表。
在复杂链表中，每个节点除了有一个 next 指针指向下一个节点，还有一个 random 指针指向链表中的任意节点或者 null。

*/
/*
// Definition for a Node.
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
*/
class SolutionOffer35 {
public:
    Node* copyRandomList(Node* head) {
        //线性的时间复杂度，1的空间复杂度
        //简单一点的话还可以用map
        //大致思路是把所有复制的新节点添加在旧节点的后边，然后解链
        Node* cur = head;
        while(cur!=nullptr){
            Node* curnext = cur->next;
            cur->next = new Node(cur->val);
            cur->next->next = curnext;
            cur = curnext;
        }
        cur = head;
        while(cur!=nullptr){
            cur->next->random = cur->random==nullptr?nullptr:cur->random->next;
            cur = cur->next->next;
        }
        cur = head;
        Node* res = nullptr;
        while(cur!=nullptr){
            if (cur==head){
                res = cur->next;
            }
            Node* curnext = cur->next;
            cur->next = curnext->next;
            curnext->next = curnext->next==nullptr?nullptr:curnext->next->next;
            cur = cur->next; 
        }
        return res;
    }
};





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



/*
21. 合并两个有序链表
将两个升序链表合并为一个新的 升序 链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。 

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
class Solution21 {
public:
    ListNode* solveMethod1(ListNode* l1, ListNode* l2) {
        //用迭代的方法做
        if(l1==nullptr)
            return l2;
        else if (l2 == nullptr)
            return l1;
        
        ListNode* leftcur = l1;
        ListNode* leftend = nullptr;
        ListNode* rightcur = l2;
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

        if (leftcur==leftend && rightcur!=rightend){
            mergeCur->next = rightcur;
        }
        else if (leftcur!=leftend && rightcur==rightend){
            mergeCur->next = leftcur;
        }
        return mergebegin;
    }
    ListNode* solveMethod2(ListNode* l1, ListNode* l2) {
        //用递归方式解决，代码非常简单好写
        //重点是定义递归的返回是什么，然后根据返回来写
        if (l1==nullptr)
            return l2;
        else if (l2==nullptr)
            return l1;
        
        if (l1->val<=l2->val){
            l1->next = solveMethod2(l1->next,l2);
            return l1;
        }
        else{
            l2->next = solveMethod2(l1,l2->next);
            return l2;
        }
        return nullptr;
    }
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        return solveMethod2(l1,l2);
    } //仍然是能用递归尽量用递归
};


/*
146. LRU 缓存机制
运用你所掌握的数据结构，设计和实现一个  LRU (最近最少使用) 缓存机制 。
实现 LRUCache 类：

LRUCache(int capacity) 以正整数作为容量 capacity 初始化 LRU 缓存
int get(int key) 如果关键字 key 存在于缓存中，则返回关键字的值，否则返回 -1 。
void put(int key, int value) 如果关键字已经存在，则变更其数据值；
如果关键字不存在，则插入该组「关键字-值」。
当缓存容量达到上限时，它应该在写入新数据之前删除最久未使用的数据值，从而为新的数据值留出空间。
 

进阶：你是否可以在 O(1) 时间复杂度内完成这两种操作？

*/

//一个比较傻（低效）的实现，运行超时了，但是运行结果是正确的
class LRUCacheMethod1 {
public:
    LRUCacheMethod1(int capacity):_cap(capacity) {}
    
    int get(int key) {
        _time++;
        if (MAP.find(key)!=MAP.end()){
            MAPvisit[key] = _time;
            return MAP[key];
        }
        else{
            return -1;
        }
    }
    
    void put(int key, int value) {
        _time++;
        if (MAP.size()<_cap){
            MAPvisit[key] = _time;
            MAP[key] = value;
        }
        else{
            if (MAP.find(key)==MAP.end()){
                int max = INT_MIN;
                int recordMinindex = -1;
                for(auto& pair:MAPvisit){
                    if ((_time-pair.second)>max){
                        max = _time-pair.second;
                        recordMinindex = pair.first;
                    }
                }
                MAP.erase(recordMinindex);
                MAPvisit.erase(recordMinindex);
            }
            
            MAP[key] = value;
            MAPvisit[key] = _time;
        }
    }
private:
    unordered_map<int,int> MAP;
    unordered_map<int,int> MAPvisit;
    const int _cap;
    int _time = 0;
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

class node{
public:
    node(int key,int value):_key(key),_value(value){}
    node* next = nullptr;
    node* prev = nullptr;
    int _key;
    int _value;
};
/* pthread_mutex_lock */
/* pthread_mutex_unlock */
//一个比较高效的实现 逻辑还是挺简单的
class LRUCache {
    //用双向链表和哈希表来实现LRU
    //最近访问的通过HASHMAP O(1)找到后放在链表的最后，或者找不到时新建一个node加到链表最后
    //要删除一个最久未使用的数据值时直接删除掉双向链表的头结点
public:
    LRUCache(int capacity):_capacity(capacity) {

    }
    
    int get(int key) {
        auto found = MAP.find(key);
        if(found==MAP.end()){
            return -1;
        }
        else{
            node* foundNode = found->second;
            eraseNode(foundNode);
            insertNode(foundNode);
            return foundNode->_value;
        }
    }
    
    void put(int key, int value) {
        if (MAP.find(key)!=MAP.end()){
            MAP[key]->_value = value;
            eraseNode(MAP[key]);
            insertNode(MAP[key]); //注意这个更新数据也算是对数据进行访问
        }
        else{
            node * newnode = new node(key,value);
            if (MAP.size()<_capacity){
                insertNode(newnode);
                MAP[key] = newnode;
            }
            else{
                node * deletenode = firstnode;
                eraseNode(deletenode);
                MAP.erase(deletenode->_key);
                delete deletenode;
                insertNode(newnode);
                MAP[key] = newnode;
            }
        }
    }
private:
    unordered_map<int,node*> MAP;
    const int _capacity;

    node* lastnode = nullptr;
    node* firstnode = nullptr;

    void insertNode(node* addr){
        if (lastnode==nullptr){
            lastnode = addr;
            firstnode = addr;
            addr->next = nullptr;
            addr->prev = nullptr;
        }
        else{
            lastnode->next = addr;
            addr->next = nullptr;
            addr->prev = lastnode;
            lastnode = addr;
        }
    }
    void eraseNode(node* addr){
        if (addr->next==nullptr && addr->prev==nullptr){
            firstnode = nullptr;
            lastnode = nullptr;
        }
        else if (addr->prev==nullptr){
            addr->next->prev = nullptr;
            firstnode = addr->next;
        }
        else if (addr->next==nullptr){
            addr->prev->next = nullptr;
            lastnode = addr->prev;
        }
        else{
            addr->prev->next = addr->next;
            addr->next->prev = addr->prev;
        }
    }
};

//线程安全的LRU缓存
class LRUCacheThreadSafe {
    //用双向链表和哈希表来实现LRU
    //最近访问的通过HASHMAP O(1)找到后放在链表的最后，或者找不到时新建一个node加到链表最后
    //要删除一个最久未使用的数据值时直接删除掉双向链表的头结点
public:
    LRUCacheThreadSafe(int capacity):_capacity(capacity) {

    }
    
    int get(int key) { //这个可以同时读访问

        pthread_mutex_lock(&mutexreadCount);
        readCount++;
        if (readCount==1){
            pthread_mutex_lock(&mutexWrite);
        }
        pthread_mutex_unlock(&mutexreadCount);

        auto found = MAP.find(key);
        if(found==MAP.end()){
            return -1;
        }
        else{
            node* foundNode = found->second;
            eraseNode(foundNode);
            insertNode(foundNode);
            return foundNode->_value;
        }

        pthread_mutex_lock(&mutexreadCount);
        readCount--;
        if (readCount==0){
            pthread_mutex_unlock(&mutexWrite);
        }
        pthread_mutex_unlock(&mutexreadCount);
    }
    
    void put(int key, int value) {
        pthread_mutex_lock(&mutexWrite);
        writeCount++;
        if (MAP.find(key)!=MAP.end()){
            MAP[key]->_value = value;
            eraseNode(MAP[key]);
            insertNode(MAP[key]); //注意这个更新数据也算是对数据进行访问
        }
        else{
            node * newnode = new node(key,value);
            if (MAP.size()<_capacity){
                insertNode(newnode);
                MAP[key] = newnode;
            }
            else{
                node * deletenode = firstnode;
                eraseNode(deletenode);
                MAP.erase(deletenode->_key);
                delete deletenode;
                insertNode(newnode);
                MAP[key] = newnode;
            }
        }
        writeCount--;
        pthread_mutex_unlock(&mutexWrite);
    }
private:
    unordered_map<int,node*> MAP;
    const int _capacity;

    pthread_mutex_t mutex1;
    
    pthread_mutex_t mutexWrite;

    pthread_mutex_t mutexreadCount;
    unsigned int readCount = 0;

    unsigned int writeCount = 0;

    node* lastnode = nullptr;
    node* firstnode = nullptr;

    void insertNode(node* addr){
        pthread_mutex_lock(&mutex1);
        if (lastnode==nullptr){
            lastnode = addr;
            firstnode = addr;
            addr->next = nullptr;
            addr->prev = nullptr;
        }
        else{
            lastnode->next = addr;
            addr->next = nullptr;
            addr->prev = lastnode;
            lastnode = addr;
        }
        pthread_mutex_unlock(&mutex1);
    }
    void eraseNode(node* addr){
        pthread_mutex_lock(&mutex1);
        if (addr->next==nullptr && addr->prev==nullptr){
            firstnode = nullptr;
            lastnode = nullptr;
        }
        else if (addr->prev==nullptr){
            addr->next->prev = nullptr;
            firstnode = addr->next;
        }
        else if (addr->next==nullptr){
            addr->prev->next = nullptr;
            lastnode = addr->prev;
        }
        else{
            addr->prev->next = addr->next;
            addr->next->prev = addr->prev;
        }
        pthread_mutex_unlock(&mutex1);
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

class LRUCacheReview {
public:
    LRUCache(int capacity):cap(capacity) {

    }
    
    int get(int key) {
        if(MAP.find(key)!=MAP.end()){
            eraseNode(MAP[key]);
            insertNode(MAP[key]);
            return MAP[key]->value;
        }
        return -1;    
    }
    
    void put(int key, int value) {
        if (MAP.find(key)!=MAP.end()){
            MAP[key]->value = value;
            eraseNode(MAP[key]);
            insertNode(MAP[key]);
        }
        else{
            node* newnode = new node(key,value);
            if (cur==cap){
                node* before = listHead;
                MAP.erase(listHead->key);
                eraseNode(listHead);
                delete before;
            }
            else{
                cur++;
            }
            insertNode(newnode);
            MAP[key] = newnode;
        }
    }
private:
    class node{
    public:
        node(int key,int value):key(key),value(value){}
        int key;
        int value;
        node* next;
        node* prev;
    };
    void insertNode(node* nodeptr){
        if (nodeptr==nullptr){
            return;
        }
        if (listTail==nullptr){
            listHead = nodeptr;
            listTail = nodeptr;
            listHead->prev = nullptr;
            listHead->next = nullptr;
        }
        else{
            listTail->next = nodeptr;
            nodeptr->prev = listTail;
            nodeptr->next = nullptr;
            listTail = nodeptr;
        }
    }
    void eraseNode(node* nodeptr){
        if (nodeptr->prev == nullptr && nodeptr->next == nullptr){
            listHead = nullptr;
            listTail = nullptr;
        }
        else if (nodeptr->prev == nullptr){
            listHead = listHead->next;
            listHead->prev = nullptr;
        }
        else if (nodeptr->next == nullptr){
            listTail = listTail->prev;
            listTail->next = nullptr;
        }
        else{
            nodeptr->prev->next = nodeptr->next;
            nodeptr->next->prev = nodeptr->prev;
        }
    }
    node* listHead = nullptr;
    node* listTail = nullptr;
    int cap;
    int cur = 0;
    unordered_map<int,node*> MAP;
};

/*
160. 相交链表
给你两个单链表的头节点 headA 和 headB ，请你找出并返回两个单链表相交的起始节点。如果两个链表没有交点，返回 null 。

图示两个链表在节点 c1 开始相交：



题目数据 保证 整个链式结构中不存在环。

注意，函数返回结果后，链表必须 保持其原始结构 。



*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution160 {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode* cur1 = headA;
        ListNode* cur2 = headB;
        while(cur1!=cur2){
            cur1 = cur1==nullptr?headB:cur1->next;
            cur2 = cur2==nullptr?headA:cur2->next;
        }
        return cur1;
    }
};


/*
剑指 Offer 24. 反转链表
定义一个函数，输入一个链表的头节点，反转该链表并输出反转后链表的头节点。
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class SolutionOffer24 {
public:
    ListNode* HEAD = nullptr;
    ListNode* recur(ListNode* head){
        if (head==nullptr){
            return nullptr;
        }
        if (head->next==nullptr){
            HEAD = head;
            return head;
        }
        recur(head->next)->next = head;
        return head;
    }
    ListNode* solveMethod1(ListNode* head){
        if (head == nullptr){
            return nullptr;
        }
        recur(head)->next = nullptr;
        return HEAD;
    }
    ListNode* solveMethod2(ListNode* head){
        ListNode* cur = head;
        ListNode* last = nullptr;
        while(cur!=nullptr){
            ListNode* next = cur->next;
            cur->next = last;
            last = cur;
            cur = next;
        }
        return last;
    }
    ListNode* reverseList(ListNode* head) {
        return solveMethod2(head);
    }
};



