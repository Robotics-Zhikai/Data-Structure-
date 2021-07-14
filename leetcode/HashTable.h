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