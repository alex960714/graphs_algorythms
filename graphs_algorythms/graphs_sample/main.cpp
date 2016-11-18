#include <stdio.h>
#include "hamilton_cycle_search.h"
#include <stack>
#include <fstream>
#include <Windows.h>
using namespace std;

int main(int argc, char** argv)
{
	int **matr;
	int size;
	double st_time, en_time;
	stack<int> st;
	ifstream is;

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