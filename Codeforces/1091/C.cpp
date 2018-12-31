#include <algorithm>
#include <cstdio>
#include <set>
#define int long long

const int N = 1e3+31;

std::set<int> s;
int n;

signed main() {
	scanf("%lld", &n);
	for (int i = 1; i*i <= n; i++) {
		if (n % i) continue;
		s.insert((2 + (n / i - 1) * i) * (n / i) / 2);
		i = n / i;
		s.insert((2 + (n / i - 1) * i) * (n / i) / 2);
		i = n / i;
	}
	for (const auto& i : s) {
		printf("%lld ", i);
	}
}