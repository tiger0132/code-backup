#include <algorithm>
#include <cstdio>
#define int long long

int n, a, b, c, d, ans;
signed main() {
	for (scanf("%lld", &n); n--;) {
		ans = 0;
		scanf("%lld%lld%lld%lld", &a, &b, &c, &d);
		for (int i = 1; i * i <= d; i++) {
			if (d % i) continue;
			ans += !(i % b) && std::__gcd(i, a) == b && i * c / std::__gcd(i, c) == d;
			if (i * i == d) break;
			i = d / i, ans += !(i % b) && std::__gcd(i, a) == b && i * c / std::__gcd(i, c) == d, i = d / i;
		}
		printf("%lld\n", ans);
	}
}