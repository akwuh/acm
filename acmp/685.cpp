#include <iostream>

using namespace std;

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int a[3], b[3];
	scanf("%d %d %d %d %d %d", &a[0], &a[1], &a[2], &b[0], &b[1], &b[2]);
	for (int i = 0; i < 3; i++)
		for (int j = i; j < 3; j++) {
			if (a[i] > a[j]) swap(a[i], a[j]);
			if (b[i] > b[j]) swap(b[i], b[j]);
		}
	cout << (a[0] * b[0] + a[1] * b[1] + a[2] * b[2]);
	return 0;
}