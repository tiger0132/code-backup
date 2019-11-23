#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 1e2 + 21, M = 2e3 + 32, P = 998244353;

int n, m, a[N][M], s[N], dp[N][2 * N], ans;
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) scanf("%d", a[i] + j), s[i] = (s[i] + a[i][j]) % P;
	for (int col = 1; col <= m; col++) {
		memset(dp, 0, sizeof dp), dp[0][n] = 1;
		for (int i = 1; i <= n; i++)
			for (int l = n - i; l <= n + i; l++)  // l = 2k - j + n
				dp[i][l] = (dp[i - 1][l] + 1ll * (l > 0) * a[i][col] * dp[i - 1][l - 1] +
							1ll * (s[i] + P - a[i][col]) * dp[i - 1][l + 1]) %
						   P;
		for (int i = n + 1; i <= 2 * n; i++) ans = (ans + P - dp[n][i]) % P;
	}
	memset(dp, 0, sizeof dp), dp[0][0] = 1;
	for (int i = 1; i <= n; i++)
		for (int j = 0; j <= n; j++)
			dp[i][j] = (dp[i - 1][j] + 1ll * (j > 0) * s[i] * dp[i - 1][j - 1]) % P;
	for (int i = 1; i <= n; i++) ans = (ans + dp[n][i]) % P;
	printf("%d", ans);
}