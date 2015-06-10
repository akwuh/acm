#include <iostream>
#include <ctime>
#include <cstdlib>
#include <chrono>

using namespace std;

/**
 * @brief bubble sort
 * @stable true
 * 
 * @memory 1
 * @best n	
 * @average n n
 * @worst n n
 */
template <typename T>
void bubble_sort(T* &a, int n)
{
	bool sorted;
	do {
		for (int i = 0; i < n - 1; ++i) {
			sorted = true;
			for (int j = 0; j < n - 1; ++j) {
				if (a[j] > a[j + 1]) {
					std::swap(a[j], a[j + 1]);
					sorted = false;
				}
			}
		}
	} while (!sorted);
}


/**
 * @brief coctail sort
 * @stable true
 * 
 * @memory 1
 * @best n
 * @average n n
 * @worst n n
 */
template <typename T>
void coctail_sort(T* &a, int n)
{
	int left = 0, right = n;
	while (left < right) {
		for (int i = 0; i < right - 1; ++i)
		{
			if (a[i] > a[i + 1])
				std::swap(a[i], a[i + 1]);
		}
		++left;

		for (int i = right - 1; i > left; --i)
		{
			if (a[i] < a[i - 1])
				std::swap(a[i], a[i - 1]);
		}
		--right;
	}
}

/**
 * @brief selection sort
 * @stable false
 * 
 * @memory 1
 * @best n n
 * @average n n
 * @worst n n
 */
template <typename T>
void selection_sort(T* &a, int n)
{
	int min;
	for (int i = 0; i < n; ++i) {
		min = i;
		for (int j = i + 1; j < n; ++j)
			if (a[min] > a[j])
				min = j;
		if (i != min)
			std::swap(a[i], a[min]);
	}
}

/**
 * @brief insertion sort
 * @stable true
 * 
 * @memory 1
 * @best n
 * @average n n
 * @worst n n
 */
template <typename T>
void insertion_sort(T* &a, int n)
{
	T tmp;
	int k;
	for (int i = 1; i < n; ++i) {
		k = i;
		tmp = a[i];
		while (k != 0 && a[k - 1] > tmp) {
			a[k] = a[k - 1];
			k--;
		}
		a[k] = tmp;
	}
}

/**
 * @brief merge sort
 * @stable true
 * 
 * @memory n
 * @best n log n
 * @average n log n
 * @worst n log n
 */

template <typename T>
void merge_sort(T* &a, int n)
{
	int i, j, left, left_border, right_border, part = 1;
	T* buf = new T[n];
	do{
		left = 0;
		while (left < n) {
			i = j = 0;
			left_border = (left + part > n ? n : left + part);
			right_border = (left + 2 * part > n ? n : left + 2 * part);
			while (left + i + j < n) {
				if (left + i < left_border && left + part + j < right_border) {
					if (a[left + i] < a[left + part + j]) {
						buf[left + i + j] = a[left + i];
						++i;
					} else {
						buf[left + i + j] = a[left + part + j];
						++j;
					}
				} else if (left + part + j >= right_border) {
					buf[left + i + j] = a[left + i];
					++i;
				} else {
					buf[left + i + j] = a[left + part + j];
					++j;
				}
			}
			left += 2 * part;
		}
		std::swap(buf, a);
		part *= 2;
	} while (part < n);
}

/**
 * @brief binary tree sort
 * @description tree must be self-balanced
 * @stable true
 * 
 * @memory n
 * @best n
 * @average n log n
 * @worst n log n
 */
template <typename T>
void binary_tree_sort(T* &a, int n);

/**
 * @brief counting sort
 * @description non-comparison sort(i.e. for numbers). Effective only
 * when we have to sort small range  of values
 * @stable true
 * 
 * @memory n + max - min
 * @best n + max - min
 * @average n + max - min
 * @worst n + max - min
 */
template <typename T>
void counting_sort(T* &a, int n, int min, int max)
{
	int *c = new int[max - min + 1];
	T* b = new T[n];
	for (int i = 0; i < max - min + 1; ++i)
		c[i] = 0;

	for (int i = 0; i < n; ++i)
		++c[a[i] - min];
	
	for (int i = 1; i < max - min + 1; ++i)
		c[i] += c[i - 1];

	for (int i = 0; i < n; ++i)
		b[--c[a[i] - min]] = a[i];

	std::swap(a, b);
}

/**
 * @brief shell sort
 * @stable false
 * @description improved insertion sort
 * @memory n
 * @best n
 * @average n log n log n
 * @worst n log n log n	
 */
template <typename T>
void shell_sort(T* &a, int n)
{
	T tmp;
	int k;
	for (int d = n / 2; d > 0; d /= 2) {
		for (int i = d; i < n; i += d) {
			k = i;
			tmp = a[i];
			while (k > 0 && a[k - d] > tmp) {
				a[k] = a[k - d];
				k -= d;
			}
			a[k] = tmp;
		}
	}
}

/**
 * @brief comb sort
 * @description improved bubble sort
 * @stable false
 * 
 * @memory n
 * @best n
 * @average n log n
 * @worst n n
 */
template <typename T>
void comb_sort(T* &a, int n)
{
	bool sorted = false;
	for (int k = n; k > 0; k /= 1.237) {
		sorted = true;
		for (int i = 0; i + k < n; ++i) {
			if (a[i] > a[i + k]) {
				swap(a[i], a[i + k]);
				sorted = false;
			}
		}
	}
}

double test(void (*f)(int*&, int))
{
	double t = 0;
	int n = 3000, k = 100, *a;
	a = new int[n];
	std::chrono::milliseconds start, end;
	for (int i = 0; i < k; ++i) {
		
		for (int i = 0; i < n; ++i)
			a[i] = rand() % 1000;

		start = std::chrono::duration_cast< std::chrono::milliseconds >
		(std::chrono::high_resolution_clock::now().time_since_epoch());
		
		f(a, n);
		
		end = std::chrono::duration_cast< std::chrono::milliseconds >
		(std::chrono::high_resolution_clock::now().time_since_epoch());
		t += (end.count() - start.count());
	}
	return t / k;
}

int main()
{
	cout << "\nbubble_sort:\t" << test(&bubble_sort<int>);
	cout << "\ncoctail_sort:\t" << test(&coctail_sort<int>);
	cout << "\nselection_sort:\t" << test(&selection_sort<int>);
	cout << "\ninsertion_sort:\t" << test(&insertion_sort<int>);
	cout << "\nmerge_sort:\t" << test(&merge_sort<int>);
	cout << "\nshell_sort:\t" << test(&shell_sort<int>);
	cout << "\ncomb_sort:\t" << test(&comb_sort<int>);
	cout << "\n";
	system("pause");
	return 0;
}