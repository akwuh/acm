// ptr array should be ordered up(down)
template <typename T>
int find(T* ptr, int n, T const &t)
{
	int i = n / 2;
	int di = n / 2 + n % 2;
	while (di) {
		di = (di == 1 ? 0 : di / 2 + di % 2);
		if (ptr[i] == k)
			return i;
		else if (k > ptr[i])
			i += di;
		else
			i -= di;
		if (i < 0) i = 0;
		if (i > n - 1) i = n - 1;
	}
	return -1;
}