#include"Sort.h"

#include <time.h>



vector<double> GenerateRandomData(int pointsNum, double RangeXmin, double RangeXmax)
//generate pointsNum random points in [RangeXmin,RangeXmax,RangeYmin,RangeYmax]
{

	vector<double> Data;
	srand((int)time(0));  // 产生随机种子  把0换成NULL也行
	for (int i = 0; i < pointsNum; i++)
	{
		double a = RangeXmin;
		double b = RangeXmax;
		double temp = a + (rand() / double(RAND_MAX))*(b - a);
		Data.push_back(temp);
	}
	return Data;
}


int main()
{ 
	vector<double> Data = GenerateRandomData(100, 1, 100);
	cout << CheckSorted(Data);
	Data = BubbleSort(Data);
	cout << CheckSorted(Data);
	system("pause");
}