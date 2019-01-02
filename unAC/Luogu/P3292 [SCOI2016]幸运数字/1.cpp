#include <algorithm>
#include <cstring>
#include <cstdio>

const int N = 2e4+42, M = 64;
typedef long long ll;

inline void insert(ll *lb, ll x) {
	for (int i = 60; i >= 0; i--) {
		if (1 & ~(x >> (ll)i)) continue;
		if (!lb[i]) { lb[i] = x; return; }
		x ^= lb[i];
	}
}
inline void merge(ll *x, ll *y) {
	for (int i = 0; i <= 60; i++) if (y[i]) insert(x, y[i]);
}

struct node *newNode();
struct node {
	int l, r, mid;
	node *lc, *rc;
	ll lb[M]; // linear basis
	inline void pushup() {
		memcpy(lb, lc->lb, sizeof lb);
		merge(lb, rc->lb);
	}
	void build(int L, int R, ll *a) {
		l = L; r = R; mid = (l+r) >> 1;
		if (l == r) return insert(lb, a[l]);
		(lc = newNode())->build(l, mid, a);
		(rc = newNode())->build(mid+1, r, a);
		pushup();
	}
	inline void query(int L, int R, ll *ret) {
		if (L <= l && r <= R) merge(ret, lb);
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

int par[N], dfn[N], dep[N], son[N], sz[N], top[N], w[N], w_[N], idx;
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
ll pathLB(int x, int y) {
	ll lb[M] = {};
	while (top[x] != top[y]) {
		if (dep[top[x]] < dep[top[y]]) std::swap(x, y);
		root->query();
		x = par[top[x]];
	}
	if (dep[x] > dep[y]) std::swap(x, y);
	return (ret + BIT::query(dfn[x], dfn[y])) % P;
}

int n, m;	
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", w_[i]);
	}
	dfs1(1, -1, 1);
	dfs2(1, 1);

}