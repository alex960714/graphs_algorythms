#ifndef _MY_GRAPH_H_
#define _MY_GRAPH_H_


class My_graph
{
private:
	int** adj_matr;      //матрица смежности
	//int** inc_matr;      //матрица инцидентности
	int NodesNum;
	int EdgesNum;

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

	bool isAdjacent(int node1, int node2);                  
	bool IsEmpty() { return !NodesNum; };
};


#endif
