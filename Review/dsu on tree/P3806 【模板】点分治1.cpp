#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 1e4 + 41, M = 1e2 + 21, K = 1e7 + 71;
struct edge {
	int to, next, w;
} e[N << 1];
int head[N], cnt;
void addedge(int x, int y, int z) {
	e[++cnt] = (edge){y, x[head], z}, x[head] = cnt;
	e[++cnt] = (edge){x, y[head], z}, y[head] = cnt;
}

int dep[N], par[N], sz[N], son[N];
int m, qry[M], ans[M];
bool v[K];
void dfs1(int x, int p, int d) {
	x[par] = p, x[sz] = 1, x[dep] = d;
	for (int i = x[head], nx, mx = 0; i; i = e[i].next)
		if ((nx = e[i].to) != p) {
			dfs1(nx, x, d + e[i].w), x[sz] += nx[sz];
			if (nx[sz] > mx) mx = nx[sz], x[son] = nx;
		}
}
void add(int x) {
	// printf("ADD %d\n", x[dep]);
	x[dep][v] = 1;
	for (int i = x[head], nx; i; i = e[i].next)
		if ((nx = e[i].to) != x[par]) add(nx);
}
void del(int x) {
	// printf("DEL %d\n", x[dep]);
	x[dep][v] = 0;
	for (int i = x[head], nx; i; i = e[i].next)
		if ((nx = e[i].to) != x[par]) del(nx);
}
void calc(int x, int t) {
	for (int i = 1, l; i <= m; i++)
		if ((l = qry[i] - x[dep] + 2 * t[dep]) >= 0) ans[i] |= v[l];
	for (int i = x[head], nx; i; i = e[i].next)
		if ((nx = e[i].to) != x[par]) calc(nx, t);
}
void dfs3(int x, bool f) {
	for (int i = x[head], nx; i; i = e[i].next)
		if ((nx = e[i].to) != x[par] && nx != x[son]) dfs3(nx, false);
	if (x[son]) dfs3(x[son], true);
	x[dep][v] = 1;
	for (int i = 1, l; i <= m; i++)
		if ((l = qry[i] + x[dep]) >= 0) ans[i] |= v[l];
	for (int i = x[head], nx; i; i = e[i].next)
		if ((nx = e[i].to) != x[par] && nx != x[son]) {
			calc(nx, x);
			add(nx);
		}
	if (!f) del(x);
}

int n, x, y, z;
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i < n; i++) scanf("%d%d%d", &x, &y, &z), addedge(x, y, z);
	for (int i = 1; i <= m; i++) scanf("%d", qry + i);
	dfs1(x, 0, 0), dfs3(x, true);
	for (int i = 1; i <= m; i++) puts(ans[i] ? "AYE" : "NAY");
}