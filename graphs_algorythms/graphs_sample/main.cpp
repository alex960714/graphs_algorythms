#include <stdio.h>
#include "hamilton_cycle_search.h"
#include <stack>
#include <fstream>
using namespace std;

int main(int argc, char** argv)
{
	int **matr;
	int size;
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

	if (hamilton_cycle::search(matr, size, st))
	{
		printf("Hamilton cycle:\n");
		while (!st.empty())
		{
			printf("%d ", st.top());
			st.pop();
		}
		printf("\n");
	}
	else printf("No hamilton cycle\n");
	
	is.close();

	for (int i = 0; i < size; i++)
		delete[] matr[i];
	delete[] matr;
	return 0;
}