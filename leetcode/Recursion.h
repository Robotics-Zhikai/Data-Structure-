#pragma once
#include "main.h"
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


/*
剑指 Offer 33. 二叉搜索树的后序遍历序列
输入一个整数数组，判断该数组是不是某二叉搜索树的后序遍历结果。如果是则返回 true，否则返回 false。假设输入的数组的任意两个数字都互不相同。
*/
class SolutionOffer33 {
public:
    bool recur(vector<int> & postorder,int L,int R) //判断在[L,R)范围的元素是否符合后序遍历
    { //要充分利用二叉搜索树这一条件，在[L,R)的序列范围内，最靠右的是根节点，然后从最靠右往前判断找到小于postorder[R-1]的点
        if (R-L==1 || R-L==0 || R-L==2 ) //当等于这些时肯定是正确的
            return 1;
        
        int i;
        for(i = R-2;i>=L;i--){
            if (postorder[i]<postorder[R-1])
                break;
        }
        for(int j = i;j>=L;j--){
            if (postorder[j]>postorder[R-1]) //在这之前必然大于postorder[R-1]，否则就说明bool为0
                return 0;
        }
        if (i<L)
            return recur(postorder,L,R-1);
        else
            return recur(postorder,L,i+1)&&recur(postorder,i+1,R-1);
    }
    //单调栈O(n)复杂度的方法见https://leetcode-cn.com/problems/er-cha-sou-suo-shu-de-hou-xu-bian-li-xu-lie-lcof/solution/di-gui-he-zhan-liang-chong-fang-shi-jie-jue-zui-ha/
    bool verifyPostorder(vector<int>& postorder) {
        return recur(postorder,0,postorder.size()); //递归方式面试时容易想到 用单调栈的方式不太容易想到
        //递归方式用主定理可以得到复杂度是nlogn，但是在糟糕的情况时复杂度是n^2
    }
};


/*
2. 两数相加
给你两个 非空 的链表，表示两个非负的整数。它们每位数字都是按照 逆序 的方式存储的，并且每个节点只能存储 一位 数字。

请你将两个数相加，并以相同形式返回一个表示和的链表。

你可以假设除了数字 0 之外，这两个数都不会以 0 开头。



*/