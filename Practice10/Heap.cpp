#include "Heap.h"


void Heap ::SetMaxsizeHeap(int MaxSize)
{
	Heap::MaxSize = MaxSize;
}

int Heap :: IsFullHeap()
{
	if (Heap::HeapData.size() > Heap::MaxSize)
	{
		cout << "元素超过了最大值，这是不允许的！" << endl;
		return -1;
	}
	if (Heap::HeapData.size() == Heap::MaxSize)
		return 1;
	else
		return 0;
}

int Heap::IsEmptyHeap()
{
	if (Heap::HeapData.size() == 0)
		return 1;
	else
		return 0;
}

void Heap::SetMaxorMin(int MaxorMin)
{
	Heap::MaxorMin = MaxorMin;
}

void Heap::InsertHeapElement(ElemenType Element)
{
	if (Heap::IsFullHeap() == 1)
		return;
	Heap::HeapData.push_back(Element);
	if (Heap::HeapData.size() == 1)
		return;

	if (Heap::MaxorMin == 1)
	{
		for (int i = Heap::HeapData.size() - 1;i>0 ;i= ceil(double(i) / 2.0) - 1)
		{
			if (Heap::HeapData[i] >= Heap::HeapData[ceil(double(i) / 2.0) - 1])
			{
				ElemenType midnum = Heap::HeapData[ceil(double(i) / 2.0) - 1];
				Heap::HeapData[ceil(double(i) / 2.0) - 1] = Heap::HeapData[i];
				Heap::HeapData[i] = midnum;
			}
			else
				break;
		}
	}
	if (Heap::MaxorMin == 2)
	{
		for (int i = Heap::HeapData.size() - 1; i>0; i = ceil(double(i) / 2.0) - 1)
		{
			if (Heap::HeapData[i] <= Heap::HeapData[ceil(double(i) / 2.0) - 1])
			{
				ElemenType midnum = Heap::HeapData[ceil(double(i) / 2.0) - 1];
				Heap::HeapData[ceil(double(i) / 2.0) - 1] = Heap::HeapData[i];
				Heap::HeapData[i] = midnum;
			}
			else
				break;
		}
	}
}

vector <ElemenType> Change2Heap(vector <ElemenType> RandomElement, int root,int maxormin)
//以root为根节点，调整对应的子树为Heap,当然必须是在一定基础上调整
//复杂度为logn
{
	if (RandomElement.size() <= 1)
		return RandomElement;

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
						i = rchild;
					}
					else
					{
						ElemenType mid = RandomElement[lchild];
						RandomElement[lchild] = RandomElement[i];
						RandomElement[i] = mid;
						i = lchild;
					}
				}
				else if (RandomElement[lchild] >= RandomElement[i] && RandomElement[rchild] < RandomElement[i])
				{
					ElemenType mid = RandomElement[lchild];
					RandomElement[lchild] = RandomElement[i];
					RandomElement[i] = mid;
					i = lchild;
				}
				else if (RandomElement[rchild] >= RandomElement[i] && RandomElement[lchild] < RandomElement[i])
				{
					ElemenType mid = RandomElement[rchild];
					RandomElement[rchild] = RandomElement[i];
					RandomElement[i] = mid;
					i = rchild;
				}
			}
			else
			{
				if (RandomElement[lchild] > RandomElement[i])
				{
					ElemenType mid = RandomElement[lchild];
					RandomElement[lchild] = RandomElement[i];
					RandomElement[i] = mid;
					i = lchild;
				}
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
						i = rchild;
					}
					else
					{
						ElemenType mid = RandomElement[lchild];
						RandomElement[lchild] = RandomElement[i];
						RandomElement[i] = mid;
						i = lchild;
					}
				}
				else if (RandomElement[lchild] <= RandomElement[i] && RandomElement[rchild] > RandomElement[i])
				{
					ElemenType mid = RandomElement[lchild];
					RandomElement[lchild] = RandomElement[i];
					RandomElement[i] = mid;
					i = lchild;
				}
				else if (RandomElement[rchild] <= RandomElement[i] && RandomElement[lchild] > RandomElement[i])
				{
					ElemenType mid = RandomElement[rchild];
					RandomElement[rchild] = RandomElement[i];
					RandomElement[i] = mid;
					i = rchild;
				}
			}
			else
			{
				if (RandomElement[lchild] < RandomElement[i])
				{
					ElemenType mid = RandomElement[lchild];
					RandomElement[lchild] = RandomElement[i];
					RandomElement[i] = mid;
					i = lchild;
				}
			}
		}
	}
	return RandomElement;
}

ElemenType Heap::DeleteHeapRoot()
{
	if (Heap::IsEmptyHeap() == 1)
		return ElemenTypical;
	ElemenType returnele;
	returnele = *Heap::HeapData.begin();
	Heap::HeapData[0] = *(Heap::HeapData.end()-1);
	Heap::HeapData.pop_back();

	Heap::HeapData = Change2Heap(Heap::HeapData, 0, Heap::MaxorMin);//这就是在一定基础上调整

	return returnele;
}

void Heap:: CreateHeap(vector <ElemenType> RandomElement)
//输入为任意序列，经过堆整理后得到对应的堆序列存到HeapData中
//如果是一个一个插入，那么是nlogn的算法，但是有n的线性算法
//下边这个是n的线性算法
{
	if (RandomElement.size() <= 1)
	{
		Heap::HeapData = RandomElement;
		return;
	}

	for (int i = ceil(double((RandomElement.size() - 1) / 2.0)) - 1; i >= 0; i--)
	{
		RandomElement = Change2Heap(RandomElement, i, Heap::MaxorMin);
	}
	RandomElement = Heap::HeapData;
	return;

}