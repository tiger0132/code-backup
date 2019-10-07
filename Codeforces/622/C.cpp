#include <algorithm>
#include <cstdio>
#include <cstring>
#define DWT_XOR                               \
	[](int& x, int& y) {                      \
		int u = x, v = y;                     \
		x = (u + v) % P, y = (u - v + P) % P; \
	}
#define IDWT_XOR                                                        \
	[](int& x, int& y) {                                                \
		int u = x, v = y;                                               \
		x = 1ll * (u + v) * div2 % P, y = 1ll * (u - v + P) * div2 % P; \
	}

const int N = 22, M = 131072, K = 1048576, div2 = 499122177, P = 998244353;

template <typename F>
void FWT(int n, int* a, F f) {
	for (int i = 1; i < n; i <<= 1)
		for (int j = 0; j < n; j += i * 2)
			for (int k = 0; k < i; k++) f(a[j + k], a[j + k + i]);
}

int n, m, f[K + 9], g[K + 9], ans = 0x3f3f3f3f;
char mp[N][M];
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%s", mp[i] + 1);
	for (int i = 1; i < K; i++) g[i] = g[i >> 1] + (i & 1);
	for (int i = 1; i < K; i++) g[i] = std::min(g[i], n - g[i]);
	for (int j = 1; j <= m; j++) {
		int msk = 0;
		for (int i = 1; i <= n; i++) msk = (msk << 1) | (mp[i][j] ^ 48);
		f[msk]++;
	}
	FWT(1 << n, f, DWT_XOR), FWT(1 << n, g, DWT_XOR);
	for (int i = 0; i < (1 << n); i++) f[i] = 1ll * f[i] * g[i] % P;
	FWT(1 << n, f, IDWT_XOR);
	for (int i = 0; i < (1 << n); i++) ans = std::min(ans, f[i]);
	printf("%d", ans);
}