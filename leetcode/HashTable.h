#pragma once
#include "main.h"

/*
��ָ Offer 48. ������ظ��ַ������ַ���
����ַ������ҳ�һ����Ĳ������ظ��ַ������ַ��������������ַ����ĳ��ȡ�

*/
class SolutionOffer48 {
public:
	int lengthOfLongestSubstringUnorderedMap(string s)
	{
		int maxLen = 0;
		int curmaxlen = 0;
		unordered_map<char, int> mapping;
		for (int i = 0; i<s.size(); i++)
		{
			char cur = s[i];
			if (mapping.find(cur) == mapping.end()) //û�ҵ�
			{
				mapping[cur] = i;
				curmaxlen++;
			}
			else  //�ҵ���
			{
				if (i - mapping[cur]>curmaxlen)
				{
					curmaxlen++;
				}
				else
				{
					curmaxlen = i - mapping[cur];
				}
				mapping[cur] = i;
			}
			if (curmaxlen>maxLen)
				maxLen = curmaxlen;
		}
		return maxLen;
	}
	int lengthOfLongestSubstringChararray(string s)
		//Ҳ�õ��˵㻬�����ڵ�˼��
	{
		int maxLen = 0;
		int curmaxlen = 0;
		int mapping[128]; //ASCII��һ����128�� ��ϣ����Ҫ�������ڳ���ʱ�����ж��Ƿ�ǰ����ִ����ظ�����ĸ
						  //����������ɨ��Ļ�����O(n)�ĸ��Ӷ����ж��Ƿ����ظ�
		memset(mapping, -1, sizeof(mapping));
		for (int i = 0; i<s.size(); i++)
		{
			char cur = s[i];
			if (mapping[cur] == -1) //û�ҵ�
			{
				mapping[cur] = i;
				curmaxlen++; //curmaxlen��ʵ���ǻ������ڵĴ�С
			}
			else  //�ҵ���
			{
				if (i - mapping[cur]>curmaxlen)
				{
					curmaxlen++;
				}
				else
				{
					curmaxlen = i - mapping[cur]; //�ظ�Ԫ�������˻�������֮�ڣ���С��������
				}
				mapping[cur] = i;
			}
			if (curmaxlen>maxLen)
				maxLen = curmaxlen;
		}
		return maxLen;
	}
	int lengthOfLongestSubstring(string s) {
		//return lengthOfLongestSubstringUnorderedMap(s);//12ms 8MB 73.59% 68.24%
		return lengthOfLongestSubstringChararray(s);//��Hash�������unorderedmap�Ļ���4ms 7MB 96.97% 80.79% 
													//�ռ临�Ӷ��иĽ���ʱ�临�Ӷ���ͬ������O(n)
	}
};


/*
1. ����֮��
����һ���������� nums ��һ������Ŀ��ֵ target�������ڸ��������ҳ� ��ΪĿ��ֵ target  ���� ���� ���������������ǵ������±ꡣ

����Լ���ÿ������ֻ���Ӧһ���𰸡����ǣ�������ͬһ��Ԫ���ڴ��ﲻ���ظ����֡�

����԰�����˳�򷵻ش𰸡�

*/
class Solution1 {
public:
    vector<int> solveMethod1Review(vector<int>& nums, int target){
        vector<vector<int>> numsindex;
        for(int i = 0;i<nums.size();i++){
            numsindex.push_back(vector<int>{nums[i],i});
        }
        sort(numsindex.begin(),numsindex.end(),[](vector<int>&a,vector<int>&b)->bool{return a[0]<b[0];});
        int left = 0;
        int right = nums.size()-1;
        vector<int > res;
        while(left<right){
            if (numsindex[left][0]+numsindex[right][0]<target){
                do{
                    left++;
                }while(left<numsindex.size() && numsindex[left][0]==numsindex[left-1][0]);
            }
            else if (numsindex[left][0]+numsindex[right][0]>target){
                do{
                    right--;
                }while(right>=0 && numsindex[right][0]==numsindex[right+1][0]);
            }
            else{
                res = vector<int>{numsindex[left][1],numsindex[right][1]};
                do{
                    left++;
                }while(left<numsindex.size() && numsindex[left][0]==numsindex[left-1][0]);
                do{
                    right--;
                }while(right>=0 && numsindex[right][0]==numsindex[right+1][0]);
            }
        }

        return res;
    }
    vector<int> solveMethod1(vector<int>& nums, int target){
        //�������nlogn��ʱ�临�Ӷȣ�n�Ŀռ临�Ӷ�
        //������֮���õ��ķ������
        int left = 0;
        int right = nums.size()-1;
        vector<vector<int>> copynums;
        for (int i = 0;i<nums.size();i++){
            copynums.push_back({i,nums[i]});
        }
        sort(copynums.begin(),copynums.end(),[](vector<int>&a,vector<int>&b){return a[1]<b[1];});
        while(left<right){
            int cur = copynums[left][1]+copynums[right][1];
            if (cur>target){
                do{
                    right--;
                }while(right>=0 && copynums[right][1]==copynums[right+1][1]);
            }
            else if (cur<target){
                do{
                    left++;
                }while(left<copynums.size() && copynums[left][1]==copynums[left-1][1]);
            }
            else{
                return {copynums[left][0],copynums[right][0]};
            }
        }
        return {};
    }
    vector<int> solveMethod2(vector<int>& nums, int target){
        unordered_map<int,int> MAP;
        for(int i = 0;i<nums.size();i++){
            MAP.insert({nums[i],i});
        }
        for(int i = 0;i<nums.size();i++){
            auto right = MAP.find(target-nums[i]);
            if (right != MAP.end() ){
                if (right->second==i)
                    continue;
                return {i,right->second};
            }
        }
        return {};
    }
    vector<int> solveMethod2Review(vector<int>&nums,int target){
        map<int,int> MAP;
        for(int i = 0;i<nums.size();i++){
            MAP[nums[i]] = i;
        }
        for(int i = 0;i<nums.size();i++){
            if (MAP.find(target-nums[i])!=MAP.end() && MAP[target-nums[i]]!=i){
                return vector<int>{i,MAP[target-nums[i]]};
            }
        }
        return {};
    }

    vector<int> solveMethod3(vector<int>& nums, int target){
        //����֮�Ϳ϶����������������±ߵķ������
        unordered_map<int,int> MAP;
        for (int i = 0;i<nums.size();i++){
            auto Find = MAP.find(target-nums[i]);
            if (Find!=MAP.end()){
                return {Find->second,i};
            }
            MAP[nums[i]] = i;
        }
        return {};
    }
    //���HASH��ʵ������д����Ҫ��д������������
    vector<int> twoSum(vector<int>& nums, int target) {
        return solveMethod3(nums,target);
        return solveMethod2(nums,target);
    }
};



/*
560. ��ΪK��������
����һ�����������һ������ k������Ҫ�ҵ��������к�Ϊ k ��������������ĸ�����

ʾ�� 1 :

����:nums = [1,1,1], k = 2
���: 2 , [1,1] �� [1,1] Ϊ���ֲ�ͬ�������
˵�� :

����ĳ���Ϊ [1, 20,000]��
������Ԫ�صķ�Χ�� [-1000, 1000] �������� k �ķ�Χ�� [-1e7, 1e7]��


*/

class Solution560 {
public:
    // int subarraySum(vector<int>& nums, int k) { //�����˫ָ��ֻⷨ����nums�϶������ʱ��ſ���
	// 	sort(nums.begin(),nums.end());
	// 	int Lindex = 0;
	// 	int Rindex = 0;
	// 	int cur = 0;
	// 	int res = 0;

	// 	do{
	// 		while(Rindex<nums.size()){
	// 			cur+=nums[Rindex++];
	// 			if (cur>=k){
	// 				break;
	// 			}
	// 		}
	// 		if (cur==k){
	// 			res++;
	// 		}
	// 		while(Lindex<Rindex){
	// 			cur-=nums[Lindex++];
	// 			if (cur<=k){
	// 				break;
	// 			}
	// 		}
	// 		if (cur==k){
	// 			res++;
	// 		}
	// 	}while(Rindex!=nums.size());
	// 	return res;
    // }
	int solveMethod1(vector<int>& nums,int k){
		//n^2��ʱ�临�Ӷ� �ֳ�ʱ��
		vector<int> acc(nums.size()+1,0); //��
		acc[0] = 0;
		for(int i = 1;i<acc.size();i++){
			acc[i] = acc[i-1]+nums[i-1];
		}
		int res = 0;
		for(int i = 0;i<=nums.size();i++){
			for(int j = i+1;j<=nums.size();j++){
				if (acc[j]-acc[i]==k){
					res++;
				}
			}
		}
		return res;
	}
	int solveMethod2(vector<int>& nums,int k){
		//���Ҳ̫��д�ˡ�����������������
		int acc = 0;
		map<int,int> MAP; //��ʾ��Ӧ��ĳһ��ֵ��������ж�����
		int res = 0;
		for (int i = 0;i<nums.size();i++){
			acc += nums[i];
			if (acc==k){
				res++;
			}

            if (MAP.find(acc-k)!=MAP.end()){
                res+=MAP[acc-k];
            } //������if�ǳ���д
			
			MAP[acc]++;
		}
		return res;
	}
	int subarraySum(vector<int>& nums, int k) {
		return solveMethod2(nums,k);
	}
};


//437���ϱߵ�560�ǲ���
/*
437. ·���ܺ� III
����һ��������������ÿ����㶼�����һ������ֵ��

�ҳ�·���͵��ڸ�����ֵ��·��������

·������Ҫ�Ӹ��ڵ㿪ʼ��Ҳ����Ҫ��Ҷ�ӽڵ����������·��������������µģ�ֻ�ܴӸ��ڵ㵽�ӽڵ㣩��

������������1000���ڵ㣬�ҽڵ���ֵ��Χ�� [-1000000,1000000] ��������

*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution437 {
public:
    void DFS(TreeNode* root,int& targetSum,int & curSum){
		if (root==nullptr){
			return ;
		}
		curSum += root->val;
        if (curSum == targetSum){
            res++;
        }
		DFS(root->left,targetSum,curSum);
        curSum -= root->left==nullptr?0:root->left->val;
		DFS(root->right,targetSum,curSum);
        curSum -= root->right==nullptr?0:root->right->val;
	}
	int res = 0;
    int solveMethod1(TreeNode* root,int targetSum){
        //�����O(n^2)�ĸ��Ӷ�
        if(root == nullptr){
            return 0;
        }
        int curSum = 0;
		DFS(root,targetSum,curSum);
        pathSum(root->left,targetSum);
		pathSum(root->right,targetSum);
		return res;
    }
    void DFS(map<int,int>&MAP,TreeNode* root,int targetSum,int& curSum){
        if (root==nullptr){
            return;
        }

        curSum+=root->val;
        if (curSum == targetSum){
            res++;
        }
		if (MAP.find(curSum-targetSum)!=MAP.end()){
			res+=MAP[curSum-targetSum];
		}
        MAP[curSum]++;
        DFS(MAP,root->left,targetSum,curSum);
        if (root->left!=nullptr)
            MAP[curSum]--;
        curSum -= root->left==nullptr?0:root->left->val;
		
        DFS(MAP,root->right,targetSum,curSum);
        if (root->right!=nullptr)
            MAP[curSum]--;
        curSum -= root->right==nullptr?0:root->right->val;
		

    }
    int solveMethod2(TreeNode* root,int targetSum){
        //����ǰ׺�ͣ����������Ͻ���ǰ׺����һ����
        //�����Ļ���ֱ�ӽ�����N�ĸ��Ӷ�
		map<int,int> MAP;
		int curSum = 0;
		DFS(MAP,root,targetSum,curSum);
		return res;
    }
    int pathSum(TreeNode* root, int targetSum) {
        return solveMethod2(root,targetSum);
    }
};

/*
438. �ҵ��ַ�����������ĸ��λ��
���������ַ��� s �� p���ҵ� s ������ p �� ��λ�� ���Ӵ���������Щ�Ӵ�����ʼ�����������Ǵ������˳��

��λ�� ָ��ĸ��ͬ�������в�ͬ���ַ�����

*/
class Solution438 {
public:
    bool match(string&s1,string&s2,vector<bool>&isvist,int index2){
        if (index2==s2.size()){
            return 1;
        }
        for(int i = 0;i<s1.size();i++){
            if (s1[i]==s2[index2] && isvist[i]==0){
                isvist[i] = 1;
                if (match(s1,s2,isvist,index2+1)){
                    return 1;
                }
                else{
                    return 0;
                }
            }
        }
        return 0;
    }
    vector<int> solveMethod1(string s,string p){
        //���ֱ�ӳ�ʱ��
        int sum = 0;
        for(char&c:p){
            sum+=(c-'a');
        }
        if (p.empty())
            return {};
        if (s.size()<p.size()){
            return {};
        }
        int init = -1;
        vector<int> res;
        for(int i = 0;i<=s.size()-p.size();i++){
            if (init==-1){
                init = 0;
                for(int j = 0;j<p.size();j++){
                    init+=(s[j]-'a');
                }
            }
            else{
                init = init-(s[i-1]-'a')+(s[i+p.size()-1]-'a');
            }
            if (init==sum){ //���ܵ������������ĺ��Ƿ����
                string windowstr(s.begin()+i,s.begin()+i+p.size());
                vector<bool> isvist(p.size(),0);
                if (match(windowstr,p,isvist,0)){
                    res.push_back(i);
                }
            }
        }
        return res;
    }
    vector<int> solveMethod2(string s,string p){
        vector<int> freqTarget(26,0); //map
        vector<int> freqCur(26,0);
        for(char c:p){
            freqTarget[c-'a']++;
        }
        if (s.size()<p.size()){
            return {};
        }
        vector<int> res;
        for(int i = 0;i<=s.size()-p.size();i++){
            if (i==0){
                for(int j = 0;j<p.size();j++){
                    freqCur[s[j]-'a']++;
                }
            }
            else{
                freqCur[s[i-1]-'a']--;
                freqCur[s[i+p.size()-1]-'a']++; //����ֱ����hash������DFS�ж��Ƿ�matchЧ�ʸ߶���
            }
            if (freqCur==freqTarget){ //ע������vector����ֱ�ӿ��Ƿ����
                res.push_back(i);
            }
        }
        return res;
    }

    vector<int> findAnagrams(string s, string p) {
        return solveMethod2(s,p);
    }
};

/*
49. ��ĸ��λ�ʷ���
����һ���ַ������飬����ĸ��λ�������һ�𡣿��԰�����˳�򷵻ؽ���б�

��ĸ��λ��ָ��ĸ��ͬ�������в�ͬ���ַ�����


*/

class Solution49 {
public:
    vector<vector<string>> solveMethod1(vector<string>& strs){
        map<vector<int>,vector<string>> MAP;
        for(auto & str:strs){
            vector<int> tmp(26,0);
            for(char c:str){
                tmp[c-'a']++;
            }
            MAP[tmp].push_back(str);
        }
        vector<vector<string>> res;
        for(auto&pair:MAP){
            res.push_back(pair.second);
        }
        return res;
    }
    vector<vector<string>> solveMethod2(vector<string>& strs){
        map<string,vector<string>> MAP;
        for(auto & str:strs){
            string tmp = str;
            sort(tmp.begin(),tmp.end());
            MAP[tmp].push_back(str);
        }
        vector<vector<string>> res;
        for(auto&pair:MAP){
            res.push_back(pair.second);
        }
        return res;
    }
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        return solveMethod2(strs);
    }
};


/*
������3. �������ظ�������
�ҳ��������ظ������֡�

��һ������Ϊ n ������ nums ����������ֶ��� 0��n-1 �ķ�Χ�ڡ�
������ĳЩ�������ظ��ģ�����֪���м��������ظ��ˣ�Ҳ��֪��ÿ�������ظ��˼��Ρ����ҳ�����������һ���ظ������֡�
*/
class SolutionOffer3 {
public:
    int solveMethod1(vector<int>&nums){
        //n��ʱ�临�Ӷȣ�n�Ŀռ临�Ӷ�
        unordered_set<int> SET;
        for(int n:nums){
            if (SET.find(n)==SET.end())
                SET.insert(n);
            else{
                return n;
            }
        }
        return 0;
    }
    int solveMethod2(vector<int>&nums){
        //n��ʱ�临�Ӷȣ�1�Ŀռ临�Ӷ�
        //https://leetcode-cn.com/problems/shu-zu-zhong-zhong-fu-de-shu-zi-lcof/solution/mian-shi-ti-03-shu-zu-zhong-zhong-fu-de-shu-zi-yua/
        int i = 0;
        while(i<nums.size()){
            if (i==nums[i]){
                i++;
                continue;
            }
            if (nums[i]==nums[nums[i]]){
                return nums[i];
            }
            swap(nums[i],nums[nums[i]]);
        }
        return 0;
    }
    int findRepeatNumber(vector<int>& nums) {
        return solveMethod2(nums);
    }
};



/*
554. שǽ
�����ǰ��һ�¾��εġ��� n ��ש����ɵ�שǽ��
��Щש��߶���ͬ��Ҳ����һ����λ�ߣ����ǿ�Ȳ�ͬ��ÿһ��ש��Ŀ��֮����ȡ�

������Ҫ��һ�� �Զ����� �ġ����� ���� ש��Ĵ��ߡ�����㻭����ֻ�Ǵ�ש��ı�Ե�������Ͳ��㴩�����ש��
�㲻������ǽ��������ֱ��Ե֮һ���ߣ�������Ȼ��û�д���һ��ש�ġ�

����һ����ά���� wall ��������������ǽ�������Ϣ�����У�wall[i] ��һ�������������ÿ��ש�Ŀ�ȵ����顣
����Ҫ�ҳ�����������ʹ������ ������ש���������� �����ҷ��� ������ש������ ��


*/
class Solution554 {
public:
    int solveMethod1(vector<vector<int>>& wall){
        //ֱ�ӳ�ʱ�ˣ�Ӧ���м�֦��
        int sumlen = 0;
        for(int e:wall[0]){
            sumlen+=e;
        }
        vector<set<float>> vecSet(wall.size(),set<float>{});
        set<float> bianjie;
        for(int i = 0;i<wall.size();i++){
            set<float> acc;
            float accnum = 0;
            acc.insert(accnum);
            
            for(int j = 0;j<wall[i].size();j++){
                accnum+=wall[i][j];
                acc.insert(accnum);
                bianjie.insert(accnum);
            }
            vecSet[i] = acc;
        }
        int res = INT_MAX;
        for(float j = 0.5;j<sumlen;j=j+0.5){
            int throughCount = 0;
            for(auto & SET:vecSet){
                if (SET.find(j)==SET.end()){
                    throughCount++;
                }
            }
            if (throughCount<res){
                res = throughCount;
            }
        }
        return res;
    }
    int solveMethod2(vector<vector<int>>& wall){
        //��϶���ľ�������ש�����ٵ�
        unordered_map<int,int> MAP;
        int sumlen = 0;
        for(int e:wall[0]){
            sumlen+=e;
        }
        for(int i = 0;i<wall.size();i++){
            int acc = 0;
            for(int j = 0;j<wall[i].size();j++){
                acc+=wall[i][j];
                if (acc!=sumlen)
                    MAP[acc]++;
            }
        }
        int res = INT_MIN;
        for(auto& ele:MAP){
            if (ele.second>res){
                res = ele.second;
            }
        }
        res = wall.size()-res;
        return res<0?wall.size():res;
    }
    int leastBricks(vector<vector<int>>& wall) {
        return solveMethod2(wall);
    }
};


/*
1094. ƴ��
��������һλ˳�糵˾������������� capacity ������λ���������ؿ͡�
���ڵ�·�����ƣ��� ֻ�� ��һ��������ʻ��Ҳ����˵���������ͷ��ı䷽������Խ�������Ϊһ����������

�����һ�ݳ˿��г̼ƻ��� trips[][]������ trips[i] = [num_passengers, start_location, end_location] 
�����˵� i ��˿͵��г���Ϣ��

������͵ĳ˿�������
�˿͵��ϳ��ص㣻
�Լ��˿͵��³��ص㡣
��Щ�����ĵص�λ���Ǵ���� ��ʼ ����λ����ǰ��ʻ����Щ�ص�����ľ��루����һ���������ʻ�����ϣ���

������ݸ������г̼ƻ���ͳ��ӵ���λ�������ж���ĳ��Ƿ����˳����ɽ������г˿͵�����
�����ҽ�������������и������г��н������г˿�ʱ������ true�������뷵�� false����
*/
class Solution1094 {
public:
    bool carPooling(vector<vector<int>>& trips, int capacity) {
        unordered_map<int,int> upPeaple;
        unordered_map<int,int> downPeaple;
        int endloc = INT_MIN;
        for(int i = 0;i<trips.size();i++){
            endloc = max(endloc,trips[i][2]);
            upPeaple[trips[i][1]]+=trips[i][0];
        }
        for(int i = 0;i<trips.size();i++){
            downPeaple[trips[i][2]]+=trips[i][0];
        }
        int curcap = capacity;
        for(int i = 0;i<=endloc;i++){
            curcap = curcap+downPeaple[i];
            if (curcap<upPeaple[i]){
                return false;
            }
            curcap-=upPeaple[i];
        }
        return true;
    }
};


/*
73. ��������
����һ�� m x n �ľ������һ��Ԫ��Ϊ 0 �����������к��е�����Ԫ�ض���Ϊ 0 ����ʹ�� ԭ�� �㷨��

���ף�

һ��ֱ�۵Ľ��������ʹ��  O(mn) �Ķ���ռ䣬���Ⲣ����һ���õĽ��������
һ���򵥵ĸĽ�������ʹ�� O(m + n) �Ķ���ռ䣬������Ȼ������õĽ��������
�������һ����ʹ�ó����ռ�Ľ��������
*/
class Solution73 {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        bool firstcolZero = 0;
        bool firstrowZero = 0;
        for(int i=0;i<matrix.size();i++){
            if (matrix[i][0]==0){
                firstcolZero = 1;
                break;
            }
        }
        for(int j = 0;j<matrix[0].size();j++){
            if (matrix[0][j]==0){
                firstrowZero = 1;
                break;
            }
        }
        for(int i = 1;i<matrix.size();i++){
            for(int j = 1;j<matrix[i].size();j++){
                if (matrix[i][j]==0){
                    matrix[i][0] = 0;//����ĵ�һ�к͵�һ�зֱ����Ƕ�Ӧ���к����Ƿ���0
                    matrix[0][j] = 0;
                }
            }
        }
        for(int i=1;i<matrix.size();i++){
            if (matrix[i][0]==0){
                for(int j = 1;j<matrix[i].size();j++){
                    matrix[i][j] = 0;
                }
            }
        }
        for(int j = 1;j<matrix[0].size();j++){
            if (matrix[0][j]==0){
                for(int i = 1;i<matrix.size();i++){
                    matrix[i][j] = 0;
                }
            }
        }
        if (firstcolZero){
            for(int i = 0;i<matrix.size();i++){
                matrix[i][0] = 0;
            }
        }
        if (firstrowZero){
            for(int j = 0;j<matrix[0].size();j++){
                matrix[0][j] = 0;
            }
        }
    }
};