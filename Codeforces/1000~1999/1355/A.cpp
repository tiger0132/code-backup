#include <algorithm>
#include <cstdio>
#include <cstring>
#define int long long

int n, k, ans, mn, mx;
void cal(int x) {
	mn = 10, mx = -1;
	while (x) {
		mn = std::min(mn, x % 10);
		mx = std::max(mx, x % 10);
		x /= 10;
	}
}
signed main() {
	for (scanf("%*d"); ~scanf("%lld%lld", &n, &k);) {
		while (--k) {
			cal(n);
			if (!mn) break;
			n += mn * mx;
		}
		printf("%lld\n", n);
	}
}