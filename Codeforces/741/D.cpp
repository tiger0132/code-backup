#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 5e5 + 55, M = 1 << 22;
struct edge {
	int to, next, w;
} e[N << 1];
int head[N], cnt;
void addedge(int x, int y, int z) { e[++cnt] = (edge){y, x[head], z}, x[head] = cnt; }

int dep[N], par[N], son[N], sz[N], path[N], s[N];
void dfs1(int x, int p, int d) {
	x[sz] = 1, x[par] = p, x[dep] = d;
	for (int i = x[head], nx, mx = 0; i; i = e[i].next) {
		nx[path] = x[path] ^ e[i].w, dfs1(nx, x, d + 1), sz[x] += sz[nx];
		if (sz[nx] > mx) mx = sz[nx], son[x] = nx;
	}
}

int dis[M];
void dfs3(int x) {  // 暴力统计

	for (int i = x[head], nx; i; i = e[i].next)
		if ((nx = e[i].to) != x[par] && !nx[vis]) dfs3(nx);
}

int n, m, x;
char c[2];
int main() {
	scanf("%d", &n);
	for (int i = 2; i <= n; i++) scanf("%d%s", &x, c), addedge(x, i, *c - 'a');
}