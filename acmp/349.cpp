#include <iostream>

using namespace std;

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int a, b, j = 3, i, t, n = 1, o = 0;;
	scanf("%d %d", &a, &b);
	int p[100000] = {2};
	if (2 >= a && 2 <= b) {
		cout << "2 ";
		o = 1;
	}
	while (j <= b)
	{
		t = i = 0;
		while (p[i] * p[i] <= j)
			if (j % p[i++] == 0) t = 1;
		if (!t) p[n++] = j;
		if (!t && j >= a) {
			cout << j << ' ';
			o = 1;
		}
		j+=2;
	}
	if (!o) cout << "Absent";
}