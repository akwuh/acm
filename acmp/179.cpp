#include <iostream>
#include <fstream>

using namespace std;

long long f(long long k){
	return k == 1 ? 2 : 3 * f(k - 1) - 2;
}

int main()
{
	ifstream in("input.txt");
	ofstream out("output.txt");
	long k;
	in >> k;
	out << f(k + 1);
	return 0;
}