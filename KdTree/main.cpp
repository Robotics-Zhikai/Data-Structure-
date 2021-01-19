#include <stdlib.h>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;




template<typename Ty>
class node
{
public:

	node() = default;
	node(vector<Ty> input) :Data(input) {}

	size_t sortType = 0; //标记是哪种Compare
	size_t readDimension()const { return Data.size(); }

	bool operator>(node<Ty> in)
	{
		if (Compare(in, sortType) == 1)
			return 1;
		else
			return 0;
	}
	bool operator>=(node<Ty> in)
	{
		int comp = Compare(in, sortType);
		if (comp == 1 || comp==0)
			return 1;
		else
			return 0;
	}
	bool operator<(node<Ty> in)
	{
		if (Compare(in, sortType) == -1)
			return 1;
		else
			return 0;
	}
	bool operator<=(node<Ty> in)
	{
		int comp = Compare(in, sortType);
		if (comp == -1 || comp == 0)
			return 1;
		else
			return 0;
	}
	bool operator==(node<Ty> in)
	{
		if (Compare(in, sortType) == 0)
			return 1;
		else
			return 0;
	}

	vector<Ty> Data;
	int lchild = -1;
	int rchild = -1;
	int father = -1;
private:

	int Compare(node<Ty> node2, size_t bit) //大于node2返回1 小于node2返回-1 等于node2返回0
	{
		if (Data.size() != node2.Data.size())
			throw exception("Data.size()!=node2.Data.size()");
		if (bit >= Data.size())
			throw exception("bit>= Data.size()");
		if (Data[bit] > node2.Data[bit])
			return 1;
		else if (Data[bit] == node2.Data[bit])
			return 0;
		else if (Data[bit] < node2.Data[bit])
			return -1;
	}
};

template<typename Ty>
class KdTree
{
public:
	KdTree(vector<node<Ty>> dataflow)
	{
		makeListAsKdTree(dataflow, 0, dataflow.size() - 1, 0, dataflow[0].readDimension());
		KdTreeDataflow = dataflow;
	}

private:
	vector<node<Ty>> KdTreeDataflow;

	//vector<node<Ty>>::iterator sad;
	//typedef _Vector_iterator<_Vector_val<_Simple_types<node<Ty> > > > nodeiterator;
	int makeListAsKdTree(vector<node<Ty>>& List,int left,int right,unsigned int depth,const size_t & dimension,int l_r=-1)
		//将没有KdTree关系的线性表组织成kdtree,dimension为每个数据的维度
	{
		if (right<left || left>right)
		{
			return -1;
		}

		size_t sorttype = depth%dimension;
		for (auto i = left; i <= right; i++)
			List[i].sortType = sorttype;
		sort(List.begin() + left, List.begin() + right);

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
				throw exception("程序出错");
		}
			
		List[midnum].lchild = makeListAsKdTree(List,left,midnum-1, depth + 1, dimension,0);
		List[midnum].rchild = makeListAsKdTree(List,midnum+1,right, depth + 1, dimension,1);

		return currentNode;
	}
};


int main()
{
	try
	{
		vector<node<double>> dataflow;
		dataflow.push_back(vector<double>{ 2, 3, 1 });
		dataflow.push_back(vector<double>{ 3, 3, 2 });
		dataflow.push_back(vector<double>{ 5, 4, 6 });
		dataflow.push_back(vector<double>{ 9, 6, 7 });
		dataflow.push_back(vector<double>{ 4, 7, 2 });
		dataflow.push_back(vector<double>{ 4, 8, 5 });
		dataflow.push_back(vector<double>{ 8, 1, 3 });
		dataflow.push_back(vector<double>{ 7, 2, 9 });

		vector<node<double>>::iterator ss = dataflow.begin();
		
		KdTree<double> tmp1(dataflow);
	}
	catch (exception d)
	{
		cout << d.what() << endl;
	}
	
}