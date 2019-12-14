#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 11;

int dp[N][2], num[N], tot;
int dfs(int x, bool lim, bool f) {
	if (!x) return 1;
	if (!lim && dp[x][f]) return dp[x][f];
	int r = 0, ub = lim ? num[x] : 9;
	for (int i = 0; i <= ub; i++)
		if (i != 4 && (i != 2 || !f)) r += dfs(x - 1, lim && i == ub, i == 6);
	if (!lim) dp[x][f] = r;
	return r;
}
int calc(int x) {
	for (tot = 0; x; x /= 10) num[++tot] = x % 10;
	return dfs(tot, 1, 0);
}

int l, r;
int main() {
	memset(dp, 0, sizeof dp);
	for (; scanf("%d%d", &l, &r), l || r;) printf("%d\n", calc(r) - calc(l - 1));
}