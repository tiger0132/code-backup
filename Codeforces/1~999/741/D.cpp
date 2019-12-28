#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 5e5 + 55, M = 1 << 23;
struct edge {
	int to, next, w;
} e[N << 1];
int head[N], cnt;
void addedge(int x, int y, int z) { e[++cnt] = (edge){y, x[head], z}, x[head] = cnt; }

int dep[N], par[N], son[N], sz[N], path[N], s[N];
void dfs1(int x, int d) {
	x[sz] = 1, x[dep] = d;
	for (int i = x[head], nx, mx = 0; i; i = e[i].next) {
		(nx = e[i].to)[path] = x[path] ^ (1 << e[i].w), dfs1(nx, d + 1), sz[x] += sz[nx];
		if (sz[nx] > mx) mx = sz[nx], son[x] = nx;
	}
}

int dis[M], ans[N];
void del(int x) {
	x[path][dis] = 0;
	for (int i = x[head]; i; i = e[i].next) del(e[i].to);
}
void add(int x) {
	x[path][dis] = std::max(x[path][dis], x[dep]);
	for (int i = x[head]; i; i = e[i].next) add(e[i].to);
}
void calc(int x, int anc) {
	if (x[path][dis]) anc[ans] = std::max(anc[ans], x[path][dis] + x[dep] - 2 * anc[dep]);
	for (int i = 1; i <= 4194304; i <<= 1) {
		if ((x[path] ^ i)[dis])
			anc[ans] = std::max(anc[ans], (x[path] ^ i)[dis] + x[dep] - 2 * anc[dep]);
	}
	anc[ans] = std::max(anc[ans], x[ans]);
	for (int i = x[head]; i; i = e[i].next) calc(e[i].to, anc);
}
void dfs2(int x, bool f) {
	for (int i = x[head], nx; i; i = e[i].next)
		if ((nx = e[i].to) != x[son]) dfs2(nx, false), x[ans] = std::max(x[ans], nx[ans]);
	if (x[son]) dfs2(x[son], true), x[ans] = std::max(x[ans], x[son][ans]);
	for (int i = x[head], nx; i; i = e[i].next)
		if ((nx = e[i].to) != x[son]) calc(nx, x), add(nx);
	// printf("\t%d[ans] <- %d\n", x[path][dis] - x[dep]);
	x[ans] = std::max(x[ans], x[path][dis] - x[dep]);
	for (int i = 1; i <= 4194304; i <<= 1)
		x[ans] = std::max(x[ans], (x[path] ^ i)[dis] - x[dep]);
	x[path][dis] = std::max(x[path][dis], x[dep]);
	if (!f) del(x);
}

int n, m, x;
bool dump;
char c[2];
int main() {
	scanf("%d", &n);
	for (int i = 2; i <= n; i++) scanf("%d%s", i + par, c), addedge(i[par], i, *c - 'a');
	dfs1(1, 0), dfs2(1, true);
	for (int i = 1; i <= n; i++) printf("%d ", i[ans]);
}