#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	ifstream in("input.txt");
	ofstream out("output.txt");
	int s = 1, n;
	in >> n;
	while(n--) s += n + 1;
	out << s;
	return 0;
}