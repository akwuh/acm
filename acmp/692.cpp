#include <iostream>
#include <fstream>

int main() {
	std::ifstream in("input.txt", std::ios::binary);
	std::ofstream out("output.txt");
	int a;
	in >> a;
	out << (a != 0 && !(a & (a-1)) ? "YES" : "NO");
}