// SPC: Shark Punch Center
// SCP: Scan, Copy, Print.

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#define int long long

const int N = 5e5 + 55, M = 6e5 + 56, INF = 0x3f3f3f3f3f3f3f3f;
struct edge {
	int to, next, w;
} e[M << 1], e2[M];
int head[N], cnt;
void addedge(int x, int y, int z) {
	e[++cnt] = (edge){y, head[x], z}, head[x] = cnt;
	e[++cnt] = (edge){x, head[y], z}, head[y] = cnt;
}
void _4to2(int a, int b, int c, int d, int &max, int &max2) {
	int _[4] = {a, b, c, d};
	std::sort(_, _ + 4, [](int x, int y) { return x > y; }), max = _[0];
	for (int i = 1; i < 4; i++)
		if (_[i] != _[0]) return void(max2 = _[i]);
}

struct node;
struct node *newNode();
struct node {
	int l, r, mid, max, max2;
	node *lc, *rc;
	void pushup() { _4to2(lc->max, lc->max2, rc->max, rc->max2, max, max2); }
	void build(int L, int R, int *arr) {
		l = L, r = R, mid = (l + r) >> 1, max = max2 = 0;
		if (l == r) return (void)(max = arr[l]);
		(lc = newNode())->build(L, mid, arr);
		(rc = newNode())->build(mid + 1, R, arr);
		pushup();
		// printf("[%lld, %lld]: %lld, %lld\n", l, r, max, max2);
	}
	void update(int x, int y) {
		if (l == r) return void(max = max2 = y);
		if (x <= mid) lc->update(x, y);
		if (mid < x) rc->update(x, y);
		pushup();
	}
	void query(int L, int R, int &x, int &y) {
		if (L <= l && r <= R) return _4to2(max, max2, x, y, x, y);
		if (L <= mid) lc->query(L, R, x, y);
		if (mid < R) rc->query(L, R, x, y);
	}
} pool[N << 2], *null = pool, *root, *ptr = pool + 1;
node *newNode() {
	ptr->lc = ptr->rc = null;
	return ptr++;
}

int dep[N], dfn[N], par[N], sz[N], son[N], top[N], w[N], w_[N], idx;
void dfs1(int x, int p, int d) {
	dep[x] = d, par[x] = p, sz[x] = 1;
	for (int i = head[x], nx, mx = 0; i; i = e[i].next) {
		if ((nx = e[i].to) == p) continue;
		w_[nx] = e[i].w, dfs1(nx, x, d + 1), sz[x] += sz[nx];
		if (sz[nx] > mx) mx = sz[nx], son[x] = nx;
	}
}
void dfs2(int x, int t) {
	w[dfn[x] = ++idx] = w_[x], top[x] = t;
	if (!son[x]) return;
	dfs2(son[x], t);
	for (int i = head[x], nx; i; i = e[i].next) {
		nx = e[i].to;
		if (nx != par[x] && nx != son[x]) dfs2(nx, nx);
	}
}
void query(int x, int y, int &max, int &max2) {
	max = max2 = 0;
	int t1 = 0, t2 = 0;
	for (; top[x] ^ top[y]; x = par[top[x]]) {
		if (dep[top[x]] < dep[top[y]]) std::swap(x, y);
		root->query(dfn[top[x]], dfn[x], t1, t2);
		_4to2(max, max2, t1, t2, max, max2);
	}
	if (dep[x] < dep[y]) std::swap(x, y);
	root->query(dfn[y] + 1, dfn[x], t1, t2);
	_4to2(t1, t2, max, max2, max, max2);
}

int p[N];
int f(int x) { return p[x] ? p[x] = f(p[x]) : x; }

int n, m, mst, ans = INF;
bool fl[N];
signed main() {
	scanf("%lld%lld", &n, &m);
	for (int i = 1; i <= m; i++) scanf("%lld%lld%lld", &e2[i].to, &e2[i].next, &e2[i].w);
	std::sort(e2 + 1, e2 + m + 1, [](const edge &x, const edge &y) { return x.w < y.w; });
	for (int i = 1; i <= m; i++) {
		int x = e2[i].to, y = e2[i].next, z = e2[i].w;
		if (f(x) != f(y)) fl[i] = 1, p[f(x)] = y, mst += z, addedge(x, y, z);
	}
	dfs1(1, 0, 1), dfs2(1, 1), w[1] = 0;
	(root = newNode())->build(1, n, w);
	for (int i = 1; i <= m; i++) {
		if (fl[i]) continue;
		int x = e2[i].to, y = e2[i].next, z = e2[i].w;
		int t1, t2;
		query(x, y, t1, t2);
		if (t1 < z) ans = std::min(ans, mst - t1 + z);
		if (t2 < z) ans = std::min(ans, mst - t2 + z);
	}
	printf("%lld", ans);
}