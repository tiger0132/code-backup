#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 11 + 52;
struct edge {
	int to, next;
} e[N << 1];
int head[N], cnt;
void addedge(int x, int y) {
	e[++cnt] = (edge){y, head[x]}, head[x] = cnt;
	e[++cnt] = (edge){x, head[y]}, head[y] = cnt;
}

struct dsuQwQ {
	int p[N];
	int f(int x) { return p[x] ? p[x] = f(p[x]) : x; }
	void m(int x, int y) { (x = f(x)) != (y = f(y)) && (p[x] = y); }
} dsu;

namespace $ {
int n;
int _[N];
void add(int i, int x) {
	for (; i <= n; i += i & -i) _[i] += x;
}
int query(int i) {
	int ret = 0;
	for (; i; i -= i & -i) ret += _[i];
	return ret;
}
void add(int l, int r, int x) {
	printf("upd [%d, %d] %d\n", l, r, x);
	add(l, x), add(r + 1, -x);
}
}  // namespace $

int dfn[N], dep[N], par[N], sz[N], son[N], top[N], idx;
void dfs1(int x, int p, int d) {
	par[x] = p, dep[x] = d, sz[x] = 1;
	int mx = 0;
	for (int i = head[x]; i; i = e[i].next) {
		int nx = e[i].to;
		if (nx == p) continue;
		dfs1(nx, x, d + 1);
		sz[x] += sz[nx];
		if (sz[nx] > mx) mx = sz[nx], son[x] = nx;
	}
}
void dfs2(int x, int t) {
	dfn[x] = ++idx, top[x] = t;
	if (!son[x]) return;
	dfs2(son[x], t);
	for (int i = head[x]; i; i = e[i].next) {
		int nx = e[i].to;
		if (nx != par[x] && nx != son[x]) dfs2(nx, nx);
	}
}
void update(int x, int z) {
	for (; x != 0; x = par[top[x]]) $::add(dfn[top[x]], dfn[x], z);
}

int n, q, op[N], x[N], y[N];
char buf[2];
int main() {
	scanf("%d%d", &n, &q), $::n = n;
	for (int i = 1; i <= q; i++) {
		scanf("%s%d%d", buf, x + i, y + i);
		if (*buf == 'A') op[i] = 1, addedge(x[i], y[i]);
	}
	for (int i = 1; i <= n; i++)
		if (!par[i]) dfs1(i, 0, 1);
	for (int i = 1; i <= n; i++) {
		if (!top[i]) dfs2(i, i);
		update(i, 1), update(par[i], -1);
	}
	for (int i = 1; i <= n; i++) {
		printf("%d %d %d %d %d\n", dfn[i], par[i], top[i], son[i], sz[i]);
	}
	// for (int i = 1; i <= q; i++) {
	// 	int u = x[i], v = y[i];
	// 	if (par[u] == v) std::swap(u, v);
	// 	int sv = query(dfn[v]);
	// 	if (op[i]) {
	// 		dsu.m(v, u);
	// 		update(u, sv);
	// 		update(par[dsu.f(u)], -sv);
	// 	} else {
	// 		int s = query(dfn[dsu.f(u)]);
	// 		printf("%d\n", (s - sv) * sv);
	// 	}
	// }
	for (int i = 1; i <= q; ++i) {
		int u = x[i], v = y[i];
		printf("%d:\n", i);
		if (par[u] == v) std::swap(u, v);
		int sv = $::query(dfn[v]);
		if (op[i]) {
			dsu.p[v] = dsu.f(u);
			update(u, sv);
			update(par[dsu.p[u]], -sv);
		} else {
			int s = $::query(dfn[dsu.f(u)]);
			printf("%d\n", (s - sv) * sv);
		}
	}
}