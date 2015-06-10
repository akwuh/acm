#include <iostream>
#include <fstream>
#include <limits>
#include <cassert>
#include <malloc.h>

#define ALLOCATOR_CHUNK 1000

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
	AdjacencyList(int);
	void push(int, int, double);
	friend void dijkstra(AdjacencyList const& /*adjacency_list*/, int /*vertex*/, double*& /*weights*/, int*& /*parents*/);
};

AdjacencyList::AdjacencyList(int _vertex_count)
{
	vertex_count = _vertex_count;
	arc_count = 0;
	adjacency = (Node*)calloc(ALLOCATOR_CHUNK, sizeof(Node));
	first = (int*)calloc(vertex_count, sizeof(int));
}

void AdjacencyList::push(int i, int j, double w)
{
	assert(i >= 0 && j >= 0);
	if (++arc_count % ALLOCATOR_CHUNK == 0)
		adjacency = (Node*)realloc(adjacency, (arc_count + ALLOCATOR_CHUNK) * sizeof(Node));
	adjacency[arc_count] = Node(j, w, first[i]);
	first[i] = arc_count;
}

void dijkstra(AdjacencyList const& adjacency_list, int vertex, double*& weights, int*& parents)
{
	bool *used = (bool*)calloc(adjacency_list.vertex_count, sizeof(bool));
	used[vertex] = true;
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

	int w = 0;

	for (int i = 0; i < adjacency_list.vertex_count - 1; ++i)
	{
		for (int j = 0; j < adjacency_list.vertex_count; ++j) {
			if (used[w] || weights[j] < weights[w] && !used[j]) {
				w = j;
			}
		}
		used[w] = true;
		r = adjacency_list.first[w];
		while (r) {
			if (weights[adjacency_list.adjacency[r].v] > weights[w] + adjacency_list.adjacency[r].w) {
				weights[adjacency_list.adjacency[r].v] = weights[w] + adjacency_list.adjacency[r].w;
				parents[adjacency_list.adjacency[r].v] = w;
			}
			r = adjacency_list.adjacency[r].next;
		}
	}
}

using namespace std;

int main()
{
	ifstream in("input.txt");
	ofstream out("output.txt");
	
	int n, m;
	in >> n >> m;
	int ** a = new int*[n];
	AdjacencyList al(n * m);

	for (int i = 0; i < n; ++i) {
		a[i] = new int[m];
		for (int j = 0; j < m; ++j)
			in >> a[i][j];
	}

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			// if (i > 0) al.push(i *m + j, (i - 1) * m + j, a[i - 1][j]);
			if (i < n - 1) al.push(i * m + j, (i + 1) * m + j, a[i + 1][j]);
			// if (j > 0) al.push(i * m + j, i * m + j - 1, a[i][j - 1]);
			if (j < m - 1) al.push(i * m + j, i * m + j + 1, a[i][j + 1]);
		}
	}

	double* weights;
	int* parents;
	dijkstra(al, 0, weights, parents);
	out << (weights[n * m - 1] + a[0][0]);	
	return 0;
}