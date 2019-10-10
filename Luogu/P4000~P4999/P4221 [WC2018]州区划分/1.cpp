#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 22, K = 2.1e6, P = 998244353;
int pw(int x, int y) {
	int r = 1;
	for (; y; y >>= 1, x = 1ll * x * x % P)
		if (y & 1) r = 1ll * r * x % P;
	return r;
}

int _[N], d[N], nc;
int $(int x) { return x[_] ? x[_] = $(x[_]) : x; }
void u(int x, int y) { (x = $(x)) != (y = $(y)) && (x[_] = y, nc--); }

template <typename F>
void FWT(int n, int *a, F f) {
	for (int i = 1; i < n; i <<= 1)
		for (int j = 0; j < n; j += 2 * i)
			for (int k = 0; k < i; k++) f(a[j + k], a[j + k + i]);
}

const auto d_or = [](int x, int &y) { y = (y + x) % P; };
const auto id_or = [](int x, int &y) { y = (y - x + P) % P; };
int n, m, k, p, x, y, f[N][K], s[K], g[N][K], gph[N][N], v[N];
int main() {
	for (scanf("%d%d%d", &n, &m, &p); m--;)
		scanf("%d%d", &x, &y), gph[x][y] = gph[y][x] = 1;
	for (int i = 1; i <= n; i++) scanf("%d", v + i);
	k = 1 << n;
	for (int i = 1, f; i < k; i++) {
		memset(_, 0, sizeof _), memset(d, 0, sizeof d), nc = __builtin_popcount(i);
		for (int jj = i, j; jj; jj ^= jj & -jj) {
			s[i] += v[j = __builtin_ffs(jj)];
			for (int k = 0; k < j; k++)
				if (gph[j][k] && ((i >> (k - 1)) & 1)) d[j]++, d[k]++, u(j, k);
		}
		f = nc > 1;
		for (int j = 1; j <= n; j++)
			if (((i >> (j - 1)) & 1) && d[j] % 2) f = 1;
		s[i] = pw(s[i], p);
		if (f) g[__builtin_popcount(i)][i] = s[i];
		s[i] = pw(s[i], P - 2);
	}
	f[0][0] = 1;
	FWT(k, f[0], d_or);
	for (int i = 1; i <= n; i++) FWT(k, g[i], d_or);
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < i; j++)
			for (int t = 0; t < k; t++)
				f[i][t] = (f[i][t] + 1ll * g[i - j][t] * f[j][t]) % P;
		FWT(k, f[i], id_or);
		for (int t = 0; t < k; t++) f[i][t] = 1ll * f[i][t] * s[t] % P;
		if (i < n) FWT(k, f[i], d_or);
	}
	printf("%d", f[n][k - 1]);
}