#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 5e5 + 55;
struct edge {
	int to, next;
} e[N << 1];
int head[N], cnt;
void addedge(int x, int y) {
	e[++cnt] = (edge){y, x[head]}, x[head] = cnt;
	e[++cnt] = (edge){x, y[head]}, y[head] = cnt;
}

int par[N], sz[N], dep[N], son[N], top[N];
void dfs1(int x, int p, int d) {
	x[sz] = 1, x[par] = p, x[dep] = d;
	for (int i = x[head], nx, mx = 0; i; i = e[i].next)
		if ((nx = e[i].to) != p) {
			dfs1(nx, x, d + 1), x[sz] += nx[sz];
			if (nx[sz] > mx) mx = nx[sz], x[son] = nx;
		}
}
void dfs2(int x, int t) {
	x[top] = t;
	if (!x[son]) return;
	dfs2(x[son], t);
	for (int i = x[head], nx; i; i = e[i].next)
		if ((nx = e[i].to) != x[par] && nx != x[son]) dfs2(nx, nx);
}
int lca(int x, int y) {
	for (; x[top] != y[top]; x = x[top][par])
		if (x[top][dep] < y[top][dep]) std::swap(x, y);
	return x[dep] < y[dep] ? x : y;
}
int dis(int x, int y) { return x[dep] + y[dep] - 2 * lca(x, y)[dep]; }
int dis(int x, int y, int l) { return x[dep] + y[dep] - 2 * l[dep]; }

int n, m, x, y, z, l, la, ans, mi;
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i < n; i++) scanf("%d%d", &x, &y), addedge(x, y);
	dfs1(1, 0, 1), dfs2(1, 1);
	for (int i = 1; i <= m; i++) {
		scanf("%d%d%d", &x, &y, &z), ans = 1e9;
		if ((l = lca(x, y)), ans > (la = dis(x, y, l) + dis(l, z))) ans = la, mi = l;
		if ((l = lca(x, z)), ans > (la = dis(x, z, l) + dis(l, y))) ans = la, mi = l;
		if ((l = lca(y, z)), ans > (la = dis(y, z, l) + dis(l, x))) ans = la, mi = l;
		printf("%d %d\n", mi, ans);
	}
}