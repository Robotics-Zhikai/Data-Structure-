#ifndef GRAPH_H
#define GRAPH_H

#include "Visualization.h"
#include <queue>
#include <stack>
#include <algorithm>
#include <iostream>
#include "ConvexHull.h"
#include <Eigen/Dense>

using namespace Eigen;
using namespace std;

//在这里可以定义当认为不是边时的权值
#define BrokenEdge 0
#define PositiveInfEdgeValue 999999
#define NegativeInfEdgeValue -PositiveInfEdgeValue

typedef Point GraphNode;//节点不只有位置的形式，还可能是机器人的状态
//若改掉Point的话，可视化会有问题，其余没问题
class GraphAdjList;
class GraphAdjMat;

GraphAdjList TransferMat2List(GraphAdjMat Mat);
GraphAdjMat TransferList2Mat(GraphAdjList GraphList);


class GraphAdjMat
//用邻接矩阵储存图的信息，自己不可能指向自己
{
public:
	vector <GraphNode> NodesInfo; //存储节点的位置信息
	vector < vector <float> > GraphInfo; //储存边的信息,可以二值化表示连通与否，也可以定量化表示权值
	vector <int> Isvisited; //储存是否访问过某一节点
		 
	void MapVisualize(float NodeSize, float LineWeight);
	void InsertNode(GraphNode node);
	void DeleteNode(GraphNode node);
	void UpdateEdge(GraphNode node1, GraphNode node2, float value);//更新有向边，权值为value
	vector <GraphNode> DFS(GraphNode BeginNode);//DFS递归遍历
	vector <GraphNode> DFSNotRecur(GraphNode BeginNode);//DFS的非递归遍历
	void SearchVisualize(vector <GraphNode> sequence,float SquareSize); //对遍历结果进行可视化，加框
	vector <GraphNode> BFS(GraphNode BeginNode);

	GraphAdjMat()
	{
		for (int i = 0; i < NodesInfo.size(); i++)
		{
			Isvisited.push_back(0);
		}
	}
	//void operator = (GraphAdjMat test)
	//{
	//	this->GraphInfo = test.GraphInfo;
	//	this->NodesInfo = test.NodesInfo;
	//}

	//void operator = (GraphAdjList test) //这个不知道为啥出错了
	//{
	//	GraphAdjMat result;
	//	result = TransferList2Mat(test);
	//	this->operator=(result);
	//}
	
};

struct info
{
	int locationindex; //点的位置
	float Value; //相连的权值
};
struct GraphAdjListNode
{
	GraphNode ThisNode;
	vector <info> out;
	vector <info> in;
};

class GraphAdjList
//用邻接表储存图的信息，自己不可能指向自己
{
public:
	vector <GraphAdjListNode> List;
	vector <int> Isvisited; //储存是否访问过某一节点

	void RandomGenerateGraph(int NumOfNodes,int NumOfEdges, float RangeXmin, float RangeXmax, float RangeYmin, float RangeYmax);

	void MapVisualize(float NodeSize, float LineWeight);
	void PathVisualize(vector <GraphNode> Path,float SquareSize, float PathEdgeSize); //可视化路径
	void sequenceHollowVisualize(vector <GraphNode> sequence, float SquareSize); //对sequence进行可视化，加框

	void InsertNode(GraphNode node);
	void DeleteNode(GraphNode node);

	void UpdateEdge(GraphNode node1, GraphNode node2, float value);//更新有向边，权值为value
	void UpdateEdge(int Node1Index, int Node2Index, float value);//输入参数为节点索引，这样就降低复杂度到O(1)
	bool CheckIndexValid(int num);//检查节点的索引是否合法，合法为1 否则为0

	bool IsConnectEdge(GraphNode Node1,GraphNode Node2); // 检查Node1到Node2是否存在边
	bool IsConnectEdge(int Node1Index, int Node2Index);
	float GetConnectEdgeValue(int Node1index, int Node2index); // 得到node1index到node2index的边的权重 如果没有边返回BrokenEdge
	float GetConnectEdgeValue(GraphNode Node1, GraphNode Node2);

	vector <GraphNode> DFS(GraphNode BeginNode);//DFS递归遍历
	vector <GraphNode> DFSNotRecur(GraphNode BeginNode);//DFS的非递归遍历
	vector <GraphNode> BFS(GraphNode BeginNode);
	vector <int> BFS(int BeginIndex);

	MatrixXd Dijkstra(GraphNode BeginNode);
	MatrixXd Dijkstra(int BeginIndex);

	bool IsConnectPath(int Beginindex, int Endindex);//从beginindex到endindex是否有一条可连通的路,这条路不一定是最短路
	vector<int> FindShortestPath(int BeginIndex, int EndIndex, float & PathDist);
	//得到从起始索引到终止索引的最短路径，并返回PathDist即经历的路径的权重和
	vector<GraphNode> FindShortestPath(GraphNode BeginNode, GraphNode EndNode, float & PathDist);

	int IsNodeInMap(GraphNode Node); //判断Node是否在实例化的图里，不管图全连通与否
	int ReturnNodeIndex(GraphNode Node); //返回Node在List中的索引
	void ResetIsvisited(int num); //重置Isvisited全为num num的取值只有1和0
	void ResetEdgeValue(float value); //重置所有不为BrokenEdge的边的权重为value

	int GetOutDegree(GraphNode Node); //得到节点Node的出度
	int GetInDegree(GraphNode Node); //得到节点Node的入度
	int GetOutDegree(int NodeIndex); //得到节点Node的出度
	int GetInDegree(int NodeIndex); //得到节点Node的入度

	GraphAdjList()
	{
		for (int i = 0; i < List.size(); i++)
		{
			Isvisited.push_back(0);
		}
	}


	//void operator = (GraphAdjList test)
	//{
	//	this->List = test.List;
	//}

	//void operator = (GraphAdjMat test)
	//{
	//	GraphAdjList result;
	//	result = TransferMat2List(test);
	//	this->operator=(result);
	//}
private:
	
};

GraphAdjMat RandomCreateGraphInAdjmat(int NumOfNodes, float RangeXmin, float RangeXmax, float RangeYmin, float RangeYmax);
//随机生成图顶点和图的边 储存在邻接矩阵的形式











#endif 


