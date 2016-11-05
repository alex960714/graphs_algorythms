#ifndef _HAM_CYC_SEARCH_H_
#define _HAM_CYC_SEARCH_H_

#include <stack>
using namespace std;

void init(int **matr, int size, stack<int> &st, int node)
{
	while (!st.empty())
		st.pop();

	for (int i = 0; i < size;i++)
		if (matr[node][i])
			st.push(i);
}

bool find_elem(stack<int> st, int elem)
{
	while (!st.empty())
	{
		if (st.top() == elem)
			return true;
		st.pop();
	}
	return false;
}

bool search(int **matr, int size, stack<int> &path)
{
	int a = 0;
	//stack<int> path;
	stack<int> *N = new stack<int>[size];

	path.push(a);
	for (int i = 0; i < size; i++)
		init(matr, size, N[i], i);

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
					return false;
			}
		}
		else
		{
			path.pop();
		}
	}
	return false;
}


#endif
