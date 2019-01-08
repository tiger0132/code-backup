// 40pts, TLE, O(n log^4 n) / O(n log^3 n).

#include <algorithm>
#include <cstring>
#include <cstdio>

typedef long long ll;
const int N = 2e4+42, M = 60;

struct $ {
	ll lb[M+1];
	inline $(const $& rhs) { memcpy(lb, rhs.lb, sizeof lb); }
	inline $() { memset(lb, 0, sizeof lb); }
	inline void insert(ll x) {
		for (ll i = M; i >= 0; i--) if ((x >> i) & 1) {
			if (!lb[i]) return (void)(lb[i] = x);
			x ^= lb[i];
		}
	}
	inline void merge(const $& rhs) {
		for (int i = 0; i <= M; i++) insert(rhs.lb[i]);
	}
	inline ll ans() {
		ll ret = 0;
		for (int i = M; i >= 0; i--) ret = std::max(ret, ret ^ lb[i]);
		return ret;
	}
};

struct node *newNode();
struct node {
	int l, r, mid; $ _;
	node *lc, *rc;
	inline void pushup() { _ = lc->_; _.merge(rc->_); }
	void build(int L, int R, ll *a) {
		l = L; r = R; mid = (l+r) >> 1;
		if (l == r) return _.insert(a[l]);
		(lc = newNode())->build(l, mid, a);
		(rc = newNode())->build(mid+1, r, a);
		pushup();
	}
	inline void query(int L, int R, $& ret) {
		if (L <= l && r <= R) {
			return ret.merge(_);
		}
		if (L <= mid) lc->query(L, R, ret);
		if (mid < R) rc->query(L, R, ret);
	}
} pool[N<<2], *root, *null = pool;
node *newNode() {
	static node *ptr = pool+1;
	ptr->lc = ptr->rc = null;
	return ptr++;
}

struct edge { int to, next; } e[N<<1];
int head[N], cnt;
void addedge(int x, int y) {
	e[++cnt] = (edge){y, head[x]}; head[x] = cnt;
	e[++cnt] = (edge){x, head[y]}; head[y] = cnt;
}

int par[N], dfn[N], dep[N], son[N], sz[N], top[N], idx;
ll w[N], w_[N];
void dfs1(int x, int p, int d) {
	sz[x] = 1; par[x] = p; dep[x] = d;
	int mx = -1;
	for (int i = head[x]; i; i = e[i].next) {
		int nx = e[i].to;
		if (nx == p) continue;
		dfs1(nx, x, d+1);
		sz[x] += sz[nx];
		if (sz[nx] > mx) {
			mx = sz[nx];
			son[x] = nx;
		}
	}
}
void dfs2(int x, int t) {
	dfn[x] = ++idx; top[x] = t; w[idx] = w_[x];
	if (!son[x]) return;
	dfs2(son[x], t);
	for (int i = head[x]; i; i = e[i].next) {
		int nx = e[i].to;
		if (nx == par[x] || nx == son[x]) continue;
		dfs2(nx, nx);
	}
}
inline ll pathSum(int x, int y) {
	$ t;
	while (top[x] != top[y]) {
		if (dep[top[x]] < dep[top[y]]) std::swap(x, y);
		root->query(dfn[top[x]], dfn[x], t);
		x = par[top[x]];
	}
	if (dep[x] > dep[y]) std::swap(x, y);
	root->query(dfn[x], dfn[y], t);
	return t.ans();
}

int n, m, x, y;

int main() {
	freopen("in.in", "r", stdin);
	freopen("out.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%lld", w_+i);
	for (int i = 1; i < n; i++) {
		scanf("%d%d", &x, &y);
		addedge(x, y);
	}
	dfs1(1, -1, 1);
	dfs2(1, 1);
	(root = newNode())->build(1, n, w);
	while (m--) {
		scanf("%d%d", &x, &y);
		printf("%lld\n", pathSum(x, y));
	}
}