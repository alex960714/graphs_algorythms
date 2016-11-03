#ifndef _MY_GRAPH_H_
#define _MY_GRAPH_H_


class My_graph
{
private:
	int** adj_matr;      //матрица смежности
	int** inc_matr;      //матрица инцидентности
	int NodesNum;

public:
	My_graph() { NodesNum = 0; };
	My_graph(int len);
	My_graph(int** matr, int len, bool is_adj_matr = true);

	~My_graph();

	int getNodesNum() { return NodesNum; };
	void getAdjMatr(int** matr, int& len);
	void getIncMatr(int** matr, int& len);
	
	void setAdjMatr(int** matr, int len);
	void setIncMatr(int** matr, int len);

	bool IsEmpty() { return !NodesNum; };
};


#endif
