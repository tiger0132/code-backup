#include <algorithm>
#include <cstdio>
#define int long long

const int N = 1e5 + 51, INF = 0x7fffffff;
struct edge {
	int to, next;
} e[N << 1];
int head[N], cnt;
void addedge(int x, int y) {
	e[++cnt] = (edge){y, head[x]}, head[x] = cnt;
	e[++cnt] = (edge){x, head[y]}, head[y] = cnt;
}

extern struct node _[];
int newNode(int, int, int), n;
struct node {
	int lc, rc, v;
	int insert(int x, int l = 1, int r = INF) {
		int mid = l + (r - l) / 2;
		if (l == r) return newNode(0, 0, v + 1);
		if (x <= mid) return newNode(_[lc].insert(x, l, mid), rc, v + 1);
		return newNode(lc, _[rc].insert(x, mid + 1, r), v + 1);
	}
} _[N * 90];
int rt[N];
int newNode(int lc, int rc, int v) {
	static int cnt = 1;
	_[cnt].lc = lc, _[cnt].rc = rc, _[cnt].v = v;
	return cnt++;
}

int sz[N], par[N], dep[N], son[N], top[N], dfn[N], a[N], idx;
void dfs1(int x, int p, int d) {
	par[x] = p, dep[x] = d, sz[x] = 1;
	rt[x] = _[rt[par[x]]].insert(a[x]);
	for (int i = head[x], mx = 0; i; i = e[i].next) {
		int nx = e[i].to;
		if (nx == p) continue;
		dfs1(nx, x, d + 1), sz[x] += sz[nx];
		if (sz[nx] > mx) mx = sz[nx], son[x] = nx;
	}
}
void dfs2(int x, int t) {
	dfn[x] = ++idx, top[x] = t;
	if (!son[x]) return;
	dfs2(son[x], t);
	for (int i = head[x]; i; i = e[i].next) {
		int nx = e[i].to;
		if (nx == par[x] || nx == son[x]) continue;
		dfs2(nx, nx);
	}
}
int lca(int x, int y) {
	for (; top[x] != top[y]; x = par[top[x]])
		if (dep[top[x]] < dep[top[y]]) std::swap(x, y);
	return dep[x] < dep[y] ? x : y;
}
int query(int a, int b, int c, int d, int x, int l = 1, int r = INF) {
	if (l == r) return l;
	int mid = (l + r) >> 1, sum = _[_[a].lc].v + _[_[b].lc].v - _[_[c].lc].v - _[_[d].lc].v;
	if (x <= sum) return query(_[a].lc, _[b].lc, _[c].lc, _[d].lc, x, l, mid);
	return query(_[a].rc, _[b].rc, _[c].rc, _[d].rc, x - sum, mid + 1, r);
}

int m, x, y, z, l, lans;
signed main() {
	scanf("%lld%lld", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%lld", a + i);
	for (int i = 1; i < n; i++) {
		scanf("%lld%lld", &x, &y);
		addedge(x, y);
	}
	dfs1(1, -1, 1);
	dfs2(1, 1);
	while (m--) {
		scanf("%lld%lld%lld", &x, &y, &z);
		l = lca(x ^= lans, y);
		printf("%lld\n", lans = query(rt[x], rt[y], rt[l], rt[par[l]], z));
	}
}