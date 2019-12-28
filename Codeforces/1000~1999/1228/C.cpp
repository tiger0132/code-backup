#include <algorithm>
#include <cstdio>
#include <cstring>
#define int long long

const int N = 1e5 + 51, P = 1e9 + 7;

int x, n, fac[N], t, ans = 1, c;
int pw(int x, int y) {
	int r = 1;
	for (; y; y >>= 1, x = x * x % P)
		if (y & 1) r = r * x % P;
	return r;
}
signed main() {
	scanf("%lld%lld", &x, &n);
	for (int i = 2; i * i <= x; i++) {
		if (x % i) continue;
		fac[++t] = i;
		while (x % i == 0) x /= i;
	}
	if (x > 1) fac[++t] = x;
	for (int i = 1; i <= t; i++) {
		c = 0;
		for (int j = n; j; j /= fac[i]) c = (c + j / fac[i]) % (P - 1);
		ans = ans * pw(fac[i], c) % P;
	}
	printf("%lld", ans);
}