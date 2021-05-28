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