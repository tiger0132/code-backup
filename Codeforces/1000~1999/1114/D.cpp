#include <algorithm>
#include <cstdio>
#include <cstring>
const int N = 5e3 + 35;
int n, a[N], dp[N][N];
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	n = std::unique(a + 1, a + n + 1) - a - 1;
	for (int len = 2; len <= n; len++) {
		for (int l = 1; l <= n - len + 1; l++) {
			int r = l + len - 1;
			if (a[l] == a[r])
				dp[l][r] = dp[l + 1][r - 1] + 1;
			else
				dp[l][r] = std::min(dp[l + 1][r], dp[l][r - 1]) + 1;
		}
	}
	printf("%d", dp[1][n]);
}