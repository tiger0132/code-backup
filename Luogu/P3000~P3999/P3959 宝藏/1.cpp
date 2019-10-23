#include <algorithm>
#include <cstdio>
#include <cstring>
#define int long long

const int N = 13, M = 1 << 12;

int n, m, x, y, z, siz, dp[N][M], d[M][M], g[N][N], dis[N][M], ans;
signed main() {
	std::memset(dp, 0x3f, sizeof dp), ans = 1e15;
	scanf("%lld%lld", &n, &m), siz = 1 << n;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) g[i][j] = 1e10;
		for (int j = 0; j < siz; j++) dis[i][j] = 1e10;
	}
	while (m--)
		scanf("%lld%lld%lld", &x, &y, &z), g[x][y] = g[y][x] = std::min(g[x][y], z);
	for (int i = 0; i < siz; i++)
		for (int j = 1; j <= n; j++)
			for (int k = i; k; k ^= k & -k)
				dis[j][i] = std::min(dis[j][i], g[j][__builtin_ffs(k)]);
	for (int i = 0; i < siz; i++)
		for (int j = 1, l = 1; j < siz; j++, l = j & -j)
			d[i][j] = d[i][j ^ l] + dis[__builtin_ffs(j)][i];
	for (int i = 1; i <= n; i++) dp[1][1 << (i - 1)] = 0;
	for (int lv = 2; lv <= n; ans = std::min(ans, dp[lv++][(1 << n) - 1]))
		for (int i = 0; i < siz; i++)
			for (int j = i; j; j = (j - 1) & i)
				dp[lv][i] =
					std::min(dp[lv][i], dp[lv - 1][i ^ j] + d[i ^ j][j] * (lv - 1));
	printf("%lld", ans == 1e15 ? 0 : ans);
}