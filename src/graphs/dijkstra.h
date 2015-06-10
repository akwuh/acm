#ifndef __DIJKSTRA_H_INCLUDED__
#define __DIJKSTRA_H_INCLUDED__

#include <limits>
#include "adjacency.h"


template <typename T>
void dijkstra(AdjacencyList<T> const& adjacency_list, int vertex, T*& weights, int*& parents)
{
	bool *used = (bool*)calloc(adjacency_list.vertex_count, sizeof(bool));
	used[vertex] = true;
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
	
	int w = 0;

	for (int i = 0; i < adjacency_list.vertex_count - 1; ++i)
	{
		for (int j = 0; j < adjacency_list.vertex_count; ++j) {
			if (used[w] || weights[j] < weights[w] &&  !used[j]) {
				w = j;
			}
		}
		used[w] = true;
		r = adjacency_list.first[w];
		while (r) {
			if (weights[adjacency_list.G[r].v] > weights[w] + adjacency_list.G[r].w) {
				weights[adjacency_list.G[r].v] = weights[w] + adjacency_list.G[r].w;
				parents[adjacency_list.G[r].v] = w;
			}
			r = adjacency_list.G[r].next;
		}
	}
}
#endif