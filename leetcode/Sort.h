#pragma once
#include "main.h"

/*
��ָ Offer 45. �������ų���С����
����һ���Ǹ��������飬����������������ƴ�������ų�һ��������ӡ��ƴ�ӳ���������������С��һ����
https://leetcode-cn.com/problems/ba-shu-zu-pai-cheng-zui-xiao-de-shu-lcof/solution/tu-jie-wo-men-zhi-qian-ke-neng-mei-you-g-gcr3/
����һ����ϸ��֤��
���������˴����Ժͷ�֤��
AB<BA BC<CB ��AC<CA ����������ԣ���֪���зǴ�С����˳�����е��ַ�������˳�����е��ַ�������������
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