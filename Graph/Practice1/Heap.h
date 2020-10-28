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
	
	explicit HeapOperate (int MaxorMin, int MaxSize);
	explicit HeapOperate ();

	
	//������ģ��Ĵ��ڣ���˽������������ϱߵĺ�����һ����װ������vector�ĺ���
	//��������ȿ������������������������Խṹ���ֿ����Լ���ΪHeap �洢���ݲ���һЩ����
	int isfull();
	int isempty();
	void push_back(ElemenType Element);
	ElemenType pop_front();
	void inputSeqData2heap(vector <ElemenType> RandomElements); //������һ������ת��Ϊ�ѵĽṹ
	int read_map2origin(int currentindex); //��ȡ�ӵ�ǰcurrentindex��ԭʼ���ŵ�ӳ��
	int read_map2current(int originindex); //��ȡ��ԭʼ���ŵ�����λ�õ�ӳ��

	ElemenType read_origin_node_value(int OriginIndex);
	ElemenType read_current_node_value(int CurrentIndex);
	ElemenType erase_origin_node(int OriginIndex);
		//ɾ��ԭʼ�����originindex�Ľڵ�,��Ŀǰ��Data��ʲô����������Ҫ��ѯrelation����֪����
		//�൱�ڿ�����ְʱ����ΪOriginIndex��Ա��

	ElemenType erase_current_node(int CurrentIndex);
		// ɾ������������Data������ΪCurrentIndex�Ľڵ� �൱�ڿ������ڴ��ڹ�˾ĳһְλ��Ա���������乤���Ƕ���
	void update_origin_node(int OriginIndex, ElemenType value);
		//�൱�ڸ�����ְ����ΪOriginIndex��Ա���Ĺ���
	void update_current_node(int CurrentIndex, ElemenType value);

	int findindex_ele(ElemenType ele); // �ҵ�ele��������λ��,���Ҳ�������-1

	template <class Ele> void swap(vector<Ele> & tmp, int indexi, int indexj);
	
	template <class Ele> bool CheckindexValid(vector<Ele> checkdata, int index);

	void error(string msg);

private:
	int GetfatherIndex(int Currentindex); // �õ��ڵ�ǰData��index�����ĸ��׽ڵ�
	int GetlchildIndex(int Currentindex);
	int GetrchildIndex(int Currentindex);

	int IsFullHeap(vector <ElemenType>  HeapData);
	int IsEmptyHeap(vector <ElemenType>  HeapData);

	void ElementUpswap(int CurrentIndex); //�ڶ���ĳ��λ����һ��value������"ð��"�Ĺ��� �����Ҫ���µ���������Change2Heap����
	void InsertHeapElement(vector <ElemenType> & HeapData, ElemenType Element);

	ElemenType DeleteHeapNode(vector <ElemenType> & HeapData, int indexnode);
	void CreateHeap(vector <ElemenType> & RandomElement);//����Ϊ�������У������������õ���Ӧ�Ķ�����
	void Change2Heap(vector <ElemenType> & RandomElement, int root, int maxormin);//��rootΪ���ڵ㣬������Ӧ������ΪHeap,��Ȼ��������һ�������ϵ���


	void SetMaxsizeHeap(int MaxSize);
	void SetMaxorMin(int MaxorMin);

	void SwapAndUpdate(int i, int j); // ����index����ֵ�����¹�ϵ��
	void Delete_indexOrigin(int index); // ɾ������Ϊindex��indexOrigin��Ԫ�ؼ���Ӧ�Ĺ�ϵ��

	void clearall_data(); // �ѱ��������������洢�ı������

	void update_Data(int indexData, ElemenType value); //������Data�ϵ�����ΪindexData��ֵ
	
	int MaxSize;
	int MaxorMin;//��־�����ѻ�����С�� ȡֵΪ1��2
				 //vector <ElemenType> HeapData;//ȡֵ��0��ʼ���������ڱ�
	vector<ElemenType> Data; 
	vector<int> Relation; //ԭʼ����Ԫ�ص�λ�ú;���Heap������λ�õ�ӳ�� indexΪi��Ԫ��ӳ�䵽���ڵ�Relation[i]
	vector<int> indexOrigin; //�����Heap�����ı仯���仯 ������Data��Ӧλ��Ԫ��һ��ʼ����ʱ��index���,����ʼ����Data����һ��
	
	//vector <ContainIndexElemenType> DataContainIndex;
};


template <class ElemenType>
void HeapOperate<ElemenType>::inputSeqData2heap(vector <ElemenType> RandomElements) //������һ������ת��Ϊ�ѵĽṹ
{
	CreateHeap(RandomElements);
	//Data = RandomElements;
}

template <class ElemenType>
ElemenType HeapOperate<ElemenType>::erase_origin_node(int OriginIndex)
//ɾ��ԭʼ�����originindex�Ľڵ�,��Ŀǰ��Data��ʲô����������Ҫ��ѯrelation����֪����
//�൱�ڿ�����ְʱ����ΪOriginIndex��Ա��
{
	return DeleteHeapNode(Data, Relation[OriginIndex]);
}

template <class ElemenType>
int HeapOperate<ElemenType>::isfull()
{
	return IsFullHeap(Data);
}

template <class ElemenType>
int HeapOperate<ElemenType>::isempty()
{
	return IsEmptyHeap(Data);
}

template <class ElemenType>
void HeapOperate<ElemenType>::push_back(ElemenType Element)
{
	InsertHeapElement(Data, Element);
}

template <class ElemenType>
ElemenType HeapOperate<ElemenType>::pop_front()
{
	return DeleteHeapNode(Data, 0);
}

template <class ElemenType>
int HeapOperate<ElemenType>::read_map2origin(int currentindex) //��ȡ�ӵ�ǰcurrentindex��ԭʼ���ŵ�ӳ��
{
	if (CheckindexValid(indexOrigin, currentindex))
		return indexOrigin[currentindex];
}

template <class ElemenType>
int HeapOperate<ElemenType>::read_map2current(int originindex) //��ȡ��ԭʼ���ŵ�����λ�õ�ӳ��
{
	if (CheckindexValid(Relation, originindex))
		return Relation[originindex];
}

template <class ElemenType>
ElemenType HeapOperate<ElemenType>::read_origin_node_value(int OriginIndex)
{
	if (CheckindexValid(Data, Relation[OriginIndex]))
		return Data[Relation[OriginIndex]];
}

template <class ElemenType>
ElemenType HeapOperate<ElemenType>::read_current_node_value(int CurrentIndex)
{
	if (CheckindexValid(Data, CurrentIndex))
		return Data[CurrentIndex];
}

template <class ElemenType>
ElemenType HeapOperate<ElemenType>::erase_current_node(int CurrentIndex)
// ɾ������������Data������ΪCurrentIndex�Ľڵ� �൱�ڿ������ڴ��ڹ�˾ĳһְλ��Ա���������乤���Ƕ���
{
	return DeleteHeapNode(Data, CurrentIndex);
}

template <class ElemenType>
void HeapOperate<ElemenType>::update_origin_node(int OriginIndex, ElemenType value)
//�൱�ڸ�����ְ����ΪOriginIndex��Ա���Ĺ���
{
	update_Data(Relation[OriginIndex], value);
}

template <class ElemenType>
void HeapOperate<ElemenType>::update_current_node(int CurrentIndex, ElemenType value)
{
	update_Data(CurrentIndex, value);
}

template <class ElemenType>
template <class Ele> void HeapOperate<ElemenType>::swap(vector<Ele> & tmp, int indexi, int indexj)
{
	if (indexi < 0 || indexi >= tmp.size() || indexj < 0 || indexj >= tmp.size())
		return;
	Ele mid;
	mid = tmp[indexi];
	tmp[indexi] = tmp[indexj];
	tmp[indexj] = mid;
}

template <class ElemenType>
template <class Ele> bool HeapOperate<ElemenType>::CheckindexValid(vector<Ele> checkdata, int index)
{
	if (index < 0 || index >= checkdata.size())
		return 0;
	else
		return 1;
}

template <class ElemenType>
void HeapOperate<ElemenType>::SwapAndUpdate(int i, int j) // ����index����ֵ�����¹�ϵ��
{
	if (CheckindexValid(indexOrigin, i) && CheckindexValid(indexOrigin, j))
	{
		swap<int>(HeapOperate::indexOrigin, i, j);
		HeapOperate::Relation[HeapOperate::indexOrigin[i]] = i;
		HeapOperate::Relation[HeapOperate::indexOrigin[j]] = j;
	}
}

template <class ElemenType>
void HeapOperate<ElemenType>::Delete_indexOrigin(int index) // ɾ������Ϊindex��indexOrigin��Ԫ�ؼ���Ӧ�Ĺ�ϵ��
{
	if (CheckindexValid(indexOrigin, index))
	{
		int originindex = indexOrigin[index]; //һ����Dataʱ�ĳ�ʼ����
		indexOrigin.erase(indexOrigin.begin() + index);
		Relation[originindex] = -1; // ��ϵ����ɾ�����Ԫ�أ����������Ժ�����Ԫ�ط���ID���Ե�����
	}
}

template <class ElemenType>
void HeapOperate<ElemenType>::clearall_data() // �ѱ��������������洢�ı������
{
	Data.clear();
	Relation.clear();
	indexOrigin.clear();
}

template <class ElemenType>
void HeapOperate<ElemenType>::update_Data(int indexData, ElemenType value) //������Data�ϵ�����ΪindexData��ֵ
{
	if (CheckindexValid(Data, indexData))
	{
		Data[indexData] = value;
		int fatherIndex = HeapOperate::GetfatherIndex(indexData);
		int lchild = HeapOperate::GetlchildIndex(indexData);
		int rchild = HeapOperate::GetrchildIndex(indexData);
		if (HeapOperate::MaxorMin == 1)
		{
			int Flagdone = 0;
			if (Flagdone == 0 && HeapOperate::CheckindexValid(Data, fatherIndex))
			{
				if (value > Data[fatherIndex])
				{
					ElementUpswap(indexData);
					Flagdone = 1;
				}
			}
			if (Flagdone == 0 && HeapOperate::CheckindexValid(Data, lchild))
			{
				if (value < Data[lchild])
				{
					Change2Heap(Data, indexData, HeapOperate::MaxorMin);
					Flagdone = 1;
				}
			}
			if (Flagdone == 0 && HeapOperate::CheckindexValid(Data, rchild))
			{
				if (value < Data[rchild])
				{
					Change2Heap(Data, indexData, HeapOperate::MaxorMin);
					Flagdone = 1;
				}
			}
		}
		else if (HeapOperate::MaxorMin == 2)
		{
			int Flagdone = 0;
			if (Flagdone == 0 && HeapOperate::CheckindexValid(Data, fatherIndex))
			{
				if (value < Data[fatherIndex])
				{
					ElementUpswap(indexData);
					Flagdone = 1;
				}
			}
			if (Flagdone == 0 && HeapOperate::CheckindexValid(Data, lchild))
			{
				if (value > Data[lchild])
				{
					Change2Heap(Data, indexData, HeapOperate::MaxorMin);
					Flagdone = 1;
				}
			}
			if (Flagdone == 0 && HeapOperate::CheckindexValid(Data, rchild))
			{
				if (value > Data[rchild])
				{
					Change2Heap(Data, indexData, HeapOperate::MaxorMin);
					Flagdone = 1;
				}
			}
		}
	}
	else
	{
		error("��������ά��");
	}
}

template <class ElemenType>
HeapOperate<ElemenType>::HeapOperate(int MaxorMin, int MaxSize)
{
	HeapOperate::SetMaxorMin(MaxorMin);
	HeapOperate::SetMaxsizeHeap(MaxSize);
}

template <class ElemenType>
HeapOperate<ElemenType>::HeapOperate()
{
	HeapOperate::SetMaxorMin(1);
	HeapOperate::SetMaxsizeHeap(10);
}

template <class ElemenType>
void HeapOperate<ElemenType>::CreateHeap(vector <ElemenType> & RandomElement)
//����Ϊ�������У������������õ���Ӧ�Ķ����д浽HeapData��
//�����һ��һ�����룬��ô��nlogn���㷨��������n�������㷨
//�±������n�������㷨
{
	if (RandomElement.size() <= 1)
	{
		//Heap::HeapData = RandomElement;
		//return RandomElement;
		return;
	}

	HeapOperate::clearall_data();

	vector <ElemenType> RandomElementNew = RandomElement;
	int NumE = RandomElement.size(); //��֤����������޶ȣ�����ֻȡǰmaxsiz��Ԫ��
	if (NumE > HeapOperate::MaxSize)
	{
		NumE = HeapOperate::MaxSize;
		RandomElementNew.clear();
		for (int i = 0; i < NumE; i++)
			RandomElementNew.push_back(RandomElement[i]);
	}

	for (int i = 0; i < NumE; i++)
	{
		HeapOperate::indexOrigin.push_back(i);
		HeapOperate::Relation.push_back(i);
		//HeapOperate::Data.push_back(RandomElement[i]);
	}


	for (int i = ceil(double((NumE - 1) / 2.0)) - 1; i >= 0; i--)
	{
		Change2Heap(RandomElementNew, i, HeapOperate::MaxorMin);
	}

	for (int i = 0; i < NumE; i++)
		HeapOperate::Data.push_back(RandomElementNew[i]);

	//RandomElement = Heap::HeapData;
	//return RandomElement;
	return;

}

template <class ElemenType>
int HeapOperate<ElemenType>::findindex_ele(ElemenType ele)
//��Ϊ�ѻ����Ƕ���������������ṹ����˻��ǲ��ܴﵽO(n)�ĸ��Ӷȵ�
{
	int index = -1;
	if (isempty() == 1)
		return index;
	for (int i = 0; i < Data.size(); i++)
	{
		if (ele == Data[i])
			return i;
	}
}

template <class ElemenType>
ElemenType HeapOperate<ElemenType>::DeleteHeapNode(vector <ElemenType> & HeapData, int indexnode)
{
	if (indexnode < 0 || indexnode >= HeapData.size())
	{
		cout << "Error����������ά��" << endl;
		system("pause");
	}
		//return ElemenTypical;
	if (HeapOperate::IsEmptyHeap(HeapData) == 1)
	{
		cout << "Error����������ά��" << endl;
		system("pause");
	}
		//return ElemenTypical;

	HeapOperate::SwapAndUpdate(indexnode, HeapOperate::indexOrigin.size() - 1);
	HeapOperate::Delete_indexOrigin(HeapOperate::indexOrigin.size() - 1);

	ElemenType returnele;
	returnele = *(HeapData.begin() + indexnode);
	HeapData[indexnode] = *(HeapData.end() - 1);
	HeapData.pop_back();

	Change2Heap(HeapData, indexnode, HeapOperate::MaxorMin);//�������һ�������ϵ���

	return returnele;
}

template <class ElemenType>
void HeapOperate<ElemenType>::Change2Heap(vector <ElemenType> & RandomElement, int root, int maxormin)
//��rootΪ���ڵ㣬������Ӧ������ΪHeap,��Ȼ��������һ�������ϵ���
//���Ӷ�Ϊlogn
{
	if (RandomElement.size() <= 1)
		return;

	if (maxormin == 1)
	{
		for (int i = root; i < RandomElement.size(); )
		{
			int lchild = i * 2 + 1;
			int rchild = lchild + 1;
			if (lchild >= RandomElement.size())
				break;
			if (rchild < RandomElement.size())
			{
				if (RandomElement[lchild] > RandomElement[i] && RandomElement[rchild] > RandomElement[i])
				{
					if (RandomElement[rchild] >= RandomElement[lchild])
					{
						ElemenType mid = RandomElement[rchild];
						RandomElement[rchild] = RandomElement[i];
						RandomElement[i] = mid;

						HeapOperate::SwapAndUpdate(i, rchild);//indexOrigin���涯��

						i = rchild;
					}
					else
					{
						ElemenType mid = RandomElement[lchild];
						RandomElement[lchild] = RandomElement[i];
						RandomElement[i] = mid;

						HeapOperate::SwapAndUpdate(i, lchild);//indexOrigin���涯��

						i = lchild;
					}
				}
				else if (RandomElement[lchild] >= RandomElement[i] && RandomElement[rchild] == RandomElement[i])
				{
					ElemenType mid = RandomElement[lchild];
					RandomElement[lchild] = RandomElement[i];
					RandomElement[i] = mid;

					HeapOperate::SwapAndUpdate(i, lchild);//indexOrigin���涯��

					i = lchild;
				}
				else if (RandomElement[lchild] >= RandomElement[i] && RandomElement[rchild] < RandomElement[i])
				{
					ElemenType mid = RandomElement[lchild];
					RandomElement[lchild] = RandomElement[i];
					RandomElement[i] = mid;

					HeapOperate::SwapAndUpdate(i, lchild);//indexOrigin���涯��

					i = lchild;
				}
				else if (RandomElement[rchild] >= RandomElement[i] && RandomElement[lchild] < RandomElement[i])
				{
					ElemenType mid = RandomElement[rchild];
					RandomElement[rchild] = RandomElement[i];
					RandomElement[i] = mid;

					HeapOperate::SwapAndUpdate(i, rchild);//indexOrigin���涯��

					i = rchild;
				}
				else if (RandomElement[rchild] >= RandomElement[i] && RandomElement[lchild] == RandomElement[i])
				{
					ElemenType mid = RandomElement[rchild];
					RandomElement[rchild] = RandomElement[i];
					RandomElement[i] = mid;

					HeapOperate::SwapAndUpdate(i, rchild);//indexOrigin���涯��

					i = rchild;
				}
				else
					break;
			}
			else
			{
				if (RandomElement[lchild] > RandomElement[i])
				{
					ElemenType mid = RandomElement[lchild];
					RandomElement[lchild] = RandomElement[i];
					RandomElement[i] = mid;

					HeapOperate::SwapAndUpdate(i, lchild);//indexOrigin���涯��

					i = lchild;
				}
				else
					break;
			}
		}
	}
	if (maxormin == 2)
	{
		for (int i = root; i < RandomElement.size(); )
		{
			int lchild = i * 2 + 1;
			int rchild = lchild + 1;
			if (lchild >= RandomElement.size())
				break;
			if (rchild < RandomElement.size())
			{
				if (RandomElement[lchild] < RandomElement[i] && RandomElement[rchild] < RandomElement[i])
				{
					if (RandomElement[rchild] <= RandomElement[lchild])
					{
						ElemenType mid = RandomElement[rchild];
						RandomElement[rchild] = RandomElement[i];
						RandomElement[i] = mid;

						HeapOperate::SwapAndUpdate(i, rchild);//indexOrigin���涯��

						i = rchild;
					}
					else
					{
						ElemenType mid = RandomElement[lchild];
						RandomElement[lchild] = RandomElement[i];
						RandomElement[i] = mid;

						HeapOperate::SwapAndUpdate(i, lchild);//indexOrigin���涯��

						i = lchild;
					}
				}
				else if (RandomElement[lchild] <= RandomElement[i] && RandomElement[rchild] == RandomElement[i])
				{
					ElemenType mid = RandomElement[lchild];
					RandomElement[lchild] = RandomElement[i];
					RandomElement[i] = mid;

					HeapOperate::SwapAndUpdate(i, lchild);//indexOrigin���涯��

					i = lchild;
				}
				else if (RandomElement[lchild] <= RandomElement[i] && RandomElement[rchild] > RandomElement[i])
				{
					ElemenType mid = RandomElement[lchild];
					RandomElement[lchild] = RandomElement[i];
					RandomElement[i] = mid;

					HeapOperate::SwapAndUpdate(i, lchild);//indexOrigin���涯��

					i = lchild;
				}
				else if (RandomElement[rchild] <= RandomElement[i] && RandomElement[lchild] > RandomElement[i])
				{
					ElemenType mid = RandomElement[rchild];
					RandomElement[rchild] = RandomElement[i];
					RandomElement[i] = mid;

					HeapOperate::SwapAndUpdate(i, rchild);//indexOrigin���涯��

					i = rchild;
				}
				else if (RandomElement[rchild] <= RandomElement[i] && RandomElement[lchild] == RandomElement[i])
				{
					ElemenType mid = RandomElement[rchild];
					RandomElement[rchild] = RandomElement[i];
					RandomElement[i] = mid;

					HeapOperate::SwapAndUpdate(i, rchild);//indexOrigin���涯��

					i = rchild;
				}
				else
					break;
			}
			else
			{
				if (RandomElement[lchild] < RandomElement[i])
				{
					ElemenType mid = RandomElement[lchild];
					RandomElement[lchild] = RandomElement[i];
					RandomElement[i] = mid;

					HeapOperate::SwapAndUpdate(i, lchild);//indexOrigin���涯��

					i = lchild;
				}
				else
					break;
			}
		}
	}
	return;
}

template <class ElemenType>
void HeapOperate<ElemenType>::ElementUpswap(int CurrentIndex)
//����Ϊ���ڵ�Ԫ������λ����������λ��λ��
//�ڶ���ĳ��λ����һ��value������"ð��"�Ĺ��� �����Ҫ���µ���������Change2Heap����
{
	if (HeapOperate::CheckindexValid(HeapOperate::Data, CurrentIndex))
	{
		if (HeapOperate::MaxorMin == 1)
		{
			for (int i = CurrentIndex; i>0; i = ceil(double(i) / 2.0) - 1)
			{
				if (Data[i] >= Data[ceil(double(i) / 2.0) - 1])
				{
					ElemenType midnum = Data[ceil(double(i) / 2.0) - 1];
					Data[ceil(double(i) / 2.0) - 1] = Data[i];
					Data[i] = midnum;

					HeapOperate::SwapAndUpdate(i, ceil(double(i) / 2.0) - 1);
					/*HeapOperate::swap<int>(HeapOperate::indexOrigin, i, ceil(double(i) / 2.0) - 1);
					HeapOperate::Relation[HeapOperate::indexOrigin[i]] = i;
					HeapOperate::Relation[HeapOperate::indexOrigin[ceil(double(i) / 2.0) - 1]] = ceil(double(i) / 2.0) - 1;*/
				}
				else
					break;
			}
		}
		if (HeapOperate::MaxorMin == 2)
		{
			for (int i = CurrentIndex; i>0; i = ceil(double(i) / 2.0) - 1)
			{
				if (Data[i] <= Data[ceil(double(i) / 2.0) - 1])
				{
					ElemenType midnum = Data[ceil(double(i) / 2.0) - 1];
					Data[ceil(double(i) / 2.0) - 1] = Data[i];
					Data[i] = midnum;

					HeapOperate::SwapAndUpdate(i, ceil(double(i) / 2.0) - 1);
				}
				else
					break;
			}
		}
	}
	else
	{
		cout << "error,��������ά��" << endl;
		system("pause");
	}
}

template <class ElemenType>
void HeapOperate<ElemenType>::InsertHeapElement(vector <ElemenType> & HeapData, ElemenType Element)
{

	if (HeapOperate::IsFullHeap(HeapData) == 1) //��������˾�ʲôҲ����
		return;

	HeapData.push_back(Element);

	HeapOperate::indexOrigin.push_back(HeapData.size() - 1);
	HeapOperate::Relation.push_back(HeapData.size() - 1);

	if (HeapData.size() == 1)
		return;

	HeapOperate<ElemenType>::ElementUpswap(HeapData.size() - 1);
	
}

template <class ElemenType>
void HeapOperate<ElemenType>::SetMaxsizeHeap(int MaxSize)
{
	HeapOperate::MaxSize = MaxSize;
}

template <class ElemenType>
int HeapOperate<ElemenType>::IsFullHeap(vector <ElemenType> HeapData)
{
	if (HeapData.size() > HeapOperate::MaxSize)
	{
		cout << "Ԫ�س��������ֵ�����ǲ�����ģ�" << endl;
		return -1;
	}
	if (HeapData.size() == HeapOperate::MaxSize)
		return 1;
	else
		return 0;
}

template <class ElemenType>
int HeapOperate<ElemenType>::IsEmptyHeap(vector <ElemenType> HeapData)
{
	if (HeapData.size() == 0)
		return 1;
	else
		return 0;
}

template <class ElemenType>
void HeapOperate<ElemenType>::SetMaxorMin(int MaxorMin)
{
	if (MaxorMin != 1 && MaxorMin != 2)
		HeapOperate::MaxorMin = 1; //���������ֵ������ȡĬ��ֵ1
	HeapOperate::MaxorMin = MaxorMin;
}

template <class ElemenType>
void HeapOperate<ElemenType>::error(string msg)
{
	cout << "error:" << msg << endl;
	system("pause");
}

template <class ElemenType>
int HeapOperate<ElemenType>::GetfatherIndex(int Currentindex)
{
	if (HeapOperate::CheckindexValid(Data, Currentindex))
		return ceil(double(Currentindex) / 2.0) - 1;
	else
		HeapOperate::error("��������ά��!");
	
}

template <class ElemenType>
int HeapOperate<ElemenType>::GetlchildIndex(int Currentindex)
{
	int lchild = Currentindex * 2 + 1;
	if (HeapOperate::CheckindexValid(Data, Currentindex))
		return lchild;
	else
		HeapOperate::error("��������ά��!");
}

template <class ElemenType>
int HeapOperate<ElemenType>::GetrchildIndex(int Currentindex)
{
	int lchild = Currentindex * 2 + 1;
	int rchild = lchild + 1;
	if (HeapOperate::CheckindexValid(Data, Currentindex))
		return rchild;
	else
		HeapOperate::error("��������ά��!");
}
#endif
