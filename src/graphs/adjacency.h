#ifndef __ADJACENCY_H_INCLUDED__
#define __ADJACENCY_H_INCLUDED__

#define ALLOCATE_CHUNK 10000

#include <malloc.h>
#include <cassert>

// int or double
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
	Node<T> *G;
	int *first;
	AdjacencyList(int /*vertex_count*/);
	void add(int /*_v*/, int /*_u*/, T /*_w*/);
};

template <typename T>
AdjacencyList<T>::AdjacencyList(int _vertex_count) : arc_count(0), vertex_count(_vertex_count)
{
	first = (int*)calloc(vertex_count, sizeof(int));
	G = (Node<T>*)calloc(ALLOCATE_CHUNK, sizeof(Node<T>));
}

template <typename T>
void AdjacencyList<T>::add(int _v, int _u, T _w)
{
	assert(_v >= 0 && _u >= 0);
	if (++arc_count % ALLOCATE_CHUNK == 0)
		G = (Node<T>*)realloc(G, (arc_count + ALLOCATE_CHUNK) * sizeof(Node<T>));
	G[arc_count] = Node<T>(_u, _w, first[_v]);
	first[_v] = arc_count;
}

#endif