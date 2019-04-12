#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <map>

const int N = 1e5 + 51, M = 2e5 + 52;
struct edge {
	int to, next;
} e[M << 1];
int head[N], cnt;
void addedge(int x, int y) {
	e[++cnt] = (edge){y, head[x]}, head[x] = cnt;
	e[++cnt] = (edge){x, head[y]}, head[y] = cnt;
}

#define mid (l + r) / 2
extern struct node _[];
int $() {
	static int ptr = 1;
	return ptr++;
}
struct node {
	int tag, sum, lc, rc;
	void up() { sum = _[lc].sum + _[rc].sum; }
	void pd() { tag && (_[lc].sum = _[rc].sum = tag = 0, _[lc].tag = _[rc].tag = 1); }
	void build(int l, int r) {
		if (l == r) return void(sum = 1);
		_[lc = $()].build(l, mid), _[rc = $()].build(mid + 1, r), up();
	}
	void set(int L, int R, int l, int r) {
		assert(L <= R && L && R);
		if (L <= l && r <= R) return (void)(tag = 1, sum = 0);
		if (pd(), L <= mid) _[lc].set(L, R, l, mid);
		if (mid < R) _[rc].set(L, R, mid + 1, r);
		up();
	}
	int qry(int L, int R, int l, int r) {
		if (L <= l && r <= R) return sum;
		int ret = 0;
		if (pd(), L <= mid) ret += _[lc].qry(L, R, l, mid);
		if (mid < R) ret += _[rc].qry(L, R, mid + 1, r);
		return ret;
	}
} _[N << 2];

std::map<int, int> mp;
int n, m, q, rt;
bool flg[N];
int id(int i, int j) {
	if (i > j) std::swap(i, j);
	return i * n + j;
}

int dep[N], par[N], sz[N], son[N], dfn[N], top[N], idx;
void dfs1(int x, int p, int d) {
	par[x] = p, dep[x] = d, sz[x] = 1;
	int mx = 0;
	for (int i = head[x]; i; i = e[i].next) {
		int nx = e[i].to;
		if (sz[nx]) continue;
		flg[mp[id(x, nx)]] = false;
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
		if (nx != son[x] && par[nx] == x) dfs2(nx, nx);
	}
}
void upd(int x, int y) {
	for (; top[x] != top[y]; x = par[top[x]]) {
		if (dep[top[x]] < dep[top[y]]) std::swap(x, y);
		_[rt].set(dfn[top[x]], dfn[x], 1, n);
	}
	if (dep[x] > dep[y]) std::swap(x, y);
	if (x != y) _[rt].set(dfn[x] + 1, dfn[y], 1, n);
}
int qry(int x, int y) {
	int r = 0;
	for (; top[x] != top[y]; x = par[top[x]]) {
		if (dep[top[x]] < dep[top[y]]) std::swap(x, y);
		r += _[rt].qry(dfn[top[x]], dfn[x], 1, n);
	}
	if (dep[x] > dep[y]) std::swap(x, y);
	if (x != y) r += _[rt].qry(dfn[x] + 1, dfn[y], 1, n);
	return r;
}

int x[M], y[M], op[M], u[M], v[M], ans[M];
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) {
		scanf("%d%d", x + i, y + i);
		mp[id(x[i], y[i])] = i, flg[i] = true;
	}
	while (scanf("%d", op + ++q), ~op[q]) {
		scanf("%d%d", u + q, v + q);
		if (!op[q]) flg[mp[id(u[q], v[q])]] = false;
	}
	q--;
	for (int i = 1; i <= m; i++)
		if (flg[i]) addedge(x[i], y[i]);
	for (int i = 1; i <= n; i++)
		if (!sz[i]) dfs1(i, -1, 1), dfs2(i, i);
	_[rt = $()].build(1, n);
	for (int i = 1; i <= m; i++)
		if (flg[i]) upd(x[i], y[i]);
	for (int i = q; i >= 1; i--) {
		if (!op[i])
			upd(u[i], v[i]);
		else
			ans[i] = qry(u[i], v[i]);
	}
	for (int i = 1; i <= q; i++)
		if (op[i]) printf("%d\n", ans[i]);
}