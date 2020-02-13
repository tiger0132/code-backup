#include <algorithm>
#include <cstdio>
#include <cstring>

long long n, m, g, b, x, y, ans;
int main() {
	for (scanf("%*d"); ~scanf("%lld%lld%lld", &n, &g, &b);) {
		m = (n + 1) / 2;
		x = m / g, y = m % g;
		ans = x * (g + b) + y;
		if (!y) ans -= b;
		printf("%lld\n", std::max(ans, n));
	}
}