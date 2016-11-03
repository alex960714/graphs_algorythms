#include "my_graph.h"

My_graph::My_graph(int nodes)
{
	NodesNum = nodes;
	EdgesNum = 0;
	adj_matr = new int*[nodes];
	for (int i = 0; i < NodesNum; i++)
		adj_matr[i] = new int[nodes];
	for (int i = 0; i < NodesNum; i++)
		for (int j = 0; j < NodesNum; j++)
			adj_matr[i][j] = 0;
}

My_graph::My_graph(int** matr, int nodes, bool is_adj_matr, int edges)
{

}

My_graph::~My_graph()
{

}

void My_graph::getAdjMatr(int** matr, int& len)
{
	
}

void My_graph::getIncMatr(int** matr, int& len)
{

}

void My_graph::setAdjMatr(int** matr, int len)
{

}

void My_graph::setIncMatr(int** matr, int len)
{

}
