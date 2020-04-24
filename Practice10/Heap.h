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
	void CreateHeap(vector <ElemenType> RandomElement);//����Ϊ�������У������������õ���Ӧ�Ķ����д浽HeapData��
private:
	void SetMaxsizeHeap(int MaxSize);
	void SetMaxorMin(int MaxorMin);
	int MaxSize;
	int MaxorMin;//��־�����ѻ�����С��
	vector <ElemenType> HeapData;//ȡֵ��0��ʼ���������ڱ�

};




#endif
