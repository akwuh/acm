#include <iostream>
#include <fstream>

using namespace std;

struct Cell
{
	Cell(){};
	Cell(int _i, int _j, int _z) : i(_i), j(_j), z(_z){};
	int i, j, z;
};

int main()
{
	ifstream in("input.txt");
	ofstream out("output.txt");
	int h, n, m, si, sj, sz;
	in >> h >> n >> m;

	char c;
	int ***a = new int**[n];
	Cell* wave = new Cell[4 * n * m];
	Cell* dwave = new Cell[4 * n * m];

	for (int r = 0; r < h; ++r) {
		a[r] = new int*[n];
		for (int i = 0; i < n; ++i) {
			a[r][i] = new int[m];
			for (int j = 0; j < m; ++j) {
				in >> c;
				if (c == '.') a[r][i][j] = 0;
				else if (c == '1') {
					a[r][i][j] = -1;
					si = i;
					sj = j;
					sz = r;
				}
				else if (c == '2') a[r][i][j] = -2;
				else a[r][i][j] = -3;
			}
		}
	}

	int p = 0, count = 0, dcount = 0, i, j, k;
	int tmp;
	Cell cu;
	bool trigger = false;
	dwave[dcount++] = Cell(si, sj, sz);
	while (true) {
		count = 0;
		tmp = dcount;
		for (int u = 0; u < tmp; ++u) {
			cu = dwave[--dcount];
			i = cu.i;
			j = cu.j;
			k = cu.z;
			if (a[k][i][j] == -3) continue;
			if (a[k][i][j] == -2) trigger = true;
			if (i > 0 && a[k][i - 1][j] != -3) {
				wave[count++] = Cell(i - 1, j, k);
			}
			if (i < n - 1 && a[k][i + 1][j] != -3) {
				wave[count++] = Cell(i + 1, j, k);
			}
			if (j > 0 && a[k][i][j - 1] != -3) {
				wave[count++] = Cell(i, j - 1, k);
			}
			if (j < m - 1 && a[k][i][j + 1] != -3) {
				wave[count++] = Cell(i, j + 1, k);
			}
			if (k < h - 1 && a[k + 1][i][j] != -3) {
				wave[count++] = Cell(i, j, k + 1);
			}
			a[k][i][j] = -3;
		}
		if (trigger) break;
		swap(wave, dwave);
		swap(count, dcount);
		p++;
	}
	out << (p * 5);
	return 0;
}