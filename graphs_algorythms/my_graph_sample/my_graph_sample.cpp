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
    return 0;
}

