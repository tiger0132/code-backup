#include <algorithm>
#include <cstdio>
#include <cstring>
#define _(x) (1 << (x - 1))

typedef long long ll;
int n, m, k, x, y, z, msk, v[22], g[22][22];
ll ans, dp[22][266666];
int main() {
	scanf("%d%d%d", &n, &m, &k), msk = (1 << n) - 1;
	for (int i = 1; i <= n; i++) scanf("%d", v + i);
	for (int i = 1; i <= k; i++)
		scanf("%d%d%d", &x, &y, &z), g[x][y] = std::max(g[x][y], z);
	memset(dp, 0xc0, sizeof dp);
	for (int i = 1; i <= n; i++) dp[i][_(i)] = v[i];
	for (int S = 0; S <= msk; S++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				if (S & _(j))
					dp[i][S] = std::max(dp[i][S], dp[j][S ^ _(i)] + g[j][i] + v[i]);
	for (int i = 1; i <= n; i++)
		for (int S = 0; S <= msk; S++)
			if (__builtin_popcount(S) == m) ans = std::max(ans, dp[i][S]);
	printf("%lld", ans);
}