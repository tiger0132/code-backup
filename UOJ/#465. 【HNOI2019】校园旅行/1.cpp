#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

const int N = 5e3 + 35, M = 5e5 + 55;

// clang-format off
// TEMPLATE BEGIN
struct graph {
	struct edge { int to, next; } e[M << 1]; int head[N], cnt = 1;
	void addedge(int x, int y) {
		e[++cnt] = (edge){y, head[x]}, head[x] = cnt;
		e[++cnt] = (edge){x, head[y]};
		if (x != y) head[y] = cnt;
	}
} g00, g01, g11, h;
struct dsu {
	int p[N]; int f(int x) { return p[x] ? p[x] = f(p[x]) : x; }
} d[2];
// TEMPLATE END
// clang-format on

int dp[N][N], c[N];
char col[N];
bool flg;
void dfs1(const graph& g, int x) {
	for (int i = g.head[x], nx; i; i = g.e[i].next) {
		if (c[nx = g.e[i].to] == -1)
			c[nx] = !c[x], h.addedge(x, nx), dfs1(g, nx);
		else if (c[nx] == c[x] && flg)
			flg = false, h.addedge(x, x);
	}
}
void dfs2(int x, int y) {
	if (x > y) std::swap(x, y);
	if (dp[x][y]) return;
	dp[x][y] = true;
	for (int i = h.head[x], nx; i; i = h.e[i].next)
		for (int j = h.head[y], ny; j; j = h.e[j].next)
			if (col[nx = h.e[i].to] == col[ny = h.e[j].to] && ((nx > ny && (std::swap(nx, ny), 0)), !dp[nx][ny])) dfs2(nx, ny);
}

int n, m, q, x, y;
int main() {
	scanf("%d%d%d%s", &n, &m, &q, col + 1);
	for (int i = 1; i <= n; i++) col[i] -= 48;
	for (int i = 1; i <= m; i++) {
		scanf("%d%d", &x, &y);
		if (col[x] != col[y]) g01.addedge(x, y);
		if (col[x] && col[y]) g11.addedge(x, y);
		if (!col[x] && !col[y]) g00.addedge(x, y);
	}
	memset(c, -1, sizeof c);
	for (int i = 1; i <= n; i++)
		if (c[i] == -1) c[i] = 0, flg = true, dfs1(g00, i);
	memset(c, -1, sizeof c);
	for (int i = 1; i <= n; i++)
		if (c[i] == -1) c[i] = 0, flg = true, dfs1(g11, i);
	memset(c, -1, sizeof c);
	for (int i = 1; i <= n; i++)
		if (c[i] == -1) c[i] = 0, flg = true, dfs1(g01, i);
	for (int i = 1; i <= n; i++) dfs2(i, i);
	for (int i = 1; i <= n; i++)
		for (int j = h.head[i], nx; j; j = h.e[j].next)
			if ((nx = h.e[j].to) > i && col[i] == col[nx]) dfs2(i, nx);
	while (q--) {
		scanf("%d%d", &x, &y), (x > y && (std::swap(x, y), 0));
		puts(dp[x][y] || dp[y][x] ? "YES" : "NO");
	}
}