#include <iostream>
#include <cmath>

using namespace std;

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	float a,b,c;
	scanf("%f %f %f", &a, &b, &c);
	float x1,x2, d = sqrt(b * b - 4 * a * c);
	char const * s =
		a == 0 
			? b == 0 
				? c == 0 
					? "-1" 
					: "0"
				: "1\n%f"
			: d == 0
				? "1\n%f"
				: d > 0 
					? "2\n%f\n%f" : "0";
	x1 = 
		a != 0
			? (-b + d)/2/a
			: c == 0
				? 0 : -c/b; 
	if (a != 0) x2 = (-b - d)/2/a;
	printf(s, x1, x2);
	return 0;
}