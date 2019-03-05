#include <algorithm>
#include <bitset>
#include <cstdio>
#include <cstring>
#include <vector>

const int N = 5e2 + 25;

int dp[N][N];
char s[N];
int n;

int main() {
	scanf("%d%s", &n, s + 1);
	n = std::unique(s + 1, s + n + 1) - s - 1;
	for (int i = 1; i <= n; i++) dp[i][i] = 1;
	for (int len = 2; len <= n; len++) {
		for (int l = 1; l <= n - len + 1; l++) {
			int r = l + len - 1;
			dp[l][r] = 0x3f3f3f3f;
			for (int k = l; k <= r; k++) {
				// printf("[%d, %d] %d: %d %d\n", l, r, k, dp[l + 1][k] + dp[k + 1][r], dp[l][k] + dp[k + 1][r - 1]);
				if (l < k && s[l] == s[k]) dp[l][r] = std::min(dp[l][r], dp[l + 1][k] + dp[k + 1][r]);
				if (k < r && s[r] == s[k]) dp[l][r] = std::min(dp[l][r], dp[l][k] + dp[k + 1][r - 1]);
				dp[l][r] = std::min(dp[l][r], dp[l][k] + dp[k + 1][r]);
			}
			// printf("[%d, %d] = %d\n", l, r, dp[l][r]);
		}
	}
	printf("%d", dp[1][n]);
}