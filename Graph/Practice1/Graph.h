#ifndef GRAPH_H
#define GRAPH_H

#include "Visualization.h"

class GraphAdjMat
//���ڽӾ��󴢴�ͼ����Ϣ���Լ�������ָ���Լ�
{
public:
	vector <Point> NodesInfo; //�洢�ڵ��λ����Ϣ
	vector < vector <float> > GraphInfo; //����ߵ���Ϣ,���Զ�ֵ����ʾ��ͨ���Ҳ���Զ�������ʾȨֵ

	GraphAdjMat()
	{
		
	}
	void Visualize(float NodeSize, float LineWeight);
};

GraphAdjMat RandomCreateGraphInAdjmat(int NumOfNodes, float RangeXmin, float RangeXmax, float RangeYmin, float RangeYmax);
//�������ͼ�����ͼ�ı� �������ڽӾ������ʽ









#endif 


