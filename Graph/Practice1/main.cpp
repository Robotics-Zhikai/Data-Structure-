#include "Visualization.h"
#include "Graph.h"

void Test_GetConvexHull_GS()//GrahamScan算法
{
	clock_t start, end;

	vector <Point> Points;

	Points = GenerateRandomPoint(50000, 0, 10, 1, 10);

	vector <Point> Points2;
	Points2 = GenerateRandomPoint(850, 0, 9.99, 0.5, 0.5);
	for (int i = 0; i < Points2.size(); i++)
	{
		Points.push_back(Points2[i]);
	}
	//Points.push_back(Point(-1, 0.5, 0));
	Points2 = GenerateRandomPoint(850, 9, 9, 0.5, 10);
	for (int i = 0; i < Points2.size(); i++)
	{
		Points.push_back(Points2[i]);
	}

	OpenGLplot();
	AddBufferPoints(Points, 2.0f);
	start = clock();
	cout << "求" << Points.size() << "个点的凸包" << endl;
	Points = GetCHGrahamScan(Points);
	end = clock();

	double endtime = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "GrahamScan算法用时" << endtime << "s" << endl;

	AddBufferPoints(Points, 5.0f);
	vector <Point> temp = Points;
	//temp.push_back(Points[0]);

	//Points = BubbleSortPoints(Points);
	temp = Points;
	temp.push_back(Points[0]);
	AddBufferSequenceLine(temp, 1.0f);
	cout << "凸包的顶点个数：" << Points.size() - 1 << endl;
	CloseGLplot();
}

void Test_Graph()
{
	OpenGLplot();

	clock_t start, end;

	GraphAdjMat test;
	test = RandomCreateGraphInAdjmat(585,0,10, 0, 10);

	GraphAdjList trans;
	trans = TransferMat2List(test);
	GraphAdjMat test1;
	test1 = TransferList2Mat(trans);
	int index = 10;

	start = clock();
	vector <Point> BFSSequence = test1.BFS(test1.NodesInfo[index]);
	vector <Point> DFSSequence = test1.DFS(test1.NodesInfo[index]);
	vector <Point> DFSNotRecurSequence = test1.DFSNotRecur(test1.NodesInfo[index]);
	end = clock();
	double endtime = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "零阶矩阵存储形式用时" << endtime << "s" << endl;

	start = clock();
	vector <Point> BFSSequencelist = trans.BFS(test1.NodesInfo[index]);
	vector <Point> DFSSequencelist = trans.DFS(test1.NodesInfo[index]);
	vector <Point> DFSNotRecurSequencelist = trans.DFSNotRecur(test1.NodesInfo[index]);
	end = clock();
	endtime = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "零阶表存储形式用时" << endtime << "s" << endl;


	test1.MapVisualize(5.0f, 1.0f);

	test1.SearchVisualize(BFSSequence, 0.03);
	test1.SearchVisualize(DFSSequence, 0.05);
	test1.SearchVisualize(DFSNotRecurSequence, 0.07);
	
	//trans.Visualize(5.0f, 1.0f);
	//test1.Visualize(5.0f, 1.0f);
	CloseGLplot();
}
void main()
{
	
	//Test_GetConvexHull_GS();
	Test_Graph();
}