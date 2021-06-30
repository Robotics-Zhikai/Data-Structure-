
#include "CustomizeDataType.h"

int DistributeUniqueID()//分配一独有的ID
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

//测试同步更新1023
//测试同步更新1023
//测试同步更新1023
//测试同步更新1023