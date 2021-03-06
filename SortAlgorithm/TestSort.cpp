#include"Sort.h"









void testBubbleSort(vector<double> Data)
{
	clock_t start, end;
	RandomData test;
	//vector<double> Data = test.GenerateRandomData(1000, 1, 100);
	cout << test.CheckSorted(Data);
	start = clock();
	Data = BubbleSort(Data);
	end = clock();
	cout << test.CheckSorted(Data);

	double endtime = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "冒泡排序算法用时" << endtime <<"s"<< endl;
}

void testInsertionSort(vector<double> Data)
{
	clock_t start, end;
	RandomData test;
	//vector<double> Data = test.GenerateRandomData(10000, 1, 100);
	/*vector<double> Data;
	Data.push_back(1); Data.push_back(2); Data.push_back(3); Data.push_back(4); Data.push_back(1);*/
	cout << test.CheckSorted(Data);
	start = clock();
	Data = InsertionSort(Data,0,Data.size()-1);
	end = clock();
	cout << test.CheckSorted(Data);
	//test.PrintData(Data);
	double endtime = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "插入排序算法用时" << endtime << "s" << endl;
}

void testCPPSTDSort(vector<double> Data)
{
	clock_t start, end;
	RandomData test;
	//vector<double> Data = test.GenerateRandomData(10000, 1, 100);
	/*vector<double> Data;
	Data.push_back(1); Data.push_back(2); Data.push_back(3); Data.push_back(4); Data.push_back(1);*/
	cout << test.CheckSorted(Data);
	start = clock();
	sort(Data.begin(), Data.end());
	end = clock();
	cout << test.CheckSorted(Data);
	//test.PrintData(Data);
	double endtime = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "C++algorithm库排序算法用时" << endtime << "s" << endl;
}

void testShellSort(vector<double> Data)
{
	clock_t start, end;
	RandomData test;
	//vector<double> Data = test.GenerateRandomData(10000, 1, 100);
	/*vector<double> Data;
	Data.push_back(1); Data.push_back(2); Data.push_back(3); Data.push_back(4); Data.push_back(1);*/
	cout << test.CheckSorted(Data);
	start = clock();
	Data = ShellSort(Data);
	end = clock();
	cout << test.CheckSorted(Data);
	//test.PrintData(Data);
	double endtime = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "希尔排序算法用时" << endtime << "s" << endl;
}

void testHeapSort(vector<double> Data)
{
	clock_t start, end;
	RandomData test;
	vector <double> Data1;
	//vector<double> Data = test.GenerateRandomData(10000, 1, 100);
	/*vector<double> Data;
	Data.push_back(1); Data.push_back(2); Data.push_back(3); Data.push_back(4); Data.push_back(1);*/
	cout << test.CheckSorted(Data);
	start = clock();
	Data1 = HeapSortfaster(Data);
	end = clock();
	cout << test.CheckSorted(Data1);
	//test.PrintData(Data);
	double endtime = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "快速堆排序算法用时" << endtime << "s" << endl;

	cout << test.CheckSorted(Data);
	start = clock();
	Data1 = HeapSortslow(Data);
	end = clock();
	cout << test.CheckSorted(Data1);
	//test.PrintData(Data);
	endtime = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "慢速堆排序算法用时" << endtime << "s" << endl;
}

void testMergeSort(vector<double> Data)
{
	clock_t start, end;
	RandomData test;
	vector <double> Data1;
	//vector<double> Data = test.GenerateRandomData(10000, 1, 100);
	/*vector<double> Data;
	Data.push_back(1); Data.push_back(2); Data.push_back(3); Data.push_back(4); Data.push_back(1);*/
	cout << test.CheckSorted(Data);
	start = clock();
	Data1 = MergeSortRecur(Data,0,Data.size()-1);
	end = clock();
	cout << test.CheckSorted(Data1);
	//test.PrintData(Data);
	double endtime = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "递归实现的归并排序算法用时" << endtime << "s" << endl;

	cout << test.CheckSorted(Data);
	start = clock();
	Data1 = MergeSortNotRecur(Data, 0, Data.size() - 1);
	end = clock();
	cout << test.CheckSorted(Data1);
	//test.PrintData(Data);
	endtime = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "非递归实现的归并排序算法用时" << endtime << "s" << endl;
}

void testQuickSort(vector<double> Data)
{
	clock_t start, end;
	RandomData test;
	vector <double> Data1;
	int cutoff;
	int cishu;
	double endtime;

	cout << test.CheckSorted(Data);
	start = clock();
	cutoff = 800;
	cishu = 1;
	Data1 = QuickSort(Data,0,Data.size()-1, cutoff, cishu);
	end = clock();
	cout << test.CheckSorted(Data1);
	endtime = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "快速排序算法用时" << endtime << "s" << " cutoff："<<cutoff<<" cishu："<<cishu<<endl;

	cout << test.CheckSorted(Data);
	start = clock();
	cutoff = 800;
	cishu = 2;
	Data1 = QuickSort(Data, 0, Data.size() - 1, cutoff, cishu);
	end = clock();
	cout << test.CheckSorted(Data1);
	endtime = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "快速排序算法用时" << endtime << "s" << " cutoff：" << cutoff << " cishu：" << cishu << endl;
	//cout << test.CheckSorted(Data);
	//start = clock();
	//Data1 = MergeSortNotRecur(Data);
	//end = clock();
	//cout << test.CheckSorted(Data1);
	////test.PrintData(Data);
	//endtime = (double)(end - start) / CLOCKS_PER_SEC;
	//cout << "非递归实现的归并排序算法用时" << endtime << "s" << endl;
}

int main()
{ 
	RandomData test;

	vector<double> Data = test.GenerateRandomData(150000, -10, 10);
	cout << "排序元素个数:" << Data.size() << endl;
	/*for (int i = 0; i < 500; i++)
	{
		Data.push_back(43.2);
	}*/
	testCPPSTDSort(Data);
	/*testBubbleSort(Data);
	testInsertionSort(Data);*/
	testShellSort(Data);
	testHeapSort(Data);
	testMergeSort(Data);
	testQuickSort(Data);
	system("pause");


}