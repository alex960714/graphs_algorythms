#ifndef _HAM_CYC_SEARCH_H_
#define _HAM_CYC_SEARCH_H_

#include <stack>
#include <list>
#include <vector>
using namespace std;

class hamilton_cycle
{
private:
	static void init(int **matr, int size, stack<int> &st, int node);
	static bool find_elem(stack<int> st, int elem);

public:
	static bool search(int **matr, int size, stack<int> &path);
	static void dirac_search(int **matr, int size, list<int> &path);
};


#endif
