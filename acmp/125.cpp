#include <iostream>
#include <vector>

using namespace std;

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int n;
	scanf("%d", &n);
	vector< vector<int> > r (n, vector<int>(n));
	vector<int> v(n);
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			scanf("%d", &r[i][j]);
	for (int i = 0; i < n; ++i)
		scanf("%d", &v[i]);

	int k = 0;
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			if (r[i][j] && v[i] != v[j]) k++;

	cout << k/2;
}