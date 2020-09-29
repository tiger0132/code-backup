#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#define int long long

int n;
signed main() {
	for (scanf("%*d"); ~scanf("%lld", &n);) {
		int ans = n - 1;
		int l = std::max((int)sqrtl(n) - 10, 0ll);
		int r = std::min((int)sqrtl(n) + 10, n - 1);
		for (int i = l; i <= r; i++) {
			ans = std::min(ans, i - 1 + (n + i) / (i + 1));
		}
		printf("%lld\n", ans);
	}
}