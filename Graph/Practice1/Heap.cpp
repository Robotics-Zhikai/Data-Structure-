#include "Heap.h"

template <class ElemenType>
ElemenType Default;
#define ElemenTypical Default

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
void HeapOperate<ElemenType>::InsertHeapElement(vector <ElemenType> & HeapData, ElemenType Element)
{
	
	if (HeapOperate::IsFullHeap(HeapData) == 1) //如果堆满了就什么也不做
		return;

	HeapData.push_back(Element);

	HeapOperate::indexOrigin.push_back(HeapData.size()-1);
	HeapOperate::Relation.push_back(HeapData.size() - 1);

	if (HeapData.size() == 1)
		return;


	if (HeapOperate::MaxorMin == 1)
	{
		for (int i = HeapData.size() - 1; i>0; i = ceil(double(i) / 2.0) - 1)
		{
			if (HeapData[i] >= HeapData[ceil(double(i) / 2.0) - 1])
			{
				ElemenType midnum = HeapData[ceil(double(i) / 2.0) - 1];
				HeapData[ceil(double(i) / 2.0) - 1] = HeapData[i];
				HeapData[i] = midnum;

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
		for (int i = HeapData.size() - 1; i>0; i = ceil(double(i) / 2.0) - 1)
		{
			if (HeapData[i] <= HeapData[ceil(double(i) / 2.0) - 1])
			{
				ElemenType midnum = HeapData[ceil(double(i) / 2.0) - 1];
				HeapData[ceil(double(i) / 2.0) - 1] = HeapData[i];
				HeapData[i] = midnum;

				HeapOperate::SwapAndUpdate(i, ceil(double(i) / 2.0) - 1);
			}
			else
				break;
		}
	}
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
ElemenType HeapOperate<ElemenType>::DeleteHeapNode(vector <ElemenType> & HeapData,int indexnode)
{
	if (indexnode < 0 || indexnode >= HeapData.size())
		return ElemenTypical;
	if (HeapOperate::IsEmptyHeap(HeapData) == 1)
		return ElemenTypical;

	HeapOperate::SwapAndUpdate(indexnode, HeapOperate::indexOrigin.size() - 1);
	HeapOperate::Delete_indexOrigin(HeapOperate::indexOrigin.size()-1);

	ElemenType returnele;
	returnele = *(HeapData.begin()+indexnode);
	HeapData[indexnode] = *(HeapData.end() - 1);
	HeapData.pop_back();

	Change2Heap(HeapData, indexnode, HeapOperate::MaxorMin);//这就是在一定基础上调整

	return returnele;
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