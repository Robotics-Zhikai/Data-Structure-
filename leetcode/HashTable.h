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



