#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 2e2 + 22, M = 4e4 + 44;

int n, m, g[N][N], id[N][N], col[M], a[N][N], b[N][N], c[N][N], tmp[N];
inline int _(int i, int j) { return m * (i - 1) + j; }
int main() {
	scanf("%d%d", &n, &m);
	auto dfs = [&](auto d, int x, int cur, int last) -> void {
		std::swap(x[g][cur], x[g][last]);
		std::swap(x[id][cur], x[id][last]);
		x[id][last][col] = last;
		if (x[g][last]) d(d, x[g][last], last, cur);
	};
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) {
			scanf("%d", a[i] + j);
			int x = (a[i][j] - 1) / m + 1, y = i + n, u = 0, v = 0, nid = m * (i - 1) + j;
			for (int k = 1; !u && k <= m; k++)
				if (!x[g][k]) u = k;
			for (int k = 1; !v && k <= m; k++)
				if (!y[g][k]) v = k;
			if (x[g][v]) dfs(dfs, x, v, u);
			x[g][v] = y, x[id][v] = nid;
			y[g][v] = x, y[id][v] = nid;
			nid[col] = v;
		}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) b[i][_(i, j)[col]] = a[i][j];
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) printf("%d%c", b[i][j], " \n"[j == m]);
	for (int j = 1; j <= m; j++) {
		for (int i = 1; i <= n; i++) tmp[i] = b[i][j];
		std::sort(tmp + 1, tmp + n + 1);
		for (int i = 1; i <= n; i++) c[i][j] = tmp[i];
	}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++) printf("%d%c", c[i][j], " \n"[j == m]);
}
