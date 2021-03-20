#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

const int N = 2e2 + 22, M = 8e4 + 48;

int n, m, k, deg[2 * N], nid[2 * N], g[M][N], eid[M][N], col[M], cnt;
int main() {
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= n; i++) scanf("%*d");
	auto dfs = [&](auto d, int x, int cur, int last) -> void {
		std::swap(x[g][cur], x[g][last]);
		std::swap(x[eid][cur], x[eid][last]);
		x[eid][last][col] = last;
		if (x[g][last]) d(d, x[g][last], last, cur);
	};
	for (int i = 1, x, y; i <= m; i++) {
		scanf("%d%d", &x, &y), y += n;
		if (x[deg]++ % k == 0) x[nid] = ++cnt;
		if (y[deg]++ % k == 0) y[nid] = ++cnt;
		x = x[nid], y = y[nid];
		int u = 0, v = 0;
		for (int j = 1; !u && j <= k; j++)
			if (!x[g][j]) u = j;
		for (int j = 1; !v && j <= k; j++)
			if (!y[g][j]) v = j;
		if (x[g][v]) dfs(dfs, x, v, u);
		x[g][v] = y, x[eid][v] = i;
		y[g][v] = x, y[eid][v] = i;
		i[col] = v;
	}
	for (int i = 1; i <= m; i++) printf("%d\n", col[i]);
}