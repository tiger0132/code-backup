#include <algorithm>
#include <cstdio>
#include <cstring>
#define popcnt(S) __builtin_popcount(S)
#define ctz(S) __builtin_ctz(S)

const int N = 1e5 + 51, M = 24, K = 1 << M, U0 = (1 << 12) - 1;

int c0[M][U0 + 1], c1[M][U0 + 1], c2[M][U0 + 1], c3[M][U0 + 1];
int s[N], g[K], rec[M][M], f[K];
int n, m, k, U;
inline int cnt1(int x, int S) {
	int hi = S >> 12, lo = S & U0;
	return c0[x][lo] + c1[x][hi];
}
inline int cnt2(int S, int x) {
	int hi = S >> 12, lo = S & U0;
	return c2[x][lo] + c3[x][hi];
}
int main() {
	scanf("%d%d%d", &n, &m, &k), U = (1 << m) - 1;
	for (int i = 1; i <= n; i++) {
		scanf("%d", s + i), s[i]--;
		if (i > 1) rec[s[i - 1]][s[i]]++;
	}
	for (int i = 0; i < m; i++)
		for (int S = 1; S <= U0; S++) {
			int x0 = ctz(S), x1 = x0 + 12;
			c0[i][S] = c0[i][S & (S - 1)] + rec[i][x0];
			c1[i][S] = c1[i][S & (S - 1)] + rec[i][x1];
			c2[i][S] = c2[i][S & (S - 1)] + rec[x0][i];
			c3[i][S] = c3[i][S & (S - 1)] + rec[x1][i];
		}
	for (int S = 1; S <= U; S++) {
		int S0 = S & (S - 1), x = ctz(S);
		g[S] = g[S0] + cnt1(x, U ^ S) - cnt2(S0, x);
	}
	memset(f, 0x3f, sizeof f);
	f[0] = 0;
	for (int S = 0; S < U; S++)
		for (int i = 0; i < m; i++)
			if (!((S >> i) & 1))
				f[S | (1 << i)] = std::min(
					f[S | (1 << i)],
					f[S] + g[S] +
						k * (popcnt(S) + 1) * (cnt1(i, S) + cnt2(U ^ S ^ (1 << i), i)));
	printf("%d\n", f[U]);
}