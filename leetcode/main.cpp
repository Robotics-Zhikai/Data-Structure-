#include "main.h"
#include "DivideAndConquer.h"
#include "DynamicProgramming.h"

void test()
{
	vector<int>(10, 2);
	string te = "125asg";

	string sub = te.substr(1, 3); //注意substr的用法

	vector<int > hafg{ 1,2,3,4 };
	hafg.erase(hafg.begin());
	hafg.insert(hafg.begin() + 1,8);
	vector<int > hafg1 = { hafg.begin(),hafg.end() };
	swap(*hafg.begin(), *(hafg.begin() + 1)); //交换元素时输入参数是引用
	auto lambdaf = [](int a, int b) {return a > b; };
	vector<int> testheap{ 1,2,3,4 };
	make_heap(testheap.begin(), testheap.end());
	if (int(-20))
		cout << "int(-20)" << endl;
	int * tmp = nullptr;
	if (tmp == nullptr)
		cout << "s" << endl;
	vector<int> vectmp = { 1,2,3,4 };
	vector<int> hahaffg(vectmp.begin(), vectmp.begin() + 1);
	list<int> sagg = {1,2,3,4};
	list<int> sgahah(sagg.begin(), sagg.end());
	
	unordered_map<string, int> ag;
	ag["stin"] = 1;
	auto finded = ag.find("stin");
	
}



// using nodetype = pair<char,int> ;
// vector<nodetype> heap;
// int getfather(int index)
// {
//     return index/2;
// }
// int getlchild(int index)
// {
//     return index*2;
// }
// int getrchild(int index)
// {
//     return index*2+1;
// }
// void swap(int l,int r)
// {
//     nodetype tmp = heap[l];
//     heap[l] = heap[r];
//     heap[r] = tmp;
//     if (heap[l].first==heap[r].first)
//     {
//         heap[l].second++;
//         heap[r].second++;
//     }
// }
// void make_heap(const string& in)
// {
//     heap.push_back(make_pair("首元素",0));
//     for(auto it = in.begin();it!=in.end();it++)
//     {
//         heap.push_back(make_pair(*it,0));
//     }
//     //这里不能用堆 但是这里的关于堆的简便写法可以借鉴
// }


int main()
{
	try
	{
		vector<int> saf(10, 1);
		bool s=saf.empty();
		Solution5 Solution5;
		Solution5.test();

		Solution70 Solution70;
		Solution70.test();

		Solution4 Solution4;
		Solution4.test();

		Solution240 Solution240;
		Solution240.test();

		Solution23 Solution23;
		Solution23.test();
		test();

		Solution215 Solution215;
		Solution215.test();
	}
	catch (const std::exception& d)
	{
		cout << d.what() << endl;
	}
	

	system("pause");
}