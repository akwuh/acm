#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;


int cmp (const void * a, const void * b)
{
  if ( *(int*)a <  *(int*)b ) return -1;
  if ( *(int*)a == *(int*)b ) return 0;
  if ( *(int*)a >  *(int*)b ) return 1;
}

int main()
{
	ifstream in("input.txt");
	ofstream out("output.txt");
	int n;
	in >> n;
	int *a = new int[n];
	int *f = new int[n];
	for (int i = 0; i < n; ++i) {
		in >> a[i];
		f[i] = 1;
		for (int j = 0; j < i; ++j) {
			if (a[j] < a[i])
				f[i] = max(f[i], f[j] + 1);
		}
	}


	qsort(f, n, sizeof(int), cmp);
	out << f[n - 1];
	return 0;
}