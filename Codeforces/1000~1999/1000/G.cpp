#include <algorithm>
#include <cstdio>
#include <cstring>
#define int long long

const int N = 3e5 + 53;
struct edge {
	int to, next, w;
} e[N << 1];
int head[N], cnt;
void addedge(int x, int y, int z) {
	e[++cnt] = (edge){y, x[head], z}, x[head] = cnt;
	e[++cnt] = (edge){x, y[head], z}, y[head] = cnt;
}

int son[N], sz[N], top[N], par[N], dep[N], a[N];
int dis[N], up[N], dn[N], v[N], f[N];
void dfs1(int x) {
	x[sz] = 1, x[dn] = x[a];
	for (int i = x[head], nx, mx = 0; i; i = e[i].next)
		if ((nx = e[i].to) != x[par]) {
			nx[v] = e[i].w, nx[par] = x, nx[dep] = x[dep] + 1, dfs1(nx);
			x[sz] += nx[sz], x[dn] += nx[f];
			if (nx[sz] > mx) mx = nx[sz], x[son] = nx;
		}
	x[f] = std::max(0ll, dn[x] - 2 * x[v]);
}
void dfs2(int x, int t) {
	x[top] = t;
	x[dis] = x[par][dn] - f[x] - v[x];
	x[up] = std::max(0ll, x[par][up] + x[dis] - v[x]);
	x[dis] += x[par][dis];
	if (!x[son]) return;
	dfs2(x[son], t);
	for (int i = x[head], nx; i; i = e[i].next)
		if ((nx = e[i].to) != x[par] && nx != x[son]) dfs2(nx, nx);
}
int lca(int x, int y) {
	for (; top[x] != top[y]; x = x[top][par])
		if (x[top][dep] < y[top][dep]) std::swap(x, y);
	return x[dep] > y[dep] ? y : x;
}

int n, m, x, y, z;
signed main() {
	scanf("%lld%lld", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%lld", a + i);
	for (int i = 1; i < n; ++i) scanf("%lld%lld%lld", &x, &y, &z), addedge(x, y, z);
	dfs1(1), dfs2(1, 1);
	for (int i = 1; i <= m; ++i) {
		scanf("%lld%lld", &x, &y), z = lca(x, y);
		printf("%lld\n", x[dis] + y[dis] - 2 * z[dis] + x[dn] + y[dn] - z[dn] + z[up]);
	}
}