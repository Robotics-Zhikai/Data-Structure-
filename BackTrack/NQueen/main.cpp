#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <queue>
#include <ctime>

using namespace std;

class Nqueen
{
public:
	Nqueen(unsigned int Nin) :N(Nin), FitMap(Nin, vector<bool>(Nin*Nin,1)), RealPos(Nin), Start(clock()){}
	//一开始时所有位置均可放

	void SolutionNqueen(); 
	//递归方法求解
	void SolutionNqueenNotRecur();
	//非递归方法求解
	void SolutionNqueenCSP(); 
	//CSP 最小冲突方法求解N皇后问题
	
private:
	const unsigned int N;
	//N皇后问题
	vector<vector<bool>> FitMap; 
	//可放置皇后的图示意，由某个棋子管辖的地方为1，不管辖的地方为0  满足八皇后约束时，有N层图，每个位置取N个&为1可放，N个&位0不可放
	vector<unsigned int> RealPos;
	//八个皇后的实际位置 编号为0的皇后默认在第0列，编号为1的皇后默认在第一列
	clock_t Start;

	size_t getMapfromPixel2loc(unsigned int x, unsigned int y)const;
	//得到从像素图到fitmap位置的映射
	bool PutInLoc(unsigned int Number,unsigned int x, unsigned int y);
	//放置在x y位置，遵循第一象限，若满足八皇后的限制，则放置成功，并修改Fitmap,否则放置失败,返回false
	void PutInLocIgnoreNqueenConflict(unsigned int Number, unsigned int x, unsigned int y);
	//忽略八皇后的限制，强制放置某皇后到棋盘，但要保证基本的两皇后位置不重叠
	
	void CheckRightPixel(unsigned int x, unsigned int y)const;
	void CheckRightQueenNumber(unsigned int number)const;
	
	void TakeAwayQueen(unsigned int Number); 
	// 拿走Number编号的棋子
	bool IsBoardLocateFinePut(unsigned x, unsigned y); 
	//棋盘的某一位置满足八皇后约束是否可放,最基本的要满足两皇后位置不重叠
	void BackTrackNqueen(unsigned int Number, unsigned int j);

	void SolutionNqueenNotRecursub(unsigned j0);

	void GetQueenInfluence(unsigned int Number, unsigned int x, unsigned int y);
	//得到Number编号的皇后放置在x y处的影响，并将影响体现在fitmap中

	unsigned int GenerateRandNum(unsigned int lower, unsigned int upper);
	unsigned int GetConflictCountExceptSelf(unsigned int Number)const;
	//其他棋子在某一编号的皇后处的冲突数量 除了棋子自己本身
	unsigned int GetConflictCount(unsigned int x, unsigned int y)const;
	//得到所有在棋盘上的棋子在某一x y处的冲突数量

	void outputRealPos(unsigned int CountSolution)const;
};
void Nqueen::outputRealPos(unsigned int CountSolution)const
{
	//static int CountSolution = 1;
	//cout << endl;
	cout << N<<"皇后的解 "<<CountSolution++ << ":";
	for (int i = 0; i < RealPos.size(); i++)
	{
		cout << RealPos[i] << " ";
	}
	cout << " ";
	clock_t end = clock();
	cout<<"至此花费时间："<<(double)(end - Start) / CLOCKS_PER_SEC << "秒" << endl;
}
unsigned int Nqueen::GetConflictCount(unsigned int x, unsigned int y)const
{
	CheckRightPixel(x, y);
	unsigned int result = 0;
	for (int i = 0; i < N; i++)
	{
		if (FitMap[i][getMapfromPixel2loc(x, y)] == 0)
			result++;
	}
	return result;
}

unsigned int Nqueen::GetConflictCountExceptSelf(unsigned int Number)const
{
	CheckRightQueenNumber(Number);
	unsigned int result = 0;
	for (int i = 0; i < N; i++)
	{
		if (i != Number)
		{
			if (FitMap[i][getMapfromPixel2loc(Number, RealPos[Number])] == 0)
				result++;
		}
	}
	return result;
}

unsigned int Nqueen::GenerateRandNum(unsigned int lower, unsigned int upper)
{
	if (lower > upper)
		throw exception("Lower不能大于Upper");
	else if (lower == upper)
		return lower;
	srand((int)time(0));
	return lower + rand() % (upper - lower+1);
}

bool Nqueen::IsBoardLocateFinePut(unsigned x, unsigned y)
{
	CheckRightPixel(x, y);
	bool result = 1;
	auto loc = getMapfromPixel2loc(x, y);
	for (int i = 0; i < N; i++)
	{
		result = result & FitMap[i][loc];
	}
	return result;
}

void Nqueen::CheckRightQueenNumber(unsigned int number)const
{
	if (number >= N)
		throw exception("棋子编号超限");
}

void Nqueen::CheckRightPixel(unsigned int x, unsigned int y)const 
{
	if (x >= N || y >= N)
		throw exception("x y 超限");
}

size_t Nqueen::getMapfromPixel2loc(unsigned int x, unsigned int y)const
{
	CheckRightPixel(x, y);
	return  x + y*N;
}

void Nqueen::SolutionNqueenCSP()
{
	while (1)
	{
		for (int i = 0; i < N; i++)
		{
			PutInLocIgnoreNqueenConflict(i, i, GenerateRandNum(0, N - 1));
		}
		vector<int> ConflictCount(N, 0); //其他棋子在某一编号的皇后处的冲突数量

		vector<queue<unsigned int>> DuplicateRec(N);
		unsigned Queuesize = 20;
		unsigned int Maxnum = 8000;
		unsigned int CountRow = 0;
		for (unsigned int countCSP = 0; countCSP < Maxnum; countCSP++)
		{
			for (int Number = 0; Number < N; Number++)
			{
				ConflictCount[Number] = GetConflictCountExceptSelf(Number);
			}
			vector<int> HaveConflictNumber(0);
			for (int i = 0; i < ConflictCount.size(); i++)
			{
				if (ConflictCount[i] != 0)
					HaveConflictNumber.push_back(i);
			}//得到冲突不为0的编号

			//cout << HaveConflictNumber.size() << " ";
			if (HaveConflictNumber.empty())//说明符合最后的结果，输出
			{
				static int CountSolution = 1;
				outputRealPos(CountSolution++);
				break;
			}
			else
			{
				//auto ConflictCol = GenerateRandNum(0, HaveConflictNumber.size() - 1); //随机选一个冲突的列
				auto ConflictCol = (CountRow++) % N; //挨个进行能收敛，随机选不收敛
				TakeAwayQueen(ConflictCol);
				auto minConflict = GetConflictCount(ConflictCol, 0);
				unsigned int minConflictIndex = 0; //得到所处的行

				//DuplicateRec[ConflictCol].pop();
				int flagchange = 0;
				if (DuplicateRec[ConflictCol].size() == Queuesize)
				{
					if (DuplicateRec[ConflictCol].front() == DuplicateRec[ConflictCol].back())
						flagchange = 1;
				}
				

				for (int j = 1; j < N; j++)
				{
					auto thiscount = GetConflictCount(ConflictCol, j);
					if (thiscount < minConflict)
					{
						minConflict = thiscount;
						minConflictIndex = j;
					}
				}
				if (DuplicateRec[ConflictCol].size() < Queuesize)
				{
					DuplicateRec[ConflictCol].push(minConflictIndex);
				}
				else
				{
					DuplicateRec[ConflictCol].pop();
					DuplicateRec[ConflictCol].push(minConflictIndex);
				}
				if (flagchange)
				{
					auto Origin = minConflictIndex;
					while (minConflictIndex == Origin)
						minConflictIndex = GenerateRandNum(0, N - 1); //脱出局部极小 必须有这个脱出极小 否则会死循环 陷入局部极小无法自拔
				}
				PutInLocIgnoreNqueenConflict(ConflictCol, ConflictCol, minConflictIndex); //放到最小冲突处
			}
		}
	}
}

void Nqueen::SolutionNqueenNotRecur()
{
	for (int j0 = 0; j0 < N; j0++)
	{
		SolutionNqueenNotRecursub(j0);
	}
}

void Nqueen::SolutionNqueenNotRecursub(unsigned j0)  //终于写对了！！！！！ 这个可以和普通的八叉树遍历进行对照 真正理解。
{
	vector<unsigned int> tobeNextChild(N,0);

	int Number = 0;
	PutInLoc(Number, Number, j0);
	tobeNextChild[Number] = 0;
	RealPos[Number] = j0;

	unsigned int y;
	while (1)
	{
		for (y = tobeNextChild[Number]; y < N; y++)
		{
			if (PutInLoc(Number + 1, Number + 1, y) == 0)
				tobeNextChild[Number]++;
			else
			{
				tobeNextChild[Number]++;
				Number++;
				RealPos[Number] = y;
				if (Number == N - 1)
				{
					static int CountSolution = 1;
					outputRealPos(CountSolution++);
					TakeAwayQueen(Number);
					Number--;
				}
				break;
			}
		}
		if (y == N)
		{
			for (int i = Number; i < N; i++)
				tobeNextChild[i] = 0;
			TakeAwayQueen(Number);
			Number--;
			if (Number < 0)
				break;
		}
	}
	
		

	



	/*int Number = 0;
	PutInLoc(Number, Number, j0);
	int i;
	vector<vector<unsigned int>> Child(N,vector<unsigned int>(N,-1) );
	vector<unsigned int> Allavailable;
	for (int i = 0; i < N; i++)
		Allavailable.push_back(N-1-i);
	int flagbreak ;

	Child[Number] = Allavailable;
	while (Child[0].empty()==0)
	{
		flagbreak = 0;
		while(!Child[Number].empty())
		{
			if (PutInLoc(Number + 1, Number + 1, *(Child[Number].end()-1)))
			{
				RealPos[Number+1] = *(Child[Number].end() - 1);
				Number++;
				if (Number == N - 1)
				{
					static int CountSolution = 1;
					cout << CountSolution++ << ":";
					for (int i = 0; i < RealPos.size(); i++)
					{
						cout << RealPos[i] << " ";
					}
					cout << endl;
					TakeAwayQueen(Number);
					Number--;
					Child[Number].pop_back();
					flagbreak = 2;
				}
				else
				{
					Child[Number] = Allavailable;
					flagbreak = 1;
					break;
				}
					
			}
			else
				Child[Number].pop_back();
		}

		if (flagbreak == 0)
		{
			Number--;
			if (Number == 0)
				break;
			TakeAwayQueen(Number);
			if (Child[Number-1].empty()==0)
				Child[Number - 1].pop_back();
		}
		else if (flagbreak == 1)
		{

		}
		else if (flagbreak == 2)
		{
			TakeAwayQueen(Number);
			Child[Number - 1].pop_back();
		}
	}*/
}

void Nqueen::SolutionNqueen()
{
	for (int i = 0; i < N; i++)
	{
		BackTrackNqueen(0, i);
	}
}

void Nqueen::BackTrackNqueen(unsigned int Number,unsigned int j)
{
	if (PutInLoc(Number, Number, j) == 0) //回溯 剪枝
	{
		return;
	}
	RealPos[Number] = j;
	if (Number == N-1)//说明此时找到一个解了
	{
		static int CountSolution = 1;
		outputRealPos(CountSolution++);
		TakeAwayQueen(Number);
		return;
	}
		
	for (unsigned int i = 0; i < N; i++)
	{
		BackTrackNqueen(Number + 1, i);
	}
	TakeAwayQueen(Number);


	/*for (unsigned int y = y_begin; y < N; y++)
	{
		if (PutInLoc(Number, Number, y))
		{
			auto NumberNext = Number + 1;
			if (NumberNext < N)
			{
				if (BackTrackNqueen(Number + 1,0) == 0)
				{
					TackAwayQueen(Number);
					continue;
				}
				else
				{
					for (int i = 0; i < N; i++)
					{
						cout << RealPos[i] << " ";
					}
					cout << endl;
					return 1;
				}
					
			}
			else
				return 1;
		}
	}	
	return 0;*/
	
}

void Nqueen::TakeAwayQueen(unsigned int Number)
{
	CheckRightQueenNumber(Number);
	if (RealPos[Number] < N)
	{
		RealPos[Number] = N;
		for (size_t i = 0; i < FitMap[Number].size(); i++)
		{
			FitMap[Number][i] = 1;
		}
	}
}

void Nqueen::GetQueenInfluence(unsigned int Number, unsigned int x, unsigned int y)
{
	CheckRightQueenNumber(Number);
	CheckRightPixel(x, y);
	for (unsigned int i = x; i < N; i++)
		FitMap[Number][getMapfromPixel2loc(i, y)] = 0;
	for (unsigned int i = 0; i < x; i++)
		FitMap[Number][getMapfromPixel2loc(i, y)] = 0;
	for (unsigned int j = y; j < N; j++)
		FitMap[Number][getMapfromPixel2loc(x, j)] = 0;
	for (unsigned int j = 0; j < y; j++)
		FitMap[Number][getMapfromPixel2loc(x, j)] = 0;

	unsigned int count = 1;
	for (unsigned int i = x + 1; i < N; i++)
	{
		auto j = y + (count++);
		if (j < N)
			FitMap[Number][getMapfromPixel2loc(i, j)] = 0;
		else
			break;
	}
	count = 1;
	for (int i = x - 1; i >= 0; i--)
	{
		int j = int(y) - int(count++);
		if (j >= 0)
			FitMap[Number][getMapfromPixel2loc(i, j)] = 0;
		else
			break;
	}
	count = 1;
	for (int i = x + 1; i < N; i++)
	{
		int j = int(y) - int(count++);
		if (j >= 0)
			FitMap[Number][getMapfromPixel2loc(i, j)] = 0;
		else
			break;
	}
	count = 1;
	for (int i = x - 1; i >= 0; i--)
	{
		int j = int(y) + int(count++);
		if (j < N)
			FitMap[Number][getMapfromPixel2loc(i, j)] = 0;
		else
			break;
	}
}

void Nqueen::PutInLocIgnoreNqueenConflict(unsigned int Number, unsigned int x, unsigned int y)
{
	CheckRightQueenNumber(Number);
	CheckRightPixel(x, y);
	if (Number != x)
		throw exception("不符合编号是多少就是多少列的默认假设");

	GetQueenInfluence(Number, x, y);
	RealPos[Number] = y;
}

bool Nqueen::PutInLoc(unsigned int Number,unsigned int x, unsigned int y) //Number表示第Number号棋子
{
	CheckRightQueenNumber(Number);
	CheckRightPixel(x, y);
	if (Number != x)
		throw exception("不符合编号是多少就是多少列的默认假设");

	auto maploc = getMapfromPixel2loc(x, y);
	if (IsBoardLocateFinePut(x,y) == 0)
		return 0;
	else
	{
		GetQueenInfluence(Number, x, y);
		RealPos[Number] = y;
		return 1;
	}
}


int main()
{
	try
	{
		cout << "SolutionNqueen 回溯法递归方式解8皇后问题" << endl;
		Nqueen test(8);
		test.SolutionNqueen();
		cout << "SolutionNqueenNotRecur 回溯法迭代方式解8皇后问题" << endl;
		Nqueen test1(8);
		test1.SolutionNqueenNotRecur();
		unsigned int Num = 18;
		cout << "CSP解" << Num << "皇后问题，速度远快于回溯法，时间有限，没有添加去除重复结果的算法" << endl;
		Nqueen test3(Num);
		test3.SolutionNqueenCSP();

		Num = 150;
		cout << "CSP解"<<Num<<"皇后问题，速度远快于回溯法，时间有限，没有添加去除重复结果的算法" << endl;
		Nqueen test2(Num);
		test2.SolutionNqueenCSP();
		
	}
	catch (exception d)
	{
		cout << d.what() << endl;
		
	}
	system("pause");
}