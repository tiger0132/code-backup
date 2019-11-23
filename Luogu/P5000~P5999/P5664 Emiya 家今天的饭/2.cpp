#include <algorithm>
#include <cstdio>
#include <cstring>
#define X i % 2
#define Y ~i % 2

const int N = 1e2 + 21, M = 2e3 + 32, P = 998244353;

int n, m, a[N][M], s[N], dp[2][2 * N], *f, *g, ans;
int main() {
	f = dp[0], g = dp[1];
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) scanf("%d", a[i] + j), s[i] = (s[i] + a[i][j]) % P;
	for (int col = 1; col <= m; col++) {
		memset(f, 0, sizeof *dp), f[n] = 1;
		for (int i = 1; i <= n; i++, std::swap(f, g), memset(g, 0, sizeof *dp))
			for (int l = n - i; l <= n + i; l++)  // l = 2k - j + n
				g[l] = (f[l] + 1ll * (l > 0) * a[i][col] * f[l - 1] +
						1ll * (s[i] + P - a[i][col]) * f[l + 1]) %
					   P;
		for (int i = n + 1; i <= 2 * n; i++) ans = (ans + P - f[i]) % P;
	}
	memset(f, 0, sizeof *dp), f[0] = 1;
	for (int i = 1; i <= n; i++, std::swap(f, g), memset(g, 0, sizeof *dp))
		for (int j = 0; j <= n; j++) g[j] = (f[j] + 1ll * (j > 0) * s[i] * f[j - 1]) % P;
	for (int i = 1; i <= n; i++) ans = (ans + f[i]) % P;
	printf("%d", ans);
}