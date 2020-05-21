#ifndef GRAPH_H
#define GRAPH_H

#include "Visualization.h"

//在这里可以定义当认为不是边时的权值
#define BrokenEdge 0

typedef Point GraphNode;//节点不只有位置的形式，还可能是机器人的状态
//若改掉Point的话，可视化会有问题，其余没问题

class GraphAdjMat
//用邻接矩阵储存图的信息，自己不可能指向自己
{
public:
	vector <GraphNode> NodesInfo; //存储节点的位置信息
	vector < vector <float> > GraphInfo; //储存边的信息,可以二值化表示连通与否，也可以定量化表示权值

	void Visualize(float NodeSize, float LineWeight);
	void InsertNode(GraphNode node);
	void InsertEdge(GraphNode node1, GraphNode node2, float value);//插入有向边，权值为value
};

struct info
{
	GraphNode * location; //点的位置
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
	void Visualize(float NodeSize, float LineWeight);
	void InsertNode(GraphNode node);
	void InsertEdge(GraphNode node1, GraphNode node2, float value);//插入有向边，权值为value
};

GraphAdjMat RandomCreateGraphInAdjmat(int NumOfNodes, float RangeXmin, float RangeXmax, float RangeYmin, float RangeYmax);
//随机生成图顶点和图的边 储存在邻接矩阵的形式

GraphAdjList TransferMat2List(GraphAdjMat Mat);
GraphAdjMat TransferList2Mat(GraphAdjList GraphList);









#endif 


