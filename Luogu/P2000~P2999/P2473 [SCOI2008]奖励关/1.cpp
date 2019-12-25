#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#define nS (S | (1 << (i - 1)))

const int N = 1e2 + 21, K = 3.3e4 + 433;

int k, n, msk[N], v[N];
double dp[N][K], inf;
double dfs(int x, int S) {
	if (x > k) return 0;
	if (dp[x][S] != inf) return dp[x][S];
	dp[x][S] = 0;
	for (int i = 1; i <= n; i++)
		if ((S >> (i - 1)) & 1)
			dp[x][S] += (std::max(v[i], 0) + dfs(x + 1, S)) / n;
		else if ((msk[i] & S) == msk[i])
			if (v[i] >= 0)
				dp[x][S] += (v[i] + dfs(x + 1, nS)) / n;
			else
				dp[x][S] += std::max(dfs(x + 1, S), v[i] + dfs(x + 1, nS)) / n;
		else
			dp[x][S] += dfs(x + 1, S) / n;
	return dp[x][S];
}
int main() {
	scanf("%d%d", &k, &n);
	memset(dp, 0x7f, sizeof dp), inf = **dp;  // 别问我为什么，问就是玄学
	for (int i = 1, x; i <= n; i++)
		for (scanf("%d", v + i); scanf("%d", &x), x;) msk[i] |= 1 << (x - 1);
	printf("%.6f", dfs(1, 0));
}