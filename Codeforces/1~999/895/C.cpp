#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 1e2 + 21, K = 70, M = 5.3e5 + 535, _ = 1e5 + 51, P = 1e9 + 7,
		  p[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67};

int n, cnt[N], dp[N][M], pw2[_], ans, x;
int main() {
	for (scanf("%*d"); ~scanf("%d", &x);) x[cnt]++;
	dp[0][0] = 1, pw2[0] = 1;
	for (int i = 1; i < _; i++) pw2[i] = 2 * pw2[i - 1] % P;
	for (int i = 1; i <= K; i++) {
		if (!i[cnt]) {
			memcpy(dp[i], dp[i - 1], sizeof *dp);
			continue;
		}
		int msk = 0;
		for (int tmp = i, j = 0; j < 19; j++)
			for (; tmp % p[j] == 0; tmp /= p[j]) msk ^= 1 << j;
		for (int j = 0; j < 524288; j++)
			dp[i][j] = 1ll * (dp[i - 1][j ^ msk] + dp[i - 1][j]) * pw2[i[cnt] - 1] % P;
	}
	ans = (dp[K][0] - 1) % P;
	printf("%d", ans);
}