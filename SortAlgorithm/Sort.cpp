#include "Sort.h"

int CheckSorted(vector <double> Data)
//�����Ƿ��ź�˳��
{
	if (Data.size() <= 2)
		return 1;
	double lastcompare = Data[0] - Data[1];
	int i;
	for (i = 1; i < Data.size()-1; i++)
	{
		double nowcompare = Data[i] - Data[i + 1];
		if (lastcompare < 0)
			lastcompare = -1;
		else if (lastcompare > 0)
			lastcompare = 1;

		if (nowcompare < 0)
			nowcompare = -1;
		else if (nowcompare > 0)
			nowcompare = 1;

		if (lastcompare != 0 && nowcompare != 0)
		{
			if (lastcompare != nowcompare)
				break;
		}
		if (nowcompare != 0)
			lastcompare = nowcompare;
	}
	if (i >= Data.size() - 1)
		return 1;
	else
		return 0;
}

vector<double> BubbleSort(vector<double> Data)
//��С��������
{
	for (int i = 1; i < Data.size(); i++)
	{
		for (int j = 0; j < Data.size()-i; j++)
		{
			if (Data[j] > Data[j + 1])
			{
				double temp = Data[j];
				Data[j] = Data[j + 1];
				Data[j + 1] = temp;
			}
		}
	}
	return Data;
}


