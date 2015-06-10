/**
 * @description Treap can be used to quickly find on segment
 * sum
 * min/max (and number of times it appears)
 * gcd/lcm
 * count zeros(or any number)
 * find k-th zero
 * prefix with the sum (only if a[i] > 0)
 * subsegment with maximum sum
 * minimal number greater than x
 * 
 */

#ifndef __TREAP_H_INCLUDED__
#define __TREAP_H_INCLUDED__

#include <algorithm>
#include <iostream>
#include <assert.h>

class Treap
{
public:
	int* t;
	Treap(int);
	void build(int*, int, int, int);
	int sum(int, int, int, int, int);
	void update(int, int, int, int, int);
};

/**
 * @brief constructor
 * 
 * @param size defines number of the array elements
 */
Treap::Treap(int size)
{
	t = new int[4 * size];
}

/**
 * @brief build
 * @details recursive implementation
 * 
 * @param a array of elements
 * @param v vertex index. Used for recursive calls. In the first call make v = 0
 * @param l left border of segment. In the first call it should be 0
 * @param r right border of segment. In the first call it should be n - 1
 * @return
 */
void Treap::build(int* a, int v, int l, int r)
{
	assert(l <= r);
	assert(l >= 0);
	if (l == r) {
		t[v] = a[l];
	} else {
		int m = (l + r) / 2;
		build(a, 2 * v + 1, l, m);
		build(a, 2 * v + 2, m + 1, r);
		/**
		 * for minimum we need replace this line with:
		 * t[v] = std::min(t[2 * v + 1], t[2 * v + 2]);
		 */
		t[v] = t[2 * v + 1] + t[2 * v + 2];
	}
}

/**
 * @brief sum
 * @details recursive implementation
 * 
 * @param v vertex index. Used for recursion. In the first call make v = 0
 * @param tl left border of segment. In the first call it should be 0
 * @param tr right border of segment. In the first call it should be n - 1
 * @param l left border of request. Any
 * @param r right border of request. Any. l <= r
 * @return sum on the segment [l, r]
 */
int Treap::sum(int v, int tl, int tr, int l, int r)
{
	assert(tl <= tr);
	assert(tl >= 0);
	assert(l >= 0);
	assert(l <= r);
	if (l == tl && r == tr) {
		return t[v];
	} else {
		/**
		 * for minimum replace this block with:
		 * int minimum, m = (tl + tr) / 2;
		 * if (l <= m)
		 * 		minimum = min(2 * v + 1, tl, m, l, std::min(r, m));
		 * if (r > m)
		 * 		minimum = std::min(minimum, min(2 * v + 2, m + 1, tr, std::max(l, m + 1), r));
		 * 	return minimum;
		 */
		int s = 0, m = (tl + tr) / 2;
		if (l <= m)
			s += sum(2 * v + 1, tl, m, l, std::min(r, m));
		if (r > m)
			s += sum(2 * v + 2, m + 1, tr, std::max(l, m + 1), r);
		return s;
	}
}

/**
 * @brief update
 * @details recursive implementation of updating value. Recursion may be avoided
 * 
 * @param v vertex index. Used for recursion. In first call should be 0
 * @param l left border of segment. In the first call should be 0
 * @param r right border of segment. In the first call should be n - 1
 * @param i index of element to update in initial array
 * @param value value of changing element
 */
void Treap::update(int v, int l, int r, int i, int value)
{;
	if (l == r) {
		t[v] = value;
	} else {
		int m = (l + r) / 2;
		if (i > m)
			update(2 * v + 2, m + 1, r, i, value);
		else
			update(2 * v + 1, l, m, i, value);
		/**
		 * for minimum replace this line with:
		 * t[v] = std::min(t[2 * v + 1], t[2 * v + 2]);
		 */
		t[v] = t[2 * v + 1] + t[2 * v + 2];
	}

}

#endif

int main()
{
	int a[] = {1, 2, 3, 4, 5, 6};
	Treap tr(6);
	tr.build(a, 0, 0, 5);
	std::cout << (tr.sum(0, 0, 5, 1, 3));
	return 0;
}