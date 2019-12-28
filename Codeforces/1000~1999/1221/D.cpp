#include <algorithm>
#include <cstdio>
#include <cstring>
#define int long long

const int N = 3e5 + 53;

int n, a[N], b[N], dp[N][3];
signed main() {
	a[0] = -1e9;
	for (scanf("%*d"); ~scanf("%lld", &n);) {
		for (int i = 1; i <= n; i++) {
			scanf("%lld%lld", a + i, b + i);
			dp[i][0] = dp[i][1] = dp[i][2] = 1e18;
			for (int k = 0; k <= 2; k++)
				for (int j = 0; j <= 2; j++)
					if (a[i - 1] + j != a[i] + k)
						dp[i][k] = std::min(dp[i][k], dp[i - 1][j] + k * b[i]);
		}
		printf("%lld\n", std::min({dp[n][0], dp[n][1], dp[n][2]}));
	}
}