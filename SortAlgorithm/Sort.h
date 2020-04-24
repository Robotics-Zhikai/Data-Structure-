#ifndef SORT
#define SORT
#include <iostream>
#include <vector>
#include <math.h>
#include <time.h>
#include <algorithm>
#include "Heap.h"
using namespace std;

class RandomData
{
public:

	vector<double> GenerateRandomData(int pointsNum, double RangeXmin, double RangeXmax);
	int CheckSorted(vector <double> Data);
	void PrintData(vector <double> Data);
};



vector<double> BubbleSort(vector<double> Data);
vector <double> InsertionSort(vector<double> Data);
vector <double> ShellSort(vector<double> Data);
vector <double> HeapSort(vector<double> Data);
#endif