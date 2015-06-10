#include <iostream>

using namespace std;

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int n, i, m = 0, p = 1;
	int nums[101] = {0};
	scanf("%d", &n);
	while(n--)
	{
		scanf("%d", &i);
		if (nums[i] != 0 && p - nums[i] > m) m = p - nums[i];
		nums[i] = p++;
	}
	cout << m;
	return 0;
}