#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

int  main()
{
	ifstream in("input.txt");
	ofstream out("output.txt");
	int n, max = 1;
	int l, c, s = 1;
	bool tr;
	in >> n >> l;
	if (n != 1) {
		while (in.good()) {
			in >> c;
			if (c != l && (s == 1 || (c > l) ^ tr)) {
				++s;
			} else {
				max = std::max(max, s);
				s = 1 + (c != l);
			}
			tr = c > l;
			l = c;
		}
		max = std::max(max, s);
	}
	out << max;
	return 0;
}