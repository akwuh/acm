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
public:
	int arc_count, vertex_count;
	Node *adjacency;
	int *first;
	AdjacencyList(int /*vertex_count*/);
	void push(int /*_i*/, int /*_j*/, double /*_w*/);
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

bool ford(AdjacencyList const& adjacency_list, int vertex, double*& weights, int*& parents)
{
	weights = new double[adjacency_list.vertex_count];
	parents = new int[adjacency_list.vertex_count];
	for (int i = 0; i < adjacency_list.vertex_count; ++i)
		weights[i] = std::numeric_limits<double>::infinity();
	int r = adjacency_list.first[vertex];
	while (r) {
		weights[adjacency_list.adjacency[r].v] = adjacency_list.adjacency[r].w;
		parents[adjacency_list.adjacency[r].v] = vertex;
		r = adjacency_list.adjacency[r].next;
	}
	weights[vertex] = 0;
	for (int k = 0; k < adjacency_list.vertex_count - 1; ++k) {
		for (int i = 0; i < adjacency_list.vertex_count; ++i){
			r = adjacency_list.first[i];
			while(r) {
				if (weights[adjacency_list.adjacency[r].v] > weights[i] + adjacency_list.adjacency[r].w) {
					weights[adjacency_list.adjacency[r].v] = weights[i] + adjacency_list.adjacency[r].w;
					parents[adjacency_list.adjacency[r].v] = i;
				}
				r = adjacency_list.adjacency[r].next;
			}
		}
	}

	for (int i = 0; i < adjacency_list.vertex_count; ++i){
		r = adjacency_list.first[i];
		while(r) {
			if (weights[adjacency_list.adjacency[r].v] > weights[i] + adjacency_list.adjacency[r].w) {
				return true;
			}
			r = adjacency_list.adjacency[r].next;
		}
	}
	return false;
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
	int n, tmp;
	in >> n;

	AdjacencyList al(n);

	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j) {
			in >> tmp;
			al.push(i, j, tmp == 100000 ? 10000000 : tmp);
		}

	double *weights;
	int *parents;
	bool *v = new bool[n];
	for (int i = 0; i < n; ++i)
		v[i] = false;

	out << (ford(al, 0, weights, parents) ? "YES" : "NO");
	return 0;
}