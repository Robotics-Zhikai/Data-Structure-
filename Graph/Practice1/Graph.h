#ifndef GRAPH_H
#define GRAPH_H

#include "Visualization.h"

//��������Զ��嵱��Ϊ���Ǳ�ʱ��Ȩֵ
#define BrokenEdge 0

typedef Point GraphNode;//�ڵ㲻ֻ��λ�õ���ʽ���������ǻ����˵�״̬
//���ĵ�Point�Ļ������ӻ��������⣬����û����

class GraphAdjMat
//���ڽӾ��󴢴�ͼ����Ϣ���Լ�������ָ���Լ�
{
public:
	vector <GraphNode> NodesInfo; //�洢�ڵ��λ����Ϣ
	vector < vector <float> > GraphInfo; //����ߵ���Ϣ,���Զ�ֵ����ʾ��ͨ���Ҳ���Զ�������ʾȨֵ

	void Visualize(float NodeSize, float LineWeight);
	void InsertNode(GraphNode node);
	void InsertEdge(GraphNode node1, GraphNode node2, float value);//��������ߣ�ȨֵΪvalue
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
	void Visualize(float NodeSize, float LineWeight);
	void InsertNode(GraphNode node);
	void InsertEdge(GraphNode node1, GraphNode node2, float value);//��������ߣ�ȨֵΪvalue
};

GraphAdjMat RandomCreateGraphInAdjmat(int NumOfNodes, float RangeXmin, float RangeXmax, float RangeYmin, float RangeYmax);
//�������ͼ�����ͼ�ı� �������ڽӾ������ʽ

GraphAdjList TransferMat2List(GraphAdjMat Mat);
GraphAdjMat TransferList2Mat(GraphAdjList GraphList);









#endif 


