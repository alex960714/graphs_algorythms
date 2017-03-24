#include "hamilton_cycle_search.h"

void hamilton_cycle::init(int **matr, int size, stack<int> &st, int node)
{
	while (!st.empty())
		st.pop();

	for (int i = 0; i < size; i++)
		if (matr[node][i])
			st.push(i);
}

bool hamilton_cycle::find_elem(stack<int> st, int elem)
{
	while (!st.empty())
	{
		if (st.top() == elem)
			return true;
		st.pop();
	}
	return false;
}

bool hamilton_cycle::search(int **matr, int size, stack<int> &path)
{
	int a = 0;                              //стартовая вершина
	stack<int> *N = new stack<int>[size];   //множество вершин, смежных с текущей, ребро между которыми ещё не рассматривалось

	path.push(a);
	init(matr, size, N[a], a);				//инициализация множества смежных вершин

	while (!path.empty())
	{
		int x = path.top();
		if (!N[x].empty())
		{
			int y = N[x].top();
			N[x].pop();
			if (!find_elem(path, y))
			{
				path.push(y);
				init(matr, size, N[y], y);
				if (path.size() == size && matr[path.top()][a])
					return true;
				else if (path.size() == size)
					path.pop();
			}
		}
		else
		{
			path.pop();
		}
	}
	return false;
}