#include <algorithm>
#include <cstdio>
#include <cstring>
#include <numeric>

const int N = 2e2 + 22;
struct edge {
	int to, next;
} e[N << 1];
int head[N], cnt;
void addedge(int x, int y) {
	e[++cnt] = (edge){y, x[head]}, x[head] = cnt;
	e[++cnt] = (edge){x, y[head]}, y[head] = cnt;
}

int a[N], dp[N][N], dp2[N], k;
void dfs(int x, int p) {
	dp[x][0] = a[x];
	for (int i = x[head], nx; i; i = e[i].next)
		if ((nx = e[i].to) != p) {
			dfs(nx, x);
			memset(dp2, 0, 4 * (k + 1));
			for (int u = 0; u <= k; u++)
				for (int v = k - u, t; v <= k; v++)
					t = std::min(u, v + 1),
					dp2[t] = std::max(dp2[t], dp[x][u] + dp[nx][v]);
			memcpy(dp[x], dp2, 4 * (k + 1));
		}
}

int n, x, y;
int main() {
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	for (int i = 1; i < n; i++) scanf("%d%d", &x, &y), addedge(x, y);
	dfs(1, 0);
	printf("%d", std::accumulate(dp[1], dp[1] + k + 1, 0,
								 [](int x, int y) { return x > y ? x : y; }));
}