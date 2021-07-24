#pragma once
#include "main.h"

/*
��ָ Offer 45. �������ų���С����
����һ���Ǹ��������飬����������������ƴ�������ų�һ��������ӡ��ƴ�ӳ���������������С��һ����
https://leetcode-cn.com/problems/ba-shu-zu-pai-cheng-zui-xiao-de-shu-lcof/solution/tu-jie-wo-men-zhi-qian-ke-neng-mei-you-g-gcr3/
����һ����ϸ��֤��
���������˴����Ժͷ�֤��
AB<BA BC<CB ��AC<CA ����������ԣ���֪���зǴ�С����˳�����е��ַ�������˳�����е��ַ������������
*/
class SolutionOffer45 {
public:
	bool compareSmaller(string stra, string strb)
	{
		//string stra = to_string(a); //����ת�ַ���
		//string strb = to_string(b);
		string apb = stra + strb;
		string bpa = strb + stra;
		//unsigned long numapb = stoul(apb); //�ַ���ת����
		//unsigned long numbpa = stoul(bpa);
		if (apb<bpa) //�ֵ�����бȽ�
			return 1;
		else
			return 0;
	}
	string minNumber(vector<int>& nums) //����˼·�����¶���һ���Ƚϴ�С�Ļ���
	{
		vector<string> numsStr;
		for (int i = 0; i<nums.size(); i++)
			numsStr.push_back(to_string(nums[i]));
		sort(numsStr.begin(), numsStr.end(),
			[this](string a, string b)->bool {return compareSmaller(a, b); });
		//ע��lambda��Ҫ����this  �������Ҫ��compareSmaller���ó�static
		string result = "";
		for (int i = 0; i<numsStr.size(); i++)
			result += numsStr[i];
		return result;
	}
};

/*
406. ��������ؽ�����
�����д���˳���һȺ��վ��һ�����У����� people ��ʾ������һЩ�˵����ԣ���һ����˳�򣩡�
ÿ�� people[i] = [hi, ki] ��ʾ�� i ���˵����Ϊ hi ��ǰ�� ���� �� ki ����ߴ��ڻ���� hi ���ˡ�

�������¹��첢������������ people ����ʾ�Ķ��С�
���صĶ���Ӧ�ø�ʽ��Ϊ���� queue ������ queue[j] = [hj, kj] �Ƕ����е� j ���˵����ԣ�queue[0] �����ڶ���ǰ����ˣ���

*/

//�漰�����������⣬��Ҫע��Ҫ�����ն���ؼ���˳���������ķ������˼��
class Solution406 {
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        sort(people.begin(),people.end(),[](vector<int>&a,vector<int>&b)->bool
        {
            return a[0]>b[0] || (a[0]==b[0]&&a[1]<b[1]);
        }); 
        //һ��Ҫע�⵱a[0]==b[0]ʱ��kС�ķ���ǰ��
        //�����һ����k��һ����ʱ��Ʃ��[5,2]��[5,3], ���������������飬
		//[5,2]��Ȼ��[5,3]��ǰ�档�������������ʱ��[5,3]��ǰ�棬�����Ȳ����꣬
		//���ʱ����ǰ�����3�����ڵ�����������ԣ�������[5,2]��ʱ��
		//����Ȼ�ֻ����[5,3]ǰ�棨��Ϊ���������������Ϊ2�ĵط��������ʱ��[5,3]ǰ��ͻ���4�����ڵ�������������ˣ������ͻ����
        vector<vector<int>> res;
        for(auto&person:people){
            res.insert(res.begin()+person[1],person); //�ɴ˿ɼ�insert��һ����Ҫ��������Ԫ�ص�ʱ�����
        } //Ȼ�����β���Ϳ���
        return res;
    }
};