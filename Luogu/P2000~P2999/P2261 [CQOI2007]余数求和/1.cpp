#include <algorithm>
#include <cstdio>
#define int long long

int n, k, l, r, ans;
signed main() {
	scanf("%lld%lld", &n, &k), ans = n * k;
	for (l = 1; l <= n; l = r + 1) {
		r = k / l ? std::min(k / (k / l), n) : n;
		ans -= (k / l) * (l + r) * (r - l + 1) / 2;
	}
	printf("%lld", ans);
}