#include <algorithm>
#include <cstdio>
#include <cstring>

typedef long long L;
const int N = 3e3 + 33, P = 1e9 + 7;

int n, m, dp[N][N];
char mp[N][N];
int calc(int x1, int y1, int x2, int y2) {
	memset(dp, 0, sizeof dp), dp[x1][y1] = mp[x1][y1] == '.';
	for (int i = x1; i <= x2; i++)
		for (int j = y1; j <= y2; j++)
			if (mp[i][j] == '.') dp[i][j] = (dp[i][j] + dp[i - 1][j] + dp[i][j - 1]) % P;
	return dp[x2][y2];
}
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%s", mp[i] + 1);
	printf("%lld\n", ((L)calc(1, 2, n - 1, m) * calc(2, 1, n, m - 1) + P -
					  (L)calc(1, 2, n, m - 1) * calc(2, 1, n - 1, m) % P) %
						 P);
}