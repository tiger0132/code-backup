#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <stack>

const int N = 2e5 + 52;

struct graph {
	struct edge {
		int to, next;
	} e[N << 1];
	int head[N], cnt = 1;
	void addedge(int x, int y) {
		e[++cnt] = (edge){y, x[head]}, x[head] = cnt;
		e[++cnt] = (edge){x, y[head]}, y[head] = cnt;
		assert(cnt < N * 2);
	}
} g, h;

int dfn[N], low[N], col[N], f[N << 1], idx, dc;
void dfs(int x, int p) {
	x[dfn] = x[low] = ++idx;
	assert(idx < N);
	for (int i = x[g.head], nx; i; i = g.e[i].next)
		if (!(nx = g.e[i].to)[dfn]) {
			dfs(nx, i);
			x[low] = std::min(x[low], nx[low]);
			if (nx[low] > x[dfn]) i[f] = (i ^ 1)[f] = 1;
		} else if (i != (p ^ 1))
			x[low] = std::min(x[low], nx[dfn]);
}
void dfs0(int x, int c) {
	x[col] = c;
	for (int i = x[g.head], nx; i; i = g.e[i].next)
		if (!i[f] && !(nx = g.e[i].to)[col]) dfs0(nx, c);
}

int son[N], sz[N], top[N], par[N], dep[N], a[N], _col[N];
void dfs1(int x, int c) {
	x[sz] = 1, x[_col] = c;
	for (int i = x[h.head], nx, mx = 0; i; i = h.e[i].next)
		if ((nx = h.e[i].to) != x[par]) {
			nx[par] = x, nx[dep] = x[dep] + 1, dfs1(nx, c), x[sz] += nx[sz];
			if (nx[sz] > mx) mx = nx[sz], x[son] = nx;
		}
}
void dfs2(int x, int t) {
	x[top] = t;
	if (!x[son]) return;
	dfs2(x[son], t);
	for (int i = x[h.head], nx; i; i = h.e[i].next)
		if ((nx = h.e[i].to) != x[par] && nx != x[son]) dfs2(nx, nx);
}
int lca(int x, int y) {
	for (; top[x] != top[y]; x = x[top][par])
		if (x[top][dep] < y[top][dep]) std::swap(x, y);
	return x[dep] > y[dep] ? y : x;
}

int up[N], dn[N];
bool fl = true;
void dfs3(int x, int p) {
	for (int i = x[h.head], nx; i; i = h.e[i].next)
		if ((nx = h.e[i].to) != p) {
			dfs3(nx, x);
			if (nx[up] && nx[dn]) fl = false;
			x[up] += nx[up], x[dn] += nx[dn];
		}
}

int n, m, q, x[N], y[N], u, v, l;
int main() {
	scanf("%d%d%d", &n, &m, &q);
	for (int i = 1; i <= m; i++) {
		scanf("%d%d", x + i, y + i);
		g.addedge(x[i], y[i]);
	}

	// e-DCC
	for (int i = 1; i <= n; i++)
		if (!i[dfn]) dfs(i, -1);
	for (int i = 1; i <= n; i++)
		if (!i[col]) dfs0(i, ++dc);
	for (int i = 1; i <= m; i++)
		if (x[i][col] != y[i][col]) h.addedge(x[i][col], y[i][col]);
	assert(dc <= n);

	// HLD
	for (int i = 1; i <= n; i++)
		if (!i[sz]) dfs1(i, i), dfs2(i, i);

	while (q--) {
		scanf("%d%d", &u, &v), u = u[col], v = v[col];
		if (u[_col] != v[_col]) return puts("No"), 0;
		if (u == v) continue;
		l = lca(u, v);
		up[u]++, up[l]--;
		dn[v]++, dn[l]--;
	}
	dfs3(1, 1);
	puts(fl ? "Yes" : "No");
}