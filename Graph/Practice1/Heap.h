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
	
	explicit HeapOperate (int MaxorMin, int MaxSize);
	explicit HeapOperate ();

	
	//由于有模板的存在，因此接下来将利用上边的函数进一步封装类似于vector的函数
	//这样本类既可以做操作函数操作其他线性结构，又可以自己作为Heap 存储数据并做一些操作
	int isfull();
	int isempty();
	void push_back(ElemenType Element);
	ElemenType pop_front();
	void inputSeqData2heap(vector <ElemenType> RandomElements); //将随便的一串序列转化为堆的结构
	int read_map2origin(int currentindex); //读取从当前currentindex到原始工号的映射
	int read_map2current(int originindex); //读取从原始工号到现在位置的映射

	ElemenType read_origin_node_value(int OriginIndex);
	ElemenType read_current_node_value(int CurrentIndex);
	ElemenType erase_origin_node(int OriginIndex);
		//删除原始标号是originindex的节点,但目前在Data的什么索引处是需要查询relation才能知道的
		//相当于开除入职时工号为OriginIndex的员工

	ElemenType erase_current_node(int CurrentIndex);
		// 删除现在所处与Data的索引为CurrentIndex的节点 相当于开除现在处于公司某一职位的员工而不管其工号是多少
	void update_origin_node(int OriginIndex, ElemenType value);
		//相当于更新入职工号为OriginIndex的员工的工资
	void update_current_node(int CurrentIndex, ElemenType value);

	int findindex_ele(ElemenType ele); // 找到ele所在索引位置,如找不到返回-1

	template <class Ele> void swap(vector<Ele> & tmp, int indexi, int indexj);
	
	template <class Ele> bool CheckindexValid(vector<Ele> checkdata, int index);

	void error(string msg);

private:
	int GetfatherIndex(int Currentindex); // 得到在当前Data下index索引的父亲节点
	int GetlchildIndex(int Currentindex);
	int GetrchildIndex(int Currentindex);

	int IsFullHeap(vector <ElemenType>  HeapData);
	int IsEmptyHeap(vector <ElemenType>  HeapData);

	void ElementUpswap(int CurrentIndex); //在堆中某空位插入一个value后，向上"冒泡"的过程 如果需要向下调整，则有Change2Heap函数
	void InsertHeapElement(vector <ElemenType> & HeapData, ElemenType Element);

	ElemenType DeleteHeapNode(vector <ElemenType> & HeapData, int indexnode);
	void CreateHeap(vector <ElemenType> & RandomElement);//输入为任意序列，经过堆整理后得到对应的堆序列
	void Change2Heap(vector <ElemenType> & RandomElement, int root, int maxormin);//以root为根节点，调整对应的子树为Heap,当然必须是在一定基础上调整


	void SetMaxsizeHeap(int MaxSize);
	void SetMaxorMin(int MaxorMin);

	void SwapAndUpdate(int i, int j); // 交换index处的值并更新关系表
	void Delete_indexOrigin(int index); // 删除索引为index的indexOrigin的元素及对应的关系表

	void clearall_data(); // 把本类中所有用作存储的变量清空

	void update_Data(int indexData, ElemenType value); //更新在Data上的索引为indexData的值
	
	int MaxSize;
	int MaxorMin;//标志是最大堆还是最小堆 取值为1或2
				 //vector <ElemenType> HeapData;//取值从0开始，不设置哨兵
	vector<ElemenType> Data; 
	vector<int> Relation; //原始输入元素的位置和经过Heap整理后的位置的映射 index为i的元素映射到现在的Relation[i]
	vector<int> indexOrigin; //这个随Heap操作的变化而变化 储存着Data对应位置元素一开始进入时的index编号,长度始终与Data保持一致
	
	//vector <ContainIndexElemenType> DataContainIndex;
};


template <class ElemenType>
void HeapOperate<ElemenType>::inputSeqData2heap(vector <ElemenType> RandomElements) //将随便的一串序列转化为堆的结构
{
	CreateHeap(RandomElements);
	//Data = RandomElements;
}

template <class ElemenType>
ElemenType HeapOperate<ElemenType>::erase_origin_node(int OriginIndex)
//删除原始标号是originindex的节点,但目前在Data的什么索引处是需要查询relation才能知道的
//相当于开除入职时工号为OriginIndex的员工
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
int HeapOperate<ElemenType>::read_map2origin(int currentindex) //读取从当前currentindex到原始工号的映射
{
	if (CheckindexValid(indexOrigin, currentindex))
		return indexOrigin[currentindex];
}

template <class ElemenType>
int HeapOperate<ElemenType>::read_map2current(int originindex) //读取从原始工号到现在位置的映射
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
// 删除现在所处与Data的索引为CurrentIndex的节点 相当于开除现在处于公司某一职位的员工而不管其工号是多少
{
	return DeleteHeapNode(Data, CurrentIndex);
}

template <class ElemenType>
void HeapOperate<ElemenType>::update_origin_node(int OriginIndex, ElemenType value)
//相当于更新入职工号为OriginIndex的员工的工资
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
void HeapOperate<ElemenType>::SwapAndUpdate(int i, int j) // 交换index处的值并更新关系表
{
	if (CheckindexValid(indexOrigin, i) && CheckindexValid(indexOrigin, j))
	{
		swap<int>(HeapOperate::indexOrigin, i, j);
		HeapOperate::Relation[HeapOperate::indexOrigin[i]] = i;
		HeapOperate::Relation[HeapOperate::indexOrigin[j]] = j;
	}
}

template <class ElemenType>
void HeapOperate<ElemenType>::Delete_indexOrigin(int index) // 删除索引为index的indexOrigin的元素及对应的关系表
{
	if (CheckindexValid(indexOrigin, index))
	{
		int originindex = indexOrigin[index]; //一加入Data时的初始索引
		indexOrigin.erase(indexOrigin.begin() + index);
		Relation[originindex] = -1; // 关系表不能删掉这个元素，否则会出现以后加入的元素分配ID不对的问题
	}
}

template <class ElemenType>
void HeapOperate<ElemenType>::clearall_data() // 把本类中所有用作存储的变量清空
{
	Data.clear();
	Relation.clear();
	indexOrigin.clear();
}

template <class ElemenType>
void HeapOperate<ElemenType>::update_Data(int indexData, ElemenType value) //更新在Data上的索引为indexData的值
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
		error("索引超出维度");
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
//输入为任意序列，经过堆整理后得到对应的堆序列存到HeapData中
//如果是一个一个插入，那么是nlogn的算法，但是有n的线性算法
//下边这个是n的线性算法
{
	if (RandomElement.size() <= 1)
	{
		//Heap::HeapData = RandomElement;
		//return RandomElement;
		return;
	}

	HeapOperate::clearall_data();

	vector <ElemenType> RandomElementNew = RandomElement;
	int NumE = RandomElement.size(); //保证不超过最大限度，否则只取前maxsiz个元素
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
//因为堆还不是二叉搜索树的有序结构，因此还是不能达到O(n)的复杂度的
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
		cout << "Error：超出索引维度" << endl;
		system("pause");
	}
		//return ElemenTypical;
	if (HeapOperate::IsEmptyHeap(HeapData) == 1)
	{
		cout << "Error：超出索引维度" << endl;
		system("pause");
	}
		//return ElemenTypical;

	HeapOperate::SwapAndUpdate(indexnode, HeapOperate::indexOrigin.size() - 1);
	HeapOperate::Delete_indexOrigin(HeapOperate::indexOrigin.size() - 1);

	ElemenType returnele;
	returnele = *(HeapData.begin() + indexnode);
	HeapData[indexnode] = *(HeapData.end() - 1);
	HeapData.pop_back();

	Change2Heap(HeapData, indexnode, HeapOperate::MaxorMin);//这就是在一定基础上调整

	return returnele;
}

template <class ElemenType>
void HeapOperate<ElemenType>::Change2Heap(vector <ElemenType> & RandomElement, int root, int maxormin)
//以root为根节点，调整对应的子树为Heap,当然必须是在一定基础上调整
//复杂度为logn
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

						HeapOperate::SwapAndUpdate(i, rchild);//indexOrigin是随动的

						i = rchild;
					}
					else
					{
						ElemenType mid = RandomElement[lchild];
						RandomElement[lchild] = RandomElement[i];
						RandomElement[i] = mid;

						HeapOperate::SwapAndUpdate(i, lchild);//indexOrigin是随动的

						i = lchild;
					}
				}
				else if (RandomElement[lchild] >= RandomElement[i] && RandomElement[rchild] == RandomElement[i])
				{
					ElemenType mid = RandomElement[lchild];
					RandomElement[lchild] = RandomElement[i];
					RandomElement[i] = mid;

					HeapOperate::SwapAndUpdate(i, lchild);//indexOrigin是随动的

					i = lchild;
				}
				else if (RandomElement[lchild] >= RandomElement[i] && RandomElement[rchild] < RandomElement[i])
				{
					ElemenType mid = RandomElement[lchild];
					RandomElement[lchild] = RandomElement[i];
					RandomElement[i] = mid;

					HeapOperate::SwapAndUpdate(i, lchild);//indexOrigin是随动的

					i = lchild;
				}
				else if (RandomElement[rchild] >= RandomElement[i] && RandomElement[lchild] < RandomElement[i])
				{
					ElemenType mid = RandomElement[rchild];
					RandomElement[rchild] = RandomElement[i];
					RandomElement[i] = mid;

					HeapOperate::SwapAndUpdate(i, rchild);//indexOrigin是随动的

					i = rchild;
				}
				else if (RandomElement[rchild] >= RandomElement[i] && RandomElement[lchild] == RandomElement[i])
				{
					ElemenType mid = RandomElement[rchild];
					RandomElement[rchild] = RandomElement[i];
					RandomElement[i] = mid;

					HeapOperate::SwapAndUpdate(i, rchild);//indexOrigin是随动的

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

					HeapOperate::SwapAndUpdate(i, lchild);//indexOrigin是随动的

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

						HeapOperate::SwapAndUpdate(i, rchild);//indexOrigin是随动的

						i = rchild;
					}
					else
					{
						ElemenType mid = RandomElement[lchild];
						RandomElement[lchild] = RandomElement[i];
						RandomElement[i] = mid;

						HeapOperate::SwapAndUpdate(i, lchild);//indexOrigin是随动的

						i = lchild;
					}
				}
				else if (RandomElement[lchild] <= RandomElement[i] && RandomElement[rchild] == RandomElement[i])
				{
					ElemenType mid = RandomElement[lchild];
					RandomElement[lchild] = RandomElement[i];
					RandomElement[i] = mid;

					HeapOperate::SwapAndUpdate(i, lchild);//indexOrigin是随动的

					i = lchild;
				}
				else if (RandomElement[lchild] <= RandomElement[i] && RandomElement[rchild] > RandomElement[i])
				{
					ElemenType mid = RandomElement[lchild];
					RandomElement[lchild] = RandomElement[i];
					RandomElement[i] = mid;

					HeapOperate::SwapAndUpdate(i, lchild);//indexOrigin是随动的

					i = lchild;
				}
				else if (RandomElement[rchild] <= RandomElement[i] && RandomElement[lchild] > RandomElement[i])
				{
					ElemenType mid = RandomElement[rchild];
					RandomElement[rchild] = RandomElement[i];
					RandomElement[i] = mid;

					HeapOperate::SwapAndUpdate(i, rchild);//indexOrigin是随动的

					i = rchild;
				}
				else if (RandomElement[rchild] <= RandomElement[i] && RandomElement[lchild] == RandomElement[i])
				{
					ElemenType mid = RandomElement[rchild];
					RandomElement[rchild] = RandomElement[i];
					RandomElement[i] = mid;

					HeapOperate::SwapAndUpdate(i, rchild);//indexOrigin是随动的

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

					HeapOperate::SwapAndUpdate(i, lchild);//indexOrigin是随动的

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
//输入为现在的元素所处位置索引即工位的位置
//在堆中某空位插入一个value后，向上"冒泡"的过程 如果需要向下调整，则有Change2Heap函数
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
		cout << "error,超出索引维度" << endl;
		system("pause");
	}
}

template <class ElemenType>
void HeapOperate<ElemenType>::InsertHeapElement(vector <ElemenType> & HeapData, ElemenType Element)
{

	if (HeapOperate::IsFullHeap(HeapData) == 1) //如果堆满了就什么也不做
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
		cout << "元素超过了最大值，这是不允许的！" << endl;
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
		HeapOperate::MaxorMin = 1; //如果输入数值出错，则取默认值1
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
		HeapOperate::error("索引超出维度!");
	
}

template <class ElemenType>
int HeapOperate<ElemenType>::GetlchildIndex(int Currentindex)
{
	int lchild = Currentindex * 2 + 1;
	if (HeapOperate::CheckindexValid(Data, Currentindex))
		return lchild;
	else
		HeapOperate::error("索引超出维度!");
}

template <class ElemenType>
int HeapOperate<ElemenType>::GetrchildIndex(int Currentindex)
{
	int lchild = Currentindex * 2 + 1;
	int rchild = lchild + 1;
	if (HeapOperate::CheckindexValid(Data, Currentindex))
		return rchild;
	else
		HeapOperate::error("索引超出维度!");
}
#endif
