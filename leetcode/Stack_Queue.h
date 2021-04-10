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