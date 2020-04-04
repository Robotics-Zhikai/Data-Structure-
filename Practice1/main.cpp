/*设计函数分别求两个一元多项式的乘积与和。

输入格式:
输入分2行，每行分别先给出多项式非零项的个数，再以指数递降方式输入一个多项式非零项系数和指数（绝对值均为不超过1000的整数）。数字间以空格分隔。

输出格式 :
输出分2行，分别以指数递降方式输出乘积多项式以及和多项式非零项的系数和指数。数字间以空格分隔，但结尾不能有多余空格。零多项式应输出0 0。

输入样例 :
4 3 4 - 5 2  6 1 - 2 0
3 5 20 - 7 4  3 1



输出样例 :
	15 24 - 25 22 30 21 - 10 20 - 21 8 35 6 - 33 5 14 4 - 15 3 18 2 - 6 1
	5 20 - 4 4 - 5 2 9 1 - 2 0
	*/
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

typedef struct PolyNode* Polynomial;
struct PolyNode
{
	int Coef;
	int Expon;
	Polynomial Next;
};

Polynomial ReadPolynomial(int * input)
{
	//int input[] = { 4,3,4,-5,2,6,1,-2,0 };
	Polynomial Begin;
	Begin = (Polynomial)malloc(sizeof(PolyNode));
	
	Begin->Next = (Polynomial)malloc(sizeof(PolyNode));
	if (input[0] == 0)
	{
		Begin->Next->Coef = 0;
		Begin->Next->Expon = 0;
		Begin->Next->Next = NULL;
		return Begin;
	}
	Polynomial temp;
	temp = Begin->Next;
	for (int i = 0; i < 2*input[0]; )
	{
		temp->Coef = input[++i];
		temp->Expon = input[++i];
		if (i <2* input[0])
		{
			temp->Next = (Polynomial)malloc(sizeof(PolyNode));
			temp = temp->Next;
		}
		else
			temp->Next = NULL;
	}
	return Begin;

}

Polynomial Multiple(Polynomial Polynomial1, Polynomial Polynomial2)
{
	Polynomial Begin = (Polynomial)malloc(sizeof(PolyNode));
	Polynomial temp1 = Polynomial1->Next;
	Polynomial temp2 ;
	int num = 0;
	Polynomial Storage;
	while (temp1 != NULL)
	{
		temp2 = Polynomial2->Next;
		while (temp2 != NULL)
		{
			num++;
			Polynomial NewNode = (Polynomial)malloc(sizeof(PolyNode));
 			NewNode->Coef = temp1->Coef * temp2->Coef;
			NewNode->Expon = temp1->Expon + temp2->Expon;
			NewNode->Next = NULL;
			if (num == 1)
			{
				Begin->Next = NewNode;
			}
			else
			{
				Storage->Next = NewNode;
			}
			Storage = NewNode;
			temp2 = temp2->Next;
		}
		temp1 = temp1->Next;
	}
	Polynomial temp3 = Begin->Next;
	while (temp3 != NULL)
	{
		Polynomial temp4 = temp3->Next;
		int tempcoef = temp3->Coef;
		Polynomial Storetemp4 = temp3;
		while (temp4 != NULL)
		{
			if (temp4->Expon == temp3->Expon)
			{
				tempcoef = tempcoef + temp4->Coef;
				Storetemp4->Next = temp4->Next;
				free(temp4);
				temp4 = Storetemp4;
			}
			Storetemp4 = temp4;
			temp4 = temp4->Next;
		}
		temp3->Coef = tempcoef;
		temp3 = temp3->Next;
	}
	return Begin;
}

Polynomial Link(Polynomial Polynomial1, Polynomial Polynomial2) //连接两个链表到新的链表，返回新链表的地址
{
	Polynomial Result = (Polynomial)malloc(sizeof(PolyNode));
	Result->Next = NULL;
	Polynomial temp1 = Polynomial1->Next;
	Polynomial temp2 = Polynomial2->Next;
	Polynomial tempstorage = Result;
	while (temp1 != NULL)
	{
		Polynomial NewNode = (Polynomial)malloc(sizeof(PolyNode));
		NewNode->Coef = temp1->Coef;
		NewNode->Expon = temp1->Expon;
		tempstorage->Next = NewNode;
		tempstorage = NewNode;
		temp1 = temp1->Next;
	}
	while (temp2 != NULL)
	{
		Polynomial NewNode = (Polynomial)malloc(sizeof(PolyNode));
		NewNode->Coef = temp2->Coef;
		NewNode->Expon = temp2->Expon;
		tempstorage->Next = NewNode;
		tempstorage = NewNode;
		temp2 = temp2->Next;
	}
	tempstorage->Next = NULL;
	return Result;
}

Polynomial Add(Polynomial Polynomial1, Polynomial Polynomial2)
{
	Polynomial Linked = Link(Polynomial1, Polynomial2);
	Polynomial temp3 = Linked->Next;
	while (temp3 != NULL)
	{
		Polynomial temp4 = temp3->Next;
		int tempcoef = temp3->Coef;
		Polynomial Storetemp4 = temp3;
		while (temp4 != NULL)
		{
			if (temp4->Expon == temp3->Expon)
			{
				tempcoef = tempcoef + temp4->Coef;
				Storetemp4->Next = temp4->Next;
				free(temp4);
				temp4 = Storetemp4;
			}
			Storetemp4 = temp4;
			temp4 = temp4->Next;
		}
		temp3->Coef = tempcoef;
		temp3 = temp3->Next;
	}
	return Linked;
}

void printPolynomial(Polynomial Polynomial1)
{
	Polynomial temp = Polynomial1->Next;
	int num = 0;
	while (temp != NULL)
	{
		num++;
		temp = temp->Next;
	}
	cout << num << " ";
	temp = Polynomial1->Next;
	while (temp != NULL)
	{
		cout << temp->Coef << " " << temp->Expon<<" ";
		temp = temp->Next;
	}
	cout << endl;
}

void sortPolynomial(Polynomial Polynomial1) //链表排序 从大到小 冒泡排序法
{
	Polynomial temp = Polynomial1->Next;
	Polynomial tempstorage = NULL;
	while (temp != NULL)
	{
		if (temp->Next == tempstorage)
		{
			tempstorage = temp;
			temp = Polynomial1->Next;
			continue;
		}
		if (temp->Next != NULL)
		{
			if (temp->Next->Expon > temp->Expon)
			{
				int midCoef,midExpon;
				midCoef = temp->Next->Coef  ;
				midExpon = temp->Next->Expon ;
				temp->Next->Coef = temp->Coef;
				temp->Next->Expon = temp->Expon;
				temp->Coef = midCoef;
				temp->Expon = midExpon;
			}
		} 
		temp = temp->Next;
	}
}

int main()
{
	Polynomial temp;
	int input[] = { 4,3,4,-5,2,6,1,-2,0 };
	
	temp = ReadPolynomial(input);
	Polynomial temp1;
	int input1[] = { 3,5,20,-7,4,3,1 };
	temp1 = ReadPolynomial(input1);
	Polynomial MultipleResult = Multiple(temp, temp1);
	Polynomial AddResult = Add(temp, temp1);
	sortPolynomial(MultipleResult);
	sortPolynomial(AddResult);
	printPolynomial(temp);
	printPolynomial(temp1);
	printPolynomial(MultipleResult);
	printPolynomial(AddResult);
	system("pause");
}
