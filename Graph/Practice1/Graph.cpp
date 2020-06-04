#include "Graph.h"

GraphAdjMat RandomCreateGraphInAdjmat(int NumOfNodes,float RangeXmin, float RangeXmax, float RangeYmin, float RangeYmax)
//随机生成图顶点和图的边 储存在邻接矩阵的形式
{
	GraphAdjMat result;
	result.NodesInfo = GenerateRandomPoint(NumOfNodes, RangeXmin, RangeXmax, RangeYmin, RangeYmax);
	//srand((int)time(0));  // 产生随机种子  把0换成NULL也行
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
//这个函数不一定最后调用
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
				tmp.push_back(GraphAdjMat::NodesInfo[j]);//i指向j
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
	for (int i = 0; i < GraphAdjMat::NodesInfo.size(); i++)
	{
		if (node == GraphAdjMat::NodesInfo[i])
		{
			return;
		}	
	}

	GraphAdjMat::NodesInfo.push_back(node);

	vector <float> tmp;
	for (int i = 0; i < GraphAdjMat::NodesInfo.size(); i++)
		tmp.push_back(BrokenEdge);
	GraphAdjMat::GraphInfo.push_back(tmp);
}

void GraphAdjMat::DeleteNode(GraphNode node)
//还未测试
{
	int record = -1;
	for (int i = 0; i < GraphAdjMat::NodesInfo.size(); i++)
	{
		if (node == GraphAdjMat::NodesInfo[i])
		{
			record = i;
			break;
		}
	}
	if (record == -1)
		return;
	GraphAdjMat::NodesInfo.erase(GraphAdjMat::NodesInfo.begin() + record);
	GraphAdjMat::GraphInfo.erase(GraphAdjMat::GraphInfo.begin() + record);
	for (int i = 0; i < GraphAdjMat::GraphInfo.size(); i++)
	{
		GraphAdjMat::GraphInfo[i].erase(GraphAdjMat::GraphInfo[i].begin() + record);
	}
}

void GraphAdjMat::UpdateEdge(GraphNode node1, GraphNode node2, float value)
//更新两节点间的权值，可以把本来有的边弄成brokenedge 也可以把本来是brokenedge的边弄成有权值
//进这个函数之前应该保证没有重复的节点
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
	if (node1Index == -1 || node2Index == -1) //说明不存在这样的节点
	{
		cout << "不存在这样的节点" << endl;
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
	if (BeginNum >= GraphAdjMat::NodesInfo.size()) //判断不存在初始节点
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


//两种格式相互转换，对于表明是BrokenEdge的权值，就进行丢弃，不在邻接表中显示
GraphAdjList TransferMat2List(GraphAdjMat Mat)
//将邻接矩阵的格式转化为邻接表的格式
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
				tmpinfo.locationindex = j;
				tmpinfo.Value = Mat.GraphInfo[i][j];
				outtmp.push_back(tmpinfo);
			}
		}
		Result.List[i].out = outtmp;
	}

	//邻接矩阵其实是一个方矩阵
	for (int i = 0; i < Mat.GraphInfo.size(); i++)
	{
		vector <info> intmp;
		info tmpinfo;
		for (int j = 0; j < Mat.GraphInfo[i].size(); j++)
		{
			if ((i != j) && (Mat.GraphInfo[j][i] != BrokenEdge))
			{
				tmpinfo.locationindex = j;
				tmpinfo.Value = Mat.GraphInfo[j][i];
				intmp.push_back(tmpinfo);
			}
		}
		Result.List[i].in = intmp;
	}
	return Result;
}

GraphAdjMat TransferList2Mat(GraphAdjList GraphList)
//将邻接表的格式转化为邻接矩阵的格式
//O(n^3)
{
	GraphAdjMat result;
	for (int i = 0; i < GraphList.List.size(); i++)
		result.NodesInfo.push_back(GraphList.List[i].ThisNode);
	
	for (int j = 0; j < result.NodesInfo.size(); j++)
	{
		vector <float> tmpvalue;
		for (int i = 0; i < result.NodesInfo.size(); i++)
			tmpvalue.push_back(BrokenEdge); //先假设所有节点都是独立的，没有相互可达关系
		result.GraphInfo.push_back(tmpvalue);
	}

	for (int i = 0; i < GraphList.List.size(); i++)
	{
		for (int j = 0; j < GraphList.List[i].out.size(); j++)
		{
			for (int k = 0; k < result.NodesInfo.size(); k++)
			{
				if (result.NodesInfo[k] == GraphList.List[GraphList.List[i].out[j].locationindex].ThisNode)
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
//O(n+E) E为边数 当边过多的时候，反而不如邻接矩阵的形式
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
			tmpthis.push_back(GraphAdjList::List[GraphAdjList::List[i].out[j].locationindex].ThisNode);//i指向j
			AddBufferLinesArrows(tmpthis, LineWeight);
		}

		for (int j = 0; j < GraphAdjList::List[i].in.size(); j++)
		{
			vector <Point> tmpthis;
			tmpthis.push_back(GraphAdjList::List[GraphAdjList::List[i].in[j].locationindex].ThisNode);
			tmpthis.push_back(GraphAdjList::List[i].ThisNode);
			AddBufferLinesArrows(tmpthis, LineWeight);
		}
	}
}

void GraphAdjList::SearchVisualize(vector <GraphNode> sequence, float SquareSize)
{
	AddBufferHollowSquare(sequence, SquareSize);
}

void GraphAdjList::InsertNode(GraphNode node)
{
	for (int i = 0; i < GraphAdjList::List.size(); i++)
	{
		if (node == GraphAdjList::List[i].ThisNode)
		{
			return;
		}
	}

	GraphAdjListNode tmp;
	tmp.ThisNode = node;
	GraphAdjList::List.push_back(tmp);
}

void GraphAdjList::UpdateEdge(GraphNode node1, GraphNode node2, float value)
//进这个函数之前应该保证没有重复的节点
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
	if (node1Index == -1 || node2Index == -1) //说明不存在这样的节点
	{
		cout << "不存在这样的节点" << endl;
		return;
	}

	int tmpnode2Index = -1;
	for (int i = 0; i < GraphAdjList::List[node1Index].out.size(); i++)
	{
		if (node2 == GraphAdjList::List[GraphAdjList::List[node1Index].out[i].locationindex].ThisNode)
			tmpnode2Index = i;
	}
	if (tmpnode2Index == -1)
	{
		if (value == BrokenEdge)
			return;
		else
		{
			info tmpinfo;
			tmpinfo.locationindex = node2Index;
			tmpinfo.Value = value;
			GraphAdjList::List[node1Index].out.push_back(tmpinfo);

			tmpinfo.locationindex = node1Index;
			tmpinfo.Value = value;
			GraphAdjList::List[node2Index].in.push_back(tmpinfo);
		}
	}
	else
	{
		if (value == BrokenEdge)
		{
			GraphAdjList::List[node1Index].out.erase(GraphAdjList::List[node1Index].out.begin() + tmpnode2Index);

			for (int i = 0; i < GraphAdjList::List[node2Index].in.size(); i++)
			{
				if (GraphAdjList::List[node2Index].in[i].locationindex == GraphAdjList::List[node1Index].out[tmpnode2Index].locationindex)
				{
					GraphAdjList::List[node2Index].in.erase(GraphAdjList::List[node2Index].in.begin() + i);
					break;
				}
			}
		}
		else
		{
			GraphAdjList::List[node1Index].out[tmpnode2Index].Value = value;

			for (int i = 0; i < GraphAdjList::List[node2Index].in.size(); i++)
			{
				if (GraphAdjList::List[node2Index].in[i].locationindex == GraphAdjList::List[node1Index].out[tmpnode2Index].locationindex)
				{
					GraphAdjList::List[node2Index].in[i].Value = value;
					break;
				}
			}
		}
	}
}

vector <GraphNode> GraphAdjList::DFSNotRecur(GraphNode BeginNode)
{
	vector <GraphNode> result;
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

	vector <int> DFSseq;
	GraphAdjList::Isvisited[Beginnum] = 1;
	stack <int> DFSstack;
	DFSstack.push(Beginnum);
	while (DFSstack.empty() == 0)
	{
		int popindex = DFSstack.top();
		DFSseq.push_back(popindex);
		DFSstack.pop();

		for (int i = 0; i < GraphAdjList::List[popindex].out.size(); i++)
		{
			int thisindex = GraphAdjList::List[popindex].out[i].locationindex;
			if (GraphAdjList::Isvisited[thisindex] == 0)
			{
				DFSstack.push(thisindex);
				GraphAdjList::Isvisited[thisindex] = 1;
			}
		}
	}

	for (int i = 0; i < DFSseq.size(); i++)
	{
		result.push_back(GraphAdjList::List[DFSseq[i]].ThisNode);
	}
	return result;
}

void DFSGraphAdjList(vector <int> & isvisited, int & Num, const vector <GraphAdjListNode> & List, vector <int> & DFSSequence)
{
	isvisited[Num] = 1;
	DFSSequence.push_back(Num);
	for (int i = 0; i < List[Num].out.size(); i++)
	{
		int indexthis = List[Num].out[i].locationindex;
		if (isvisited[indexthis] != 1)
		{
			DFSGraphAdjList(isvisited, indexthis, List, DFSSequence);
		}
	}
}
vector <GraphNode> GraphAdjList::DFS(GraphNode BeginNode)
{
	vector <int> DFSSequence;
	vector <GraphNode> result;
	DFSSequence.clear();
	int BeginNum = 0;
	for (BeginNum = 0; BeginNum < GraphAdjList::List.size(); BeginNum++)
	{
		if (GraphAdjList::List[BeginNum].ThisNode == BeginNode)
			break;
	}
	if (BeginNum >= GraphAdjList::List.size()) //判断不存在初始节点
		return result;
	GraphAdjList::Isvisited.clear();
	for (int i = 0; i < GraphAdjList::List.size(); i++)
	{
		GraphAdjList::Isvisited.push_back(0);
	}
	DFSGraphAdjList(GraphAdjList::Isvisited, BeginNum, GraphAdjList::List, DFSSequence);
	for (int i = 0; i < DFSSequence.size(); i++)
	{
		result.push_back(GraphAdjList::List[DFSSequence[i]].ThisNode);
	}
	return result;
}

vector <GraphNode> GraphAdjList::BFS(GraphNode BeginNode)
{
	vector <GraphNode> result;
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

	queue <int> Nodeindex;
	Nodeindex.push(Beginnum);
	GraphAdjList::Isvisited[Beginnum] = 1;
	vector <int> BFSindex;
	while (Nodeindex.empty() == 0)
	{
		int popindex = Nodeindex.front();
		BFSindex.push_back(popindex);
		Nodeindex.pop();

		for (int i = 0; i < GraphAdjList::List[popindex].out.size(); i++)
		{
			int thisindex = GraphAdjList::List[popindex].out[i].locationindex;
			if (GraphAdjList::Isvisited[thisindex] == 0)
			{
				Nodeindex.push(thisindex);
				GraphAdjList::Isvisited[thisindex] = 1;
			}
		}
	}

	for (int i = 0; i < BFSindex.size(); i++)
		result.push_back(GraphAdjList::List[BFSindex[i]].ThisNode);
	return result;
}

void GraphAdjList::DeleteNode(GraphNode node)
//还未测试
{
	int record = -1;
	for (int i = 0; i < GraphAdjList::List.size(); i++)
	{
		if (node == GraphAdjList::List[i].ThisNode)
		{
			record = i;
			break;
		}
	}
	if (record == -1)
		return;

	for (int i = 0; i < GraphAdjList::List[record].out.size(); i++)
	{
		for (int j = 0; j < GraphAdjList::List[GraphAdjList::List[record].out[i].locationindex].in.size(); j++)
		{
			if (GraphAdjList::List[GraphAdjList::List[record].out[i].locationindex].in[j].locationindex == GraphAdjList::List[record].out[i].locationindex)
				GraphAdjList::List[GraphAdjList::List[record].out[i].locationindex].in.erase(GraphAdjList::List[GraphAdjList::List[record].out[i].locationindex].in.begin() + j);
		}
	}

	for (int i = 0; i < GraphAdjList::List[record].in.size(); i++)
	{
		for (int j = 0; j < GraphAdjList::List[GraphAdjList::List[record].in[i].locationindex].out.size(); j++)
		{
			if (GraphAdjList::List[GraphAdjList::List[record].in[i].locationindex].out[j].locationindex == GraphAdjList::List[record].in[i].locationindex)
				GraphAdjList::List[GraphAdjList::List[record].in[i].locationindex].out.erase(GraphAdjList::List[GraphAdjList::List[record].in[i].locationindex].out.begin() + j);
		}
	}

	GraphAdjList::List.erase(GraphAdjList::List.begin() + record);
}