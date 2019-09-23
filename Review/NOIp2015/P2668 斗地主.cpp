#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 25, _[] = {14, 12, 13}, ofs[] = {0, 5, 3, 2};

int dp[N][N][N][N][N], cnt[N], c[N];
int x, y, t, n, ans;
void dfs(int x) {
	if (x >= ans) return;
	for (int k = 1; k <= 3; k++)
		for (int l = 1; l <= 12; l++) {
			for (int i = l; i < l + ofs[k]; i++)
				if (cnt[i] < k) goto end;
			for (int r = l + ofs[k] - 1; r <= 12; r++) {
				if (cnt[r] < k) break;
				for (int i = l; i <= r; i++) cnt[i] -= k;
				dfs(x + 1);
				for (int i = l; i <= r; i++) cnt[i] += k;
			}
		end:;
		}
	memset(c, 0, sizeof c);
	for (int i = 1; i <= 13; i++) c[cnt[i]]++;
	ans = std::min(ans, dp[c[1]][c[2]][c[3]][c[4]][cnt[14]] + x);
}
int main() {
	memset(dp, 0x3f, sizeof dp);
	scanf("%d%d", &t, &n);
	*****dp = 0;
	for (int d = 0; d <= n; d++)
		for (int c = 0; c <= n; c++)
			for (int a = 0; a <= n; a++)
				for (int b = 0; b <= n; b++)
					for (int e = 0; e <= 2; e++) {
						int &p = dp[a][b][c][d][e];
						if (a) p = std::min(p, dp[a - 1][b][c][d][e] + 1);
						if (b) p = std::min(p, dp[a][b - 1][c][d][e] + 1);
						if (c) {
							p = std::min(p, dp[a][b][c - 1][d][e] + 1);
							p = std::min(p, dp[a + 1][b + 1][c - 1][d][e]);
							if (a) p = std::min(p, dp[a - 1][b][c - 1][d][e] + 1);
							if (b) p = std::min(p, dp[a][b - 1][c - 1][d][e] + 1);
							if (e) p = std::min(p, dp[a][b][c - 1][d][e - 1] + 1);
						}
						if (d) {
							if (a > 1) p = std::min(p, dp[a - 2][b][c][d - 1][e] + 1);
							if (b) p = std::min(p, dp[a][b - 1][c][d - 1][e] + 1);
							if (b > 1) p = std::min(p, dp[a][b - 2][c][d - 1][e] + 1);
							if (a && e)
								p = std::min(p, dp[a - 1][b][c][d - 1][e - 1] + 1);
							if (e > 1) p = std::min(p, dp[a][b][c][d - 1][e - 2] + 1);
							if (d > 1) p = std::min(p, dp[a][b][c][d - 2][e] + 1);
							p = std::min(p, dp[a + 1][b][c + 1][d - 1][e]);
						}
						if (e) p = std::min(p, dp[a][b][c][d][e - 1] + 1);
						if (e > 1) p = std::min(p, dp[a][b][c][d][e - 2] + 1);
					}
	while (t--) {
		memset(cnt, 0, sizeof cnt), ans = n;
		for (int i = 1; i <= n; i++) scanf("%d%*d", &x), cnt[x > 2 ? x - 2 : _[x]]++;
		dfs(0);
		printf("%d\n", ans);
	}
}