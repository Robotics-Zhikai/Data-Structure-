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

//��������Զ��嵱��Ϊ���Ǳ�ʱ��Ȩֵ
#define BrokenEdge 0
#define PositiveInfEdgeValue 999999
#define NegativeInfEdgeValue -PositiveInfEdgeValue

typedef Point GraphNode;//�ڵ㲻ֻ��λ�õ���ʽ���������ǻ����˵�״̬
//���ĵ�Point�Ļ������ӻ��������⣬����û����
class GraphAdjList;
class GraphAdjMat;

GraphAdjList TransferMat2List(GraphAdjMat Mat);
GraphAdjMat TransferList2Mat(GraphAdjList GraphList);


class GraphAdjMat
//���ڽӾ��󴢴�ͼ����Ϣ���Լ�������ָ���Լ�
{
public:
	vector <GraphNode> NodesInfo; //�洢�ڵ��λ����Ϣ
	vector < vector <float> > GraphInfo; //����ߵ���Ϣ,���Զ�ֵ����ʾ��ͨ���Ҳ���Զ�������ʾȨֵ
	vector <int> Isvisited; //�����Ƿ���ʹ�ĳһ�ڵ�
		 
	void MapVisualize(float NodeSize, float LineWeight);
	void InsertNode(GraphNode node);
	void DeleteNode(GraphNode node);
	void UpdateEdge(GraphNode node1, GraphNode node2, float value);//��������ߣ�ȨֵΪvalue
	vector <GraphNode> DFS(GraphNode BeginNode);//DFS�ݹ����
	vector <GraphNode> DFSNotRecur(GraphNode BeginNode);//DFS�ķǵݹ����
	void SearchVisualize(vector <GraphNode> sequence,float SquareSize); //�Ա���������п��ӻ����ӿ�
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

	//void operator = (GraphAdjList test) //�����֪��Ϊɶ������
	//{
	//	GraphAdjMat result;
	//	result = TransferList2Mat(test);
	//	this->operator=(result);
	//}
	
};

struct info
{
	int locationindex; //���λ��
	float Value; //������Ȩֵ
};
struct GraphAdjListNode
{
	GraphNode ThisNode;
	vector <info> out;
	vector <info> in;
};

class GraphAdjList
//���ڽӱ���ͼ����Ϣ���Լ�������ָ���Լ�
{
public:
	vector <GraphAdjListNode> List;
	vector <int> Isvisited; //�����Ƿ���ʹ�ĳһ�ڵ�

	void RandomGenerateGraph(int NumOfNodes,int NumOfEdges, float RangeXmin, float RangeXmax, float RangeYmin, float RangeYmax);
	float RandomGenerateEdgeValue(float lower,float upper);

	void MapVisualize(float NodeSize, float LineWeight);
	void PathVisualize(vector <GraphNode> Path,float SquareSize, float PathEdgeSize); //���ӻ�·��
	void sequenceHollowVisualize(vector <GraphNode> sequence, float SquareSize); //��sequence���п��ӻ����ӿ�

	void InsertNode(GraphNode node);
	void DeleteNode(GraphNode node);

	void UpdateEdge(GraphNode node1, GraphNode node2, float value);//��������ߣ�ȨֵΪvalue
	void UpdateEdge(int Node1Index, int Node2Index, float value);//�������Ϊ�ڵ������������ͽ��͸��Ӷȵ�O(1)
	bool CheckIndexValid(int num);//���ڵ�������Ƿ�Ϸ����Ϸ�Ϊ1 ����Ϊ0

	bool IsConnectEdge(GraphNode Node1,GraphNode Node2); // ���Node1��Node2�Ƿ���ڱ�
	bool IsConnectEdge(int Node1Index, int Node2Index);
	float GetConnectEdgeValue(int Node1index, int Node2index); // �õ�node1index��node2index�ıߵ�Ȩ�� ���û�б߷���BrokenEdge
	float GetConnectEdgeValue(GraphNode Node1, GraphNode Node2);

	vector <GraphNode> DFS(GraphNode BeginNode);//DFS�ݹ����
	vector <GraphNode> DFSNotRecur(GraphNode BeginNode);//DFS�ķǵݹ����
	vector <GraphNode> BFS(GraphNode BeginNode);
	vector <int> BFS(int BeginIndex);

	vector <int> GetPathFromFloydResult(const MatrixXd & PathMat,int beginindex,int endindex);//��Floyd�㷨�õ��Ľ��������������֮������·������
	vector <MatrixXd> Floyd();//��Դ���·���㷨 �õ��Ǹ�ͼ���������ڵ�֮������·�� [DistMat,PathMat]
	MatrixXd Dijkstra(GraphNode BeginNode);
	MatrixXd Dijkstra(int BeginIndex);

	bool IsConnectPath(int Beginindex, int Endindex);//��beginindex��endindex�Ƿ���һ������ͨ��·,����·��һ�������·
	vector<int> FindShortestPath(int BeginIndex, int EndIndex, float & PathDist);
	//�õ�����ʼ��������ֹ���������·����������PathDist��������·����Ȩ�غ�
	vector<GraphNode> FindShortestPath(GraphNode BeginNode, GraphNode EndNode, float & PathDist);

	int IsNodeInMap(GraphNode Node); //�ж�Node�Ƿ���ʵ������ͼ�����ͼȫ��ͨ���
	int ReturnNodeIndex(GraphNode Node); //����Node��List�е�����
	void ResetIsvisited(int num); //����IsvisitedȫΪnum num��ȡֵֻ��1��0
	void ResetEdgeValue(float value); //�������в�ΪBrokenEdge�ıߵ�Ȩ��Ϊvalue

	int GetOutDegree(GraphNode Node); //�õ��ڵ�Node�ĳ���
	int GetInDegree(GraphNode Node); //�õ��ڵ�Node�����
	int GetOutDegree(int NodeIndex); //�õ��ڵ�Node�ĳ���
	int GetInDegree(int NodeIndex); //�õ��ڵ�Node�����

	int CountEdgesNum();
	int CountNodesNum();

	int readNodeNum()
	{
		return NodeNum;
	}
	int readEdgeNum()
	{
		return EdgeNum;
	}
	void updateNodeNum(int num)
	{
		if (num < 0)
			num = 0;
		NodeNum = num;
	}
	void updateEdgeNum(int num)
	{
		if (num < 0)
			num = 0;
		EdgeNum = num;
	}

	GraphAdjList()
	{
		for (int i = 0; i < List.size(); i++)
		{
			Isvisited.push_back(0);
		}
		NodeNum = 0;
		EdgeNum = 0;
	}

	void operator = (GraphAdjList test)
	{
		this->List = test.List;
		this->Isvisited = test.Isvisited;
		this->EdgeNum = test.readEdgeNum();
		this->NodeNum = test.readNodeNum();
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
	int NodeNum; // ����ͼ���ж��ٽڵ� ���������Ҫ��֤���и������ܹ����ø���
	int EdgeNum; // ����ͼ���ж��ٱ� ���������Ҫ��֤���и������ܹ����ø���
};

GraphAdjMat RandomCreateGraphInAdjmat(int NumOfNodes, float RangeXmin, float RangeXmax, float RangeYmin, float RangeYmax);
//�������ͼ�����ͼ�ı� �������ڽӾ������ʽ











#endif 
