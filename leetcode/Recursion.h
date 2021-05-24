#pragma once
/*
剑指 Offer 10- I. 斐波那契数列
写一个函数，输入 n ，求斐波那契（Fibonacci）数列的第 n 项（即 F(N)）。斐波那契数列的定义如下：

F(0) = 0,   F(1) = 1
F(N) = F(N - 1) + F(N - 2), 其中 N > 1.
斐波那契数列由 0 和 1 开始，之后的斐波那契数就是由之前的两数相加而得出。

答案需要取模 1e9+7（1000000007），如计算初始结果为：1000000008，请返回 1。

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
	}//直接超时
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
剑指 Offer 16. 数值的整数次方
实现 pow(x, n) ，即计算 x 的 n 次幂函数（即，xn）。不得使用库函数，同时不需要考虑大数问题。

*/

class SolutionOffer16 {
public:
    double recur(double x,long n)
    {
        if (n==1)
            return x;
        if (n==0 || x==1)
            return 1;
        double tmp = recur(x,n/2); //用主定理可知时间复杂度是logn
        if (n%2==0)
            return tmp*tmp;
        else
            return tmp*tmp*x;
    }
    double myPowRecur(double x,int n) //递归方法做
    {
        if(x==0)
            return 0;
        if (n<0)
            // return 1/recur(x,-n); //注意int的第一位是符号位， 导致了正负取值范围不对称，当n=-2^31时，-n仍等于-2^31
            return recur(1/x,-(long)n);
        else
            return recur(x,n);
    }

    double myPowIterate(double x,int n) //迭代方法做
    {
        //当n为偶数，x^n=(x^2)^(n/2)=(x^4)^(n/4)=...
        //当n为奇数，x^n=x*(x^2)^(n/2)
        if(x == 0) return 0;
        long absn = n;
        if (n<0){
            absn = -(long)n;
            x = 1/x;
        }
        
        double res = 1;
        double curx = x;
        while(absn>0){
            if (absn&1){ //说明此时n是奇数 最后一次迭代肯定是奇数
                res *= curx; //curx就是把x^n=x*(x^2)^(n/2)上一次迭代括号里边的x剥出来
            }
            curx = curx*curx;
            absn>>=1; //absn/2 logn的复杂度
        }
        return res;
    }

    double myPow(double x, int n) {
        // return myPowRecur(x,n); //用递归的方法空间复杂度是O(n)
        return myPowIterate(x,n); //用迭代方法的空间复杂度是O(1)
        //迭代方法比较难写！！！！！！！！！！！！！！！！！！！！！！！
        //递归方法很好写
    }
};