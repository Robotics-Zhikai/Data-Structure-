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



