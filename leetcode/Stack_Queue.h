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