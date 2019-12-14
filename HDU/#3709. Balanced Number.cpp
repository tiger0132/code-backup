#include <algorithm>
#include <cstdio>
#include <cstring>
#define int long long

const int N = 22, K = 2e3 + 32;

int dp[N][N][K], num[N], tot;
int dfs(int x, int sub, int pos, bool lim) {
	if (!x) return !sub;
	if (sub < 0) return 0;
	if (!lim && ~dp[x][pos][sub]) return dp[x][pos][sub];
	int ub = lim ? num[x] : 9, r = 0;
	for (int i = 0; i <= ub; i++) {
		r += dfs(x - 1, sub + (x - pos) * i, pos, lim && i == ub);
	}
	if (!lim) dp[x][pos][sub] = r;
	return r;
}
int calc(int x) {
	if (x < 0) return 0;
	for (tot = 0; x; x /= 10) num[++tot] = x % 10;
	int r = 0;
	for (int i = 1; i <= tot; i++) r += dfs(tot, 0, i, 1);
	return r - tot + 1;
}

int l, r;
signed main() {
	memset(dp, -1, sizeof dp);
	for (scanf("%*d"); ~scanf("%lld%lld", &l, &r);)
		printf("%lld\n", calc(r) - calc(l - 1));
}