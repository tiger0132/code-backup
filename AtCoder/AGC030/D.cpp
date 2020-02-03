#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 3e3 + 33, P = 1e9 + 7, div2 = (P + 1) / 2;

int n, m, x, y, a[N], b[N], dp[N][N], tmp[N][N], ans, pw2 = 1;
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", a + i), b[i] = a[i];
	std::sort(b + 1, b + n + 1);
	for (int i = 1; i <= n; i++) a[i] = std::lower_bound(b + 1, b + n + 1, a[i]) - b;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) dp[i][j] = a[i] > a[j];
	for (int i = 1; i <= m; i++) {
		scanf("%d%d", &x, &y);
		for (int j = 1, u, v; j <= n; j++)
			if (j != x && j != y) {
				u = 1ll * (dp[j][x] + dp[j][y]) * div2 % P;
				v = 1ll * (dp[y][j] + dp[x][j]) * div2 % P;
				dp[j][x] = u, dp[j][y] = u;
				dp[x][j] = v, dp[y][j] = v;
			}
		int u = 1ll * (dp[x][y] + dp[y][x]) * div2 % P;
		dp[x][y] = dp[y][x] = u;
		pw2 = pw2 * 2 % P;
	}
	for (int i = 1; i < n; i++)
		for (int j = i + 1; j <= n; j++) ans = (ans + dp[i][j]) % P;
	printf("%lld", 1ll * ans * pw2 % P);
}