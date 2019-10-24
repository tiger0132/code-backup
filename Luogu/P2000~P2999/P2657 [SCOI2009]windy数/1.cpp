#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>

int dp[22][22], a[22], len;
int dfs(int x, int y, bool tr, bool lim) {  // len -> 0
	if (!x) return 1;
	if (!lim && dp[x][y] != -1) return dp[x][y];
	int ret = 0, rb = lim ? a[x] : 9;
	for (int i = 0; i <= rb; i++) {
		if (abs(y - i) < 2) continue;
		if (tr && !i)
			ret += dfs(x - 1, -2, 1, lim && i == rb);
		else
			ret += dfs(x - 1, i, 0, lim && i == rb);
	}
	if (!tr && !lim) dp[x][y] = ret;
	return ret;
}
int calc(int x) {
	for (len = 0; x; x /= 10) a[++len] = x % 10;
	memset(dp, -1, sizeof dp);
	return dfs(len, -2, 1, 1);
}

int l, r;
int main() {
	scanf("%d%d", &l, &r);
	printf("%d", calc(r) - calc(l - 1));
}