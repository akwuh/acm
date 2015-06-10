#include <iostream>

using namespace std;

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int n, k;
	cin >> n >> k;
	int a[100][50];

	for (int i = 0; i < 100; ++i)
	{
		for (int j = 0; j < 50; ++j)
		{
			a[i][j] = 0;
		}
	}

	a[50][0] = 1;

	for (int j = 0; j < k + 2; ++j) {
		for (int i = 0; i < 100; ++i) {
			if (a[i][j]) {
				if (i < 50 + n) a[i + 1][j + 1] += a[i][j];
				if (i < 50 + n) a[i - 1][j + 1] += a[i][j];
			}
		}
	}

	cout << a[50 + n][k];

	system("pause");
	return 0;
}