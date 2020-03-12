#include <algorithm>
#include <cstring>
#include <cstdio>

const int N = 5e2 + 25;

int n, dp[N][N], dp2[N];
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", dp[i] + i);
	for (int len = 2; len <= n; len++)
		for (int l = 1; l <= n - len + 1; l++) {
			int r = l + len - 1;
			for (int k = l; k < r; k++)
				if (dp[l][k] && dp[l][k] == dp[k + 1][r]) {
					dp[l][r] = dp[l][k] + 1;
					break;
				}
		}
	memset(dp2, 0x3f, sizeof dp2);
	dp2[0] = 0;
	for (int i = 1; i <= n; i++)
		for (int j = i - 1; j >= 0; j--)
			if (dp[j + 1][i]) dp2[i] = std::min(dp2[i], dp2[j] + 1);
	printf("%d", dp2[n]);
}