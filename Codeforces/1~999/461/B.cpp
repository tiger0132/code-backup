#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 1e5 + 51, P = 1e9 + 7;
struct edge {
	int to, next;
} e[N << 1];
int head[N], cnt;
void addedge(int x, int y) {
	e[++cnt] = (edge){y, x[head]}, x[head] = cnt;
	e[++cnt] = (edge){x, y[head]}, y[head] = cnt;
}

int dp[N][2], col[N];
void dfs(int x, int p) {
	dp[x][x[col]] = 1;
	for (int i = x[head], nx; i; i = e[i].next)
		if ((nx = e[i].to) != p) {
			dfs(nx, x);
			dp[x][1] =
				(1ll * dp[x][1] * (dp[nx][1] + dp[nx][0]) + 1ll * dp[x][0] * dp[nx][1]) %
				P;
			dp[x][0] = 1ll * dp[x][0] * (dp[nx][1] + dp[nx][0]) % P;
		}
}

int n, x;

int main() {
	scanf("%d", &n);
	for (int i = 2; i <= n; i++) scanf("%d", &x), addedge(i, x + 1);
	for (int i = 1; i <= n; i++) scanf("%d", col + i);
	dfs(1, 0);
	printf("%d", dp[1][1]);
}