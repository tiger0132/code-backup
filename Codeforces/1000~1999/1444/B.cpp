#include <algorithm>
#include <cstdio>
#include <cstring>
#define int long long

const int N = 4e5 + 54, P = 998244353;

int pw(int x, int y) {
	int r = 1;
	for (; y; y >>= 1, x = x * x % P)
		if (y & 1) r = r * x % P;
	return r;
}

int n, a[N];
signed main() {
	scanf("%lld", &n);
	for (int i = 1; i <= 2 * n; i++) scanf("%lld", a + i);
	std::sort(a + 1, a + 2 * n + 1);
	int ans = 0, p = 1, q = 1;
	for (int i = 1; i <= n; i++) ans += a[2 * n - i + 1] - a[i];
	ans %= P;
	for (int i = n + 1; i <= 2 * n; i++) p = p * i % P;
	for (int i = 1; i <= n; i++) q = q * i % P;
	printf("%lld", ans * p % P * pw(q, P - 2) % P);
}