#include <algorithm>
#include <cstdio>
#include <cstring>
#define int long long

const int N = 2e5 + 52, P = 998244353;

int n, a[N], b[N], k, s, ans = 1;
signed main() {
	scanf("%lld%lld", &n, &k);
	for (int i = 1; i <= n; i++) scanf("%lld", a + i), b[i] = i;
	std::sort(b + 1, b + n + 1, [](int x, int y) { return x[a] > y[a]; });
	std::sort(b + 1, b + k + 1, [](int x, int y) { return x < y; });
	s = a[b[1]];
	for (int i = 2; i <= k; i++) s += a[b[i]], ans = 1ll * ans * (b[i] - b[i - 1]) % P;
	printf("%lld %lld", s, ans);
}