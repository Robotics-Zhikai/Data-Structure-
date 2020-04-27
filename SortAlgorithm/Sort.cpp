#include "Sort.h"

vector<double> RandomData::GenerateRandomData(int pointsNum, double RangeXmin, double RangeXmax)
//generate pointsNum random points in [RangeXmin,RangeXmax,RangeYmin,RangeYmax]
{

	vector<double> Data;
	srand((int)time(0));  // �����������  ��0����NULLҲ��
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
//�����Ƿ��ź�˳��
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
//��С��������
//���O(n) �O(n^2)
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
			break;//˵��ȫ���޽���
	}
	return Data;
}

vector <double> InsertionSort(vector<double> Data,int Left,int Right)
//����������ȴ��˿���������
//O(n^2)
{
	if (Data.size() <= 1)
		return Data;
	RandomData test;
	vector <double> Sorted;
	for (int i = Left; i < Right + 1; i++)
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
	int indexnum = 0;
	for (int i = Left; i < Right + 1; i++)
	{
		Data[i] = Sorted[indexnum];
		indexnum++;
	}
	return Data;
}

vector <double> ShellSort(vector<double> Data)
//���� ƽ�����Ӷ�ΪO(n^(7/6)) ����Ӷ�ΪO(n^(4/3))
//˼���Ǿ���Զ����������ԣ�һ�������ü��������
{
	if (Data.size() <= 1)
		return Data;
	vector <int> Sedgewick; //��������
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
			subdata = InsertionSort(subdata,0,subdata.size()-1);
			for (int k = 0; k < subdata.size(); k++)
				Data[subdataindex[k]] = subdata[k];
		}
	}
	return Data;
}

vector <ElemenType> Change2Heap(vector <ElemenType> RandomElement, int root, int maxormin)
//��rootΪ���ڵ㣬������Ӧ������ΪHeap,��Ȼ��������һ�������ϵ���
//���Ӷ�Ϊlogn
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
//������
//���Ӷ�ΪO(nlogn)
//ƽ���Ƚϴ�����2NlogN-O(NloglogN) ��ʵ��Ч��������Sedgewick�������е�ϣ������
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
//������
//���Ӷ�ΪO(nlogn)
//ƽ���Ƚϴ�����2NlogN-O(NloglogN) ��ʵ��Ч��������Sedgewick�������е�ϣ������
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
	while (tmpzz >= 0) //��Ҫ���ںϺ��һ�����з��ص�Data��
	{
		Data[split1Left + tmpzz] = tmp[split1Left + tmpzz];
		tmpzz--;
	}
}

void Merge(vector <double> & Data, vector <double> & tmp,int Left, int Right)
//�������ã������ٺܴ�Ŀռ�
//tmp �������洢�м����е�
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

vector <double> MergeSortRecur(vector <double> Data,int Left,int Right)
//�ݹ�Ĺ鲢����
//�鲢����
//�����Ӷ�nlogn
{
	if (Data.size() <= 1)
		return Data;
	vector <double> tmp = Data;
	Merge(Data, tmp, Left, Right);
	return Data;
}

vector <int> Splitnum(int num)
//���κ����ֽ�Ϊ2�������η�
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

//ʵ���ϸ�������ע�͵��������ô���ӣ�ֻ��Ҫ�籣�������Ĵ���һ����ÿ�ζ��Ѷ�����ںϵ����һ�������м��ɡ�
//void SubSplitMergeSort(vector <double> & Data, vector <double> & tmp ,int subLeft, int subRight)
////��λ��Left �� Right�м���������ù鲢����
////subRight- subLeft +1 ���뱣֤��2����������
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
////�ǵݹ�Ĺ鲢����
////nlogn
//{
//	vector <double> tmp = Data;
//	vector <int> splitnum;
//	splitnum = Splitnum(Data.size() );//����������Ĵ�������ת��Ϊ2���������ݹ��ɵ����У����к�Ϊ��������
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

vector <double> MergeSortNotRecur(vector <double> Data,int L,int R)
{
	if (R-L+1 <= 1)
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
		for (i = L; i<R+1; )
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
		if (i < R+1)
		{
			TwoSplitMerge(Data, tmp, i- interval, i-1, i, R);
		}
		interval = interval * 2;
		if (interval>R-L+1)
			break;
	}
	return Data;
}

int Rec = 0;
vector <double> Recordmid;
int MediumRec(int Left, int Right,int splitnum)
{
	Rec++;
	if (Rec == splitnum)
	{
		Rec--;
		Recordmid.push_back(ceil(double((Left + Right) / 2.0)));
		Recordmid.push_back(Left);
		Recordmid.push_back(Right);
		return ceil(double((Left + Right) / 2.0));
	}
	MediumRec(Left, ceil(double((Left + Right) / 2.0)), splitnum);
	MediumRec(ceil(double((Left + Right) / 2.0)), Right, splitnum);
	Rec--;
}

void Mediann(vector<double> & Data, int Left, int Right,int n)
//��Left �� Right �ֳ�n-1�ݣ�n������
{
	vector <double> Index;
	Rec = 0;
	Recordmid.clear();
	MediumRec(Left, Right, log2(n-1));
	Index = Recordmid;
	Index = InsertionSort(Index,0,Index.size()-1);
	auto i = Index.begin()+1;
	while (i != Index.end()) //ȥ���ظ�Ԫ��
	{
		if (*i == *(i - 1))
		{
			i = Index.erase(i);
		}
		else
			i++;
	}
	vector <double> value;
	for (int i = 0; i < Index.size(); i++)
		value.push_back(Data[Index[i]]);
	value = InsertionSort(value, 0, value.size() - 1);
	for (int i = 0; i < Index.size(); i++)
		Data[Index[i]] = value[i];

	double tmpmidd = Data[Index[(Index.size()-1)/2]];
	Data[Index[(Index.size() - 1) / 2]] = Data[Right - 1];
	Data[Right - 1] = tmpmidd;
}

void Median3(vector<double> & Data, int Left, int Right)
{
	int mid = ceil(double((Left + Right) / 2.0));
	if (Data[Left] > Data[mid])
	{
		double tmpmid = Data[Left];
		Data[Left] = Data[mid];
		Data[mid] = tmpmid;
	}
	if (Data[Right] < Data[mid])
	{
		double tmpmid = Data[Right];
		Data[Right] = Data[mid];
		Data[mid] = tmpmid;
	}
	if (Data[Left] > Data[mid])
	{
		double tmpmid = Data[Left];
		Data[Left] = Data[mid];
		Data[mid] = tmpmid;
	}
	if (Right - Left + 1 >= 3)
	{
		double tmpmidd = Data[mid];
		Data[mid] = Data[Right - 1];
		Data[Right - 1] = tmpmidd; 
	}
	return;
}

void Quick_Sort(vector <double> & Data, int Left, int Right,int cutoff,int cishu)
//QuickSort�ĵݹ�
//��ʱ��������ֵΪ10
{
	if (Right - Left + 1 < cutoff)
		Data = MergeSortRecur(Data, Left, Right);
	else
	{
		//Median3(Data, Left, Right);//����൱�ڲ�����������һ������ĵ��в�������������ÿ�ξ���
		Mediann(Data, Left, Right, pow(2 , cishu) + 1); //��������㷺�Ĳ������������ϱߵ��������
		int less = Left + 1;
		int more = Right - 2;
		while (1)
		{
			if (less <= more)
//����ط����׳��� ����ѵȺ�ȥ�˵Ļ�����less==moreʱ�����˳��ˣ�û���ж�lessλ�ô���Right-1λ�õ���Դ�С��break��
//����ɸ���ֵ�ŵ�λ�ÿ��ܲ��ԡ�
			{
				while (Data[less] < Data[Right - 1])
					less++;
				while (Data[more] > Data[Right - 1])
					more--;
			}
			if (less>more)
				break;
			double tmpmid = Data[less];
			Data[less] = Data[more];
			Data[more] = tmpmid;
			less++;
			more--;
		}
		double tmpmid1 = Data[less];
		Data[less] = Data[Right - 1];
		Data[Right - 1] = tmpmid1;
		Quick_Sort(Data, Left, less - 1, cutoff, cishu);
		Quick_Sort(Data, less + 1, Right, cutoff, cishu);
	}
}

vector <double> QuickSort(vector <double> Data,int Left,int Right,int Cutoff,int cishu)
//Cutoff ���������������ֵ���������С��ģ�ݹ����Ĵ������Cutoff>0
//cishu �ǲ������������ĸ�����cishu>=1
{
	Quick_Sort(Data, Left, Right, Cutoff, cishu);
	return Data;
}