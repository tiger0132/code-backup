#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 11, K = 5e3 + 35;

int dp[N][K], num[N], tot;
int dfs(int x, int s, bool lim) {
	if (!x) return 1;
	if (!lim && ~dp[x][s]) return dp[x][s];
	int ub = lim ? x[num] : 9, r = 0;
	for (int i = 0; i <= ub; i++)
		if (s >= (i << (x - 1))) r += dfs(x - 1, s - (i << (x - 1)), lim && i == ub);
	if (!lim) dp[x][s] = r;
	return r;
}

int a, k, n, _;
int main() {
	memset(dp, -1, sizeof dp);
	for (scanf("%*d"); ~scanf("%d%d", &a, &n);) {
		k = 0;
		for (int i = 1; a; a /= 10, i *= 2) k += a % 10 * i;
		for (tot = 0; n; n /= 10) num[++tot] = n % 10;
		printf("Case #%d: %d\n", ++_, dfs(tot, k, 1));
	}
}