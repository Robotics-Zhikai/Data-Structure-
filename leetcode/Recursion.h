#pragma once
/*
��ָ Offer 10- I. 쳲���������
дһ������������ n ����쳲�������Fibonacci�����еĵ� n ��� F(N)����쳲��������еĶ������£�

F(0) = 0,   F(1) = 1
F(N) = F(N - 1) + F(N - 2), ���� N > 1.
쳲����������� 0 �� 1 ��ʼ��֮���쳲�������������֮ǰ��������Ӷ��ó���

����Ҫȡģ 1e9+7��1000000007����������ʼ���Ϊ��1000000008���뷵�� 1��

*/
class SolutionOffer10 {
public:
	const int C = 1000000007;
	int recur(int n) {
		if (n == 0)
			return 0;
		if (n == 1)
			return 1;
		return (recur(n - 1) + recur(n - 2));
	}//ֱ�ӳ�ʱ
	int iterate(int n) {
		if (n == 0)
			return 0;
		if (n == 1)
			return 1;
		int F0 = 0;
		int F1 = 1;
		int F2 = F0 + F1;
		for (int i = 3; i <= n; i++) {
			F0 = F1;
			F1 = F2;
			F2 = ((F0%C) + (F1%C)) % C;
		}
		return F2;
	}
	int fib(int n) {
		return iterate(n);
		// return recur(n)%(int)(pow(10,9)+7);
	}
};