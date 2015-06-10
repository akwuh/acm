#include <iostream>
#include <vector>

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int i = 1, d, n;
	scanf("%d", &n);
	std::vector<int> v (n + 1, 0);
	while (scanf("%d", &d) == 1)
		v[d] = i++;
	for(std::vector<int>::iterator it = v.begin() + 1; it != v.end(); ++it)
		std::cout << *it << ' ';
	return 0;
}