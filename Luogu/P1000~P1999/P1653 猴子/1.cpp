#include <algorithm>
#include <cstdio>
#include <iostream>

const int N = 2e5 + 52, M = 4e5 + 54;

int n, m, ch[N][2], id[M], dir[M], v[N][2], ans[N];
int nor[N];

struct edge {
	int to, next;
} e[N << 1], orig[N];

int head[N], cnt;
void addedge(int x, int y) {
	e[++cnt] = (edge){y, x[head]}, x[head] = cnt;
	e[++cnt] = (edge){x, y[head]}, y[head] = cnt;
}

int fa[N];
int f(int x) { return x[fa] ? x[fa] = f(x[fa]) : x; }
int u(int x, int y) {
	if ((x = f(x)) != (y = f(y))) return fa[x] = y, 1;
	return 0;
}
void dfs(int x, int d) {
	ans[x] = d;
	for (int i = x[head], nx; i; i = e[i].next)
		if ((nx = e[i].to)[ans] == -1) dfs(nx, d);
}
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d%d", ch[i], ch[i] + 1), ans[i] = -1;
	for (int i = 0; i < m; i++) {
		scanf("%d%d", id + i, dir + i);
		dir[i]--, v[id[i]][dir[i]] = 1;
	}
	for (int j = 1; j <= n; j++)
		for (int i = 0; i < 2; i++) {
			if (!v[j][i] && ch[j][i] != -1) {
				int a = j, b = ch[j][i];
				if (u(a, b)) addedge(a, b);
			}
		}
	for (int i = m - 1; i >= 0; i--) {
		int aa = f(id[i]), bb = f(id[i][ch][dir[i]]);
		if (aa == bb) continue;
		if (aa == f(1)) dfs(id[i][ch][dir[i]], i);
		if (bb == f(1)) dfs(id[i], i);
		if (id[i][ch][dir[i]] == -1) continue;
		u(id[i], id[i][ch][dir[i]]);
		addedge(id[i], id[i][ch][dir[i]]);
	}
	for (int i = 1; i <= n; i++) printf("%d\n", ans[i]);
}