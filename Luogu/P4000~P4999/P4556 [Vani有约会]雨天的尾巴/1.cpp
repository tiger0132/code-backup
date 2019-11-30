#include <algorithm>
#include <cstdio>
#include <cstring>
#include <utility>

typedef std::pair<int, int> pii;
const int N = 1e5 + 51;
struct edge {
	int to, next;
} e[N << 1];
int head[N], cnt;
void addedge(int x, int y) {
	e[++cnt] = (edge){y, x[head]}, x[head] = cnt;
	e[++cnt] = (edge){x, y[head]}, y[head] = cnt;
}

int par[N];
struct {
	int top[N], dep[N], sz[N], son[N];
	void dfs1(int x, int p, int d) {
		x[par] = p, x[dep] = d, x[sz] = 1;
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
			if ((nx = e[i].to) != x[son] && nx != x[par]) dfs2(nx, nx);
	}
	void init(int rt = 1) { dfs1(rt, 0, rt), dfs2(rt, rt); }
	int operator()(int x, int y) {
		for (; x[top] != y[top]; x = x[top][par])
			if (x[top][dep] < y[top][dep]) std::swap(x, y);
		return x[dep] < y[dep] ? x : y;
	}
} LCA;

#define L ch][0
#define R ch][1
#define mid (l + r) / 2
#define _(x) (x ? x : x = ++nc)
#define mx first
#define mi second
const int M = 6e6 + 66;
int ch[M][2], nc;
pii t[M];
void up(int x) { x[t] = std::max(x[L][t], x[R][t]); }
void upd(int x, int l, int r, int i, int v) {
	if (l == r) return x[t].mx += v, x[t].mi = -l, void();
	(i <= mid ? upd(_(x[L]), l, mid, i, v) : upd(_(x[R]), mid + 1, r, i, v)), up(x);
}
int u(int x, int y, int l, int r) {
	if (!x || !y) return x | y;
	if (l == r) return x[t].mx += y[t].mx, x;
	x[L] = u(x[L], y[L], l, mid);
	x[R] = u(x[R], y[R], mid + 1, r);
	return up(x), x;
}

int ans[N], rt[N];
void dfs(int x, int p) {
	for (int i = x[head], nx; i; i = e[i].next)
		if ((nx = e[i].to) != p) dfs(nx, x), x[rt] = u(x[rt], nx[rt], 1, N);
	x[ans] = -x[rt][t].mi;
}

int n, m, x, y, z, l;
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i < n; i++) scanf("%d%d", &x, &y), addedge(x, y);
	LCA.init();
	for (int i = 1; i <= n; i++) i[rt] = ++nc;
	for (int i = 1; i <= m; i++) {
		scanf("%d%d%d", &x, &y, &z), l = LCA(x, y);
		upd(x, 1, N, z, 1), upd(y, 1, N, z, 1);
		upd(l[rt], 1, N, z, -1);
		if (l[par]) upd(l[par][rt], 1, N, z, -1);
	}
	dfs(1, 0);
	for (int i = 1; i <= n; i++) printf("%d\n", i[ans]);
}