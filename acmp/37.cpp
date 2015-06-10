#include <iostream>

using namespace std;

float norm(int& a, int& b)
{
	return a * a + b * b;
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int n, x1, x2, y1, y2;
	float q;
	scanf("%d %f", &n, &q);
	while (n)
	{
		scanf("%d %d %d %d", &x1, &x2, &y1, &y2);
		if (norm(y1, y2) > q * q * norm(x1, x2)) break;
		n--;
	}
	cout << ( n == 0 ? "Yes" : "No");
}