#pragma once
#include "main.h"
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


/*
��ָ Offer 33. �����������ĺ����������
����һ���������飬�жϸ������ǲ���ĳ�����������ĺ�����������������򷵻� true�����򷵻� false���������������������������ֶ�������ͬ��
*/
class SolutionOffer33 {
public:
    bool recur(vector<int> & postorder,int L,int R) //�ж���[L,R)��Χ��Ԫ���Ƿ���Ϻ������
    { //Ҫ������ö�����������һ��������[L,R)�����з�Χ�ڣ���ҵ��Ǹ��ڵ㣬Ȼ��������ǰ�ж��ҵ�С��postorder[R-1]�ĵ�
        if (R-L==1 || R-L==0 || R-L==2 ) //��������Щʱ�϶�����ȷ��
            return 1;
        
        int i;
        for(i = R-2;i>=L;i--){
            if (postorder[i]<postorder[R-1])
                break;
        }
        for(int j = i;j>=L;j--){
            if (postorder[j]>postorder[R-1]) //����֮ǰ��Ȼ����postorder[R-1]�������˵��boolΪ0
                return 0;
        }
        if (i<L)
            return recur(postorder,L,R-1);
        else
            return recur(postorder,L,i+1)&&recur(postorder,i+1,R-1);
    }
    //����ջO(n)���Ӷȵķ�����https://leetcode-cn.com/problems/er-cha-sou-suo-shu-de-hou-xu-bian-li-xu-lie-lcof/solution/di-gui-he-zhan-liang-chong-fang-shi-jie-jue-zui-ha/
    bool verifyPostorder(vector<int>& postorder) {
        return recur(postorder,0,postorder.size()); //�ݹ鷽ʽ����ʱ�����뵽 �õ���ջ�ķ�ʽ��̫�����뵽
        //�ݹ鷽ʽ����������Եõ����Ӷ���nlogn���������������ʱ���Ӷ���n^2
    }
};


/*
2. �������
�������� �ǿ� ��������ʾ�����Ǹ�������������ÿλ���ֶ��ǰ��� ���� �ķ�ʽ�洢�ģ�����ÿ���ڵ�ֻ�ܴ洢 һλ ���֡�

���㽫��������ӣ�������ͬ��ʽ����һ����ʾ�͵�����

����Լ���������� 0 ֮�⣬���������������� 0 ��ͷ��



*/

//�����Ȼ�ǵݹ��д���򵥲��׳���
//  Definition for singly-linked list.
 struct ListNode {
     int val;
     ListNode *next;
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
 };
 
class Solution2 {
public:
    ListNode* solveMethod1(ListNode* l1,ListNode* l2){
        //���д�����ظ����룬���Ǻܺ�
        ListNode* cur1 = l1;
        ListNode* cur2 = l2;
        ListNode* curres = nullptr;
        ListNode* res = nullptr;
        int step = 0;
        while(cur1!=nullptr && cur2!=nullptr){
            int sum = cur1->val+cur2->val+step;
            int cur = 0;
            if (sum>=10){
                cur = sum-10;
                step = 1;
            }
            else{
                cur = sum;
                step = 0;
            }
            ListNode* newNode = new ListNode(cur);
            if (curres!=nullptr){
                curres->next = newNode;
            }
            else{
                res = newNode;
            }
            curres = newNode;
            cur1 = cur1->next;
            cur2 = cur2->next;
        }
        if (cur1!=cur2){
            ListNode* curfinal = (cur1==nullptr)?cur2:cur1;
            while(curfinal!=nullptr){
                int sum = curfinal->val+step;
                int cur = 0;
                if (sum>=10){
                    cur = sum-10;
                    step = 1;
                }
                else{
                    cur = sum;
                    step = 0;
                }
                ListNode* newNode = new ListNode(cur);
                if (curres!=nullptr){
                    curres->next = newNode;
                }
                curres = newNode;
                curfinal = curfinal->next;
            }
        }
        if (step==1){ //����������λ��������д����
            if (curres!=nullptr)
                curres->next = new ListNode(step);
            else
                res = new ListNode(step);
        }
        return res;
    }
    ListNode* solveMethod2(ListNode* l1,ListNode* l2){
        //�ϲ���һ�𣬴���д�Ĳ�����
        ListNode* cur1 = l1;
        ListNode* cur2 = l2;
        ListNode* curres = nullptr;
        ListNode* res = nullptr;
        int step = 0;
        while(cur1!=nullptr || cur2!=nullptr){
            int sum = 0;
            if (cur1!=nullptr&&cur2!=nullptr){
                sum = cur1->val+cur2->val+step;
            }
            else if (cur1!=nullptr){
                sum = cur1->val+step;
            }
            else if (cur2!=nullptr){
                sum = cur2->val+step;
            }
            int cur = 0;
            if (sum>=10){
                cur = sum-10;
                step = 1;
            }
            else{
                cur = sum;
                step = 0;
            }
            ListNode* newNode = new ListNode(cur);
            if (curres!=nullptr){
                curres->next = newNode;
            }
            else{
                res = newNode;
            }
            curres = newNode;
            if (cur1!=nullptr)
                cur1 = cur1->next;
            if (cur2!=nullptr)
                cur2 = cur2->next;
        }
        if (step==1){ //����������λ��������д����
            if (curres!=nullptr)
                curres->next = new ListNode(step);
            else
                res = new ListNode(step);
        }
        return res;
    }
    ListNode* solveMethod3(ListNode* l1,ListNode* l2, int step){ 
        //�õݹ�ķ�ʽ�������
        if (l1==nullptr && l2==nullptr && step==0)
            return nullptr;
        int sum = step;
        if (l1!=nullptr){
            sum += l1->val;
        }
        if (l2!=nullptr){
            sum += l2->val;
        }
        int cur = 0;
        if (sum>=10){
            cur = sum-10;
            step = 1;
        }
        else{
            cur = sum;
            step = 0;
        }
        ListNode* now = new ListNode(cur);
        now->next = solveMethod3(l1==nullptr?l1:l1->next,l2==nullptr?l2:l2->next,step);
        return now;
    }
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        return solveMethod3(l1,l2,0);
        return solveMethod2(l1,l2);
    }
};


/*
394. �ַ�������
����һ������������ַ������������������ַ�����

�������Ϊ: k[encoded_string]����ʾ���з������ڲ��� encoded_string �����ظ� k �Ρ�ע�� k ��֤Ϊ��������

�������Ϊ�����ַ���������Ч�ģ������ַ�����û�ж���Ŀո�������ķ��������Ƿ��ϸ�ʽҪ��ġ�

���⣬�������Ϊԭʼ���ݲ��������֣����е�����ֻ��ʾ�ظ��Ĵ��� k �����粻������� 3a �� 2[4] �����롣
 
*/

class Solution394 {
public:
    bool isNum(char c){
        if (c>='0' && c<='9')
            return true;
        else
            return false;
    }
    string solveMethod1(string s){
        //�ǵݹ鷽���õ��� �����뵽 ����Ҳ���׳���
        string sta;
        stack<char> tmp;
        stack<char> numtmp;
        for (int i = 0;i<s.size();i++){
            char cur = s[i];
            sta.push_back(s[i]);
            if (cur==']'){
                do{
                    if (sta.back()!=']' && sta.back()!='['){
                        tmp.push(sta.back());
                    }
                    sta.pop_back();
                }while(!sta.empty() && !isNum(sta.back()));

                while(!sta.empty() && isNum(sta.back())){
                    numtmp.push(sta.back());
                    sta.pop_back();
                }
                string NUM = "";
                while(!numtmp.empty()){
                    NUM.push_back(numtmp.top());
                    numtmp.pop();
                }
                int times = atoi(NUM.c_str()); //�������׳������׺��Ե����������ɶ�λ���

                string storage = "";
                while(!tmp.empty()){
                    storage.push_back(tmp.top());
                    tmp.pop();
                }
                for (int t = 0;t<times;t++){
                    sta= sta+storage;
                }
            }
        }
        return sta;
    }
    int index = 0;
    
    string solveMethod2(string & s){
        //�õݹ�ķ�ʽʵ�֣�ע�����ȥ�Ǹ�index�����ó��󵽵ݹ���ʽ������ิϰһ�£���
        string res;
        int times = 0;
        while(index<s.size()){
            if (isNum(s[index])){
                times = 10 * times + (s[index]-'0') ;
            }
            else if (!isNum(s[index])&&s[index]!='['&&s[index]!=']'){
                res.push_back(s[index]);
            }
            else if (s[index]=='['){
                index++;
                string tmp = solveMethod2(s);
                for(int i = 0;i<times;i++){
                    res+=tmp;
                }
                times = 0;
            }
            else if (s[index]==']'){
                break;
            }
            index++;
        }
        return res;
    }

    string review(string s){
        stack<char> Sta;
        stack<char> Statmp;
        for(char c:s){
            if (c!=']'){
                Sta.push(c);
            }
            else{
                while(Sta.top()!='['){
                    Statmp.push(Sta.top());
                    Sta.pop();
                }
                Sta.pop(); //����'['

                string NUMstr;
                while(!Sta.empty() && Sta.top()>='0' && Sta.top()<='9'){
                    NUMstr.push_back(Sta.top());
                    Sta.pop();
                }
                reverse(NUMstr.begin(),NUMstr.end());
                int num = atoi(NUMstr.c_str());//�����ظ�����

                string strtmp;
                while(!Statmp.empty()){
                    strtmp.push_back(Statmp.top());
                    Statmp.pop();
                }
                for(int i = 0;i<num;i++){
                    for(char c1:strtmp){
                        Sta.push(c1);
                    }
                }
            }
        }
        while(!Sta.empty()){
            Statmp.push(Sta.top());
            Sta.pop();
        }
        string res;
        while(!Statmp.empty()){
            res.push_back(Statmp.top());
            Statmp.pop();
        }
        return res;
    }
    
    string decodeString(string s) {
        return solveMethod2(s);
    }
};

/*
��ָ Offer 64. ��1+2+��+n
�� 1+2+...+n ��Ҫ����ʹ�ó˳�����for��while��if��else��switch��case�ȹؼ��ּ������ж���䣨A?B:C����


*/
class SolutionOffer64 {
public:
    int res = 0;
    int sumNums(int n) {
        bool x = (n>1) && sumNums(n-1); //��·ЧӦ &&�ŵ����Ϊ��ʱ��Ҫ�жϺ�ߵ� Ϊ��ʱ�Ͳ��жϺ�ߵ���
        res+=n;
        return res;
    }
};