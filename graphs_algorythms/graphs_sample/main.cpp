#include <stdio.h>
#include "hamilton_cycle_search.h"
#include <stack>
#include <fstream>
#include <Windows.h>
#include <iostream>
using namespace std;

int init_file(char* file_name);
void init_rand(int size, int perc);

int **matr;

int main(int argc, char** argv)
{
	setlocale(LC_CTYPE, "Russian");
	int size, perc;
	double st_time, en_time;
	stack<int> st;
	int op;

	do
	{
		cout << "Введите номер действия:" << endl << "1. Чтение из файла" << endl << "2. Заполнение случайными числами:" << endl;
		cin >> op;
		switch (op)
		{
		case 1:
			size = init_file("graph_adj.txt");
			break;
		case 2:
			cout << "Введите число вершин:" << endl;
			cin >> size;
			cout << "Введите процент плотности графа:" << endl;
			cin >> perc;
			init_rand(size, perc);
			break;
		default:
			cout << "Неправильный номер операции!" << endl;
		}
	} while (op != 1 && op != 2);

	st_time = GetTickCount();
	if (hamilton_cycle::search(matr, size, st))
	{
		en_time = GetTickCount();
		printf("Hamilton cycle:\n");
		while (!st.empty())
		{
			printf("%d ", st.top());
			st.pop();
		}
		printf("\n");
	}
	else
	{
		en_time = GetTickCount();
		printf("No hamilton cycle\n");
	}
	printf("Time: %f\n", (en_time - st_time) / 1000);

	for (int i = 0; i < size; i++)
		delete[] matr[i];
	delete[] matr;
	return 0;
}

int init_file(char* file_name)
{
	ifstream is;
	int size;
	is.open("graph_adj.txt");
	is >> size;
	matr = new int*[size];
	for (int i = 0; i < size; i++)
		matr[i] = new int[size];

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			is >> matr[i][j];
			printf("%d ", matr[i][j]);
		}
		printf("\n");
	}
	is.close();
	return size;
}

void init_rand(int size, int perc)
{
	matr = new int*[size];
	for (int i = 0; i < size; i++)
		matr[i] = new int[size];
	for (int i = 0; i < size; i++)
	{
		matr[i][i] = 0;
		for (int j = i + 1; j < size; j++)
		{
			matr[i][j] = matr[j][i] = (rand() % 100 < perc);
		}
	}

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			printf("%d ", matr[i][j]);
		}
		printf("\n");
	}
}