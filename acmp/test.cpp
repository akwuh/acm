#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

int main() {
	int n;
	__int64 s = 0;
	
	cin >> n;
	
	for (int p = 1; p <= 9; ++p)
	{
		vector< vector< vector<__int64> > > v (n + 1, vector< vector<__int64> > (11, vector<__int64> (4, 0)));
		v[1][p][0 + (int)(p == 0) + 2 * (int)(p == 9)] = 1;

		for (int i = 2; i <= n; ++i)
			for (int j = 0; j <= 9; ++j)
			{
				if (j > 0)
					for (int k = 0; k < 4; ++k)
				 		v[i][j][k] = v[i][j][k] + v[i - 1][j - 1][k];
			 	for (int k = 0; k < 4; ++k)
			 		v[i][j][k] = v[i][j][k] + v[i - 1][j + 1][k];

				if (j == 0 || j == 9) {
					v[i][j][1 + (int)(j == 9)] += v[i][j][0];
					v[i][j][0] = 0;
					v[i][j][3] += v[i][j][1 + (int)(j == 0)];
					v[i][j][1 + (int)(j == 0)] = 0;
				}
				s += v[i][j][3];
			}
	}
	cout << s;
}