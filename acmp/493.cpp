#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	ifstream in("input.txt");
	ofstream out("output.txt");

	int n, m, c = 0;
	char ** a;
	in >> n >> m;
	a = new char * [n];
	for (int i = 0; i < n; ++i) {
		a[i] = new char[m];
		for (int j = 0; j < m; ++j)
			while (a[i][j] != '*' && a[i][j] != '.') in >> a[i][j];
	}

	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
		{	
			if (a[i][j] != '.') j++;
			else if (i > 0 && a[i - 1][j] == '*');
			else if (j < m - 1 && a[i][j + 1] == '*');
			else if (i < n - 1 && a[i + 1][j] == '*');
			else if (j > 0 && a[i][j - 1] == '*');
			else c++;
		}			

	out << c;

	return 0;
}