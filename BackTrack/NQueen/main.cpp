#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class Nqueen
{
public:
	Nqueen(unsigned int Nin) :N(Nin), FitMap(Nin, vector<bool>(Nin*Nin,1)), RealPos(Nin) {}//һ��ʼʱ����λ�þ��ɷ�

	void SolutionNqueen();
private:
	const unsigned int N;//N�ʺ�����
	vector<vector<bool>> FitMap; //�ɷ��ûʺ��ͼʾ�⣬��ĳ�����ӹ�Ͻ�Ŀɷŵĵط�Ϊ1�����ɷŵĵط�Ϊ0 ��N��ͼ��ÿ��λ��ȡN��&Ϊ1�ɷţ�N��&λ0���ɷ�
	vector<unsigned int> RealPos;//�˸��ʺ��ʵ��λ��

	size_t getMapfromPixel2loc(unsigned int x, unsigned int y);//�õ�������ͼ��fitmapλ�õ�ӳ��
	bool PutInLoc(unsigned int Number,unsigned int x, unsigned int y);//������x yλ�ã���ѭ��һ���ޣ�������˻ʺ�����ƣ�����óɹ������޸�Fitmap,�������ʧ��,����false
	void CheckRightPixel(unsigned int x, unsigned int y);
	void CheckRightQueenNumber(unsigned int number);
	
	void TakeAwayQueen(unsigned int Number); // ����Number��ŵ�����
	bool IsBoardLocateFinePut(unsigned x, unsigned y); //���̵�ĳһλ���Ƿ�ɷ�
	void BackTrackNqueen(unsigned int Number, unsigned int j);
};

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

void Nqueen::CheckRightQueenNumber(unsigned int number)
{
	if (number >= N)
		throw exception("���ӱ�ų���");
}

void Nqueen::CheckRightPixel(unsigned int x, unsigned int y)
{
	if (x >= N || y >= N)
		throw exception("x y ����");
}

size_t Nqueen::getMapfromPixel2loc(unsigned int x, unsigned int y)
{
	CheckRightPixel(x, y);
	return  x + y*N;
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
		cout << CountSolution++ << ":";
		for (int i = 0; i < RealPos.size(); i++)
		{
			cout << RealPos[i] << " ";
		}
		cout << endl;
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

bool Nqueen::PutInLoc(unsigned int Number,unsigned int x, unsigned int y) //Number��ʾ��Number������
{
	CheckRightQueenNumber(Number);
	CheckRightPixel(x, y);
	auto maploc = getMapfromPixel2loc(x, y);
	if (IsBoardLocateFinePut(x,y) == 0)
		return 0;
	else
	{
		for (unsigned int i = x; i < N; i++)
			FitMap[Number][getMapfromPixel2loc(i, y)] = 0;
		for (unsigned int i = 0; i < x; i++)
			FitMap[Number][getMapfromPixel2loc(i, y)] = 0;
		for (unsigned int j = y; j < N; j++)
			FitMap[Number][getMapfromPixel2loc(x, j)] = 0;
		for (unsigned int j = 0; j < y; j++)
			FitMap[Number][getMapfromPixel2loc(x, j)] = 0;

		unsigned int count = 1;
		for (unsigned int i = x+1; i < N; i++)
		{
			auto j = y + (count++);
			if (j < N)
				FitMap[Number][getMapfromPixel2loc(i, j)] = 0;
			else
				break;
		}
		count = 1;
		for (int i = x-1; i >= 0; i--)
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
		RealPos[Number] = y;
		return 1;
	}
}


int main()
{
	try
	{
		Nqueen test(8);
		test.SolutionNqueen();
	/*	Nqueen test(8);
		test.BackTrackNqueen(0,0);
		Nqueen test1(8);
		test1.BackTrackNqueen(0, 1);
		Nqueen test2(8);
		test2.BackTrackNqueen(0, 2);
		Nqueen test3(8);
		test3.BackTrackNqueen(0, 3);
		Nqueen test4(8);
		test4.BackTrackNqueen(0, 4);
		Nqueen test5(8);
		test5.BackTrackNqueen(0, 5);*/
	}
	catch (exception d)
	{
		cout << d.what() << endl;
	}
}