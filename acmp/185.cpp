#include <iostream>
#include <fstream>
#include <vector>

struct 	Edge{
	Edge(int x, int y) : x(x), y(y){};
	int x, y;
};

using namespace std;

int main() {
	ifstream in("input.txt");
	ofstream out("output.txt");
	vector<Edge> edges;
	short a, b, n, k;
	in >> n >> k;
	vector<int> c(n + 1, 1);

	in >> a;
	while (a) {
		in >> b;
		edges.push_back(Edge(a, b));
		in >> a;
	}

	c[k] = 0;

	for (int i = 0; i < n; ++i)
		for (vector<Edge>::iterator it = edges.begin() ; it != edges.end(); ++it)
			if (c[it->x] == 0) c[it->y] = 0;

	for (int i = 1; i < n + 1; ++i)
		if (c[i]) {
			out << "No";
			return 0;
		}
		
	out << "Yes";
	return 0;
}