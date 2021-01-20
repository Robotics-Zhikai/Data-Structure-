#include <stdlib.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <random>
#include <time.h>
using namespace std;

class Category
{
public:
	Category(int catin) :Cat(catin) {}

	int Cat; //���
};

//template<typename Ty>
class node:public Category
{
public:

	node() :Category(0) {}
	node(int catin,vector<double> input) :Data(input), Category(catin) {}

	size_t CompType = 0; //���������Compare
	size_t readDimension()const { return Data.size(); }

	bool operator>(const node& in)
	{
		if (Compare(in, CompType) == 1)
			return 1;
		else
			return 0;
	}
	bool operator>=(const node& in)
	{
		int comp = Compare(in, CompType);
		if (comp == 1 || comp==0)
			return 1;
		else
			return 0;
	}
	bool operator<(const node& in)
	{
		if (Compare(in, CompType) == -1)
			return 1;
		else
			return 0;
	}
	bool operator<=(const node& in)
	{
		int comp = Compare(in, CompType);
		if (comp == -1 || comp == 0)
			return 1;
		else
			return 0;
	}
	bool operator==(const node& in)
	{
		if (Compare(in, CompType) == 0)
			return 1;
		else
			return 0;
	}

	double dist(node in)
	{
		if (Data.size() != in.Data.size())
			throw exception("Data.size() != in.Data.size() ������벻���ǲ�ͬά�ȵ����ݽ��м���");
		double odist = 0;
		for (size_t i = 0; i < Data.size(); i++)
			odist += pow(Data[i] - in.Data[i], 2);
		odist = pow(odist, 0.5);
		return odist;
	}

	

	vector<double> Data; // ֻ����vector<double>
	int lchild = -1;
	int rchild = -1;
	int father = -1;
private:

	int Compare(const node& node2, size_t bit) //����node2����1 С��node2����-1 ����node2����0
	{
		if (Data.size() != node2.Data.size())
			throw exception("Data.size()!=node2.Data.size()");
		if (bit >= Data.size())
			throw exception("bit>= Data.size()");
		if (CompType != node2.CompType) //ֻ����ȵ�comptype���ܱȽϴ�С
			throw exception("CompType!=node2.CompType");
		
		if (Data[bit] > node2.Data[bit])
			return 1;
		else if (Data[bit] == node2.Data[bit])
			return 0;
		else if (Data[bit] < node2.Data[bit])
			return -1;
	}
};

ostream &operator<<(ostream &output, const node &D)
{
	output << "��node���Ϊ��" << D.Cat << endl;
	cout << "��node�洢��ά����Ϊ��";
	for (size_t i = 0; i < D.Data.size(); i++)
	{
		output << D.Data[i] << " ";
	}
	cout << endl;
	output << "��node��kd���еĸ��ڵ�����Ϊ��" << D.father << endl;
	output << "��node��kd���е����ӽڵ�����Ϊ��" << D.lchild << endl;
	output << "��node��kd���е����ӽڵ�����Ϊ��" << D.rchild ;
	return output;
}

class valueindex
{
public:
	valueindex(double vain, size_t indin) :value(vain), index(indin) {}
	double value;
	size_t index;
	bool operator<(const valueindex& in )
	{
		if (value < in.value)
			return 1;
		else
			return 0;
	}
	bool operator>(const valueindex& in)
	{
		if (value > in.value)
			return 1;
		else
			return 0;
	}
	bool operator>=(const valueindex& in)
	{
		if (value >= in.value)
			return 1;
		else
			return 0;
	}
	bool operator<=(const valueindex& in)
	{
		if (value <= in.value)
			return 1;
		else
			return 0;
	}
};

class KdTree
{
public:
	KdTree(vector<node> dataflow) 
	{
		root = makeListAsKdTree(dataflow, 0, dataflow.size() - 1, 0, dataflow[0].readDimension());
		KdTreeDataflow = dataflow;
	}

	vector<valueindex> Search_NearkIndex(unsigned int k,node& input)const
		//�����������������k���ڵ������
	{
		if (k<=0 || k>KdTreeDataflow.size())
			throw exception("k<=0 || k>KdTreeDataflow.size()");
		vector<valueindex> recordNearDist; //�ñ�׼������ȼ����д��������k���ڵ�ľ��� ���ص��Ǿ����KdTreeDataflow������
		vector<bool> recorded(KdTreeDataflow.size(),0);
		Search_node(recorded,k,recordNearDist,root, input, 0);

		return recordNearDist;
	}
	node readnode(size_t index)const
	{
		return KdTreeDataflow[index];
	}
	vector<node> readKdTreeDataflow()const
	{
		return KdTreeDataflow;
	}
private:
	vector<node> KdTreeDataflow;
	int root;//����kdtree�ĸ��ڵ���

	template<typename Tytopk>
	void push_topk(vector<Tytopk>& recorddist, Tytopk disttmp,unsigned int k)const
	{
		if (recorddist.size() < k)
		{
			recorddist.push_back(disttmp);
			push_heap(recorddist.begin(), recorddist.end());
		}
		else
		{
			if (disttmp < recorddist[0])
			{
				pop_heap(recorddist.begin(), recorddist.end());
				recorddist.pop_back();
				recorddist.push_back(disttmp);
				push_heap(recorddist.begin(), recorddist.end());
			}
		}
	}

	void Search_node(vector<bool>& recorded,unsigned int k,vector<valueindex>& recorddist,int CurrentIndex, node& input,int depth)const
	{
		static int flagDownTree = 1;
		if (CurrentIndex == -1)
			return;
		input.CompType = depth%input.readDimension();

		if (input <= KdTreeDataflow[CurrentIndex])
		{
			Search_node(recorded,k,recorddist,KdTreeDataflow[CurrentIndex].lchild, input, depth + 1);
			if (flagDownTree == 0)
			{
				auto disttmp = input.dist(KdTreeDataflow[CurrentIndex]);
				recorded[CurrentIndex] = 1;
				push_topk<valueindex>(recorddist, valueindex(disttmp, CurrentIndex), k);

				input.CompType = depth%input.readDimension();
				double distabs = abs(input.Data[input.CompType] - KdTreeDataflow[CurrentIndex].Data[input.CompType]);
				if (distabs > recorddist[0].value)
					return;
				else
					flagDownTree = 1;
				
			}
			Search_node(recorded, k, recorddist, KdTreeDataflow[CurrentIndex].rchild, input, depth + 1);
		}
		else
		{
			Search_node(recorded,k,recorddist,KdTreeDataflow[CurrentIndex].rchild, input, depth + 1);
			if (flagDownTree == 0)
			{
				auto disttmp = input.dist(KdTreeDataflow[CurrentIndex]);
				recorded[CurrentIndex] = 1;
				push_topk<valueindex>(recorddist, valueindex(disttmp, CurrentIndex), k);

				input.CompType = depth%input.readDimension();
				double distabs = abs(input.Data[input.CompType] - KdTreeDataflow[CurrentIndex].Data[input.CompType]);
				if (distabs > recorddist[0].value)
					return;
				else
					flagDownTree = 1;
				
			}
			Search_node(recorded, k, recorddist, KdTreeDataflow[CurrentIndex].lchild, input, depth + 1);
		}

		flagDownTree = 0;
		//������͵���Ҷ�ӽڵ���
		if (recorded[CurrentIndex] == 0)
		{
			auto disttmp = input.dist(KdTreeDataflow[CurrentIndex]);
			recorded[CurrentIndex] = 1;
			push_topk<valueindex>(recorddist, valueindex(disttmp, CurrentIndex), k);
		}
	}

	//vector<node<Ty>>::iterator sad;
	//typedef _Vector_iterator<_Vector_val<_Simple_types<node<Ty> > > > nodeiterator;
	int makeListAsKdTree(vector<node>& List,int left,int right,unsigned int depth,const size_t & dimension,int l_r=-1)const
		//��û��KdTree��ϵ�����Ա���֯��kdtree,dimensionΪÿ�����ݵ�ά��
	{
		if (right<left || left>right)
		{
			return -1;
		}

		size_t sorttype = depth%dimension;
		for (auto i = left; i <= right; i++)
			List[i].CompType = sorttype;
		sort(List.begin() + left, List.begin() + right+1);//ǰ�պ�
		//һ��Ҫ��ס��1�������©��һ��С��û���������Kd������bug����������k�������������� �����bug����Щʱ��

		auto midnum = floor((left+right)/2);
		size_t currentNode = midnum;
		if (depth == 0)
			List[midnum].father = -1;
		else
		{
			if (l_r == 0)
				List[midnum].father = right + 1;
			else if (l_r == 1)
				List[midnum].father = left - 1;
			else
				throw exception("�������");
		}
			
		List[midnum].lchild = makeListAsKdTree(List,left,midnum-1, depth + 1, dimension,0);
		List[midnum].rchild = makeListAsKdTree(List,midnum+1,right, depth + 1, dimension,1);

		return currentNode;
	}
};




vector<node> GenerateGaussianData(int Category,vector<double> mean, vector<double> std,unsigned int num)
{
	default_random_engine e;
	vector<node>  output;
	for (unsigned int i = 0; i < num; i++)
	{
		vector<double> current;
		for (size_t dim = 0; dim < mean.size(); dim++)
		{
			normal_distribution<double> n(mean[dim], std[dim]);
			current.push_back(n(e));
		}
		output.push_back(node(Category, current));
	}
	return output;
}


template<typename Ty>
void addvector(vector<Ty>& A,const vector<Ty>& B)
{
	for (size_t i = 0; i < B.size(); i++)
	{
		A.push_back(B[i]);
	}
}

vector<double> k_nearest_neighbors_Violence_search(vector<node> traindata, node testnode, unsigned int k)
{
	vector<double> dist;
	for (size_t i = 0; i < traindata.size(); i++)
	{
		dist.push_back(traindata[i].dist(testnode));
	}
	sort(dist.begin(), dist.end());
	vector<double> result(k);
	for (int i = 0; i < k; i++)
		result[i] = dist[i];
	return result;
}

int DecideCategory(const vector<node>& NearkNodes)//����k�ٽ�������ͶƱ���������Ӷ������õ����
{
	vector<int> cats;
	for (size_t i = 0; i < NearkNodes.size(); i++)
		cats.push_back(NearkNodes[i].Cat);
	sort(cats.begin(), cats.end());
	
	if (!cats.empty())
	{
		int current = cats[0];
		vector<int> countCat;
		vector<int> UniqueCat;
		UniqueCat.push_back(current);
		countCat.push_back(1);

		int catsnum = 0;
		for (int i = 1; i < cats.size(); i++)
		{
			if (cats[i] == current)
			{
				countCat[catsnum] = countCat[catsnum] + 1;
			}
			else
			{
				current = cats[i];
				UniqueCat.push_back(current);
				catsnum++;
				countCat.push_back(1);
			}
		}
		if (UniqueCat.size() != countCat.size())
			throw exception("����UniqueCat.size() != countCat.size()");

		int maxcountCat = *max_element(countCat.begin(), countCat.end());
		for (int i = 0; i < countCat.size(); i++)
		{
			if (countCat[i] == maxcountCat)
				return UniqueCat[i];
		}
	}
	else
		throw exception("DecideCategory�޷��ж�"); // ֻҪk��Ϊ0���Ͷ������ж�
}

vector<double> k_nearest_neighbors_KdTree(const KdTree &trainDataKdtree,vector<node> traindata, node testnode, unsigned int k)
{
	cout << "������node�������£�" << endl;
	cout << testnode << endl;
	cout << k << "����node���£�" << endl;
	auto searchresult = trainDataKdtree.Search_NearkIndex(k, testnode);
	vector<node> NearkNode;
	vector<double> result(k);
	for (int j = 0; j < searchresult.size(); j++)
	{
		node tmpnode = trainDataKdtree.readnode(searchresult[j].index);
		NearkNode.push_back(tmpnode);
		//cout << tmpnode << endl;
		//cout << "��node�������node�ľ���Ϊ" << testnode.dist(tmpnode) << endl;
		//cout << endl;
		result[j] = testnode.dist(tmpnode);
	}

	cout << "���յ�KNN�ж�����ǣ�" << DecideCategory(NearkNode) << endl;

	sort(result.begin(),result.end());
	return result;
}


void k_nearest_neighbors(vector<node> traindata, vector<node> testdata,unsigned int k)
{
	vector<node> dataflow;
	dataflow = traindata;
	KdTree KdTreetest(dataflow);
	dataflow = KdTreetest.readKdTreeDataflow();

	clock_t startKdTree;
	clock_t endKdTree;
	clock_t startViolence_search;
	clock_t endViolence_search;
	double KdTreeT = 0;
	double Violence_searchT = 0;
	for (size_t i = 0; i < testdata.size(); i++)
	{
		startKdTree = clock();
		auto kddist = k_nearest_neighbors_KdTree(KdTreetest, dataflow, testdata[i], k);
		endKdTree = clock();
		KdTreeT += (double)(endKdTree - startKdTree) / CLOCKS_PER_SEC;

		startViolence_search = clock();
		auto violencedist = k_nearest_neighbors_Violence_search(dataflow, testdata[i], k);
		endViolence_search = clock();
		Violence_searchT+= (double)(endViolence_search - startViolence_search) / CLOCKS_PER_SEC;

		vector<double> minus;
		for (size_t j = 0; j < kddist.size(); j++)
		{
			minus.push_back(abs(kddist[j] - violencedist[j]));
			//cout << minus[j] << endl;
		}
		//cout << *max_element(minus.begin(),minus.end()) <<" "<< *min_element(minus.begin(), minus.end()) << endl;
		if (*max_element(minus.begin(), minus.end()) > 0)
			throw exception("KdTree������");

		cout << "KdTreeT:" << KdTreeT << " " << "Violence_searchT:" << Violence_searchT << endl;
	}
}



int main()
{
	try
	{
		vector<double> sdasdas{ 3,21,5,1,2,7,5,8,3 };
		std::sort(sdasdas.begin() , sdasdas.begin() + 3);
		//train set
		vector<node> Catgery1data = GenerateGaussianData(1, vector<double>{20, 3, 4, 5}, vector<double> {2, 3, 2, 1}, 1000000);
		vector<node> Catgery2data = GenerateGaussianData(2, vector<double>{2.4, 3.2, 4.5, 8}, vector<double> {2, 3, 2, 1}, 1000000);
		vector<node> Catgery3data = GenerateGaussianData(3, vector<double>{1, 5, 7, 10}, vector<double> {2, 3, 2, 1}, 1000000); //300000������ KDtree�������ٶ����� �Ǳ�������Ч�ʵ�����
		vector<node> traindata;
		addvector<node>(traindata, Catgery1data);
		addvector<node>(traindata, Catgery2data);
		addvector<node>(traindata, Catgery3data);
		//test set
		vector<node> testdata = GenerateGaussianData(-1, vector<double>{15, 3.73, 5.17, 7.67}, vector<double> {20, 34, 22, 11}, 100);
		
		unsigned int K = 100;
		k_nearest_neighbors(traindata, testdata, K);
		//tmp.push(node<double>(vector<double>{ 2, 3, 1 }));

		vector<node> dataflow;

		dataflow.push_back(node(0, vector<double>{ 2, 3, 1 }));
		dataflow.push_back(node(0, vector<double>{ 3, 3, 2 }));
		dataflow.push_back(node(0, vector<double>{ 5, 4, 6 }));
		dataflow.push_back(node(0, vector<double>{ 9, 6, 7 }));
		dataflow.push_back(node(0, vector<double>{ 4, 7, 2 }));
		dataflow.push_back(node(0, vector<double>{ 4, 8, 5 }));
		dataflow.push_back(node(0, vector<double>{ 8, 1, 3 }));
		dataflow.push_back(node(0, vector<double>{ 7, 2, 9 }));
		dataflow.push_back(node(0, vector<double>{ 2.1, 3.1, 1.1 }));


		KdTree KdTreetest(dataflow);
		KdTreetest.Search_NearkIndex(3, node(0, vector<double>{2, 3, 1}));
	}
	catch (exception d)
	{
		cout << d.what() << endl;
	}
	system("pause");
}