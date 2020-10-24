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
					randomnum = BrokenEdge;
				else
					randomnum = 1;
				result.GraphInfo[i].push_back(randomnum);
			}
			else
				result.GraphInfo[i].push_back(BrokenEdge);
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
	Result.updateEdgeNum(Result.CountEdgesNum());
	Result.updateNodeNum(Result.CountNodesNum());
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

int GraphAdjList::CountEdgesNum()
{
	int Count = 0;
	for (int i = 0; i < GraphAdjList::List.size(); i++)
	{
		Count += List[i].out.size();
	}
	return Count;
}

int GraphAdjList::CountNodesNum()
{
	return GraphAdjList::List.size();
}

float GraphAdjList::RandomGenerateEdgeValue(float lower, float upper)
{
	if (lower == upper && upper == BrokenEdge)
		return BrokenEdge + 1; //随便生成一个不是brokenedge的边

	float GeneratedValue = BrokenEdge;
	while (GeneratedValue == BrokenEdge)
	{
		GeneratedValue = RandGenerateFLOAT_a2b(lower, upper);
	}
	return GeneratedValue;
}

void GraphAdjList::RandomGenerateGraph(int NumOfNodes, int NumOfEdges, float RangeXmin, float RangeXmax, float RangeYmin, float RangeYmax)
{
	if (NumOfEdges > NumOfNodes*(NumOfNodes - 1))
		NumOfEdges = NumOfNodes*(NumOfNodes - 1);
	//20201023写在这里了
	GraphAdjList::NodeNum = 0;
	GraphAdjList::EdgeNum = 0;
		
	while (GraphAdjList::NodeNum != NumOfNodes)
	{
		vector<GraphNode> Point = GenerateRandomPoint(1, RangeXmin, RangeXmax, RangeYmin, RangeYmax);
		GraphAdjList::InsertNode(Point[0]);
	}
	
	if (NumOfNodes == 1)
		return;

	while (GraphAdjList::EdgeNum != NumOfEdges)
	{
		int randbegin = 0;
		int randend = 0;
		while (randbegin == randend)
		{
			randbegin = RandGenerateINT_a2b(0, NumOfNodes - 1);
			randend = RandGenerateINT_a2b(0, NumOfNodes - 1);
		}
		float randedge = GraphAdjList::RandomGenerateEdgeValue(0, 12);
		GraphAdjList::UpdateEdge(randbegin, randend, randedge);
	}
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

void GraphAdjList::PathVisualize(vector <GraphNode> Path, float SquareSize, float PathEdgeSize)
{
	sequenceHollowVisualize(Path, SquareSize);
	for (int i = 0; i < Path.size()-1; i++)
	{
		vector <Point> tmpthis;
		tmpthis.push_back(Path[i]);
		tmpthis.push_back(Path[i+1]);
		AddBufferLinesArrows(tmpthis, PathEdgeSize);
	}
}

void GraphAdjList::sequenceHollowVisualize(vector <GraphNode> sequence, float SquareSize)
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
	GraphAdjList::NodeNum++;
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

	GraphAdjList::UpdateEdge(node1Index, node2Index, value);
}

void GraphAdjList::UpdateEdge(int node1Index, int node2Index, float value)
{
	if (GraphAdjList::CheckIndexValid(node1Index) && GraphAdjList::CheckIndexValid(node2Index))
	{
		int tmpnode2Index = -1;
		for (int i = 0; i < GraphAdjList::List[node1Index].out.size(); i++)
		{
			if (node2Index == GraphAdjList::List[node1Index].out[i].locationindex)
				tmpnode2Index = i;
			/*if (node2 == GraphAdjList::List[GraphAdjList::List[node1Index].out[i].locationindex].ThisNode)
			tmpnode2Index = i;*/
		}
		if (tmpnode2Index == -1)
		{
			if (value == BrokenEdge)
				return;
			else // 没有边加了一个边
			{
				info tmpinfo;
				tmpinfo.locationindex = node2Index;
				tmpinfo.Value = value;
				GraphAdjList::List[node1Index].out.push_back(tmpinfo);

				tmpinfo.locationindex = node1Index;
				tmpinfo.Value = value;
				GraphAdjList::List[node2Index].in.push_back(tmpinfo);

				GraphAdjList::EdgeNum++;
			}
		}
		else
		{
			if (value == BrokenEdge) //有边然后删了一个边
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

				GraphAdjList::EdgeNum--;
			}
			else //发现两个节点有边，更新权值
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
	else
	{
		cout << "输入的节点索引不符合大小规范" << endl;
		return;
	}
}

int GraphAdjList::GetInDegree(GraphNode Node)
{
	int NodeIndex = GraphAdjList::ReturnNodeIndex(Node);
	return GraphAdjList::List[NodeIndex].in.size();
}

int GraphAdjList::GetInDegree(int NodeIndex)
{
	return GraphAdjList::List[NodeIndex].in.size();
}

int GraphAdjList::GetOutDegree(GraphNode Node)
{
	int NodeIndex = GraphAdjList::ReturnNodeIndex(Node);
	return GraphAdjList::List[NodeIndex].out.size();
}

int GraphAdjList::GetOutDegree(int NodeIndex)
{
	return GraphAdjList::List[NodeIndex].out.size();
}



bool GraphAdjList::CheckIndexValid(int num)
{
	if (num < 0 || num >= GraphAdjList::List.size())
		return 0;
	else
		return 1;
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

	vector <int> BFSindex = GraphAdjList::BFS(Beginnum);

	for (int i = 0; i < BFSindex.size(); i++)
		result.push_back(GraphAdjList::List[BFSindex[i]].ThisNode);
	return result;
}

vector <int> GraphAdjList::BFS(int Beginnum)
{
	vector <int> BFSindex;
	if (GraphAdjList::CheckIndexValid(Beginnum) == FALSE)
		return BFSindex;

	GraphAdjList::Isvisited.clear();
	for (int i = 0; i < GraphAdjList::List.size(); i++)
	{
		GraphAdjList::Isvisited.push_back(0);
	}

	queue <int> Nodeindex;
	Nodeindex.push(Beginnum);
	GraphAdjList::Isvisited[Beginnum] = 1;
	
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
	return BFSindex;
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
	GraphAdjList::NodeNum--;
}

float GraphAdjList::GetConnectEdgeValue(GraphNode Node1, GraphNode Node2)
{
	return GraphAdjList::GetConnectEdgeValue(GraphAdjList::ReturnNodeIndex(Node1), GraphAdjList::ReturnNodeIndex(Node2));
}

float GraphAdjList::GetConnectEdgeValue(int Node1index, int Node2index)
{
	if (GraphAdjList::IsConnectEdge(Node1index, Node2index))
	{
		for (int i = 0; i < GraphAdjList::GetOutDegree(Node1index); i++)
		{
			if (GraphAdjList::List[Node1index].out[i].locationindex == Node2index)
				return GraphAdjList::List[Node1index].out[i].Value;
		}
	}
	else
		return BrokenEdge;
}

vector <int> GetPathFromFloydResultRecur(const MatrixXd & PathMat, int beginindex, int endindex)
{
	vector<int> subPath1,subPath2;
	if (beginindex == endindex)
	{
		subPath1.push_back(beginindex);
		return subPath1;
	}
	else if (PathMat(beginindex, endindex) == beginindex) //说明二者可以直达
	{
		subPath1.push_back(beginindex);
		subPath1.push_back(endindex);
		return subPath1;
	}
	else if (PathMat(beginindex, endindex) == -1 || beginindex==-1 || endindex == -1) //说明二者之间没有可达路径
	{
		return subPath1;
	}

	subPath1 = GetPathFromFloydResultRecur(PathMat,beginindex, PathMat(beginindex,endindex));
	subPath2 = GetPathFromFloydResultRecur(PathMat, PathMat(beginindex, endindex), endindex);
	for (int i = 0; i < subPath2.size(); i++)
	{
		subPath1.push_back(subPath2[i]);
	}//这个是带有重复点的，需要去除重复点
	return subPath1;
}

vector <int> GraphAdjList::GetPathFromFloydResult(const MatrixXd & PathMat, int beginindex, int endindex)
{
	vector <int> Path = GetPathFromFloydResultRecur(PathMat, beginindex, endindex);
	vector <int> result;

	if (Path.size() >= 1)
		result.push_back(Path[0]);
	for (int i = 1; i < Path.size(); i++)
	{
		//这个1026开始写吧
	}
}

vector <MatrixXd> GraphAdjList::Floyd()
//多源最短路径问题，用的是动态规划
{
	int n = GraphAdjList::List.size();
	vector <MatrixXd> result;

	MatrixXd DistMat(n,n);
	MatrixXd PathMat(n,n);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			DistMat(i, j) = PositiveInfEdgeValue;
			PathMat(i, j) = -1;
		}
	}
	for (int i = 0; i < n; i++)
	{
		DistMat(i, i) = 0;
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < GraphAdjList::GetOutDegree(i); j++)
		{
			DistMat(i, GraphAdjList::List[i].out[j].locationindex) = GraphAdjList::List[i].out[j].Value;
			PathMat(i, GraphAdjList::List[i].out[j].locationindex) = i;
			//当可以直连时，中间点就为端点本身
		}
	}

	for (int k = 0; k < n; k++)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (DistMat(i, k) + DistMat(k, j) < DistMat(i, j))
				{
					DistMat(i, j) = DistMat(i, k) + DistMat(k, j);
					PathMat(i, j) = k;
				}
			}
		}
	}
	result.push_back(DistMat);
	result.push_back(PathMat);
	return result;
}

MatrixXd GraphAdjList::Dijkstra(GraphNode BeginNode)
{
	int BeginIndex = GraphAdjList::ReturnNodeIndex(BeginNode);

	return GraphAdjList::Dijkstra(BeginIndex);
}

MatrixXd GraphAdjList::Dijkstra(int BeginIndex)
{
	GraphAdjList::ResetIsvisited(0);
	MatrixXd DistMatrix(2, GraphAdjList::List.size());
	for (int i = 0; i < GraphAdjList::List.size(); i++)
	{
		if (i == BeginIndex)
		{
			DistMatrix(0, i) = 0;
			DistMatrix(1, i) = -1;
		}
		else
		{
			DistMatrix(0, i) = PositiveInfEdgeValue;
			DistMatrix(1, i) = -2; //不知道前继节点索引是多少
			//也就是说当前继没有节点时值为-2
		}
	}
	for (int i = 0; i < GraphAdjList::GetOutDegree(BeginIndex); i++)
	{
		DistMatrix(0, GraphAdjList::List[BeginIndex].out[i].locationindex) = GraphAdjList::List[BeginIndex].out[i].Value;
		DistMatrix(1, GraphAdjList::List[BeginIndex].out[i].locationindex) = BeginIndex;
	}

	int CurrentIndex = BeginIndex;
	GraphAdjList::Isvisited[CurrentIndex] = 1;
	while (1)
	{
		float min = PositiveInfEdgeValue;
		int LocateMin = -1;
		for (int i = 0; i < DistMatrix.cols(); i++)
		{
			if (GraphAdjList::Isvisited[i] == 0)
			{
				if (DistMatrix(0,i) < min)
				{
					min = DistMatrix(0, i);
					LocateMin = i;
				}
			}
		}
		if (LocateMin == -1)//此时说明没有访问过的节点与begin的距离都是PositiveInfEdgeValue;要不所有节点全部都访问过了
			break;

		CurrentIndex = LocateMin;
		GraphAdjList::Isvisited[CurrentIndex] = 1;
		for (int i = 0; i < GraphAdjList::GetOutDegree(CurrentIndex); i++)
		{
			int IndexNode = GraphAdjList::List[CurrentIndex].out[i].locationindex;
			float NewValue = DistMatrix(0, CurrentIndex) + GraphAdjList::List[CurrentIndex].out[i].Value;
			if (DistMatrix(0, IndexNode) > NewValue)
			{
				DistMatrix(0, IndexNode) = NewValue;
				DistMatrix(1, IndexNode) = CurrentIndex;
			}
		}
	}

	return DistMatrix;
}

vector<int> GraphAdjList::FindShortestPath(int BeginIndex, int EndIndex,float & PathDist)
//值得指出的是，不能利用PathDist是否等于Inf来判断Begin到End是否有通路，因为完全有可能通路存在但是权值累积和大于定义的inf
{
	MatrixXd Distmat = GraphAdjList::Dijkstra(BeginIndex);
	PathDist = Distmat(0, EndIndex);
	vector <int> Path;
	vector <int> InversePath;
	
	int CurrentIndex = Distmat(1,EndIndex);
	while (CurrentIndex != -2 && CurrentIndex!=BeginIndex) //将路径逆序装到vector中
	{
		InversePath.push_back(CurrentIndex);
		CurrentIndex = Distmat(1, CurrentIndex);
	}
	
	if (CurrentIndex != BeginIndex)
	{
		Path.push_back(BeginIndex);// 说明此时初始节点到末节点没有可行路径
	}
	else
	{
		Path.push_back(BeginIndex);
		while (InversePath.empty() != 1)
		{
			Path.push_back(*(InversePath.end()-1));
			InversePath.pop_back();
		}
		Path.push_back(EndIndex);
	}
	return Path;
}

vector<GraphNode> GraphAdjList::FindShortestPath(GraphNode BeginNode, GraphNode EndNode, float & PathDist)
{
	int BeginIndex = GraphAdjList::ReturnNodeIndex(BeginNode);
	int EndIndex = GraphAdjList::ReturnNodeIndex(EndNode);
	vector<int> Path = GraphAdjList::FindShortestPath(BeginIndex, EndIndex, PathDist);

	vector<GraphNode> PathNodes;
	for (int i = 0; i < Path.size(); i++)
	{
		PathNodes.push_back(GraphAdjList::List[Path[i]].ThisNode);
	}
	return PathNodes;
}

bool GraphAdjList::IsConnectPath(int Beginindex, int Endindex)
{
	vector<int> ConnectGraph = GraphAdjList::BFS(Beginindex); 
	//得到全连通的子图,实际上不必要全部都得到连通的子图才行，有可能找到即可停止，但并不是算法本质上的速度提升
	for (int i = 0; i < ConnectGraph.size(); i++)
	{
		if (ConnectGraph[i] == Endindex)
			return TRUE;
	}
	return FALSE;
}



bool GraphAdjList::IsConnectEdge(GraphNode Node1, GraphNode Node2)
{
	return GraphAdjList::IsConnectEdge(GraphAdjList::ReturnNodeIndex(Node1), GraphAdjList::ReturnNodeIndex(Node2));
}

bool GraphAdjList::IsConnectEdge(int Node1Index, int Node2Index)
{
	for (int i = 0; i < GraphAdjList::GetOutDegree(Node1Index); i++)
	{
		if (GraphAdjList::List[Node1Index].out[i].locationindex == Node2Index)
			return TRUE;
		else
			return FALSE;
	}
}

void GraphAdjList::ResetEdgeValue(float num)
{
	if (num == BrokenEdge)
	{
		cout << "重置的数值不能是BrokenEdge"<<endl;
		return;
	}
	else
	{
		for (int i = 0; i < GraphAdjList::List.size()-1; i++)
		{
			for (int j = i+1; j < GraphAdjList::List.size(); j++)
			{
				if (GraphAdjList::IsConnectEdge(i,j)) //不能没有边也进行更新，否则就直接所有V^2个边了，即凭空增加了很多边
					GraphAdjList::UpdateEdge(i, j, num);
			}
		}
	}
}

void GraphAdjList::ResetIsvisited(int num)
{
	if (num != 0)
		num = 1;
	else
		num = 0;
	GraphAdjList::Isvisited.clear();
	for (int i = 0; i < GraphAdjList::List.size(); i++)
		GraphAdjList::Isvisited.push_back(num);
}

int GraphAdjList::IsNodeInMap(GraphNode Node)
{
	int BeginNodeIndex = -1;
	for (int i = 0; i < GraphAdjList::List.size(); i++)
	{
		if (GraphAdjList::List[i].ThisNode == Node)
			return 1;
	}
	return 0;
}

int GraphAdjList::ReturnNodeIndex(GraphNode Node)
{
	if (IsNodeInMap(Node) == 0)
		return -1;
	else
	{
		int BeginNodeIndex = -1;
		for (int i = 0; i < GraphAdjList::List.size(); i++)
		{
			if (GraphAdjList::List[i].ThisNode == Node)
				return i;
		}
	}
}