#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 3e5 + 53, M = 19;
struct edge {
	int to, next, w;
	bool operator<(const edge& r) const { return w > r.w; }
} e[N << 1], orig[N];
int head[N], cnt;
void addedge(int x, int y, int z) {
	e[++cnt] = (edge){y, x[head], z}, x[head] = cnt;
	e[++cnt] = (edge){x, y[head], z}, y[head] = cnt;
}

int fa[N][M], mn[N][M], dep[N], v[N];
int lca(int x, int y) {
	int ret = 1e9;
	if (x[dep] < y[dep]) std::swap(x, y);
	for (int sub = x[dep] - y[dep]; sub; sub -= sub & -sub)
		ret = std::min(ret, x[mn][__builtin_ctz(sub)]), x = x[fa][__builtin_ctz(sub)];
	if (x == y) return ret;
	for (int i = M - 1; i >= 0; i--)
		if (x[fa][i] != y[fa][i])
			ret = std::min(ret, std::min(x[mn][i], y[mn][i])), x = x[fa][i], y = y[fa][i];
	return std::min(ret, std::min(x[mn][0], y[mn][0]));
}
void dfs(int x, int p, int d = 1) {
	x[v] = 1, x[dep] = d;
	for (int i = 1; i < M; i++)
		x[fa][i] = x[fa][i - 1][fa][i - 1],
		x[mn][i] = std::min(x[mn][i - 1], x[fa][i - 1][mn][i - 1]);
	for (int i = x[head], nx; i; i = e[i].next)
		if ((nx = e[i].to) != p) nx[fa][0] = x, nx[mn][0] = e[i].w, dfs(nx, x, d + 1);
}

int p[N];
int f(int x) { return x[p] ? x[p] = f(x[p]) : x; }
void u(int x, int y) {
	if ((x = f(x)) != (y = f(y))) x[p] = y;
}

int n, m, q, x, y, z;
int main() {
	memset(mn, 0x3f, sizeof mn);
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) scanf("%d%d%d", &orig[i].to, &orig[i].next, &orig[i].w);
	std::sort(orig + 1, orig + m + 1);
	for (int i = 1; i <= m; i++) {
		x = orig[i].to, y = orig[i].next;
		if (f(x) != f(y)) u(x, y), addedge(x, y, orig[i].w);
	}
	for (int i = 1; i <= n; i++)
		if (!i[v]) dfs(i, 0);
	// for (int i = 1; i <= n; i++) {
	// 	for (int j = 0; j < M; j++) printf("[%d %d]", i[fa][j], i[mn][j]);
	// 	puts("");
	// }
	scanf("%d", &q);
	while (q--) scanf("%d%d", &x, &y), printf("%d\n", f(x) != f(y) ? -1 : lca(x, y));
}