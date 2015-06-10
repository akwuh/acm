#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main()
{
	ifstream in("input.txt");
	ofstream out("output.txt");
	int n, m;
	in >> n >> m;
	int **a = new int*[n];
	for (int i = 0; i < n; ++i)
	{
		a[i] = new int[m];
		for (int j = 0; j < m; ++j)
		{
			in >> a[i][j];
		}
	}

	vector < vector< bool> > v (n, vector<bool>(m, false));

	int min, max, count = 0;
	for (int i = 0; i < n; ++i)
	{
		min = 0;
		for (int j = 0; j < m; ++j)
		{
			if (a[i][j] < a[i][min])
				min = j;
		}
		for (int j = 0; j < m; ++j)
		{
			if (a[i][j] == a[i][min])
				v[i][j] = true;
		}
		
	}

	for (int j = 0; j < m; ++j)
	{
		max = 0;
		for (int i = 0; i < n; ++i)
		{
			if (a[i][j] > a[max][j])
				max = i;
		}
		for (int i = 0; i < n; ++i)
		{
			if (a[i][j] == a[max][j])
				if (v[i][j]) count++;
		}
		
	}

	out << count;
	return 0;
}