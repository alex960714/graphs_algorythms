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

void hamilton_cycle::dirac_search(int ** matr, int size, list<int>& path)
{
	int a = 0, curr_vert;
	vector<int> out;

	for (int i = 0; i < size; i++)
		if (i != a)
			out.push_back(i);

	path.push_front(a);

	while (true)
	{
		curr_vert = path.front();
		bool hasNext = false;
		for (vector<int>::iterator it_vect = out.begin(); it_vect != out.end(); ++it_vect)
		{
			if (matr[curr_vert][*it_vect])
			{
				hasNext = true;
				path.push_front(*it_vect);
				out.erase(it_vect);
				break;
			}
		}
		if (!hasNext)
		{
			int new_end_vert = curr_vert;
			for (list<int>::iterator it_list = path.begin(); it_list != path.end(); ++it_list)
			{
				for (vector<int>::iterator it_vect = out.begin(); it_vect != out.end(); ++it_vect)
				{
					if (matr[*it_list][*it_vect])
					{
						new_end_vert = *it_list;
						for (list<int>::iterator it2 = it_list; it2 != path.end();)
						{
							int cand_vert1 = *it2;
							int cand_vert2 = *(++it2);
							if (matr[new_end_vert][cand_vert1] && matr[new_end_vert][cand_vert2])
							{
								path.insert(--it2, curr_vert);
								path.pop_front();
								break;
							}
						}
						break;
					}
				}
				if (new_end_vert != curr_vert)
					break;
			}
		}

		if (out.empty() && matr[path.front()][path.back()])
			return;
		if (out.empty())
			out.push_back(a);
	}
}
