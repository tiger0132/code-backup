#include <algorithm>
#include <cstdio>
#include <cstring>
#define int long long

const int N = 5e5 + 55;

int S(int x) { return x * (x + 1) / 2; }

int a, b, c, d, ans;
signed main() {
	scanf("%lld%lld%lld%lld", &a, &b, &c, &d);
	for (int z = c; z <= d; z++) {
		int Z = z - a - b, P = b - a, Q = c - b;
		if (P + Q <= Z) break;
		ans += (P + 1) * (Q + 1);
		ans -= S(std::max(0ll, Z + 1));
		ans += S(std::max(0ll, Z - P));
		ans += S(std::max(0ll, Z - Q));
	}
	printf("%lld", ans);
}