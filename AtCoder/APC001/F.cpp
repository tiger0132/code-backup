#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 1e5 + 51;

int dp[N], xorv[N];
int dfs(int S) {
	if (dp[S]) return dp[S];
	int ret = __builtin_popcount(S) - 1;
	for (int T = (S - 1) & S; T; T = (T - 1) & S)
		if (!xorv[T]) ret = std::min(ret, dfs(T) + dfs(S ^ T));
	return dp[S] = ret;
}

int n, x, y, z, v[N], c[22], ans, msk;
int main() {
	scanf("%d", &n);
	for (int i = 1; i < n; i++) {
		scanf("%d%d%d", &x, &y, &z), x++, y++;
		x[v] ^= z, y[v] ^= z;
	}
	for (int i = 1; i <= n; i++) i[v][c]++;
	for (int i = 1; i <= 15; i++) {
		ans += i[c] / 2;
		msk |= (i[c] & 1) << (i - 1);
	}
	for (int S = 0; S < 32768; S++)
		for (int j = 1; j <= 15; j++)
			if ((S >> (j - 1)) & 1) xorv[S] ^= j;
	printf("%d", ans + (msk ? dfs(msk) : 0));
}