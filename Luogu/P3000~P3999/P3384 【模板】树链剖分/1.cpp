#include <algorithm>
#include <cstdio>

#define int long long

typedef long long ll;
const int N = 1e5+51;

int P;
namespace BIT {
	ll a[N], b[N]; int n;
	int lowbit(int x) { return x&-x; }
	void add(ll *t, int i, int x) { for (; i <= n; i += lowbit(i)) t[i] += x; }
	ll query(ll *t, int i) { ll ret = 0; for (; i; i -= lowbit(i)) (ret += t[i]) %= P; return ret; }
	void add(int l, int r, int x) {
		x %= P;
		add(a, l, x); add(a, r+1, (P-x) % P);
		add(b, l, x * (l-1) % P); add(b, r+1, (P-x) * r % P);
	}
	ll query(int i) { return (i * query(a, i) - query(b, i)) % P; }
	ll query(int l, int r) { return ((query(r) - query(l-1)) % P + P) % P; }
	void init(int n_, int *t) { n = n_;
		for (int i = 1; i <= n; i++) {
			int x = ((t[i] - t[i-1]) % P + P) % P;
			add(a, i, x); add(b, i, x * (i-1) % P);
		}
	}
};

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

void pathAdd(int x, int y, int z) {
	z %= P;
	while (top[x] != top[y]) {
		if (dep[top[x]] < dep[top[y]]) std::swap(x, y);
		BIT::add(dfn[top[x]], dfn[x], z);
		x = par[top[x]];
	}
	if (dep[x] > dep[y]) std::swap(x, y);
	BIT::add(dfn[x], dfn[y], z);
}
ll pathSum(int x, int y) {
	ll ret = 0;
	while (top[x] != top[y]) {
		if (dep[top[x]] < dep[top[y]]) std::swap(x, y);
		(ret += BIT::query(dfn[top[x]], dfn[x])) %= P;
		x = par[top[x]];
	}
	if (dep[x] > dep[y]) std::swap(x, y);
	return (ret + BIT::query(dfn[x], dfn[y])) % P;
}
void treeAdd(int x, int y) { BIT::add(dfn[x], dfn[x]+sz[x]-1, y); }
ll treeSum(int x) { return BIT::query(dfn[x], dfn[x]+sz[x]-1); }

int n, m, r, op, x, y, z;

signed main() {
	scanf("%lld%lld%lld%lld", &n, &m, &r, &P);
	for (int i = 1; i <= n; i++) scanf("%lld", w_+i);
	for (int i = 1; i < n; i++) {
		scanf("%lld%lld", &x, &y);
		addedge(x, y);
	}
	dfs1(r, 0, 1);
	dfs2(r, r);
	BIT::init(n, w);
	while (m--) {
		scanf("%lld%lld", &op, &x);
		if (op ^ 4) scanf("%lld", &y);
		switch (op) {
			case 1: scanf("%lld", &z); pathAdd(x, y, z); break;
			case 2: printf("%lld\n", (pathSum(x, y) % P + P) % P); break;
			case 3: treeAdd(x, y); break;
			case 4: printf("%lld\n", (treeSum(x) % P + P) % P); break;
		}
	}
}