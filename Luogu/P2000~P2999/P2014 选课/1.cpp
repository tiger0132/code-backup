#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 3e2 + 23;
struct edge {
	int to, next;
} e[N];
int head[N], cnt;
void addedge(int x, int y) { e[++cnt] = (edge){y, x[head]}, x[head] = cnt; }

int dp[N][N], v[N], m;
void dfs(int x, int d) {
	for (int i = x[head], nx; ~i; i = e[i].next) {
		nx = e[i].to;
		for (int j = d + 1; j <= m; j++) dp[nx][j] = dp[x][j - 1] + nx[v];
		dfs(nx, d + 1);
		for (int j = d + 1; j <= m; j++) dp[x][j] = std::max(dp[x][j], dp[nx][j]);
	}
}

int n, x;
int main() {
	memset(head, -1, sizeof head);
	scanf("%d%d", &n, &m), m++;
	for (int i = 1; i <= n; i++) {
		scanf("%d%d", &x, v + i);
		addedge(x, i);
	}
	dfs(0, 1);
	printf("%d\n", dp[0][m]);
}