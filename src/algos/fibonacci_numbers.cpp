/**
 * @author Unknown TM
 * @description Calculating of Fibonachi sequence values by O(log n)
 */
 
#include <iostream>
#include <iomanip>
#include <assert.h>

using namespace std;

template <typename T>
class Matrix
{
public:
	T** ptr;
	int n, m;
	Matrix(T**, int, int = 0);
	template <typename T>
	friend Matrix operator + (Matrix const&, Matrix const&);
	template <typename T>
	friend Matrix operator * (Matrix const&, Matrix const&);
	void print();
};

template <typename T>
Matrix<T>::Matrix(T** _ptr, int _n, int _m) : ptr(_ptr), n(_n)
{
	m = _m ? _m : n;
}

template <typename T>
Matrix<T> operator + (Matrix<T> const &m1, Matrix<T> const &m2)
{
	assert(m1.n == m2.n && m1.m == m2.m);
	T** ptr = new T*[m1.n];
	for (int i = 0; i < m1.n; ++i) {
		ptr[i] = new T[m1.m];
		for (int j = 0; j < m1.m; ++j)
			ptr[i][j] = m1.ptr[i][j] + m2.ptr[i][j];
	}
	Matrix<T> m(ptr, m1.n, m1.m);
	return m;
}

template <typename T>
Matrix<T> operator * (Matrix<T> const &m1, Matrix<T> const &m2)
{
	assert(m1.m == m2.n);
	T s = 0;
	T** ptr = new T*[m1.n];
	for (int i = 0; i < m1.n; ++i) {
		ptr[i] = new T[m2.m];
		for (int j = 0; j < m2.m; ++j) {
			s = 0;
			for (int k = 0; k < m1.m; ++k)
				s += m1.ptr[i][k] * m2.ptr[k][j];
			ptr[i][j] = s;
		}
	}
	Matrix<T> m(ptr, m1.n, m2.m);
	return m;
}

template <typename T>
void Matrix<T>::print()
{
	for (int i = 0; i < n; ++i) {
		cout << "\n";
		for (int j = 0; j < m; ++j)
			cout << setw(3) << ptr[i][j];
	}
}

template <typename T>
T pow(T a, int n) {
	if (n == 1)
		return a;
	if (n % 2 == 1)
		return pow(a, n - 1) * a;
	else {
		T b = pow(a, n / 2);
		return b * b;
	}
}

int main()
{
	int** ptr = new int* [2] {new int[2] {0, 1}, new int[2] {1, 1}};
	Matrix<int> m(ptr, 2);
	int n;
	cin >> n;
	m = pow(m, n);
	cout << (m.ptr[1][0]) << "\n";
 	system("pause");
 	return 0;
}