
#include "CustomizeDataType.h"

int DistributeUniqueID()//����һ���е�ID
{
	static vector <int> SegmentsID;
	if (SegmentsID.empty() == 1)
	{
		SegmentsID.push_back(0);
		return 1;
	}
	else
	{
		SegmentsID.push_back(SegmentsID.size());
		return SegmentsID.size();
	}
}

int RandGenerateINT_a2b(int a, int b)
{		
	return (rand() % (b - a + 1)) + a;
}

float RandGenerateFLOAT_a2b(float a,float b)
{
	float num0_1 = rand() / double(RAND_MAX);
	return a + (b - a)*num0_1;
}

//����ͬ������1023
//����ͬ������1023
//����ͬ������1023
//����ͬ������1023