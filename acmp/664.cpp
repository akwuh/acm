#include <iostream>

using namespace std;

int main() {
	int m, n, k;
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d %d %d", &k, &m, &n);
	if (k < n)
			cout << (m * ((2 * n) / k  + ((2 * n) % k == 0 ? 0 : 1))) << '\n' ;
	else 
		cout << (2 * m);
	return 0;
}