#include <iostream>
#include <cstring>
#include <unordered_map>
#include <vector>
#include <set>
#include <locale>
using namespace std;



/**
 * @param n_rows The number of rows in the target pattern.
 * @param n_cols The number of columns in the target pattern.
 * @param target_pattern The target pattern, row by row from left to right.
 * @return The shortest possible list of pixel coordinates to activate in order to reproduce the target pattern.
 */

void	substract_row(vector<int> &a, vector<int> &b, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (a[i] + b[i] == 1)
			a[i] = 1;
		else
			a[i] = 0;
	}
}

void	eliminate(vector<vector<int>> &x, vector<int> &b, int size, int rm)
{
	vector<int>	elim;
	int			find = -1;

	for (int i = rm; i < size; i++)
	{
		if (x[i][rm])
		{
			if (find < 0)
			{
				elim = x[i];
				find = i;
			}
			else
			{
				if (b[i] + b[find] == 1)
					b[i] = 1;
				else
					b[i] = 0;
				substract_row(x[i], elim, size);
			}
		}
	}
	if (find > 0)
	{
		int temp = b[rm];
		b[rm] = b[find];
		b[find] = temp;
		x[find] = x[rm];
		x[rm] = elim;
	}
}

void	calculate_root(vector<int> &solution, vector<vector<int>> &x, vector<int> &b, int size, int index)
{
	int	res = b[size - 1 - index];

	for (int i = size - index; i < size; i++)
	{
		if (x[size - 1 - index][i])
			res += solution[size - 1 - i];
	}
	solution.push_back(res % 2);
}

vector<vector<int>> createPattern(int n_rows, int n_cols, vector<string> map)
{
	vector<int> temp(n_rows * n_cols, 0);
	vector<vector<int>> x(n_rows * n_cols, temp);
	vector<int> b;
	vector<int> solution;
	vector<vector<int>> res;

	int		size = n_rows * n_cols;

	for (int i = 0; i < n_rows; i++)
	{
		for (int j = 0; j < n_cols; j++)
		{
			if (map[i][j] == '#')
			{
				b.push_back(1);
			}
			else
			{
				b.push_back(0);
			}
			x[i * n_cols + j][i * n_cols + j] = 1;
			if (i > 0)
				x[i * n_cols + j][(i - 1) * n_cols + j] = 1;
			if (i < n_rows - 1)
				x[i * n_cols + j][(i + 1) * n_cols + j] = 1;
			if (j > 0)
				x[i * n_cols + j][i * n_cols + (j - 1)] = 1;
			if (j < n_cols - 1)
				x[i * n_cols + j][i * n_cols + (j + 1)] = 1;
		}
	}
//	for (int i = 0; i < size; i++)
//	{
//		for (int j = 0; j < size; j++)
//		{
//			printf("%d ", x[i][j]);
//		}
//		printf(" = %d", b[i]);
//		printf("\n");
//	}
	for (int i = 0; i < size; i++)
	{
//		printf("i = %d\n", i);
		eliminate(x, b, size, i);
//		for (int i = 0; i < size; i++)
//		{
//			for (int j = 0; j < size; j++)
//			{
//				printf("%d ", x[i][j]);
//			}
//			printf(" = %d", b[i]);
//			printf("\n");
//		}
	}
	for (int i = 0; i < size; i++)
	{
		calculate_root(solution, x, b, n_cols * n_rows, i);
	}
	for (int i = size - 1; i >= 0; i--)
	{
		if (solution[i])
			res.push_back({n_rows - 1 - i / n_cols, n_co - 1 - i % n_cols});
	}
	for (int i = 0; i < res.size(); i++)
	{
		printf("(%d, %d)\n", res[i][0], res[i][1]);
	}
	return (res);
}

int main ()
{
	vector<string> map;
	map.push_back("....");
	map.push_back(".#..");
	map.push_back("...#");

	createPattern(3, 4, map);
}
/* Ignore and do not change the code above */
