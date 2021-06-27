#pragma once
#include "main.h"

//leetcode 206. ��ת����
//��תһ��������
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
	ListNode * ReverseListRecur(ListNode * head)//��װ����
	{
		if (head == nullptr)
			return nullptr;
		reverseListRecur(head)->next = nullptr;
		return newhead;
	}

	ListNode* reverseList(ListNode* head) {
		//return reverseListIteration(head);
		return ReverseListRecur(head);//�ݹ鷽���͵������������
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
138. ���ƴ����ָ�������
����һ������Ϊ n ������ÿ���ڵ����һ���������ӵ����ָ�� random ����ָ�����ָ�������е��κνڵ��սڵ㡣

������������ ����� ���Ӧ�������� n �� ȫ�� �ڵ���ɣ�����ÿ���½ڵ��ֵ����Ϊ���Ӧ��ԭ�ڵ��ֵ���½ڵ�� next ָ��� random ָ��Ҳ��Ӧָ���������е��½ڵ㣬��ʹԭ����͸��������е���Щָ���ܹ���ʾ��ͬ������״̬�����������е�ָ�붼��Ӧָ��ԭ�����еĽڵ� ��

���磬���ԭ�������� X �� Y �����ڵ㣬���� X.random --> Y ����ô�ڸ��������ж�Ӧ�������ڵ� x �� y ��ͬ���� x.random --> y ��

���ظ��������ͷ�ڵ㡣

��һ���� n ���ڵ���ɵ���������ʾ����/����е�����ÿ���ڵ���һ�� [val, random_index] ��ʾ��

val��һ����ʾ Node.val ��������
random_index�����ָ��ָ��Ľڵ���������Χ�� 0 �� n-1���������ָ���κνڵ㣬��Ϊ  null ��
��Ĵ��� ֻ ����ԭ�����ͷ�ڵ� head ��Ϊ���������
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
    Node* FirstThought(Node * head) //��һ���뵽�Ľ������ ��һ��ʱ�ո��ӶȾ�ΪO(n)�ķ���
    {
        Node* cur = head;
        vector<Node*> Newlist;
        map<Node*,int> MAP;
        int index = 0;
        while(cur!=nullptr){ //��������Ȼ����ӳ�䣬�����´��Ľ�����vector��
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
            Newlist[i]->random = Newlist[MAP[Newlist[i]->random]]; //�⿪ӳ��
        }
        return Newlist[0];
    }
    Node * DFS(Node* node,map<Node*,Node*>& MAP) //ֱ�ӷ����´����Ľ��
    { //������������һ��ͼ��Ȼ��ݹ�İ���new�Ľ������
        if (node==nullptr)
            return nullptr;
        if (MAP.find(node)==MAP.end()){
            Node * newnode = new Node(node->val); 
            //�����δ���ʹ������½�һ����㣬�������ɵ�ַ���µ�ַ��ӳ�䣬�Ա�֮����ֱ���ж���û�з��ʹ�
            MAP[node] = newnode;
        }else{
            return MAP[node]; //������ʹ���ֱ�ӷ���ӳ����½��
        }
        
        MAP[node]->next = DFS(node->next,MAP);
        MAP[node]->random = DFS(node->random,MAP);
        return MAP[node]; //����ӳ����½ڵ㣬�������next��randomҲ���µĽ������Ū����
    }
    Node* DFSrecur(Node* head)
    {
        map<Node*,Node*> MAP;
        return DFS(head,MAP);
    }

    Node* NoMapMethod(Node * head) //����ӳ��ķ��� 
    {
        if (head==nullptr)
            return nullptr;
        Node* cur = head;
        while(cur!=nullptr){
            Node * curnext = cur->next;
            Node* newnode = new Node(cur->val);
            newnode->next = cur->next; //���ǰ���new�Ľ����뵽��������
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
        while(cur!=nullptr){ //�����������������
            Node* copyNode = cur->next;
            
            cur->next = copyNode==nullptr?nullptr:copyNode->next;
            copyNode->next = cur->next==nullptr?nullptr:cur->next->next; //ע������߽�����
            //�������ð�ű��ʽ�Ļ�д�����ܸ���
            cur = cur->next;
        }
        return newhead;
    }
    Node* copyRandomList(Node* head) {
        return NoMapMethod(head); //����ռ临�Ӷ���O(1)��ʱ�临����O(n)
        return FirstThought(head);//��һ���뵽�ģ���򵥵Ľ���һ��vector,Ȼ��ӳ��
        return DFSrecur(head); //��������ͼ��Ȼ����ͼ�ı��������½����
    }
};
// https://leetcode-cn.com/problems/copy-list-with-random-pointer/solution/fu-zhi-dai-sui-ji-zhi-zhen-de-lian-biao-by-leetcod/


/*
148. ��������
���������ͷ��� head ���뽫�䰴 ���� ���в����� ���������� ��

���ף�

������� O(n log n) ʱ�临�ӶȺͳ������ռ临�Ӷ��£����������������

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
        //�ռ临�Ӷ���n
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
        //�ϲ��������� �����ռ临�Ӷȣ�ֱ�Ӹ�����ָ�� 
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
    void couthead(ListNode* head){//����debug��
        ListNode*cur = head;
        while (cur!=nullptr){
            cout<<cur->val<<" ";
            cur = cur->next;
        }
        cout<<endl;
    }
    ListNode* solveMethod2(ListNode* head){
        //�ù鲢�����Ե������ţ����õ����ķ��� ʱ�临�Ӷ���nlogn���ռ临�Ӷ���1
        int N = lenList(head);
        ListNode* cur = head;
        ListNode* newhead = nullptr;
        ListNode* last = nullptr;
        for (int interval = 2;interval<=2*N;interval*=2){//2*n��Ϊ�˴���鲢����ʱ������������
            newhead = nullptr;
            last = nullptr;
            while(cur!=nullptr){
                ListNode* leftsplit = cur;
                ListNode* curnext = offsetInt(cur,interval);
                ListNode* rightsplit = offsetInt(leftsplit,interval/2);

                ListNode* thiscur; //������������������г�����������ѭ��ָ������ط����׳���
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
            cur = newhead;//����ط����׳���ÿ�ܵ���һ����ͷ���Ҫ��
        }
        return newhead;
    }
    ListNode* solveMethod3(ListNode* head){
    //ͬ���ù鲢���򣬵����õݹ�ķ�ʽʵ�֣�ʵ�������򵥣����ǿռ临�ӶȾ��ǵݹ�ջ�Ĵ�СҲ����logn������1��
    //ÿ����������е�ʱ�ÿ���ָ��ķ���������ɨһ����ܴ���ָ��õ��е���
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
        while(fast!=nullptr&& fast->next!=nullptr){//ע�����ѭ����������д�� ���뱣֤fastÿ���ƶ����񣬷���Ͳ���ʹ��fast����ȫ�̺�slow��һ���ˣ���Ҫ��Ҫ���ǵ�fast->nextΪnullptrʱ�Ͳ����ƶ������ˣ�
            slow = slow->next;
            fast = fast->next!=nullptr?fast->next->next:nullptr;
        } //�ÿ���ָ���������е�
        ListNode* rightsplit = slow->next;
        slow->next = nullptr; //�ж���
        return merge(solveMethod3(head),solveMethod3(rightsplit));
    }
    ListNode* sortList(ListNode* head) {
        return solveMethod3(head); //���־����õݹ�ķ��������׳����Ҵ������٣����Ե�ʱ����д�ݹ����ʽ
        return solveMethod2(head);
    }
};



/*
21. �ϲ�������������
��������������ϲ�Ϊһ���µ� ���� �������ء���������ͨ��ƴ�Ӹ�����������������нڵ���ɵġ� 

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
        //�õ����ķ�����
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
        //�õݹ鷽ʽ���������ǳ��򵥺�д
        //�ص��Ƕ���ݹ�ķ�����ʲô��Ȼ����ݷ�����д
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
    } //��Ȼ�����õݹ龡���õݹ�
};


/*
146. LRU �������
�����������յ����ݽṹ����ƺ�ʵ��һ��  LRU (�������ʹ��) ������� ��
ʵ�� LRUCache �ࣺ

LRUCache(int capacity) ����������Ϊ���� capacity ��ʼ�� LRU ����
int get(int key) ����ؼ��� key �����ڻ����У��򷵻عؼ��ֵ�ֵ�����򷵻� -1 ��
void put(int key, int value) ����ؼ����Ѿ����ڣ�����������ֵ��
����ؼ��ֲ����ڣ��������顸�ؼ���-ֵ����
�����������ﵽ����ʱ����Ӧ����д��������֮ǰɾ�����δʹ�õ�����ֵ���Ӷ�Ϊ�µ�����ֵ�����ռ䡣
 

���ף����Ƿ������ O(1) ʱ�临�Ӷ�����������ֲ�����

*/

//һ���Ƚ�ɵ����Ч����ʵ�֣����г�ʱ�ˣ��������н������ȷ��
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

//һ���Ƚϸ�Ч��ʵ�� �߼�����ͦ�򵥵�
class LRUCache {
    //��˫������͹�ϣ����ʵ��LRU
    //������ʵ�ͨ��HASHMAP O(1)�ҵ�������������󣬻����Ҳ���ʱ�½�һ��node�ӵ��������
    //Ҫɾ��һ�����δʹ�õ�����ֵʱֱ��ɾ����˫�������ͷ���
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
            insertNode(MAP[key]); //ע�������������Ҳ���Ƕ����ݽ��з���
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

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
