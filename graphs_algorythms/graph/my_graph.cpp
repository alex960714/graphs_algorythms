#include "my_graph.h"

void My_graph::getMem()
{
	adj_matr = new int*[NodesNum];
	for (int i = 0; i < NodesNum; i++)
		adj_matr[i] = new int[NodesNum];
}

void My_graph::cleanMem()
{
	if (adj_matr != NULL)
	{
		for (int i = 0; i < NodesNum; i++)
			delete[] adj_matr[i];
		delete[] adj_matr;
	}
}

My_graph::My_graph(int nodes)
{
	NodesNum = nodes;
	EdgesNum = 0;

	getMem();

	for (int i = 0; i < NodesNum; i++)
		for (int j = 0; j < NodesNum; j++)
			adj_matr[i][j] = 0;
}

My_graph::My_graph(int** matr, int nodes)
{
	setAdjMatr(matr, nodes);
}

My_graph::~My_graph()
{
	cleanMem();
}

int** My_graph::getAdjMatr(int& len)
{
	int** matr = new int*[NodesNum];
	for (int i = 0; i < NodesNum; i++)
		matr[i] = new int[NodesNum];

	for (int i = 0; i < NodesNum; i++)
		for (int j = 0; j < NodesNum; j++)
			matr[i][j] = adj_matr[i][j];

	len = NodesNum;
	return matr;
}

void My_graph::setAdjMatr(int** matr, int len)
{
	cleanMem();
	getMem();

	NodesNum = len;
	EdgesNum = 0;

	for (int i = 0; i < NodesNum; i++)
		for (int j = 0; j < NodesNum; j++)
		{
			adj_matr[i][j] = matr[i][j];
			EdgesNum++;
		}
	EdgesNum >> 1;
}

bool My_graph::isAdjacent(int node1, int node2)
{
	if (node1 < 0 || node1 >= NodesNum || node2 < 0 || node2 >= NodesNum)
		return false;
	return adj_matr[node1][node2];
}

void My_graph::addEdge(int node1, int node2)
{
	if (node1 >= 0 && node1 < NodesNum && node2 >= 0 && node2 < NodesNum && !adj_matr[node1][node2] && node1 != node2)
	{
		adj_matr[node1][node2] = adj_matr[node2][node1] = 1;
		EdgesNum++;
	}
}

void My_graph::removeEdge(int node1, int node2)
{
	if (node1 >= 0 && node1 < NodesNum && node2 >= 0 && node2 < NodesNum && adj_matr[node1][node2])
	{
		adj_matr[node1][node2] = adj_matr[node2][node1] = 0;
		EdgesNum--;
	}
}

int My_graph::init_file(const char * file_name)
{
	ifstream is;
	is.open(file_name);

	if (!is.is_open())
		return -1;

	is >> NodesNum;
	cleanMem();
	getMem();

	for (int i = 0; i < NodesNum; i++)
	{
		for (int j = 0; j < NodesNum; j++)
		{
			is >> adj_matr[i][j];
			//printf("%d ", matr[i][j]);
		}
		//printf("\n");
	}
	is.close();
	return NodesNum;
}
