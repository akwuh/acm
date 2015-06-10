#include <iostream>
#include <fstream>
#include <limits>
#include <cassert>
#include <malloc.h>
#include <algorithm>

#define ALLOCATE_CHUNK 100000

struct Node
{
	Node(int _v, double _w, int _next = 0) : v(_v), w(_w), next(_next){};
	int v, next;
	double w;
};

class AdjacencyList
{
private:
	int arc_count, vertex_count;
	Node *adjacency;
	int *first;
public:
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

void ford(AdjacencyList const& adjacency_list, int vertex, double*& weights, int*& parents)
{
	weights = new double[adjacency_list.vertex_count];
	parents = new int[adjacency_list.vertex_count];
	for (int i = 0; i < adjacency_list.vertex_count; ++i)
		weights[i] = std::numeric_limits<double>::infinity();
	int r = adjacency_list.first[vertex];
	while (r) {
		weights[adjacency_list.adjacency[r].v] = adjacency_list.adjacency[r].w;
		r = adjacency_list.adjacency[r].next;
	}
	weights[vertex] = 0;
	for (int i = 0; i < adjacency_list.vertex_count - 1; ++i) {
		for (int j = 0; j < adjacency_list.vertex_count; ++j) {
			r = adjacency_list.first[j];
			while (r) {
				if (weights[adjacency_list.adjacency[r].v] > weights[j] + adjacency_list.adjacency[r].w) {
					weights[adjacency_list.adjacency[r].v] = weights[j] + adjacency_list.adjacency[r].w;
					parents[adjacency_list.adjacency[r].v] = j;
				}
				r = adjacency_list.adjacency[r].next;
			}
		}
	}
}

using namespace std;

template<typename T>
T absolute(T t){
	return t < 0 ? -t : t;
}

int main()
{
	ifstream in("input.txt");
	ofstream out("output.txt");
	int n, m;
	short a, b, c;

	in >> n >> m;

	AdjacencyList al(n);

	for (int i = 0; i < m; ++i) {
		in >> a >> b >> c;
		al.push(a - 1, b - 1, c);
	}

	double* weights;
	int* parents;
	ford(al, 0, weights, parents);

	for (int i = 0; i < n; ++i)

		out << (weights[i] == std::numeric_limits<double>::infinity() ? 30000 : weights[i]) << ' ';

	return 0;
}