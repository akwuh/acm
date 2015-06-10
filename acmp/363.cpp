#include <iostream>
#include <cstring>

using namespace std;

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	char a [2501], b [2501];
	short c [5005];
	short p, k;
	int m = 0;
	scanf("%s %s", a, b);
	for (int i = 0; i < strlen(a); ++i)
		for (int j = 0; j < strlen(b); j++)
		{
			p = (a[i] - '0') * (b[j] - '0');
			k = (strlen(a) - i) + (strlen(b) - j) - 2;
			while (p > 0)
			{
				p += c[k];
				if (k > m) m = k;
				c[k++] = p % 10000;
				p/=10000;
			}
		}
	for (int i = m; i >= 0; i--)
		cout << c[i];
	return 0;
}