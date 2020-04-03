#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 4e3 + 34;

int n, m, ans, a[N], b[N], c[N], dp[N][N];
int main() {
	scanf("%d%d", &n, &m);
	for (int i = n; i >= 1; i--) scanf("%d", a + i);
	for (int i = n; i >= 1; i--) scanf("%d", b + i);
	for (int i = 1; i <= n + m; i++) scanf("%d", c + i);
	memset(dp, 0xc0, sizeof dp);
	for (int i = 1; i <= n + m; i++) dp[i][0] = 0;
	for (int i = 1; i <= n; i++) {
		int x = a[i];
		for (int j = n; j >= 1; j--)
			dp[x][j] = std::max(dp[x][j], dp[x][j - 1] + c[x] - b[i]);
		for (int j = x, l = n; j <= n + m; j++, l /= 2)
			for (int k = 0; k <= l; k++)
				dp[j + 1][k / 2] =
					std::max(dp[j + 1][k / 2], dp[j][k] + k / 2 * c[j + 1]);
	}
	printf("%d", dp[n + m + 1][0]);
}