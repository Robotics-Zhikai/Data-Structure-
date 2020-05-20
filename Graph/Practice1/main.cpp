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

	GraphAdjMat test;
	test = RandomCreateGraphInAdjmat(50,0,10, 0, 10);
	test.Visualize(5.0f,1.0f);
	CloseGLplot();
}
void main()
{
	
	//Test_GetConvexHull_GS();
	Test_Graph();
}