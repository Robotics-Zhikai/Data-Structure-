#include "Graph.h"

GraphAdjMat RandomCreateGraphInAdjmat(int NumOfNodes,float RangeXmin, float RangeXmax, float RangeYmin, float RangeYmax)
//随机生成图顶点和图的边 储存在邻接矩阵的形式
{
	GraphAdjMat result;
	result.NodesInfo = GenerateRandomPoint(NumOfNodes, RangeXmin, RangeXmax, RangeYmin, RangeYmax);
	srand((int)time(0));  // 产生随机种子  把0换成NULL也行

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
				if (randomnum < 0.5)
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

void GraphAdjMat::Visualize(float NodeSize,float LineWeight)
//这个函数不一定最后调用
{

	AddBufferPoints(GraphAdjMat::NodesInfo, NodeSize);
	for (int i = 0; i < GraphAdjMat::GraphInfo.size(); i++)
	{
		for (int j = 0; j < GraphAdjMat::GraphInfo[i].size(); j++)
		{
			if (GraphAdjMat::GraphInfo[i][j] == 1)
			{
				vector <Point> tmp;
				tmp.push_back(GraphAdjMat::NodesInfo[i]);
				tmp.push_back(GraphAdjMat::NodesInfo[j]);//i指向j
				AddBufferLinesArrows(tmp, LineWeight);
			}
		}
	}

}