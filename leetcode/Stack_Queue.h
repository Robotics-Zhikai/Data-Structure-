#pragma once
#include "main.h"

/*
��ָ Offer 09. ������ջʵ�ֶ���
������ջʵ��һ�����С����е��������£���ʵ�������������� appendTail �� deleteHead ��
�ֱ�����ڶ���β�������������ڶ���ͷ��ɾ�������Ĺ��ܡ�(��������û��Ԫ�أ�deleteHead �������� - 1)
*/
class CQueueOffer09 {
public:
	CQueueOffer09() {

	}

	void appendTail(int value) {
		left.push(value);
	}

	int deleteHead() { //����ÿ��Ԫ����˵��ɾ���ĸ��Ӷ���O(1)�ģ���Ȼ������ÿ�β�����ҪO(n)�����Ǿ���ÿ��������Ԫ��������ֻ�в����ɾ������
		if (right.empty() == 1)
		{
			while (left.empty() == 0)
			{
				right.push(left.top());
				left.pop();
			}
		}

		if (right.empty() == 1)
			return -1;
		else
		{
			int tmp = right.top();
			right.pop();
			return tmp;
		}
	}

	stack<int> left;
	stack<int> right;
};

/*
��ָ Offer 31. ջ��ѹ�롢��������
���������������У���һ�����б�ʾջ��ѹ��˳�����жϵڶ��������Ƿ�Ϊ��ջ�ĵ���˳�򡣼���ѹ��ջ���������־�����ȡ�
���磬���� {1,2,3,4,5} ��ĳջ��ѹջ���У�
���� {4,5,3,2,1} �Ǹ�ѹջ���ж�Ӧ��һ���������У��� {4,3,5,1,2} �Ͳ������Ǹ�ѹջ���еĵ������С�

*/

class SolutionOffer31 {
public:
    bool ComplexMethod(vector<int>& pushed, vector<int>& popped){ //���ӵ�ʵ�� ����ǵ�һ���뵽��
        if (pushed.empty()&&popped.empty())
            return 1;
        else if (pushed.empty() || popped.empty())
            return 0;
        int poppedIndex = 0;
        int pushedIndex = -1;
        stack<int> pushStack;
        do{
            do{
                pushedIndex++;
                pushStack.push(pushed[pushedIndex]);
            }while((pushedIndex<pushed.size()-1) && poppedIndex<popped.size() && (pushed[pushedIndex]!=popped[poppedIndex]));
           
            while((!pushStack.empty()) && (poppedIndex<popped.size()) && (pushStack.top()==popped[poppedIndex])){
                
                pushStack.pop();
                poppedIndex++;
            }
        }while(pushedIndex<pushed.size()-1);
        if (pushStack.empty())
            return 1;
        else
            return 0;
    }
    bool EasyMethod(vector<int>& pushed, vector<int>& popped){ //�򵥵�ʵ�� ����ǿ����ķ������ֵ�
        stack<int> stackpushed;
        int popindex = 0;
        for(auto &n : pushed){ //��Ҫ���ϱ߸��ӵ�ʵ�ַ�����Ҫά�����������������ֻ��Ҫά��һ����������һ��������ð�ű��ʽ�����
            stackpushed.push(n);
            while(!stackpushed.empty() && popindex<popped.size() && stackpushed.top()==popped[popindex]){
                stackpushed.pop();
                popindex++;
            }
        }   
        return stackpushed.empty();
    }
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        return EasyMethod(pushed,popped);
		return ComplexMethod(pushed,popped);
    }
};


/*
155. ��Сջ
���һ��֧�� push ��pop ��top �����������ڳ���ʱ���ڼ�������СԪ�ص�ջ��

push(x) ���� ��Ԫ�� x ����ջ�С�
pop() ���� ɾ��ջ����Ԫ�ء�
top() ���� ��ȡջ��Ԫ�ء�
getMin() ���� ����ջ�е���СԪ�ء�
*/
//leetcode 155
class MinStack {
public:
    /** initialize your data structure here. */
    MinStack() {

    }
    
    void push(int val) {
        if (MIN.empty())
            MIN.push(val);
        else if (MIN.top()>=val){
            MIN.push(val);
        }
        STACK.push(val);
    }
    
    void pop() {
        if (!MIN.empty() && MIN.top()==STACK.top()){
            MIN.pop();
        }
        STACK.pop();
    }
    
    int top() {
        return STACK.top();
    }
    
    int getMin() {    
        return MIN.top();
    }
private:
    stack<int> MIN;
    stack<int> STACK;
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */

//������ø���ջ�ķ�����̫�����뵽��Ҫ�����ص㿴��������
/*
���ǲ���Ҫ����ջ�ķ���
stack�����洢��min�Ĳ�ֵ��min�洢��Сֵ��ÿ�γ�ջ��ʱ��ͨ����ֵ�͵�ǰmin����Ҫ��ջ��ֵ��֮ǰ��min
�����ֵdiff���ڵ���0��˵��Ҫ��ջ��ֵ���ڵ��ڵ�ǰmin����ôҪ��ջ��ֵ����ջ��ʱ��û�и���min������min+diff��
�����ֵdiffС��0��˵����ǰҪ��ջ��ֵ����min(��Ϊ��ջ��ʱ������ѡ��ľ���min����ջԪ�ص���Сֵ)��ͬʱ��ͨ��min-diff�����֮ǰmin
Ҫע�����diff���ܻᳬ��int��Χ�������� Integer.MAX_VALUE - 1 ���֣�����diffҪ��Long��
    
class MinStack {

    Integer min = null;
    Stack<Long> data = new Stack<>();

 
    public MinStack1() {

    }

    public void push(int x) {
        if (data.isEmpty()) {
            data.push(0L);
            min = x;
        } else {
            //���x����С�������������Խ�磬������Long������
            data.push(Long.valueOf(x) - min); //push�����diff
            min = Math.min(x, min); //����min
        }
    }

    public void pop() {
        Long diff = data.pop();
        if (diff >= 0) {
            //return min + diff;
        } else {
            int res = min;
            min = (int) (min - diff); //ÿ��pop��Ҫ����һ��min���Ա�min��֮��Ԫ�ظĵ����ܹ�����ԭ
            //return res;
        }
    }

    public int top() {
        Long diff = data.peek();
        if (diff >= 0) {
            return (int) (min + diff);
        } else {
            return min;
        }
    }

    public int getMin() {
        return min;
    }
}
*/

/*
//һ�ָ��������ķ������������ϻ���ÿ�ζ���¼��֮ǰ����Сֵ���ȸ���ջ�ķ��������ķѿռ�����
class MinStack {
    private Node head;
    
    public void push(int x) {
        if(head == null) 
            head = new Node(x, x);
        else 
            head = new Node(x, Math.min(x, head.min), head);
    }

    public void pop() {
        head = head.next;
    }

    public int top() {
        return head.val;
    }

    public int getMin() {
        return head.min;
    }
    
    private class Node {
        int val;
        int min;
        Node next;
        
        private Node(int val, int min) {
            this(val, min, null);
        }
        
        private Node(int val, int min, Node next) {
            this.val = val;
            this.min = min;
            this.next = next;
        }
    }
}

*/

 /*
��ָ Offer 59 - I. �������ڵ����ֵ
����һ������ nums �ͻ������ڵĴ�С k�����ҳ����л�������������ֵ��

ʾ��:

����: nums = [1,3,-1,-3,5,3,6,7], �� k = 3
���: [3,3,5,5,6,7] 
����: 

  �������ڵ�λ��                ���ֵ
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7

��Դ�����ۣ�LeetCode��
���ӣ�https://leetcode-cn.com/problems/hua-dong-chuang-kou-de-zui-da-zhi-lcof
����Ȩ������������С���ҵת������ϵ�ٷ���Ȩ������ҵת����ע��������

 */
//��������ϱߵ���Сջ���������

class Solution59_I {
public:
    void MAXpush(int n )
    {
        if (MAX.empty())
            MAX.push_back(n);
        else if (n>=MAX.back()){
            MAX.push_back(n);
        }
    }
    void push(int n)
    {
        DEQ.push_back(n);
        MAXpush(n);
    }
    void pop()
    {
        if (!DEQ.empty() && !MAX.empty()){
            if (DEQ.front()==MAX.front()){
                MAX.pop_front();
            }
            DEQ.pop_front();

            //�±ߵ����for��Ҫ���������ǵ��¼����ֵС�����ֵʱ��push�������MAX������MAX���ϴ�ǰ����ʧ��
            //�������MAX��ʧΪ�գ���ʱ��Ҫȷ���µ����ֵ����Ҫ��deq�е���MAXpush��MAX��
            if(MAX.empty()){ //ע����������д���� �����Сջ�Ǹ��⣬���װ����for��������Ϊ��Сջ�Ǹ��������һ��������ʧԪ�أ�
                for(int i = 0;i<DEQ.size();i++){
                    MAXpush(DEQ[i]); //������ֳ�˫�˶��еĺô��ˣ�����ֱ�ӱ���
                }
            }
        }   
        
    }
    int getMAX()
    {
        return MAX.back();
    }

    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        if(nums.empty())
            return nums;
        vector<int> res;
        for(int i = 0;i<k;i++){ //�Ȱѵ�һ������������Ū��
            push(nums[i]);
        }
        
        res.push_back(getMAX());
        for(int base = 1;base<=nums.size()-k;base++){
            push(nums[base+k-1]);
            pop(); 
            res.push_back(getMAX());
        }
        return res;
    }


private:
    deque<int> MAX;
    deque<int> DEQ;
};