#include <iostream>
#include <fstream>
#include <limits>
#include <cassert>
#include <malloc.h>
#include <algorithm>
#include <stack>

#define ALLOCATE_CHUNK 100000

struct Node
{
	Node(int _v, double _w, int _next = 0) : v(_v), w(_w), next(_next){};
	int v, next;
	double w;
};

class AdjacencyList
{
public:
	int arc_count, vertex_count;
	Node *adjacency;
	int *first;
	AdjacencyList(int /*vertex_count*/);
	void push(int /*_i*/, int /*_j*/, double /*_w*/);
	friend void dijkstra(AdjacencyList const& /*adjacency_list*/, int /*vertex*/, double*& /*weights*/, int*& /*parents*/);
	friend void ford(AdjacencyList const& /*adjacency_list*/, int /*vertex*/, double*& /*weights*/, int*& /*parents*/);
};

AdjacencyList::AdjacencyList(int _vertex_count) : arc_count(0), vertex_count(_vertex_count)
{
	first = (int*)calloc(vertex_count, sizeof(int));
	adjacency = (Node*)calloc(ALLOCATE_CHUNK, sizeof(Node));
}

void AdjacencyList::push(int _i, int _j, double _w)
{
	assert(_i >= 0 && _j >= 0);
	if (++arc_count % ALLOCATE_CHUNK == 0)
		adjacency = (Node*)realloc(adjacency, (arc_count + ALLOCATE_CHUNK) * sizeof(Node));
	adjacency[arc_count] = Node(_j, _w, first[_i]);
	first[_i] = arc_count;
}

bool graphIsTree(AdjacencyList const& adjacency_list)
{
	bool *used = (bool*)calloc(adjacency_list.vertex_count, sizeof(bool));
	used[0] = true;
	std::stack<int> s;
	s.push(0);
	int r, c;
	while (!s.empty()) {
		r = s.top();
		s.pop();
		r = adjacency_list.first[r];
		c = 0;
		while (r) {
			if (used[adjacency_list.adjacency[r].v]) {
				c++;
			} else {
				s.push(adjacency_list.adjacency[r].v);
				used[adjacency_list.adjacency[r].v] = true;
			}
			r = adjacency_list.adjacency[r].next;
		}
		if (c > 1)
			return false;
	}

	for (int i = 0; i < adjacency_list.vertex_count; ++i)
		if (!used[i]) return false;
	return true;
}

using namespace std;

int main()
{
	ifstream in("input.txt");
	ofstream out("output.txt");
	int n, tmp;
	in >> n;
	AdjacencyList al(n);

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j)
		{
			in >> tmp;
			if (tmp)
				al.push(i, j, 0);
		}
	}
	out << (graphIsTree(al) ? "YES" : "NO");	
	return 0;
}