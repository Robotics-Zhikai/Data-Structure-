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
////�Զ�����������ʾ��
//class HeapData:public Point
//{
//public:
//	int SegmentID; //ָ���������߶α��
//	int LorR; //ָ�����߶ε���˻����Ҷˣ����ڴ�ֱ�ں�����߶Σ���Ϊ����Ϊ��
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
//}; //�����ǳ����Ԫ�أ�����Ҫ����Ƚ��������Ƚ������岻Ӧ��������������õĿ��ﶨ�� ��Ӧ��������Geometry Intersection��ߵ�
//typedef HeapData ElemenType;
///////////////////////////////////////////////////////////////////////////////////////////

//#define ElemenTypical  NULL

template <class ElemenType>
class HeapOperate //��Ϊһ��������ִ���� �������ݵĴ�����
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
	
	//������ģ��Ĵ��ڣ���˽������������ϱߵĺ�����һ����װ������vector�ĺ���
	//��������ȿ������������������������Խṹ���ֿ����Լ���ΪHeap �洢���ݲ���һЩ����
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
	void inputSeqData2heap(vector <ElemenType> RandomElements) //������һ������ת��Ϊ�ѵĽṹ
	{
		CreateHeap(RandomElements);
		//Data = RandomElements;
	}
	int read_map2origin(int currentindex) //��ȡ�ӵ�ǰcurrentindex��ԭʼ���ŵ�ӳ��
	{
		if (CheckindexValid(indexOrigin, currentindex))
			return indexOrigin(currentindex);
	}
	int read_map2current(int originindex) //��ȡ��ԭʼ���ŵ�����λ�õ�ӳ��
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
		//ɾ��ԭʼ�����originindex�Ľڵ�,��Ŀǰ��Data��ʲô����������Ҫ��ѯrelation����֪����
		//�൱�ڿ�����ְʱ����ΪOriginIndex��Ա��
	{
		return DeleteHeapNode(Data, Relation[OriginIndex]);
	}
	ElemenType erase_current_node(int CurrentIndex) 
		// ɾ������������Data������ΪCurrentIndex�Ľڵ� �൱�ڿ������ڴ��ڹ�˾ĳһְλ��Ա���������乤���Ƕ���
	{
		return DeleteHeapNode(Data, CurrentIndex);
	}
	void update_origin_node(int OriginIndex,ElemenType value)
		//�൱�ڸ�����ְ����ΪOriginIndex��Ա���Ĺ���
	{
		update_Data(Relation[OriginIndex], value);
		Change2Heap(Data, Relation[OriginIndex], MaxorMin);
	}
	void update_current_node(int CurrentIndex, ElemenType value)
	{
		update_Data(CurrentIndex, value);
		Change2Heap(Data, CurrentIndex, MaxorMin);
	}

	int findindex_ele(ElemenType ele); // �ҵ�ele��������λ��,���Ҳ�������-1

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
	void CreateHeap(vector <ElemenType> & RandomElement);//����Ϊ�������У������������õ���Ӧ�Ķ�����
	void Change2Heap(vector <ElemenType> & RandomElement, int root, int maxormin);//��rootΪ���ڵ㣬������Ӧ������ΪHeap,��Ȼ��������һ�������ϵ���


	void SetMaxsizeHeap(int MaxSize);
	void SetMaxorMin(int MaxorMin);
	int MaxSize;
	int MaxorMin;//��־�����ѻ�����С�� ȡֵΪ1��2
				 //vector <ElemenType> HeapData;//ȡֵ��0��ʼ���������ڱ�

	void SwapAndUpdate(int i, int j) // ����index����ֵ�����¹�ϵ��
	{
		if (CheckindexValid(indexOrigin, i) && CheckindexValid(indexOrigin, j))
		{
			swap<int>(HeapOperate::indexOrigin, i, j);
			HeapOperate::Relation[HeapOperate::indexOrigin[i]] = i;
			HeapOperate::Relation[HeapOperate::indexOrigin[j]] = j;
		}
	}
	void Delete_indexOrigin(int index) // ɾ������Ϊindex��indexOrigin��Ԫ�ؼ���Ӧ�Ĺ�ϵ��
	{
		if (CheckindexValid(indexOrigin, index))
		{
			int originindex = indexOrigin[index]; //һ����Dataʱ�ĳ�ʼ����
			indexOrigin.erase(indexOrigin.begin() + index);
			Relation[originindex] = -1; // ��ϵ����ɾ�����Ԫ�أ����������Ժ�����Ԫ�ط���ID���Ե�����
		}
	}
	void clearall_data() // �ѱ��������������洢�ı������
	{
		Data.clear();
		Relation.clear();
		indexOrigin.clear();
	}

	void update_Data(int indexData,ElemenType value) //������Data�ϵ�����ΪindexData��ֵ
	{
		if (CheckindexValid(Data,indexData))
		{
			Data[indexData] = value;
		}
	}

	vector<ElemenType> Data; 
	vector<int> Relation; //ԭʼ����Ԫ�ص�λ�ú;���Heap������λ�õ�ӳ�� indexΪi��Ԫ��ӳ�䵽���ڵ�Relation[i]
	vector<int> indexOrigin; //�����Heap�����ı仯���仯 ������Data��Ӧλ��Ԫ��һ��ʼ����ʱ��index���,����ʼ����Data����һ��
	
	//vector <ContainIndexElemenType> DataContainIndex;
};

//template <class ElemenType>
//class ContainIndexElemenType
//{
//public:
//	ElemenType E;
//	int indexOrigin; //ԭʼһ��ʼ���뵽���Դ洢���ڴ���ʱ��index
//	int indexNow; //�����Ѳ�������֮����Data�е�index
//
//	ContainIndexElemenType(ElemenType test)
//	{
//		this->E = test;
//	}
//};


#endif
