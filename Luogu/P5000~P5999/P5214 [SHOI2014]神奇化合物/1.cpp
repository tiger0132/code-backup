#include <algorithm>
#include <cstdio>
#include <cstring>
#include <unordered_set>

const int N = 5e3 + 35, M = 2e5 + 52;

std::unordered_set<int> e[N];
int g[N][N];
void addedge(int x, int y) {
	g[y][x]++;
	if (!g[x][y]++) e[x].insert(y), e[y].insert(x);
}

int vis[N];
void dfs(int x) {
	x[vis] = 1;
	for (int nx : e[x])
		if (!nx[vis]) dfs(nx);
}

int p[N];
int f(int x) { return x[p] ? x[p] = f(x[p]) : x; }
void l(int x, int y) {
	if ((x = f(x)) != (y = f(y))) x[p] = y;
}

int n, m, q, op[M], u[M], v[M], xx[M], yy[M], col[N], nc;
char t[9];
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) {
		scanf("%d%d", u + i, v + i);
		g[u[i]][v[i]] = g[v[i]][u[i]] = 1;
	}
	scanf("%d", &q);
	for (int i = 1; i <= q; i++) {
		scanf("%s", t);
		if (*t == 'Q')
			op[i] = 1;
		else if (*t == 'A')
			op[i] = 2, scanf("%d%d", xx + i, yy + i);
		else {
			op[i] = 3, scanf("%d%d", xx + i, yy + i);
			g[xx[i]][yy[i]] = g[yy[i]][xx[i]] = 0;
		}
	}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j < i; j++)
			if (g[i][j]) l(i, j);
	for (int i = 1; i <= n; i++)
		if (f(i) == i) i[col] = ++nc;
	for (int i = 1; i <= n; i++) i[col] = f(i)[col];
	memset(g, 0, sizeof g);
	for (int i = 1, x, y; i <= m; i++)
		if ((x = u[i][col]) != (y = v[i][col])) addedge(x, y);
	for (int i = 1; i <= q; i++) {
		xx[i] = xx[i][col];
		yy[i] = yy[i][col];
		if (op[i] == 1) {
			memset(vis, 0, sizeof vis);
			int ans = 0;
			for (int j = 1; j <= nc; j++)
				if (!j[vis]) dfs(j), ans++;
			printf("%d\n", ans);
		} else if (op[i] == 2)
			addedge(xx[i], yy[i]);
		else {
			--g[xx[i]][yy[i]];
			if (!--g[yy[i]][xx[i]]) {
				e[xx[i]].erase(yy[i]);
				e[yy[i]].erase(xx[i]);
			}
		}
	}
}