#pragma once
#include "main.h"

/*
剑指 Offer 09. 用两个栈实现队列
用两个栈实现一个队列。队列的声明如下，请实现它的两个函数 appendTail 和 deleteHead ，
分别完成在队列尾部插入整数和在队列头部删除整数的功能。(若队列中没有元素，deleteHead 操作返回 - 1)
*/
class CQueueOffer09 {
public:
	CQueueOffer09() {

	}

	void appendTail(int value) {
		left.push(value);
	}

	int deleteHead() { //对于每个元素来说，删除的复杂度是O(1)的，虽然看起来每次操作需要O(n)，但是就拿每个单独的元素来讲，只有插入和删除操作
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
剑指 Offer 31. 栈的压入、弹出序列
输入两个整数序列，第一个序列表示栈的压入顺序，请判断第二个序列是否为该栈的弹出顺序。假设压入栈的所有数字均不相等。
例如，序列 {1,2,3,4,5} 是某栈的压栈序列，
序列 {4,5,3,2,1} 是该压栈序列对应的一个弹出序列，但 {4,3,5,1,2} 就不可能是该压栈序列的弹出序列。

*/

class SolutionOffer31 {
public:
    bool ComplexMethod(vector<int>& pushed, vector<int>& popped){ //复杂的实现 这个是第一次想到的
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
    bool EasyMethod(vector<int>& pushed, vector<int>& popped){ //简单的实现 这个是看题解的方法复现的
        stack<int> stackpushed;
        int popindex = 0;
        for(auto &n : pushed){ //主要是上边复杂的实现方法需要维护两个变量，而这个只需要维护一个变量，另一个变量被冒号表达式解决了
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
155. 最小栈
设计一个支持 push ，pop ，top 操作，并能在常数时间内检索到最小元素的栈。

push(x) —— 将元素 x 推入栈中。
pop() —— 删除栈顶的元素。
top() —— 获取栈顶元素。
getMin() —— 检索栈中的最小元素。
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

//这个不用辅助栈的方法不太容易想到，要反复重点看！！！！
/*
这是不需要辅助栈的方法
stack用来存储和min的差值，min存储最小值，每次出栈的时候通过差值和当前min计算要出栈的值和之前的min
如果差值diff大于等于0，说明要出栈的值大于等于当前min，那么要出栈的值在入栈的时候没有更新min，返回min+diff；
如果差值diff小于0，说明当前要出栈的值就是min(因为入栈的时候我们选择的就是min和入栈元素的最小值)，同时，通过min-diff计算出之前min
要注意的是diff可能会超出int范围，类似于 Integer.MAX_VALUE - 1 这种，所以diff要用Long存
    
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
            //如果x是最小的数，这里可能越界，所以用Long来保存
            data.push(Long.valueOf(x) - min); //push入的是diff
            min = Math.min(x, min); //更新min
        }
    }

    public void pop() {
        Long diff = data.pop();
        if (diff >= 0) {
            //return min + diff;
        } else {
            int res = min;
            min = (int) (min - diff); //每次pop都要更新一下min，以便min被之后元素改掉的能够被复原
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
//一种更容易理解的方法，但本质上还是每次都记录了之前的最小值，比辅助栈的方法甚至耗费空间会更多
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
剑指 Offer 59 - I. 滑动窗口的最大值
给定一个数组 nums 和滑动窗口的大小 k，请找出所有滑动窗口里的最大值。

示例:

输入: nums = [1,3,-1,-3,5,3,6,7], 和 k = 3
输出: [3,3,5,5,6,7] 
解释: 

  滑动窗口的位置                最大值
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7

来源：力扣（LeetCode）
链接：https://leetcode-cn.com/problems/hua-dong-chuang-kou-de-zui-da-zhi-lcof
著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。

 */
//这个题与上边的最小栈结合起来看

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

            //下边的这个for主要处理的情况是当新加入的值小于最大值时，push不会加入MAX，进而MAX不断从前边流失，
            //最终造成MAX流失为空，此时需要确定新的最大值，需要把deq中的数MAXpush到MAX中
            if(MAX.empty()){ //注意这里容易写错！！ 类比最小栈那个题，容易把这个for丢掉（因为最小栈那个不会从另一个方向流失元素）
                for(int i = 0;i<DEQ.size();i++){
                    MAXpush(DEQ[i]); //这就体现出双端队列的好处了，可以直接遍历
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
        for(int i = 0;i<k;i++){ //先把第一个窗口完整的弄满
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