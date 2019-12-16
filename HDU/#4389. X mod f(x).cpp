#include <algorithm>
#include <cstdio>
#include <cstring>

int dp[11][82][82][82], num[11], tot;
int dfs(int x, int sum, int mod, int rem, bool lim) {
	if (!x) return sum == mod && !rem;
	if (!lim && ~dp[x][sum][mod][rem]) return dp[x][sum][mod][rem];
	int ub = lim ? num[x] : 9, r = 0;
	for (int i = 0; i <= ub; i++) {
		r += dfs(x - 1, sum + i, mod, (rem * 10 + i) % mod, lim && i == ub);
	}
	if (!lim) dp[x][sum][mod][rem] = r;
	return r;
}
int calc(int x) {
	for (tot = 0; x; x /= 10) num[++tot] = x % 10;
	int r = 0;
	for (int i = 1; i <= 81; i++) r += dfs(tot, 0, i, 0, 1);
	return r;
}

int l, r, _;
int main() {
	memset(dp, -1, sizeof dp);
	for (scanf("%*d"); ~scanf("%d%d", &l, &r);)
		printf("Case %d: %d\n", ++_, calc(r) - calc(l - 1));
}