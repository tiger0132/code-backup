#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

const int N = 2e3 + 32, M = 1e5 + 51;

int n, m, k, d, p[M], q[M], deg[2 * N], nid[2 * N], g[N][N], eid[N][N], col[M], cnt;
int main() {
	scanf("%d%d%d", &n, &m, &k);
	auto dfs = [&](auto dd, int x, int cur, int last) -> void {
		std::swap(x[g][cur], x[g][last]);
		std::swap(x[eid][cur], x[eid][last]);
		x[eid][last][col] = last;
		if (x[g][last]) dd(dd, x[g][last], last, cur);
	};
	for (int i = 1; i <= k; i++) {
		scanf("%d%d", p + i, q + i), q[i] += n;
		p[i][deg]++, q[i][deg]++;
	}
	for (int i = 1; i <= n + m; i++) d = std::max(d, i[deg]);
	for (int i = 1, x, y; i <= k; i++) {
		x = p[i], y = q[i];
		int u = 0, v = 0;
		for (int j = 1; !u && j <= d; j++)
			if (!x[g][j]) u = j;
		for (int j = 1; !v && j <= d; j++)
			if (!y[g][j]) v = j;
		if (x[g][v]) dfs(dfs, x, v, u);
		x[g][v] = y, x[eid][v] = i;
		y[g][v] = x, y[eid][v] = i;
		i[col] = v;
	}
	printf("%d\n", d);
	for (int i = 1; i <= k; i++) printf("%d%c", col[i], " \n"[i == k]);
}