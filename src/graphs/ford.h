#ifndef __FJORD_H_INCLUDED__
#define __FJORD_H_INCLUDED__
	
#include <limits>
#include "adjacency.h"

template <typename T>
void ford(AdjacencyList<T> const& adjacency_list, int vertex, T*& weights, int*& parents)
{
	weights = new T[adjacency_list.vertex_count];
	parents = new int[adjacency_list.vertex_count];
	for (int i = 0; i < adjacency_list.vertex_count; ++i)
		weights[i] = 999999;
	int r = adjacency_list.first[vertex];
	while (r) {
		weights[adjacency_list.G[r].v] = adjacency_list.G[r].w;
		parents[adjacency_list.G[r].v] = vertex;
		r = adjacency_list.G[r].next;
	}
	weights[vertex] = 0;
	for (int i = 0; i < adjacency_list.vertex_count - 1; ++i) {
		for (int j = 0; j < adjacency_list.vertex_count; ++j) {
			r = adjacency_list.first[j];
			while (r) {
				if (weights[adjacency_list.G[r].v] > weights[j] + adjacency_list.G[r].w) {
					weights[adjacency_list.G[r].v] = weights[j] + adjacency_list.G[r].w;
					parents[adjacency_list.G[r].v] = j;
				}
				r = adjacency_list.G[r].next;
			}
		}
	}
}

#endif