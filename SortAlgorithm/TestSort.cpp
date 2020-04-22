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
	Data = InsertionSort(Data);
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

int main()
{ 
	RandomData test;
	vector<double> Data = test.GenerateRandomData(1000, 1, 100);
	for (int i = 0; i < 500; i++)
	{
		Data.push_back(43.2);
	}
	testCPPSTDSort(Data);
	testBubbleSort(Data);
	testInsertionSort(Data);
	testShellSort(Data);


	system("pause");


}