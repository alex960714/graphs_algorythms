#ifndef _MY_GRAPH_H_
#define _MY_GRAPH_H_

#include <fstream>
using namespace std;

class My_graph
{
private:
	int** adj_matr;      //adjacency matrix
	//int** inc_matr;      
	int NodesNum;
	int EdgesNum;

	void getMem();
	void cleanMem();

public:
	My_graph() { NodesNum = 0; EdgesNum = 0; };
	My_graph(int nodes);
	My_graph(int** matr, int nodes);

	~My_graph();

	int getNodesNum() { return NodesNum; };
	int getEdgesNum() { return EdgesNum; };
	int** getAdjMatr(int& len);
	//void getIncMatr(int** matr, int& len);
	
	void setAdjMatr(int** matr, int len);
	//void setIncMatr(int** matr, int len);

	int isAdjacent(int node1, int node2);      //checking adjacency between 2 nodes - node1 and node2. If one of the nodes is not exists - return -1. Otherwise, return 0            
	int IsEmpty() { return !NodesNum; };

	void addEdge(int node1, int node2);       //adding edge in graph between 2 nodes - node1 and node2 (if they are exists and there is no edge between them)
	void removeEdge(int node1, int node2);    //removing edge in graph between 2 nodes - node1 and node2 (if they are exists and there is edge between them)

	int init_from_file(const char* file_name);      //reading adjecency matrix from file. Return size number of nodes if the path is correct. Otherwise, return -1
};


#endif
