#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 3e2 + 23;
struct edge {
	int to, next;
} e[N];
int head[N], cnt;
void addedge(int x, int y) { e[++cnt] = (edge){y, x[head]}, x[head] = cnt; }

int dp[N][N], v[N], s[N], sz[N], idx;
void dfs(int x) {
	s[++idx] = x, x[sz] = 1;
	for (int i = x[head]; i; i = e[i].next) dfs(e[i].to), x[sz] += e[i].to[sz];
}

int n, m, x;
int main() {
	memset(dp, 0xc0, sizeof dp);
	dp[0][0] = 0;
	scanf("%d%d", &n, &m), m++;
	for (int i = 1; i <= n; i++) {
		scanf("%d%d", &x, v + i);
		addedge(x, i);
	}
	dfs(0);
	for (int i = 1; i <= idx; i++) {
		for (int j = 1; j <= m; j++)
			dp[i][j] = std::max(dp[i][j], dp[i - 1][j - 1] + s[i][v]);
		for (int j = 1; j <= m; j++)
			dp[i + s[i][sz] - 1][j] = std::max(dp[i + s[i][sz] - 1][j], dp[i - 1][j]);
	}
	printf("%d\n", dp[idx][m]);
}