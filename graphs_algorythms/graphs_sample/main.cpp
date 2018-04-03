#include <stdio.h>
#include "hamilton_cycle_search.h"
#include "my_graph.h"
#include <stack>
#include <fstream>
#include <Windows.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <string>
using namespace std;

int init_file(const char* file_name);
void init_rand(int size, int perc);
void init_bigraph(int size, int perc);
void init_split(int size, int perc);
void exper(int num, int size, int perc, int type);
void exper_bigraph(int num, int size, int perc);
void exper_split(int num, int size, int perc);
int bron_kerbosch(int size, vector<int> *compsub, vector<int> cand, vector<int> not);
bool search_neighboors(int size, vector<int> cand, vector<int> not);
int BFS(int size);
void exper_dirac(int num, int size, int perc);
bool dirac_check(int size);
void exper_ore(int num, int size, int perc);
bool ore_check(int size);
bool hamilton_check(list<int> path, int size);

int **matr;
stack<int> st;
list<int> path;
My_graph *graph;

int main(int argc, char** argv)
{
	srand(time(NULL));
	setlocale(LC_CTYPE, "Russian");
	int size, perc;
	double st_time, en_time;
	string file_name;
	
	int op, graph_num = 1;

	do
	{
		cout << "Введите номер действия:" << endl << "1. Чтение из файла" << endl << "Заполнение случайными числами:"<<endl<<"2.Обыкновенный граф:" << endl;
		cout << "3.Двудольный граф" << endl << "4.Расщепляемый граф" << endl << "5. Граф Дирака" << endl;
		cout << "6. Граф Оре" << endl;
		cin >> op;

		if (op >= 2 && op <= 6)
		{
			cout << "Введите число вершин:" << endl;
			cin >> size;
			cout << "Введите процент плотности графа:" << endl;
			cin >> perc;
			cout << "Введите число экспериментов:" << endl;
			cin >> graph_num;

			//graph = new My_graph(size);
			matr = new int*[size];
			for (int i = 0; i < size; i++)
				matr[i] = new int[size];
		}
		switch (op)
		{
		case 1:
			cout << "Введите имя или полный путь до файла:" << endl;
			cin >> file_name;
			size = init_file(file_name.c_str());
			if (size == -1)
			{
				cout << "Неверный путь или имя файла!" << endl;
				break;
			}
			perc = 0;
			graph_num = 1;
		case 2:
			exper(graph_num, size, perc, op);
			break;
		case 3:
			exper_bigraph(graph_num, size, perc);
			break;
		case 4:
			exper_split(graph_num, size, perc);
			break;
		case 5:
			exper_dirac(graph_num, size, perc);
			break;
		case 6:
			exper_ore(graph_num, size, perc);
			break;
		}
		
	} while (op < 1 && op > 6);
	//exper(graph_num, size, perc, op - 1);
	

	for (int i = 0; i < size; i++)
		delete[] matr[i];
	delete[] matr;
	return 0;
}

//--------------------------------------------------------//

int init_file(const char* file_name)
{
	ifstream is;
	int size;
	is.open(file_name);

	if (!is.is_open())
		return -1;

	is >> size;
	matr = new int*[size];
	for (int i = 0; i < size; i++)
		matr[i] = new int[size];

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			is >> matr[i][j];
			//printf("%d ", matr[i][j]);
		}
		//printf("\n");
	}
	is.close();
	return size;
}

//--------------------------------------------------//

void init_rand(int size, int perc)
{
	/*matr = new int*[size];
	for (int i = 0; i < size; i++)
		matr[i] = new int[size];*/
	for (int i = 0; i < size; i++)
	{
		matr[i][i] = 0;
		for (int j = i + 1; j < size; j++)
		{
			matr[i][j] = matr[j][i] = (rand() % 100 < perc);
		}
	}

	if (size <= 15)
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				printf("%d ", matr[i][j]);
			}
			printf("\n");
		}
	}
}

//-------------------------------------------------//

void init_bigraph(int size, int perc)
{
	for (int i = 0; i < size/2; i++)
	{
		for (int j = 0; j < size / 2; j++)
		{
			matr[i][j] = matr[j][i] = 0;
		}
		for (int j = size/2; j < size; j++)
		{
			matr[i][j] = matr[j][i] = (rand() % 100 < perc);
			for (int k = size / 2; k < size; k++)
			{
				matr[j][k] = matr[k][j] = 0;
			}
		}
	}
	if (size <= 15)
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
				printf("%d ", matr[i][j]);
			printf("\n");
		}
		printf("\n");
	}
}

//-----------------------------------------------//

void init_split(int size, int perc)
{
	int clique = (int)(size * (perc/100.0));
	for (int i = 0; i < clique; i++)
	{
		for (int j = 0; j < clique; j++)
			matr[i][j] = matr[j][i] = 1;

		matr[i][i] = 0;

		for (int j = clique; j < size; j++)
			matr[i][j] = matr[j][i] = (rand() % 100 < perc);
	}

	for (int i = clique; i < size; i++)
		for (int j = clique; j < size; j++)
			matr[i][j] = matr[j][i] = 0;

	if (size <= 15)
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
				printf("%d ", matr[i][j]);
			printf("\n");
		}
		printf("\n");
	}
}

//----------------------------------------------//

void exper(int num, int size, int perc, int type)
{
	int cyc_num = 0;
	double st_time, en_time, avg_time = 0;
	ofstream os;
	os.open("results.txt");
	for (int i = 0; i < num; i++)
	{
		if (type == 2)
			init_rand(size, perc);
		if (size < 100)
		{
			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					os << matr[i][j] << " ";
				}
				os << endl;
			}
		}
		st_time = GetTickCount() / 1000.0;
		if (hamilton_cycle::search(matr, size, st))
		{
			cyc_num++;
			en_time = GetTickCount() / 1000.0;
			os << "Hamilton cycle:" << endl;
			while (!st.empty())
			{
				os << st.top() << " ";
				st.pop();
			}
			os << endl;
		}
		else
		{
			en_time = GetTickCount() / 1000.0;
			os << "No hamilton cycle" << endl;
		}

		os << "Time: " << (en_time - st_time) << endl;
		avg_time = (avg_time*i + (en_time - st_time)) / (i + 1);
		
		/*for (int i = 0; i < size; i++)
			delete[] matr[i];
		delete[] matr;*/

		os << "---------------------------" << endl;
	}

	cout << endl << "Число графов с гамильтоновым циклом: " << cyc_num << endl;
	cout << "Среднее время вычислений: " << avg_time << endl;

	os << endl << "Число графов с гамильтоновым циклом: " << cyc_num << endl;
	os << "Среднее время вычислений: " << avg_time << endl;
	os.close();
}

//----------------------------------------------//

void exper_bigraph(int num, int size, int perc)
{
	int cyc_num = 0;
	double st_time, en_time, avg_time = 0;
	ofstream os;
	os.open("results.txt");
	for (int i = 0; i < num; i++)
	{
		init_bigraph(size, perc);
		if (size < 100)
		{
			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					os << matr[i][j] << " ";
				}
				os << endl;
			}
		}
		st_time = GetTickCount() / 1000.0;

		/*for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				if (i != j)
					matr[i][j] = 1 - matr[i][j];*/
		//int part_size = bron_kerbosch(size, clique, candidates, not);
		/*int part_size = BFS(size);
		os << "Partition size: " << part_size << endl;*/

		/*for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				if (i != j)
					matr[i][j] = 1 - matr[i][j];*/
		if (/*part_size == size/2 && */hamilton_cycle::search(matr, size, st))
		{
			cyc_num++;
			en_time = GetTickCount() / 1000.0;
			os << "Hamilton cycle:" << endl;
			while (!st.empty())
			{
				os << st.top() << " ";
				st.pop();
			}
			os << endl;
		}
		else
		{
			en_time = GetTickCount() / 1000.0;
			os << "No hamilton cycle" << endl;
		}

		os << "Time: " << (en_time - st_time) << endl;
		avg_time = (avg_time*i + (en_time - st_time)) / (i + 1);

		/*for (int i = 0; i < size; i++)
		delete[] matr[i];
		delete[] matr;*/

		os << "---------------------------" << endl;
	}

	cout << endl << "Число графов с гамильтоновым циклом: " << cyc_num << endl;
	cout << "Среднее время вычислений: " << avg_time << endl;

	os << endl << "Число графов с гамильтоновым циклом: " << cyc_num << endl;
	os << "Среднее время вычислений: " << avg_time << endl;
	os.close();
}

//---------------------------------------------//

void exper_split(int num, int size, int perc)
{
	int cyc_num = 0;
	double st_time, en_time, avg_time = 0;
	vector<int> *clique, candidates, not;
	clique = new vector<int>();
	for (int i = 0; i < size; i++)
	{
		candidates.push_back(i);
	}
	ofstream os;
	os.open("results.txt");
	for (int i = 0; i < num; i++)
	{
		init_split(size, perc);
		if (size < 100)
		{
			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					os << matr[i][j] << " ";
				}
				os << endl;
			}
		}
		st_time = GetTickCount() / 1000.0;
		int clique_size = bron_kerbosch(size, clique, candidates, not);
		os << "Clique size: " << clique_size << endl;
		if (clique_size >= size/2 && hamilton_cycle::search(matr, size, st))
		{
			cyc_num++;
			en_time = GetTickCount() / 1000.0;
			os << "Hamilton cycle:" << endl;
			while (!st.empty())
			{
				os << st.top() << " ";
				st.pop();
			}
			os << endl;
		}
		else
		{
			en_time = GetTickCount() / 1000.0;
			os << "No hamilton cycle" << endl;
		}

		os << "Time: " << (en_time - st_time) << endl;
		avg_time = (avg_time*i + (en_time - st_time)) / (i + 1);

		/*for (int i = 0; i < size; i++)
		delete[] matr[i];
		delete[] matr;*/

		os << "---------------------------" << endl;
	}

	cout << endl << "Число графов с гамильтоновым циклом: " << cyc_num << endl;
	cout << "Среднее время вычислений: " << avg_time << endl;

	os << endl << "Число графов с гамильтоновым циклом: " << cyc_num << endl;
	os << "Среднее время вычислений: " << avg_time << endl;
	os.close();
}

//-------------------------------------------------//

int bron_kerbosch(int size, vector<int> *compsub, vector<int> cand, vector<int> not)
{
	int curr_size = 0;
	vector<int>::iterator it;
	vector<int> new_cand, new_not;

	while (!cand.empty() && !search_neighboors(size, cand, not))
	{
		int curr_vert = cand.back();
		compsub->push_back(curr_vert);
		new_cand.clear();
		new_not.clear();

		for (it = cand.begin(); it != cand.end(); ++it)
		{
			if (matr[*it][curr_vert])
				new_cand.push_back(*it);
		}
		for (it = not.begin(); it != not.end(); ++it)
		{
			if (matr[*it][curr_vert])
				new_not.push_back(*it);
		}

		int new_size;
		if (new_cand.empty() && new_not.empty())
			new_size = compsub->size();
		else
			new_size = bron_kerbosch(size, compsub, new_cand, new_not);
		
		if (new_size > curr_size) curr_size=new_size;
		compsub->pop_back();
		cand.pop_back();
		not.push_back(curr_vert);
	}
	return curr_size;
}

//---------------------------------------------------//

bool search_neighboors(int size, vector<int> cand, vector<int> not)
{
	if (not.empty()) return false;
	vector<int>::iterator it1, it2;
	for (it1 = not.begin(); it1 != not.end(); ++it1)
	{
		for (it2 = cand.begin(); it2 != cand.end(); ++it2)
		{
			if (!matr[*it1][*it2])
				return false;
		}
	}
	return true;
}

//---------------------------------------------------//

int BFS(int size)
{
	int curr_vert, part = 0;
	int *part_num = new int[size];
	queue<int> q;
	q.push(0);
	part_num[0] = 1;
	for (int i = 1; i < size; i++)
		part_num[i] = 0;
	while (!q.empty())
	{
		curr_vert = q.front();
		q.pop();
		for (int i = 0; i < size; i++)
		{
			if (matr[curr_vert][i] && !part_num[i])
			{
				q.push(i);
				part_num[i] = 3 - part_num[curr_vert];
				if (part_num[i] == 2)
					part++;
			}
		}
	}
	return part;
}

//--------------------------------------------------//

void exper_dirac(int num, int size, int perc)
{
	int cyc_num = 0, dirac_num = 0, fails_num = 0;
	double st_time, en_time, avg_time = 0, dirac_time = 0;
	ofstream os;
	list<int>::iterator it;
	os.open("results.txt");
	for (int i = 0; i < num; i++)
	{
		init_rand(size, perc);
		if (size < 100)
		{
			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					os << matr[i][j] << " ";
				}
				os << endl;
			}
		}
		st_time = GetTickCount() / 1000.0;
		if (dirac_check(size))
		{
			dirac_num++;
			hamilton_cycle::dirac_search(matr, size, path);
			en_time = GetTickCount() / 1000.0;
			dirac_time = (dirac_time*(dirac_num - 1) + (en_time - st_time)) / dirac_num;
			os << "Result:" << endl;
			for(it = path.begin(); it != path.end(); ++it)
			{
				os << *it << " ";
			}
			os << endl;
			if (hamilton_check(path, size))
			{
				os << "PASSED: hamilton cycle" << endl;
				cyc_num++;
			}
			else
			{
				os << "FAILED: NOT a namilton cycle!!!" << endl;
				fails_num++;
			}
			path.clear();
		}
		/*else if(hamilton_cycle::search(matr, size, st))
		{
			cyc_num++;
			en_time = GetTickCount() / 1000.0;
			os << "Not a Dirac graph" << endl;
			os << "Hamilton cycle:" << endl;
			while (!st.empty())
			{
				os << st.top() << " ";
				st.pop();
			}
			os << endl;
		}*/
		else
		{
			en_time = GetTickCount() / 1000.0;
			os << "Not a Dirac graph" << endl;
			//os << "No hamilton cycle" << endl;
		}

		os << "Time: " << (en_time - st_time) << endl;
		avg_time = (avg_time*i + (en_time - st_time)) / (i + 1);

		os << "---------------------------" << endl;
	}

	cout << endl << "Число графов Дирака: " << dirac_num << endl;
	cout << endl << "Число графов с гамильтоновым циклом: " << cyc_num << endl;
	cout << endl << "Число ошибок: " << fails_num << endl;
	cout << "Среднее время вычислений: " << avg_time << endl;
	cout << "Время для графов Дирака: " << dirac_time << endl;
	if (fails_num)
		cout << endl << "ОШИБКА: есть графы с ошибками" << endl;

	os << endl << "Число графов Дирака: " << dirac_num << endl;
	os << endl << "Число графов с гамильтоновым циклом: " << cyc_num << endl;
	os << endl << "Число ошибок: " << fails_num << endl;
	os << "Среднее время вычислений: " << avg_time << endl;
	os << "Время для графов Дирака: " << dirac_time << endl;
	if (fails_num)
		os << endl << "ОШИБКА: есть графы с ошибками" << endl;
	os.close();
}

//-------------------------------------------------//

bool dirac_check(int size)
{
	for (int i = 0; i < size; i++)
	{
		int power = 0;
		for (int j = 0; j < size; j++)
			if (matr[i][j])
				power++;

		if (power < size / 2)
			return false;
	}
	return true;
}

//--------------------------------------------------//

void exper_ore(int num, int size, int perc)
{
	int cyc_num = 0, ore_num = 0, fails_num = 0;
	double st_time, en_time, avg_time = 0, ore_time = 0;
	ofstream os;
	list<int>::iterator it;
	os.open("results.txt");
	for (int i = 0; i < num; i++)
	{
		init_rand(size, perc);
		if (size < 100)
		{
			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					os << matr[i][j] << " ";
				}
				os << endl;
			}
		}
		st_time = GetTickCount() / 1000.0;
		if (ore_check(size))
		{
			ore_num++;
			hamilton_cycle::dirac_search(matr, size, path);
			en_time = GetTickCount() / 1000.0;
			ore_time = (ore_time*(ore_num - 1) + (en_time - st_time)) / ore_num;
			os << "Result:" << endl;
			for (it = path.begin(); it != path.end(); ++it)
			{
				os << *it << " ";
			}
			os << endl;
			if (hamilton_check(path, size))
			{
				os << "PASSED: hamilton cycle" << endl;
				cyc_num++;
			}
			else
			{
				os << "FAILED: NOT a namilton cycle!!!" << endl;
				fails_num++;
			}
			path.clear();
		}
		else
		{
			en_time = GetTickCount() / 1000.0;
			os << "Not an Ore graph" << endl;
		}

		os << "Time: " << (en_time - st_time) << endl;
		avg_time = (avg_time*i + (en_time - st_time)) / (i + 1);

		os << "---------------------------" << endl;
	}

	cout << endl << "Число графов Оре: " << ore_num << endl;
	cout << endl << "Число графов с гамильтоновым циклом: " << cyc_num << endl;
	cout << endl << "Число ошибок: " << fails_num << endl;
	cout << "Среднее время вычислений: " << avg_time << endl;
	cout << "Время для графов Оре: " << ore_time << endl;
	if (fails_num)
		cout << endl << "ОШИБКА: есть графы с ошибками" << endl;

	os << endl << "Число графов Оре: " << ore_num << endl;
	os << endl << "Число графов с гамильтоновым циклом: " << cyc_num << endl;
	os << endl << "Число ошибок: " << fails_num << endl;
	os << "Среднее время вычислений: " << avg_time << endl;
	os << "Время для графов Оре: " << ore_time << endl;
	if (fails_num)
		os << endl << "ОШИБКА: есть графы с ошибками" << endl;
	os.close();
}

//-------------------------------------------------//

bool ore_check(int size)
{
	int* power = new int[size];
	for (int i = 0; i < size; i++)
		power[i] = 0;

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			power[i] += matr[i][j];

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			if (i != j && !matr[i][j] && power[i] + power[j] < size)
				return false;

	return true;
}

//------------------------------------------------//

bool hamilton_check(list<int> path, int size)
{
	int* checked = new int[size];
	for (int i = 0; i < size; i++)
		checked[i] = 0;
	list<int>::iterator it = path.begin();
	list<int>::iterator temp = path.begin();
	++temp;
	for (; temp != path.end(); ++it, ++temp)
	{
		if (!matr[*it][*(temp)] || checked[*it])
		{
			delete[] checked;
			return false;
		}
		checked[*it]++;
	}
	if (matr[path.front()][path.back()] && !checked[path.back()])
	{
		delete[] checked;
		return true;
	}
	delete[] checked;
	return false;
}

