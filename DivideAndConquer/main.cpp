//����ķ����㷨 �ݳ��㷨

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<math.h>
using namespace std;

class Number
{
public:
	long double AlgorithmSlow(long double Da, _int64 zhishu);
	long double AlgorithmFast(long double Da, _int64 zhishu);
	long double  operator ^(_int64 zhishu)
	{
		return AlgorithmSlow(this->Data, zhishu);
	}
	Number(long double Data)
	{
		Number::Data = Data;
	}
	Number()
	{
		Number::Data = 0;
	}
	void operator = (long double Data)
	{
		Number::Data = Data;
	}
	long double Data;
};
ostream & operator <<(ostream & co, Number n)
{
	co << n.Data;
	return co;
}
long double  Number:: AlgorithmSlow(long double Data, _int64 zhishu)
//O(n)�ĸ��Ӷ�
{
	long double result = 1;
	for (_int64 i = 0; i < zhishu; i++)
	{
		result = result*Data;
		/*if (i%10000000==0)
			cout << i << " " << zhishu <<" "<<result<< endl;*/
	}
	return result;
}

long double AlgorithmFast(long double  Data,_int64 zhishu)
{
	if (zhishu == 0)
		return 1;
	else if (zhishu == 1)
		return Data;
	_int64 next = floor(zhishu / 2.0);
	long double result1;
	result1 = AlgorithmFast(Data, next);
	result1 = result1 * result1;
	if (next + next < zhishu)
		result1 = result1*Data;
	return result1;
}
long double  Number:: AlgorithmFast(long double Data, _int64 zhishu)
//O(n)�ĸ��Ӷ�
{
	long double result = 1;
	for (_int64 i = 0; i < zhishu; i++)
	{
		result = result*Data;
		/*if (i%10000000==0)
		cout << i << " " << zhishu <<" "<<result<< endl;*/
	}
	return result;
}
int main()
{
	clock_t start, end;
	double endtime;
	_int64 zhishu;
	long double result;
	//zhishu = 50051000001;
	zhishu = 151000001;
	//zhishu = 13;

	Number n;
	n = 1.000000001;
	//n = 2;
	
	result = 0;
	start = clock();
	result = powl(n.Data, zhishu);
	end = clock();
	cout << "����" << n << "��" << zhishu << "�η���" << result << endl;
	endtime = double(end - start) / CLOCKS_PER_SEC;
	cout << "math���㷨��ʱ" << endtime << "s" << endl;

	result = 0;
	start = clock();
	result = n ^ zhishu;
	end = clock();
	cout << "����" << n << "��" << zhishu << "�η���" << result << endl;
	endtime = double(end - start) / CLOCKS_PER_SEC;
	cout << "��д�������㷨O(n)��ʱ" << endtime << "s" << endl;

	result = 0;
	start = clock();
	result = AlgorithmFast(n.Data, zhishu);
	end = clock();
	cout << "����" << n << "��" << zhishu << "�η���" << result << endl;
	endtime = double(end - start) / CLOCKS_PER_SEC;
	cout << "���Լ�д�Ŀ����㷨O(logn)��ʱ" << endtime << "s" << endl;

	system("pause");
}