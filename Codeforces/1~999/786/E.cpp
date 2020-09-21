#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <utility>
#include <vector>

typedef std::pair<int, int> pii;
const int N = 2e4 + 42, M = 1e6 + 61, LN = 16;

struct edge {
	int to, next, w;
} e[M << 1];
int head[M], cnt = 1, nc;
void addedge(int x, int y, int z) {
	if (!y) return;
	e[++cnt] = (edge){y, x[head], z}, x[head] = cnt;
	e[++cnt] = (edge){x, y[head], 0}, y[head] = cnt;
}

int fa[N][LN], pt[N][LN], dep[N], eid[N];
std::vector<pii> g[N];
void dfs(int x, int p) {
	x[fa][0] = p, x[pt][0] = ++nc;
	addedge(nc, x, 1e9);
	for (int i = 1; i < LN; i++) {
		x[fa][i] = x[fa][i - 1][fa][i - 1], x[pt][i] = ++nc;
		addedge(nc, x[pt][i - 1], 1e9), addedge(nc, x[fa][i - 1][pt][i - 1], 1e9);
	}
	for (auto [nx, id] : x[g])
		if (nx != p) nx[eid] = id, nx[dep] = x[dep] + 1, dfs(nx, x);
}
int lca(int x, int y) {
	if (x[dep] < y[dep]) std::swap(x, y);
	for (int i = LN - 1; i >= 0; i--)
		if (x[fa][i][dep] >= y[dep]) x = x[fa][i];
	if (x == y) return x;
	for (int i = LN - 1; i >= 0; i--)
		if (x[fa][i] != y[fa][i]) x = x[fa][i], y = y[fa][i];
	return x[fa][0];
}
int get(int x, int k) {
	for (int i = 0; i < LN; i++)
		if ((k >> i) & 1) x = x[fa][i];
	return x;
}
void link(int p, int x, int y) {
	if (x == y) return;
	int sub = x[dep] - y[dep];
	int k = 31 - __builtin_clz(sub);
	addedge(p, x[pt][k], 1e9);
	addedge(p, get(x, sub - (1 << k))[pt][k], 1e9);
}

int lv[M], cur[M];
bool bfs(int s, int t) {
	memset(lv, 0, sizeof lv);
	std::queue<int> q;
	for (s[lv] = 1, q.push(s); !q.empty(); q.pop())
		for (int x = q.front(), i = x[cur] = x[head], nx; i; i = e[i].next)
			if (!(nx = e[i].to)[lv] && e[i].w) nx[lv] = x[lv] + 1, q.push(nx);
	return t[lv];
}
int dfs(int s, int t, int f) {
	if (s == t || !f) return f;
	int r = 0, tt;
	for (int &i = s[cur], nx; i; i = e[i].next)
		if ((nx = e[i].to)[lv] == s[lv] + 1 &&
			(tt = dfs(nx, t, std::min(f, (int)e[i].w)))) {
			e[i].w -= tt, e[i ^ 1].w += tt, r += tt, f -= tt;
			if (!f) return r;
		}
	if (f) s[lv] = 0;
	return r;
}
int dinic(int s, int t) {
	int r = 0;
	while (bfs(s, t)) r += dfs(s, t, 1e9);
	return r;
}

bool vis[M];
void dfs2(int x) {
	x[vis] = true;
	for (int i = x[head], nx; i; i = e[i].next)
		if (e[i].w && !(nx = e[i].to)[vis]) dfs2(nx);
}

std::vector<int> v1, v2;
int n, m, S, T, c_pt[N];
int main() {
	scanf("%d%d", &n, &m), nc = n;
	for (int i = 1, x, y; i < n; i++) {
		scanf("%d%d", &x, &y);
		x[g].push_back({y, i});
		y[g].push_back({x, i});
	}
	dep[1] = 1, dfs(1, 0);
	S = ++nc, T = ++nc;
	for (int i = 1; i <= n; i++) addedge(i, T, 1);
	for (int i = 1, x, y; i <= m; i++) {
		scanf("%d%d", &x, &y);
		int l = lca(x, y), p = ++nc;
		c_pt[i] = p;
		addedge(S, p, 1);
		link(p, x, l), link(p, y, l);
	}
	printf("%d\n", dinic(S, T));
	dfs2(S);

	for (int i = 1; i <= m; i++)
		if (!c_pt[i][vis]) v1.push_back(i);
	for (int i = 2; i <= n; i++)
		if (i[vis]) v2.push_back(eid[i]);
	printf("%lu", v1.size());
	for (int i : v1) printf(" %d", i);
	puts("");
	printf("%lu", v2.size());
	for (int i : v2) printf(" %d", i);
	puts("");
}