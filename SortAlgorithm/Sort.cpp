#include "Sort.h"

vector<double> RandomData::GenerateRandomData(int pointsNum, double RangeXmin, double RangeXmax)
//generate pointsNum random points in [RangeXmin,RangeXmax,RangeYmin,RangeYmax]
{

	vector<double> Data;
	srand((int)time(0));  // 产生随机种子  把0换成NULL也行
	for (int i = 0; i < pointsNum; i++)
	{
		double a = RangeXmin;
		double b = RangeXmax;
		double temp = a + (rand() / double(RAND_MAX))*(b - a);
		Data.push_back(temp);
	}
	return Data;
}

int RandomData::CheckSorted(vector <double> Data)
//测试是否排好顺序
{
	if (Data.size() <= 2)
		return 1;
	double lastcompare = Data[0] - Data[1];
	int i;
	for (i = 1; i < Data.size()-1; i++)
	{
		double nowcompare = Data[i] - Data[i + 1];
		if (lastcompare < 0)
			lastcompare = -1;
		else if (lastcompare > 0)
			lastcompare = 1;

		if (nowcompare < 0)
			nowcompare = -1;
		else if (nowcompare > 0)
			nowcompare = 1;

		if (lastcompare != 0 && nowcompare != 0)
		{
			if (lastcompare != nowcompare)
				break;
		}
		if (nowcompare != 0)
			lastcompare = nowcompare;
	}
	if (i >= Data.size() - 1)
		return 1;
	else
		return 0;
}

void RandomData::PrintData(vector<double> Data)
{
	for (int i = 0; i < Data.size(); i++)
	{
		cout << Data[i] << " ";
	}
	cout << endl;
}
vector<double> BubbleSort(vector<double> Data)
//从小到大排序
//最好O(n) 最坏O(n^2)
{
	for (int i = 1; i < Data.size(); i++)
	{
		int flag = 0;
		for (int j = 0; j < Data.size()-i; j++)
		{
			if (Data[j] > Data[j + 1])
			{
				double temp = Data[j];
				Data[j] = Data[j + 1];
				Data[j + 1] = temp;
				flag = 1;
			}
		}
		if (flag == 0)
			break;//说明全程无交换
	}
	return Data;
}

vector <double> InsertionSort(vector<double> Data)
//插入排序，类比打扑克摸牌整理
//O(n^2)
{
	if (Data.size() <= 1)
		return Data;
	RandomData test;
	vector <double> Sorted;
	for (int i = 0; i < Data.size(); i++)
	{

		if (Sorted.empty()==1)
			Sorted.push_back(Data[i]);
		else
		{
			int flag = 0;
			for (int j = Sorted.size()-1; j >= 0; j--)
			{
				if (j >= 1)
				{
					flag = 1;
					if (Data[i] < Sorted[j] && Data[i]>=Sorted[j - 1])
					{
						Sorted.insert(Sorted.begin() + j, Data[i]);
						break;
					}
					if (Data[i] >= Sorted[j])
					{
						Sorted.push_back(Data[i]);
						break;
					}
					
				}
				else
				{
					if (flag == 1)
						Sorted.insert(Sorted.begin(), Data[i]);
					else
					{
						if (Data[i] >= Sorted[j])
							Sorted.push_back(Data[i]);
						else
							Sorted.insert(Sorted.begin(), Data[i]);
					}
					break;
				}
				
			}
		}
	}
	return Sorted;
}

vector <double> ShellSort(vector<double> Data)
//猜想 平均复杂度为O(n^(7/6)) 最坏复杂度为O(n^(4/3))
//思想是尽量远的消除逆序对，一次消除好几个逆序对
{
	if (Data.size() <= 1)
		return Data;
	vector <int> Sedgewick; //增量序列
	int a, b;
	for (int i = 1; i < Data.size(); i++)
	{
		a = 9 * pow(4 , i) - 9 * pow(2 , i) + 1;
		b = pow(4 , i) - 3 * pow(2 , i) + 1;
		if (a>0)
			Sedgewick.push_back(a);
		if (b>0)
			Sedgewick.push_back(b);
		if (a > Data.size() && b > Data.size())
			break;
	}
	Sedgewick.push_back(1);
	sort(Sedgewick.begin(), Sedgewick.end());

	int index = 0;
	for (int i = 0; i < Sedgewick.size(); i++)
	{
		if (Sedgewick[i] >= Data.size())
		{
			index = i - 1;
			break;
		}
	}

	for (int i = index; i >= 0; i--)
	{
		int Interval = Sedgewick[i];
		for (int j = 0;j<Interval;j++)
		{
			vector <double> subdata;
			vector <int> subdataindex;
			int index_j = j;
			while (index_j < Data.size())
			{
				subdata.push_back(Data[index_j]);
				subdataindex.push_back(index_j);
				index_j = index_j + Interval;
			}
			subdata = InsertionSort(subdata);
			for (int k = 0; k < subdata.size(); k++)
				Data[subdataindex[k]] = subdata[k];
		}
	}
	return Data;
}

vector <ElemenType> Change2Heap(vector <ElemenType> RandomElement, int root, int maxormin)
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

vector <double> HeapSortfaster(vector<double> Data)
//堆排序
//复杂度为O(nlogn)
//平均比较次数是2NlogN-O(NloglogN) 但实际效果不如用Sedgewick增量序列的希尔排序
{
	if (Data.size() <= 1)
		return Data;

	HeapOperate Ope(2,Data.size());
	Ope.CreateHeap(Data);
	vector <double> result;
	while (Data.size()!=0)
	{
		result.push_back(Ope.DeleteHeapRoot(Data));
	}
	return result;
}

vector <double> HeapSortslow(vector<double> Data)
//堆排序
//复杂度为O(nlogn)
//平均比较次数是2NlogN-O(NloglogN) 但实际效果不如用Sedgewick增量序列的希尔排序
{
	if (Data.size() <= 1)
		return Data;

	HeapOperate Ope(2, Data.size());
	vector <double> data1;
	for (int i = 0; i < Data.size(); i++)
	{
		Ope.InsertHeapElement(data1, Data[i]);
	}
	
	vector <double> result;
	while (data1.size() != 0)
	{
		result.push_back(Ope.DeleteHeapRoot(data1));
	}
	return result;
}

void TwoSplitMerge(vector<double> & Data, vector<double> & tmp, int split1Left, int split1Right, int split2Left, int split2Right)
{
	//if (Left == Right)
	//	return;

	//int split1Left = Left;
	//int split1Right = Left + ceil(double((Right - Left + 1) / 2.0)) - 1;
	//int split2Left = split1Right + 1;
	//int split2Right = Right;

	int split1 = split1Left;
	int split2 = split2Left;
	int tmpzz = 0;
	while (split1 <= split1Right && split2 <= split2Right)
	{
		if (Data[split2] < Data[split1])
		{
			tmp[split1Left + tmpzz] = Data[split2];
			split2++;
			tmpzz++;
		}
		else if (Data[split2] > Data[split1])
		{
			tmp[split1Left + tmpzz] = Data[split1];
			split1++;
			tmpzz++;
		}
		else
		{
			tmp[split1Left + tmpzz] = Data[split1];
			split1++;
			tmpzz++;
			tmp[split1Left + tmpzz] = Data[split2];
			split2++;
			tmpzz++;
		}
	}
	while (split1 <= split1Right)
	{
		tmp[split1Left + tmpzz] = Data[split1];
		tmpzz++;
		split1++;
	}
	while (split2 <= split2Right)
	{
		tmp[split1Left + tmpzz] = Data[split2];
		tmpzz++;
		split2++;
	}
	tmpzz--;
	while (tmpzz >= 0) //需要把融合后的一段序列返回到Data中
	{
		Data[split1Left + tmpzz] = tmp[split1Left + tmpzz];
		tmpzz--;
	}
}

void Merge(vector <double> & Data, vector <double> & tmp,int Left, int Right)
//都是引用，不开辟很大的空间
{
	if (Right - Left == 1)
	{
		if (Data[Right] < Data[Left])
		{
			double mid = Data[Right];
			Data[Right] = Data[Left];
			Data[Left] = mid;
		}
		return;
	}
	else if (Right == Left)
		return;
	int split1Left = Left;
	int split1Right = Left + ceil(double((Right- Left + 1) / 2.0)) - 1;
	int split2Left = split1Right + 1;
	int split2Right = Right;

	Merge(Data, tmp, Left, split1Right);
	Merge(Data, tmp, split2Left, split2Right);
	
	TwoSplitMerge(Data, tmp, split1Left, split1Right, split2Left, split2Right);
	return;
}

vector <double> MergeSortRecur(vector <double> Data)
//递归的归并排序
//归并排序
//排序复杂度nlogn
{
	if (Data.size() <= 1)
		return Data;
	vector <double> tmp = Data;
	Merge(Data, tmp, 0, Data.size() - 1);
	return Data;
}

vector <int> Splitnum(int num)
//将任何数分解为2的整数次方
{
	vector <int> result;
	if (num <= 0)
		return result;
	int sum = 0;
	int numtmp = num;
	while (numtmp>0)
	{
		int tmp = pow(2, floor(log2(numtmp)));
		result.push_back(tmp);
		sum = sum + tmp;
		numtmp = num - sum;
	}
	return result;
}

//实际上根本不用注释掉的这个这么复杂，只需要如保留下来的代码一样，每次都把多余的融合到最后一个序列中即可。
//void SubSplitMergeSort(vector <double> & Data, vector <double> & tmp ,int subLeft, int subRight)
////将位于Left 和 Right中间的子序列用归并排序
////subRight- subLeft +1 必须保证是2的整数次幂
//{
//	int interval = 2;
//
//	while (1)
//	{
//		int i;
//		for (i = subLeft;i<subRight- subLeft +1; i = i + interval)
//		{
//			int Left = i;
//			int Right = i + interval - 1;
//			int split1Left = Left;
//			int split1Right = Left + ceil(double((Right - Left + 1) / 2.0)) - 1;
//			int split2Left = split1Right + 1;
//			int split2Right = Right;
//			TwoSplitMerge(Data, tmp, split1Left, split1Right, split2Left, split2Right);
//		}
//		interval = interval * 2;
//		if (interval>subRight - subLeft + 1)
//			break;
//	}
//}
//vector <double> MergeSortNotRecur(vector <double> Data)
////非递归的归并排序
////nlogn
//{
//	vector <double> tmp = Data;
//	vector <int> splitnum;
//	splitnum = Splitnum(Data.size() );//将任意个数的待排序列转化为2的整数次幂构成的序列，序列和为待排序列
//
//	int sum = 0;
//	for (int i = 0; i < splitnum.size(); i++)
//	{
//		SubSplitMergeSort(Data, tmp, sum, sum + splitnum[i] - 1);
//		sum += splitnum[i];
//	}
//
//	vector<int> newsplitnum = Splitnum(splitnum.size());
//	for (int i = 0; i < newsplitnum.size(); i++)
//	{
//
//	}
//
//	
//
//	return Data;
//}

vector <double> MergeSortNotRecur(vector <double> Data)
{
	if (Data.size() <= 1)
		return Data;
	vector <double> tmp = Data;
	int interval = 2;
	int Left;
	int Right;
	int split1Left;
	int split1Right;
	int split2Left;
	int split2Right;
	int i;
	while (1)
	{
		for (i = 0; i<Data.size(); )
		{
			Left = i;
			Right = i + interval - 1;
			if (Right >= Data.size())
				break;
			split1Left = Left;
			split1Right = Left + ceil(double((Right - Left + 1) / 2.0)) - 1;
			split2Left = split1Right + 1;
			split2Right = Right;
			TwoSplitMerge(Data, tmp, split1Left, split1Right, split2Left, split2Right);
			i = Right + 1;
		}
		if (i < Data.size())
		{
			TwoSplitMerge(Data, tmp, i- interval, i-1, i, Data.size()-1);
		}
		interval = interval * 2;
		if (interval>Data.size())
			break;
	}
	return Data;
}

