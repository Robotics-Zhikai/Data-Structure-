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
	//һ��ʼʱ����λ�þ��ɷ�

	void SolutionNqueen(); 
	//�ݹ鷽�����
	void SolutionNqueenNotRecur();
	//�ǵݹ鷽�����
	void SolutionNqueenCSP(); 
	//CSP ��С��ͻ�������N�ʺ�����
	
private:
	const unsigned int N;
	//N�ʺ�����
	vector<vector<bool>> FitMap; 
	//�ɷ��ûʺ��ͼʾ�⣬��ĳ�����ӹ�Ͻ�ĵط�Ϊ1������Ͻ�ĵط�Ϊ0  ����˻ʺ�Լ��ʱ����N��ͼ��ÿ��λ��ȡN��&Ϊ1�ɷţ�N��&λ0���ɷ�
	vector<unsigned int> RealPos;
	//�˸��ʺ��ʵ��λ�� ���Ϊ0�Ļʺ�Ĭ���ڵ�0�У����Ϊ1�Ļʺ�Ĭ���ڵ�һ��
	clock_t Start;

	size_t getMapfromPixel2loc(unsigned int x, unsigned int y)const;
	//�õ�������ͼ��fitmapλ�õ�ӳ��
	bool PutInLoc(unsigned int Number,unsigned int x, unsigned int y);
	//������x yλ�ã���ѭ��һ���ޣ�������˻ʺ�����ƣ�����óɹ������޸�Fitmap,�������ʧ��,����false
	void PutInLocIgnoreNqueenConflict(unsigned int Number, unsigned int x, unsigned int y);
	//���԰˻ʺ�����ƣ�ǿ�Ʒ���ĳ�ʺ����̣���Ҫ��֤���������ʺ�λ�ò��ص�
	
	void CheckRightPixel(unsigned int x, unsigned int y)const;
	void CheckRightQueenNumber(unsigned int number)const;
	
	void TakeAwayQueen(unsigned int Number); 
	// ����Number��ŵ�����
	bool IsBoardLocateFinePut(unsigned x, unsigned y); 
	//���̵�ĳһλ������˻ʺ�Լ���Ƿ�ɷ�,�������Ҫ�������ʺ�λ�ò��ص�
	void BackTrackNqueen(unsigned int Number, unsigned int j);

	void SolutionNqueenNotRecursub(unsigned j0);

	void GetQueenInfluence(unsigned int Number, unsigned int x, unsigned int y);
	//�õ�Number��ŵĻʺ������x y����Ӱ�죬����Ӱ��������fitmap��

	unsigned int GenerateRandNum(unsigned int lower, unsigned int upper);
	unsigned int GetConflictCountExceptSelf(unsigned int Number)const;
	//����������ĳһ��ŵĻʺ󴦵ĳ�ͻ���� ���������Լ�����
	unsigned int GetConflictCount(unsigned int x, unsigned int y)const;
	//�õ������������ϵ�������ĳһx y���ĳ�ͻ����

	void outputRealPos(unsigned int CountSolution)const;
};
void Nqueen::outputRealPos(unsigned int CountSolution)const
{
	//static int CountSolution = 1;
	//cout << endl;
	cout << N<<"�ʺ�Ľ� "<<CountSolution++ << ":";
	for (int i = 0; i < RealPos.size(); i++)
	{
		cout << RealPos[i] << " ";
	}
	cout << " ";
	clock_t end = clock();
	cout<<"���˻���ʱ�䣺"<<(double)(end - Start) / CLOCKS_PER_SEC << "��" << endl;
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
		throw exception("Lower���ܴ���Upper");
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
		throw exception("���ӱ�ų���");
}

void Nqueen::CheckRightPixel(unsigned int x, unsigned int y)const 
{
	if (x >= N || y >= N)
		throw exception("x y ����");
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
		vector<int> ConflictCount(N, 0); //����������ĳһ��ŵĻʺ󴦵ĳ�ͻ����

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
			}//�õ���ͻ��Ϊ0�ı��

			//cout << HaveConflictNumber.size() << " ";
			if (HaveConflictNumber.empty())//˵���������Ľ�������
			{
				static int CountSolution = 1;
				outputRealPos(CountSolution++);
				break;
			}
			else
			{
				//auto ConflictCol = GenerateRandNum(0, HaveConflictNumber.size() - 1); //���ѡһ����ͻ����
				auto ConflictCol = (CountRow++) % N; //�������������������ѡ������
				TakeAwayQueen(ConflictCol);
				auto minConflict = GetConflictCount(ConflictCol, 0);
				unsigned int minConflictIndex = 0; //�õ���������

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
						minConflictIndex = GenerateRandNum(0, N - 1); //�ѳ��ֲ���С ����������ѳ���С �������ѭ�� ����ֲ���С�޷��԰�
				}
				PutInLocIgnoreNqueenConflict(ConflictCol, ConflictCol, minConflictIndex); //�ŵ���С��ͻ��
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

void Nqueen::SolutionNqueenNotRecursub(unsigned j0)  //����д���ˣ��������� ������Ժ���ͨ�İ˲����������ж��� ������⡣
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
	if (PutInLoc(Number, Number, j) == 0) //���� ��֦
	{
		return;
	}
	RealPos[Number] = j;
	if (Number == N-1)//˵����ʱ�ҵ�һ������
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
		throw exception("�����ϱ���Ƕ��پ��Ƕ����е�Ĭ�ϼ���");

	GetQueenInfluence(Number, x, y);
	RealPos[Number] = y;
}

bool Nqueen::PutInLoc(unsigned int Number,unsigned int x, unsigned int y) //Number��ʾ��Number������
{
	CheckRightQueenNumber(Number);
	CheckRightPixel(x, y);
	if (Number != x)
		throw exception("�����ϱ���Ƕ��پ��Ƕ����е�Ĭ�ϼ���");

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
		cout << "SolutionNqueen ���ݷ��ݹ鷽ʽ��8�ʺ�����" << endl;
		Nqueen test(8);
		test.SolutionNqueen();
		cout << "SolutionNqueenNotRecur ���ݷ�������ʽ��8�ʺ�����" << endl;
		Nqueen test1(8);
		test1.SolutionNqueenNotRecur();
		unsigned int Num = 18;
		cout << "CSP��" << Num << "�ʺ����⣬�ٶ�Զ���ڻ��ݷ���ʱ�����ޣ�û�����ȥ���ظ�������㷨" << endl;
		Nqueen test3(Num);
		test3.SolutionNqueenCSP();

		Num = 150;
		cout << "CSP��"<<Num<<"�ʺ����⣬�ٶ�Զ���ڻ��ݷ���ʱ�����ޣ�û�����ȥ���ظ�������㷨" << endl;
		Nqueen test2(Num);
		test2.SolutionNqueenCSP();
		
	}
	catch (exception d)
	{
		cout << d.what() << endl;
		
	}
	system("pause");
}