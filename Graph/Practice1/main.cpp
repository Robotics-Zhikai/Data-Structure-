#include "Visualization.h"
#include "Graph.h"
#include "ConvexHull.h"

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
	test = RandomCreateGraphInAdjmat(65,0,10, 0, 10);



	GraphAdjList trans;
	trans.RandomGenerateGraph(65, 180, 0, 10, 0, 10);
	//trans = TransferMat2List(test);
	GraphAdjMat test1;
	test1 = TransferList2Mat(trans);
	int index = 0;

	start = clock();
	vector <Point> BFSSequence = test1.BFS(test1.NodesInfo[index]);
	vector <Point> DFSSequence = test1.DFS(test1.NodesInfo[index]);
	vector <Point> DFSNotRecurSequence = test1.DFSNotRecur(test1.NodesInfo[index]);
	end = clock();
	double endtime = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "邻接矩阵存储形式用时" << endtime << "s" << endl;

	start = clock();
	vector <Point> BFSSequencelist = trans.BFS(test1.NodesInfo[index]);
	vector <Point> DFSSequencelist = trans.DFS(test1.NodesInfo[index]);
	vector <Point> DFSNotRecurSequencelist = trans.DFSNotRecur(test1.NodesInfo[index]);
	end = clock();
	endtime = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "邻接表存储形式用时" << endtime << "s" << endl;

	///////////////////////////////////////////////////////////////
	//进行算法的实验
	int beginindex = 10;
	int endindex = 10;
	float pathdist;
	vector<int> Pathint;
	vector <GraphNode> Path = trans.FindShortestPath(trans.List[0].ThisNode, (*(trans.List.end()-1)).ThisNode, pathdist);
	Pathint = trans.FindShortestPath(beginindex, endindex, pathdist);

	vector<MatrixXd> tmp = trans.Floyd();
	vector <int> Paththis = trans.GetPathFromFloydResult(tmp[1], beginindex, endindex);

	trans.DijkstraHeap(beginindex);






	test1.MapVisualize(5.0f, 1.0f);

	//test1.SearchVisualize(BFSSequence, 0.03);
	//test1.SearchVisualize(DFSSequence, 0.05);
	//test1.SearchVisualize(DFSNotRecurSequence, 0.07);

	trans.PathVisualize(Path, 0.04, 5);

	//trans.SearchVisualize(BFSSequencelist, 0.09);
	//trans.SearchVisualize(DFSSequencelist, 0.11);
	//trans.SearchVisualize(DFSNotRecurSequencelist, 0.13);

	
	//trans.Visualize(5.0f, 1.0f);
	//test1.Visualize(5.0f, 1.0f);
	CloseGLplot();
}

void main()
{
	//vector<vector<int>> IndexBeforAfter(2);
	vector<int> test1;
	vector<int> test2;

	test1.push_back(0);
	test1.push_back(1);

	test2.push_back(0);
	test2.push_back(1);
	test2.push_back(2);
	test2.push_back(3);

	test1 = test2;

	test2.push_back(100);
	//Test_GetConvexHull_GS();
	Test_Graph();
}