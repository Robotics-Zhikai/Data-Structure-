#ifndef HEAP_H
#define HEAP_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <math.h>
using namespace std;

typedef double ElemenType;
#define ElemenTypical  NULL


class Heap
{
public:
	int IsFullHeap();
	int IsEmptyHeap();
	Heap(int MaxorMin,int MaxSize)
	{
		SetMaxorMin(MaxorMin);
		SetMaxsizeHeap(MaxSize);
	}
	void InsertHeapElement(ElemenType Element);
	ElemenType DeleteHeapRoot();
	void CreateHeap(vector <ElemenType> RandomElement);//输入为任意序列，经过堆整理后得到对应的堆序列存到HeapData中
private:
	void SetMaxsizeHeap(int MaxSize);
	void SetMaxorMin(int MaxorMin);
	int MaxSize;
	int MaxorMin;//标志是最大堆还是最小堆
	vector <ElemenType> HeapData;//取值从0开始，不设置哨兵

};




#endif
