// my_graph_sample.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "my_graph.h"
#include <iostream>
#include <fstream>
using namespace std;


int main()
{
	My_graph *gr = new My_graph();
	int size = gr->init_file("graph_adj.txt");
	cout << "Nodes number: " << size << endl;
	int size2;
	int **matr = gr->getAdjMatr(size2);
	cout << "Nodes number: " << size2 << endl;
	for (int i = 0; i < size2; i++)
	{
		for (int j = 0; j < size2; j++)
			cout << matr[i][j] << " ";
		cout << endl;
	}
    return 0;
}

