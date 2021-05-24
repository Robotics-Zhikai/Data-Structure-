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

/*
��ָ Offer 16. ��ֵ�������η�
ʵ�� pow(x, n) �������� x �� n ���ݺ���������xn��������ʹ�ÿ⺯����ͬʱ����Ҫ���Ǵ������⡣

*/

class SolutionOffer16 {
public:
    double recur(double x,long n)
    {
        if (n==1)
            return x;
        if (n==0 || x==1)
            return 1;
        double tmp = recur(x,n/2); //���������֪ʱ�临�Ӷ���logn
        if (n%2==0)
            return tmp*tmp;
        else
            return tmp*tmp*x;
    }
    double myPowRecur(double x,int n) //�ݹ鷽����
    {
        if(x==0)
            return 0;
        if (n<0)
            // return 1/recur(x,-n); //ע��int�ĵ�һλ�Ƿ���λ�� ����������ȡֵ��Χ���Գƣ���n=-2^31ʱ��-n�Ե���-2^31
            return recur(1/x,-(long)n);
        else
            return recur(x,n);
    }

    double myPowIterate(double x,int n) //����������
    {
        //��nΪż����x^n=(x^2)^(n/2)=(x^4)^(n/4)=...
        //��nΪ������x^n=x*(x^2)^(n/2)
        if(x == 0) return 0;
        long absn = n;
        if (n<0){
            absn = -(long)n;
            x = 1/x;
        }
        
        double res = 1;
        double curx = x;
        while(absn>0){
            if (absn&1){ //˵����ʱn������ ���һ�ε����϶�������
                res *= curx; //curx���ǰ�x^n=x*(x^2)^(n/2)��һ�ε���������ߵ�x������
            }
            curx = curx*curx;
            absn>>=1; //absn/2 logn�ĸ��Ӷ�
        }
        return res;
    }

    double myPow(double x, int n) {
        // return myPowRecur(x,n); //�õݹ�ķ����ռ临�Ӷ���O(n)
        return myPowIterate(x,n); //�õ��������Ŀռ临�Ӷ���O(1)
        //���������Ƚ���д����������������������������������������������
        //�ݹ鷽���ܺ�д
    }
};