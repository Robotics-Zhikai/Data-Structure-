#include "Graph.h"

GraphAdjMat RandomCreateGraphInAdjmat(int NumOfNodes,float RangeXmin, float RangeXmax, float RangeYmin, float RangeYmax)
//�������ͼ�����ͼ�ı� �������ڽӾ������ʽ
{
	GraphAdjMat result;
	result.NodesInfo = GenerateRandomPoint(NumOfNodes, RangeXmin, RangeXmax, RangeYmin, RangeYmax);
	//srand((int)time(0));  // �����������  ��0����NULLҲ��
	srand(0);

	for (int i = 0; i < result.NodesInfo.size(); i++)
	{
		vector <float> tmp;
		result.GraphInfo.push_back(tmp);
		for (int j = 0; j < result.NodesInfo.size(); j++)
		{
			if (j != i)
			{
				float a = 0;
				float b = 1;
				float randomnum = a + (rand() / double(RAND_MAX))*(b - a);
				if (randomnum < 0.98)
					randomnum = 0;
				else
					randomnum = 1;
				result.GraphInfo[i].push_back(randomnum);
			}
			else
				result.GraphInfo[i].push_back(0);
		}
	}
	return result;
}
//

void GraphAdjMat::MapVisualize(float NodeSize, float LineWeight)
//���������һ��������
//O(n^2)
{
	AddBufferPoints(GraphAdjMat::NodesInfo, NodeSize);
	for (int i = 0; i < GraphAdjMat::GraphInfo.size(); i++)
	{
		for (int j = 0; j < GraphAdjMat::GraphInfo[i].size(); j++)
		{
			if (GraphAdjMat::GraphInfo[i][j] != BrokenEdge)
			{
				vector <Point> tmp;
				tmp.push_back(GraphAdjMat::NodesInfo[i]);
				tmp.push_back(GraphAdjMat::NodesInfo[j]);//iָ��j
				AddBufferLinesArrows(tmp, LineWeight);
			}
		}
	}
}

void GraphAdjMat::SearchVisualize(vector <GraphNode> sequence, float SquareSize)
{
	AddBufferHollowSquare(sequence, SquareSize);
}

void GraphAdjMat::InsertNode(GraphNode node)
{
	GraphAdjMat::NodesInfo.push_back(node);
}

void GraphAdjMat::UpdateEdge(GraphNode node1, GraphNode node2, float value)
//�������ڵ���Ȩֵ�����԰ѱ����еı�Ū��brokenedge Ҳ���԰ѱ�����brokenedge�ı�Ū����Ȩֵ
//���������֮ǰӦ�ñ�֤û���ظ��Ľڵ�
{
	if (node1 == node2)
		return;
	int node1Index = -1;
	int	node2Index = -1;
	for (int i = 0; i < GraphAdjMat::NodesInfo.size(); i++)
	{
		if (node1 == GraphAdjMat::NodesInfo[i])
			node1Index = i;
		else if (node2 == GraphAdjMat::NodesInfo[i])
			node2Index = i;
	}
	if (node1Index == -1 || node2Index == -1) //˵�������������Ľڵ�
	{
		cout << "�����������Ľڵ�" << endl;
		return;
	}
	
	GraphAdjMat::GraphInfo[node1Index][node2Index] = value;
}

vector <GraphNode> GraphAdjMat::DFSNotRecur(GraphNode BeginNode)
{
	vector <GraphNode> result;
	int Beginnum = -1;
	for (int i = 0; i < GraphAdjMat::NodesInfo.size(); i++)
	{
		if (BeginNode == GraphAdjMat::NodesInfo[i])
		{
			Beginnum = i;
			break;
		}
	}
	if (Beginnum == -1)
		return result;

	GraphAdjMat::Isvisited.clear();
	for (int i = 0; i < GraphAdjMat::NodesInfo.size(); i++)
	{
		GraphAdjMat::Isvisited.push_back(0);
	}

	vector <int> DFSindex;
	GraphAdjMat::Isvisited[Beginnum] = 1;
	stack <int> DFSstack;
	DFSstack.push(Beginnum);
	while (DFSstack.empty() == 0)
	{
		int popindex = DFSstack.top();
		DFSindex.push_back(popindex);
		DFSstack.pop();
		for (int i = 0; i < GraphAdjMat::NodesInfo.size(); i++)
		{
			if ((GraphAdjMat::GraphInfo[popindex][i] != BrokenEdge) && (GraphAdjMat::Isvisited[i] == 0))
			{
				DFSstack.push(i);
				GraphAdjMat::Isvisited[i] = 1;
			}
		}
	}

	for (int i = 0; i < DFSindex.size(); i++)
	{
		result.push_back(GraphAdjMat::NodesInfo[DFSindex[i]]);
	}
	return result;
}

void DFSGraphAdjMat(vector <int> & isvisited,int & Num,const vector < vector <float> > & GraphInfo, vector <int> & DFSSequence)
{
	isvisited[Num] = 1;
	DFSSequence.push_back(Num);
	for (int i = 0; i < isvisited.size(); i++)
	{
		if ((isvisited[i] != 1)&&(GraphInfo[Num][i] != BrokenEdge))
		{
			DFSGraphAdjMat(isvisited, i, GraphInfo, DFSSequence);
		}
	}
}
vector <GraphNode> GraphAdjMat::DFS(GraphNode BeginNode)
{
	vector <int> DFSSequence;
	vector <GraphNode> result;
	DFSSequence.clear();
	int BeginNum = 0;
	for (BeginNum = 0; BeginNum < GraphAdjMat::NodesInfo.size(); BeginNum++)
	{
		if (GraphAdjMat::NodesInfo[BeginNum] == BeginNode)
			break;
	}
	if (BeginNum >= GraphAdjMat::NodesInfo.size()) //�жϲ����ڳ�ʼ�ڵ�
		return result;
	GraphAdjMat::Isvisited.clear();
	for (int i = 0; i < GraphAdjMat::NodesInfo.size(); i++)
	{
		GraphAdjMat::Isvisited.push_back(0);
	}
	DFSGraphAdjMat(GraphAdjMat::Isvisited, BeginNum, GraphAdjMat::GraphInfo, DFSSequence);
	for (int i = 0; i < DFSSequence.size(); i++)
	{
		result.push_back(GraphAdjMat::NodesInfo[DFSSequence[i]]);
	}
	return result;
}

vector <GraphNode> GraphAdjMat::BFS(GraphNode BeginNode)
{
	vector <GraphNode> result;
	int Beginnum = -1;
	for (int i = 0; i < GraphAdjMat::NodesInfo.size(); i++)
	{
		if (BeginNode == GraphAdjMat::NodesInfo[i])
		{
			Beginnum = i;
			break;
		}
	}
	if (Beginnum == -1)
		return result;

	GraphAdjMat::Isvisited.clear();
	for (int i = 0; i < GraphAdjMat::NodesInfo.size(); i++)
	{
		GraphAdjMat::Isvisited.push_back(0);
	}

	queue <int> Nodeindex;
	Nodeindex.push(Beginnum);
	GraphAdjMat::Isvisited[Beginnum] = 1;
	vector <int> BFSindex;
	while (Nodeindex.empty() == 0)
	{
		int popindex = Nodeindex.front();
		BFSindex.push_back(popindex);
		Nodeindex.pop();
		for (int i = 0; i < GraphAdjMat::NodesInfo.size(); i++)
		{
			if ((GraphAdjMat::GraphInfo[popindex][i] != BrokenEdge) && (GraphAdjMat::Isvisited[i] == 0))
			{
				Nodeindex.push(i);
				GraphAdjMat::Isvisited[i] = 1;
			}
		}
	}

	for (int i = 0; i < BFSindex.size(); i++)
		result.push_back(GraphAdjMat::NodesInfo[BFSindex[i]]);
	return result;
}


//���ָ�ʽ�໥ת�������ڱ�����BrokenEdge��Ȩֵ���ͽ��ж����������ڽӱ�����ʾ
GraphAdjList TransferMat2List(GraphAdjMat Mat)
//���ڽӾ���ĸ�ʽת��Ϊ�ڽӱ�ĸ�ʽ
//O(n^2)
{
	GraphAdjList Result;

	for (int i = 0; i < Mat.NodesInfo.size(); i++)
	{
		GraphAdjListNode tmpListNode;
		tmpListNode.ThisNode = Mat.NodesInfo[i];
		Result.List.push_back(tmpListNode);
	}
	
	for (int i = 0; i < Mat.GraphInfo.size(); i++)
	{
		vector <info> outtmp;
		info tmpinfo;
		for (int j = 0; j < Mat.GraphInfo[i].size(); j++)
		{
			if ((i != j)&&(Mat.GraphInfo[i][j]!= BrokenEdge))
			{
				tmpinfo.location = &(Result.List[j]);
				tmpinfo.Value = Mat.GraphInfo[i][j];
				outtmp.push_back(tmpinfo);
			}
		}
		Result.List[i].out = outtmp;
	}

	//�ڽӾ�����ʵ��һ��������
	for (int i = 0; i < Mat.GraphInfo.size(); i++)
	{
		vector <info> intmp;
		info tmpinfo;
		for (int j = 0; j < Mat.GraphInfo[i].size(); j++)
		{
			if ((i != j) && (Mat.GraphInfo[j][i] != BrokenEdge))
			{
				tmpinfo.location = &(Result.List[j]);
				tmpinfo.Value = Mat.GraphInfo[j][i];
				intmp.push_back(tmpinfo);
			}
		}
		Result.List[i].in = intmp;
	}
	return Result;
}

GraphAdjMat TransferList2Mat(GraphAdjList GraphList)
//���ڽӱ�ĸ�ʽת��Ϊ�ڽӾ���ĸ�ʽ
//O(n^3)
{
	GraphAdjMat result;
	for (int i = 0; i < GraphList.List.size(); i++)
		result.NodesInfo.push_back(GraphList.List[i].ThisNode);
	
	for (int j = 0; j < result.NodesInfo.size(); j++)
	{
		vector <float> tmpvalue;
		for (int i = 0; i < result.NodesInfo.size(); i++)
			tmpvalue.push_back(BrokenEdge); //�ȼ������нڵ㶼�Ƕ����ģ�û���໥�ɴ��ϵ
		result.GraphInfo.push_back(tmpvalue);
	}

	for (int i = 0; i < GraphList.List.size(); i++)
	{
		for (int j = 0; j < GraphList.List[i].out.size(); j++)
		{
			for (int k = 0; k < result.NodesInfo.size(); k++)
			{
				if (result.NodesInfo[k] == GraphList.List[i].out[j].location->ThisNode)
				{
					result.GraphInfo[i][k] = GraphList.List[i].out[j].Value;
					break;
				}
			}
		}
	}
	return result;
}




void GraphAdjList::MapVisualize(float NodeSize, float LineWeight)
//O(n+E) EΪ���� ���߹����ʱ�򣬷��������ڽӾ������ʽ
{
	vector <Point> tmp; 
	for (int i = 0; i < GraphAdjList::List.size(); i++)
		tmp.push_back(GraphAdjList::List[i].ThisNode);
	AddBufferPoints(tmp, NodeSize);
	
	for (int i = 0; i < GraphAdjList::List.size(); i++)
	{
		for (int j = 0; j < GraphAdjList::List[i].out.size(); j++)
		{
			vector <Point> tmpthis;
			tmpthis.push_back(GraphAdjList::List[i].ThisNode);
			tmpthis.push_back(GraphAdjList::List[i].out[j].location->ThisNode);//iָ��j
			AddBufferLinesArrows(tmpthis, LineWeight);
		}

		for (int j = 0; j < GraphAdjList::List[i].in.size(); j++)
		{
			vector <Point> tmpthis;
			tmpthis.push_back(GraphAdjList::List[i].in[j].location->ThisNode);
			tmpthis.push_back(GraphAdjList::List[i].ThisNode);
			AddBufferLinesArrows(tmpthis, LineWeight);
		}
	}
}

void GraphAdjList::InsertNode(GraphNode node)
{
	GraphAdjListNode tmp;
	tmp.ThisNode = node;
	GraphAdjList::List.push_back(tmp);
}

void GraphAdjList::UpdateEdge(GraphNode node1, GraphNode node2, float value)
//���������֮ǰӦ�ñ�֤û���ظ��Ľڵ�
{
	if (node1 == node2)
		return;
	int node1Index = -1;
	int	node2Index = -1;
	for (int i = 0; i < GraphAdjList::List.size(); i++)
	{
		if (node1 == GraphAdjList::List[i].ThisNode)
			node1Index = i;
		else if (node2 == GraphAdjList::List[i].ThisNode)
			node2Index = i;
	}
	if (node1Index == -1 || node2Index == -1) //˵�������������Ľڵ�
	{
		cout << "�����������Ľڵ�" << endl;
		return;
	}

	int tmpnode2Index = -1;
	for (int i = 0; i < GraphAdjList::List[node1Index].out.size(); i++)
	{
		if (node2 == GraphAdjList::List[node1Index].out[i].location->ThisNode)
			tmpnode2Index = i;
	}
	if (tmpnode2Index == -1)
	{
		if (value == BrokenEdge)
			return;
		else
		{
			info tmpinfo;
			tmpinfo.location = &(GraphAdjList::List[node2Index]);
			tmpinfo.Value = value;
			GraphAdjList::List[node1Index].out.push_back(tmpinfo);
		}
	}
	else
	{
		GraphAdjList::List[node1Index].out[tmpnode2Index].Value = value;
	}
}

vector <GraphAdjListNode> GraphAdjList::DFSNotRecur(GraphNode BeginNode)
{
	vector <GraphAdjListNode> result;
	int Beginnum = -1;
	for (int i = 0; i < GraphAdjList::List.size(); i++)
	{
		if (BeginNode == GraphAdjList::List[i].ThisNode)
		{
			Beginnum = i;
			break;
		}
	}
	if (Beginnum == -1)
		return result;

	GraphAdjList::Isvisited.clear();
	for (int i = 0; i < GraphAdjList::List.size(); i++)
	{
		GraphAdjList::Isvisited.push_back(0);
	}

	vector <int> DFSindex;
	GraphAdjList::Isvisited[Beginnum] = 1;
	stack <GraphAdjListNode> DFSstack;
	DFSstack.push(GraphAdjList::List[Beginnum]);
	while (DFSstack.empty() == 0)
	{
		int popindex = DFSstack.top();
		DFSindex.push_back(popindex);
		DFSstack.pop();




		for (int i = 0; i < GraphAdjMat::NodesInfo.size(); i++)
		{
			if ((GraphAdjMat::GraphInfo[popindex][i] != BrokenEdge) && (GraphAdjMat::Isvisited[i] == 0))
			{
				DFSstack.push(i);
				GraphAdjMat::Isvisited[i] = 1;
			}
		}
	}

	for (int i = 0; i < DFSindex.size(); i++)
	{
		result.push_back(GraphAdjMat::NodesInfo[DFSindex[i]]);
	}
	return result;
}

void DFSGraphAdjList(vector <int> & isvisited, int & Num, const vector < vector <float> > & GraphInfo, vector <int> & DFSSequence)
{
	isvisited[Num] = 1;
	DFSSequence.push_back(Num);
	for (int i = 0; i < isvisited.size(); i++)
	{
		if ((isvisited[i] != 1) && (GraphInfo[Num][i] != BrokenEdge))
		{
			DFSGraphAdjMat(isvisited, i, GraphInfo, DFSSequence);
		}
	}
}
vector <GraphNode> GraphAdjList::DFS(GraphNode BeginNode)
{
	vector <int> DFSSequence;
	vector <GraphNode> result;
	DFSSequence.clear();
	int BeginNum = 0;
	for (BeginNum = 0; BeginNum < GraphAdjMat::NodesInfo.size(); BeginNum++)
	{
		if (GraphAdjMat::NodesInfo[BeginNum] == BeginNode)
			break;
	}
	if (BeginNum >= GraphAdjMat::NodesInfo.size()) //�жϲ����ڳ�ʼ�ڵ�
		return result;
	GraphAdjMat::Isvisited.clear();
	for (int i = 0; i < GraphAdjMat::NodesInfo.size(); i++)
	{
		GraphAdjMat::Isvisited.push_back(0);
	}
	DFSGraphAdjMat(GraphAdjMat::Isvisited, BeginNum, GraphAdjMat::GraphInfo, DFSSequence);
	for (int i = 0; i < DFSSequence.size(); i++)
	{
		result.push_back(GraphAdjMat::NodesInfo[DFSSequence[i]]);
	}
	return result;
}

vector <GraphNode> GraphAdjList::BFS(GraphNode BeginNode)
{
	vector <GraphNode> result;
	int Beginnum = -1;
	for (int i = 0; i < GraphAdjMat::NodesInfo.size(); i++)
	{
		if (BeginNode == GraphAdjMat::NodesInfo[i])
		{
			Beginnum = i;
			break;
		}
	}
	if (Beginnum == -1)
		return result;

	GraphAdjMat::Isvisited.clear();
	for (int i = 0; i < GraphAdjMat::NodesInfo.size(); i++)
	{
		GraphAdjMat::Isvisited.push_back(0);
	}

	queue <int> Nodeindex;
	Nodeindex.push(Beginnum);
	GraphAdjMat::Isvisited[Beginnum] = 1;
	vector <int> BFSindex;
	while (Nodeindex.empty() == 0)
	{
		int popindex = Nodeindex.front();
		BFSindex.push_back(popindex);
		Nodeindex.pop();
		for (int i = 0; i < GraphAdjMat::NodesInfo.size(); i++)
		{
			if ((GraphAdjMat::GraphInfo[popindex][i] != BrokenEdge) && (GraphAdjMat::Isvisited[i] == 0))
			{
				Nodeindex.push(i);
				GraphAdjMat::Isvisited[i] = 1;
			}
		}
	}

	for (int i = 0; i < BFSindex.size(); i++)
		result.push_back(GraphAdjMat::NodesInfo[BFSindex[i]]);
	return result;
}
