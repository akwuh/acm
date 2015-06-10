#include <iostream>
#include <cstring>

using namespace std;

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	char s[100];
	bool a = true, b = false, c = false;
	scanf("%s",s);
	for (int i = 0; i < strlen(s); ++i) {
		if (s[i] == 'A') swap(a,b);
		else if (s[i] == 'B') swap(c,b);
		else swap(a,c);
	}
	cout << (a ? '1' : b ? '2' : '3');
	return 0;
}