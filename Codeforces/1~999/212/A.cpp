#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

const int N = 2e2 + 22, M = 8e4 + 48;

int n, m, t, k, deg[2 * N], nid[2 * N], g[M][N], eid[M][N], col[M], ans, cnt;
int main() {
	scanf("%d%d%d%d", &n, &m, &k, &t);
	auto dfs = [&](auto d, int x, int cur, int last) -> void {
		std::swap(x[g][cur], x[g][last]);	   // swap edges
		std::swap(x[eid][cur], x[eid][last]);  // sync edge ids
		x[eid][last][col] = last;  // change the out edge (x, y, cur) -> (x, y, last)
		if (x[g][last]) d(d, x[g][last], last, cur);
	};
	for (int i = 1, x, y; i <= k; i++) {
		scanf("%d%d", &x, &y), y += n;
		if (x[deg]++ % t == 0) x[nid] = ++cnt;
		if (y[deg]++ % t == 0) y[nid] = ++cnt;
		x = x[nid], y = y[nid];
		int u = 0, v = 0;
		for (int j = 1; !u && j <= t; j++)
			if (!x[g][j]) u = j;
		for (int j = 1; !v && j <= t; j++)
			if (!y[g][j]) v = j;
		if (x[g][v]) dfs(dfs, x, v, u);
		x[g][v] = y, x[eid][v] = i;
		y[g][v] = x, y[eid][v] = i;
		i[col] = v;
	}
	for (int i = 1; i <= n + m; i++) ans += deg[i] % t > 0;
	printf("%d\n", ans);
	for (int i = 1; i <= k; i++) printf("%d%c", col[i], " \n"[i == k]);
}