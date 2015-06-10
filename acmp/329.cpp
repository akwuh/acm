#include <iostream>
#include <fstream>
#include <limits>
#include <cassert>
#include <malloc.h>
#include <string>
#include <sstream>
#include <stack>

#define ALLOCATE_CHUNK 100000

template <typename T>
struct Node
{
	Node(int _v, T _w, int _next = 0) : v(_v), w(_w), next(_next){};
	int v, next;
	T w;
};

template <typename T>
class AdjacencyList
{
public:
	int arc_count, vertex_count;
	Node<T> *adjacency;
	int *first;
	AdjacencyList(int /*vertex_count*/);
	void add(int /*_v*/, int /*_u*/, T /*_w*/);
};

template <typename T>
AdjacencyList<T>::AdjacencyList(int _vertex_count) : arc_count(0), vertex_count(_vertex_count)
{
	first = (int*)calloc(vertex_count, sizeof(int));
	adjacency = (Node<T>*)calloc(ALLOCATE_CHUNK, sizeof(Node<T>));
}

template <typename T>
void AdjacencyList<T>::add(int _v, int _u, T _w)
{
	assert(_v >= 0 && _u >= 0);
	if (++arc_count % ALLOCATE_CHUNK == 0)
		adjacency = (Node<T>*)realloc(adjacency, (arc_count + ALLOCATE_CHUNK) * sizeof(Node<T>));
	adjacency[arc_count] = Node<T>(_u, _w, first[_v]);
	first[_v] = arc_count;
}

template <typename T>
void dijkstra(AdjacencyList<T> const& adjacency_list, int vertex, T*& weights, int*& parents)
{
	bool *used = (bool*)calloc(adjacency_list.vertex_count, sizeof(bool));
	used[vertex] = true;
	weights = new T[adjacency_list.vertex_count];
	parents = new int[adjacency_list.vertex_count];
	for (int i = 0; i < adjacency_list.vertex_count; ++i)
		weights[i] = 0;
	
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
			if (used[w] || weights[j] > weights[w] &&  !used[j]) {
				w = j;
			}
		}
		used[w] = true;
		r = adjacency_list.first[w];
		while (r) {
			if (weights[adjacency_list.adjacency[r].v] < weights[w] + adjacency_list.adjacency[r].w) {
				weights[adjacency_list.adjacency[r].v] = weights[w] + adjacency_list.adjacency[r].w;
				parents[adjacency_list.adjacency[r].v] = w;
			}
			r = adjacency_list.adjacency[r].next;
		}
	}
}

using namespace std;

string itos(int i)
{
	stringstream s;
	s << i;
	return s.str();
}

int main()
{
	ifstream in("input.txt");
	ofstream out("output.txt");
	int n, c, f, s, r, start;
	stack<int> st;
	string s1;
	in >> n;

	if (n == 1) {
		in >> s;
		out << s << "\n1";
		return 0;
	}

	AdjacencyList<int> al(n);

	int i = 0;
	while (i < n) {
		in >> c;
		if (i == 0) f = c;
		if (i > 0) al.add(i - 1, i, c);
		if (i == 1) s = c;
		if (i > 1) al.add(i - 2, i, c);
		i++;
	}	

	int *p1, *p2;
	int *w1, *w2;

	dijkstra(al, 0, w1, p1);	
	dijkstra(al, 1, w2, p2);

	st.push(n);
	if (f + w1[n - 1] > s + w2[n - 1]) {
		out << (f + w1[n - 1]) << '\n';
		start = 0;
	} else {
		out << (s + w2[n - 1]) << '\n';
		p1 = p2;
		start = 1;
	}
	r = p1[n - 1];
	if (n - 1 != start) st.push(r + 1);
	while (r && n - 1 != start) {
		r = p1[r];
		st.push(r + 1);
	}
	while (!st.empty()) {
		out << st.top() << ' ';
		st.pop();
	}

	return 0;
}