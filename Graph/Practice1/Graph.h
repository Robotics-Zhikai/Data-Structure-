#ifndef GRAPH_H
#define GRAPH_H

#include "Visualization.h"

//��������Զ��嵱��Ϊ���Ǳ�ʱ��Ȩֵ
#define BrokenEdge 0

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
		 
	void Visualize(float NodeSize, float LineWeight);
	void InsertNode(GraphNode node);
	void UpdateEdge(GraphNode node1, GraphNode node2, float value);//��������ߣ�ȨֵΪvalue
	vector <GraphNode> DFS(GraphNode BeginNode);

	GraphAdjMat()
	{
		for (int i = 0; i < NodesInfo.size(); i++)
		{
			Isvisited.push_back(0);
		}
	}
	void operator = (GraphAdjMat test)
	{
		this->GraphInfo = test.GraphInfo;
		this->NodesInfo = test.NodesInfo;
	}

	//void operator = (GraphAdjList test) //�����֪��Ϊɶ������
	//{
	//	GraphAdjMat result;
	//	result = TransferList2Mat(test);
	//	this->operator=(result);
	//}
	
};

struct info
{
	GraphNode * location; //���λ��
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

	void Visualize(float NodeSize, float LineWeight);
	void InsertNode(GraphNode node);
	void UpdateEdge(GraphNode node1, GraphNode node2, float value);//��������ߣ�ȨֵΪvalue

	GraphAdjList()
	{
		for (int i = 0; i < List.size(); i++)
		{
			Isvisited.push_back(0);
		}
	}

	void operator = (GraphAdjList test)
	{
		this->List = test.List;
	}

	//void operator = (GraphAdjMat test)
	//{
	//	GraphAdjList result;
	//	result = TransferMat2List(test);
	//	this->operator=(result);
	//}
};

GraphAdjMat RandomCreateGraphInAdjmat(int NumOfNodes, float RangeXmin, float RangeXmax, float RangeYmin, float RangeYmax);
//�������ͼ�����ͼ�ı� �������ڽӾ������ʽ











#endif 


