
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

//测试同步更新1023
//测试同步更新1023
//测试同步更新1023
//测试同步更新1023