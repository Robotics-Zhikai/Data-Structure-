#ifndef GRAPH_H
#define GRAPH_H

#include "Visualization.h"
#include <queue>
#include <stack>
#include <algorithm>
#include <iostream>
#include "ConvexHull.h"
using namespace std;

//在这里可以定义当认为不是边时的权值
#define BrokenEdge 0

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

	void MapVisualize(float NodeSize, float LineWeight);
	void InsertNode(GraphNode node);
	void DeleteNode(GraphNode node);
	void UpdateEdge(GraphNode node1, GraphNode node2, float value);//更新有向边，权值为value
	vector <GraphNode> DFS(GraphNode BeginNode);//DFS递归遍历
	vector <GraphNode> DFSNotRecur(GraphNode BeginNode);//DFS的非递归遍历
	void SearchVisualize(vector <GraphNode> sequence, float SquareSize); //对遍历结果进行可视化，加框
	vector <GraphNode> BFS(GraphNode BeginNode);

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
};

GraphAdjMat RandomCreateGraphInAdjmat(int NumOfNodes, float RangeXmin, float RangeXmax, float RangeYmin, float RangeYmax);
//随机生成图顶点和图的边 储存在邻接矩阵的形式











#endif 


