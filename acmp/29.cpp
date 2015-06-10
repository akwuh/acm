#include <iostream>
#include <cmath>

using namespace std;

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int n;
	scanf("%d", &n);
	int a,b,c;
	switch(n)
	{
		case 1: 
			cout << 0;
            break;
        case 2:
        	scanf("%d %d", &a, &b);
        	cout << abs(a - b);
            break;
        default:
        	scanf("%d %d", &a, &b);
        	int pp = 0, p = abs(b - a), cu = 0;
        	while(n-- > 2)
        	{
        		scanf("%d", &c);
        		cu = min(pp + 3*abs(c - a), p + abs(c - b));
        		pp = p;
        		p = cu;
        		a = b;
        		b = c;
        	}
        	cout << cu;
        	break;
        }
	return 0;
}