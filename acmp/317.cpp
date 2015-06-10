#include <iostream>

using namespace std;

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int x, y, z, w, a = 0, b, c, count = 0;
	scanf("%d %d %d %d", &x, &y, &z, &w);
	while (a*x <= w){
		b = 0;
		while (a*x + b*y <= w){
			c = 0;
			while (a*x + b*y + c*z <= w){
				if (a*x + b*y + c*z == w) count++;
				c++;
			}
			b++;
		}
		a++;
	}
	cout << count;
}