#include <algorithm>
#include <cstdio>
#include <cstring>
#define f dp[i & 1]
#define g dp[~i & 1]
#define C(x) 1ll * (x) * (x - 1) / 2 % P

const int N = 1e2 + 21, P = 9999973;
void ad(int& x, int y) { x = (x + y) % P; }
int n, m, ans, dp[2][N][N];
int main() {
	scanf("%d%d", &n, &m);
	dp[0][0][0] = 1;
	for (int i = 1; i <= n; i++) {
		memset(f, 0, sizeof dp[0]);
		for (int j = 0; j <= m; j++)
			for (int k = 0; k <= m - j; k++) {
				f[j][k] = g[j][k];
				if (k >= 1) ad(f[j][k], (j + 1ll) * g[j + 1][k - 1] % P);
				if (j >= 1) ad(f[j][k], (m - j - k + 1ll) * g[j - 1][k] % P);
				if (k >= 2) ad(f[j][k], C(j + 2) * g[j + 2][k - 2] % P);
				if (j >= 2) ad(f[j][k], C(m - j - k + 2) * g[j - 2][k] % P);
				if (k >= 1) ad(f[j][k], (m - j - k + 1ll) * j % P * g[j][k - 1] % P);
			}
	}
	for (int i = 0; i <= m; i++)
		for (int j = 0; j <= m; j++) ad(ans, dp[n & 1][i][j]);
	printf("%d", ans);
}