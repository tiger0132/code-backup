#include <algorithm>
#include <cstdio>
#include <cstring>
#define int long long

int dp[19][163][1540], num[22], tot;
int dfs(int x, int a, int b, bool lim) {
	if (!x) return a && b % a == 0 && 1 <= -b / a && -b / a <= tot;
	if (!lim && ~dp[x - 1][-a][b]) return dp[x - 1][-a][b];
	int ub = lim ? num[x] : 9, r = 0;
	for (int i = 0; i <= ub; i++) {
		r += dfs(x - 1, a - i, b + x * i, lim && i == ub);
	}
	if (!lim) dp[x - 1][-a][b] = r;
	return r;
}
int calc(int x) {
	if (x < 0) return 0;
	for (tot = 0; x; x /= 10) num[++tot] = x % 10;
	return dfs(tot, 0, 0, 1) + 1;
}

int l, r;
signed main() {
	memset(dp, -1, sizeof dp);
	for (scanf("%*d"); ~scanf("%lld%lld", &l, &r);)
		printf("%lld\n", calc(r) - calc(l - 1));
}