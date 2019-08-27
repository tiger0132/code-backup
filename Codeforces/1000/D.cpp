#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 1e3 + 31, P = 998244353;

int n, a[N], dp[N], c[N][N], ans;

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	for (int i = 0; i <= n; i++) {
		c[i][0] = 1;
		for (int j = 1; j <= i; j++) c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % P;
	}
	for (int i = n; i >= 1; i--) {
		if (a[i] <= 0 || n - i < a[i]) continue;
		dp[i] = c[n - i][a[i]];
		for (int j = i + a[i] + 1; j <= n; j++)
			if (a[j] > 0) dp[i] = (dp[i] + 1ll * c[j - i - 1][a[i]] * dp[j]) % P;
		ans = (ans + dp[i]) % P;
	}
	printf("%d", ans);
}