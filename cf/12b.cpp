#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>

typedef uint64_t ll;
using namespace std;

struct zero : unary_function<ll, bool>
{
    bool operator() (ll i) const { 
    	return i == 0; 
    }
};

int main() {
	string n, m;
	vector<ll> nums;
	cin >> n >> m;

	for (auto it : n) {
		nums.push_back(it - '0');
	}

	sort(nums.begin(), nums.end());

	auto it = find_if_not(nums.begin(), nums.end(), zero());

	if (it != nums.begin() && it != nums.end()) {
		iter_swap(it, nums.begin());
	}

	n = "";
	for (auto it : nums) {
		n += to_string(it);
	}

	if (n == m) {
		cout << "OK";
	} else {
		cout << "WRONG_ANSWER";
	}
}