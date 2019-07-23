#include <algorithm>
#include <cstdio>
#include <cstring>

const int K = 1e5 + 51, P = 1e9 + 7;

inline int pw(int x, int y) {
	int r = 1;
	for (; y; y >>= 1, x = 1ll * x * x % P)
		if (y & 1) r = 1ll * r * x % P;
	return r;
}

int p[K], pc;
bool f[K];
inline int phi(int x) {
	int ret = 1;
	for (int i = 1; p[i] * p[i] <= x; i++) {
		if (x % p[i]) continue;
		ret *= p[i] - 1, x /= p[i];
		while (x % p[i] == 0) x /= p[i], ret *= p[i];
	}
	return x > 1 ? ret * (x - 1) : ret;
}

int t, n, ans;
int main() {
	1 [f] = true;
	for (int i = 2; i < K; i++) {
		if (!i[f]) p[++pc] = i;
		for (int j = 1; j <= pc && i * p[j] < K && i % p[j]; j++) (i * p[j])[f] = true;
	}
	for (scanf("%d", &t); t--;) {
		scanf("%d", &n), ans = 0;
		for (int d = 1; d * d <= n; d++) {
			if (n % d) continue;
			ans = (ans + 1ll * phi(n / d) * pw(n, d) % P) % P;
			if (d * d != n) ans = (ans + 1ll * phi(d) * pw(n, n / d) % P) % P;
		}
		printf("%lld\n", 1ll * ans * pw(n, P - 2) % P);
	}
}