#ifndef GRAPH_H
#define GRAPH_H

#include "Visualization.h"

class GraphAdjMat
//用邻接矩阵储存图的信息，自己不可能指向自己
{
public:
	vector <Point> NodesInfo; //存储节点的位置信息
	vector < vector <float> > GraphInfo; //储存边的信息,可以二值化表示连通与否，也可以定量化表示权值

	GraphAdjMat()
	{
		
	}
	void Visualize(float NodeSize, float LineWeight);
};

GraphAdjMat RandomCreateGraphInAdjmat(int NumOfNodes, float RangeXmin, float RangeXmax, float RangeYmin, float RangeYmax);
//随机生成图顶点和图的边 储存在邻接矩阵的形式









#endif 


