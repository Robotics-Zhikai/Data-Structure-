#ifndef HEAP_H
#define HEAP_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include "CustomizeDataType.h"
#include <stdexcept>
using namespace std;

///////////////////////////////////////////////////////////////////////////////////////////
////自定义数据类型示例
//class HeapData:public Point
//{
//public:
//	int SegmentID; //指明所述的线段编号
//	int LorR; //指明是线段的左端还是右端，对于垂直于横轴的线段，下为左，上为右
//	HeapData()
//	{
//		this->Point_X = 0;
//		this->Point_Y = 0;
//		this->Point_Z = 0;
//		this->SegmentID = -1;
//		this->LorR = 0;
//	}
//	HeapData(Point tmp,int Segmentid,int LorR)
//	{
//		this->Point_X = tmp.Point_X;
//		this->Point_Y = tmp.Point_Y;
//		this->Point_Z = tmp.Point_Z;
//		this->SegmentID = Segmentid;
//		this->LorR = LorR;
//	}
//	int operator < (HeapData P2)
//	{
//		if (this->Point_X < P2.Point_X)
//			return 1;
//		else
//			return 0;
//	}
//	int operator <= (HeapData P2)
//	{
//		if (this->Point_X <= P2.Point_X)
//			return 1;
//		else
//			return 0;
//	}
//	int operator >= (HeapData P2)
//	{
//		if (this->Point_X >= P2.Point_X)
//			return 1;
//		else
//			return 0;
//	}
//	int operator > (HeapData P2)
//	{
//		if (this->Point_X > P2.Point_X)
//			return 1;
//		else
//			return 0;
//	}
//	int operator == (HeapData P2)
//	{
//		if (this->Point_X == P2.Point_X)
//			return 1;
//		else
//			return 0;
//	}
//	int operator != (HeapData P2)
//	{
//		if (this->Point_X != P2.Point_X)
//			return 1;
//		else
//			return 0;
//	}
//
//}; //若不是常规的元素，则需要定义比较器，但比较器定义不应该在这个基础调用的库里定义 这应该是用在Geometry Intersection里边的
//typedef HeapData ElemenType;
///////////////////////////////////////////////////////////////////////////////////////////

//#define ElemenTypical  NULL

template <class ElemenType>
class HeapOperate //作为一个操作的执行者 或者数据的储存者
{
public:
	
	HeapOperate (int MaxorMin, int MaxSize)
	{
		SetMaxorMin(MaxorMin);
		SetMaxsizeHeap(MaxSize);

	}
	HeapOperate()
	{
		SetMaxorMin(1);
		SetMaxsizeHeap(10);

	}
	
	//由于有模板的存在，因此接下来将利用上边的函数进一步封装类似于vector的函数
	//这样本类既可以做操作函数操作其他线性结构，又可以自己作为Heap 存储数据并做一些操作
	int isfull()
	{
		return IsFullHeap(Data);
	}
	int isempty()
	{
		return IsEmptyHeap(Data);
	}
	void push_back(ElemenType Element)
	{
		InsertHeapElement(Data, Element);
	}
	ElemenType pop_front()
	{
		return DeleteHeapNode(Data,0);
	}
	void inputSeqData2heap(vector <ElemenType> RandomElements) //将随便的一串序列转化为堆的结构
	{
		CreateHeap(RandomElements);
		//Data = RandomElements;
	}
	int read_map2origin(int currentindex) //读取从当前currentindex到原始工号的映射
	{
		if (CheckindexValid(indexOrigin, currentindex))
			return indexOrigin(currentindex);
	}
	int read_map2current(int originindex) //读取从原始工号到现在位置的映射
	{
		if (CheckindexValid(Relation, originindex))
			return Relation[originindex];
	}
	ElemenType read_origin_node_value(int OriginIndex)
	{
		if (CheckindexValid(Data, Relation[OriginIndex]))
			return Data[Relation[OriginIndex]];
	}
	ElemenType read_current_node_value(int CurrentIndex)
	{
		if (CheckindexValid(Data, CurrentIndex))
			return Data[CurrentIndex];
	}
	ElemenType erase_origin_node(int OriginIndex) 
		//删除原始标号是originindex的节点,但目前在Data的什么索引处是需要查询relation才能知道的
		//相当于开除入职时工号为OriginIndex的员工
	{
		return DeleteHeapNode(Data, Relation[OriginIndex]);
	}
	ElemenType erase_current_node(int CurrentIndex) 
		// 删除现在所处与Data的索引为CurrentIndex的节点 相当于开除现在处于公司某一职位的员工而不管其工号是多少
	{
		return DeleteHeapNode(Data, CurrentIndex);
	}
	void update_origin_node(int OriginIndex,ElemenType value)
		//相当于更新入职工号为OriginIndex的员工的工资
	{
		update_Data(Relation[OriginIndex], value);
		Change2Heap(Data, Relation[OriginIndex], MaxorMin);
	}
	void update_current_node(int CurrentIndex, ElemenType value)
	{
		update_Data(CurrentIndex, value);
		Change2Heap(Data, CurrentIndex, MaxorMin);
	}

	int findindex_ele(ElemenType ele); // 找到ele所在索引位置,如找不到返回-1

	template <class Ele> void swap(vector<Ele> & tmp,int indexi,int indexj)
	{
		if (indexi < 0 || indexi >= tmp.size() || indexj < 0 || indexj >= tmp.size())
			return;
		Ele mid;
		mid = tmp[indexi];
		tmp[indexi] = tmp[indexj];
		tmp[indexj] = mid;
	}
	
	template <class Ele> bool CheckindexValid(vector<Ele> checkdata,int index)
	{
		if (index < 0 || index >= checkdata.size())
			return 0;
		else
			return 1;
	}

private:
	int IsFullHeap(vector <ElemenType>  HeapData);
	int IsEmptyHeap(vector <ElemenType>  HeapData);
	void InsertHeapElement(vector <ElemenType> & HeapData, ElemenType Element);
	ElemenType DeleteHeapNode(vector <ElemenType> & HeapData,int indexnode);
	void CreateHeap(vector <ElemenType> & RandomElement);//输入为任意序列，经过堆整理后得到对应的堆序列
	void Change2Heap(vector <ElemenType> & RandomElement, int root, int maxormin);//以root为根节点，调整对应的子树为Heap,当然必须是在一定基础上调整


	void SetMaxsizeHeap(int MaxSize);
	void SetMaxorMin(int MaxorMin);
	int MaxSize;
	int MaxorMin;//标志是最大堆还是最小堆 取值为1或2
				 //vector <ElemenType> HeapData;//取值从0开始，不设置哨兵

	void SwapAndUpdate(int i, int j) // 交换index处的值并更新关系表
	{
		if (CheckindexValid(indexOrigin, i) && CheckindexValid(indexOrigin, j))
		{
			swap<int>(HeapOperate::indexOrigin, i, j);
			HeapOperate::Relation[HeapOperate::indexOrigin[i]] = i;
			HeapOperate::Relation[HeapOperate::indexOrigin[j]] = j;
		}
	}
	void Delete_indexOrigin(int index) // 删除索引为index的indexOrigin的元素及对应的关系表
	{
		if (CheckindexValid(indexOrigin, index))
		{
			int originindex = indexOrigin[index]; //一加入Data时的初始索引
			indexOrigin.erase(indexOrigin.begin() + index);
			Relation[originindex] = -1; // 关系表不能删掉这个元素，否则会出现以后加入的元素分配ID不对的问题
		}
	}
	void clearall_data() // 把本类中所有用作存储的变量清空
	{
		Data.clear();
		Relation.clear();
		indexOrigin.clear();
	}

	void update_Data(int indexData,ElemenType value) //更新在Data上的索引为indexData的值
	{
		if (CheckindexValid(Data,indexData))
		{
			Data[indexData] = value;
		}
	}

	vector<ElemenType> Data; 
	vector<int> Relation; //原始输入元素的位置和经过Heap整理后的位置的映射 index为i的元素映射到现在的Relation[i]
	vector<int> indexOrigin; //这个随Heap操作的变化而变化 储存着Data对应位置元素一开始进入时的index编号,长度始终与Data保持一致
	
	//vector <ContainIndexElemenType> DataContainIndex;
};

//template <class ElemenType>
//class ContainIndexElemenType
//{
//public:
//	ElemenType E;
//	int indexOrigin; //原始一开始加入到线性存储的内存中时的index
//	int indexNow; //经过堆操作调整之后在Data中的index
//
//	ContainIndexElemenType(ElemenType test)
//	{
//		this->E = test;
//	}
//};


#endif
