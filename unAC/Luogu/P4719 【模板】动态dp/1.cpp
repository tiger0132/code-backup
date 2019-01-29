#include <algorithm>
#include <cstdio>
#include <cstring>

typedef long long ll;
const int N = 1e5 + 51, M = 52;

struct edge {
	int to, next;
} e[N << 1];
int head[N], cnt;
void addedge(int x, int y) {
	e[++cnt] = (edge){y, head[x]};
	head[x] = cnt;
	e[++cnt] = (edge){x, head[y]};
	head[y] = cnt;
}

struct state {
	int f0, f1;
	inline void operator+=(const state& rhs) {
		f1 += rhs.f0;
		f0 += std::max(rhs.f0, rhs.f1);
	}
	inline state operator+(const state& rhs) const {
		return (state){f0 + std::max(rhs.f0, rhs.f1), f1 + rhs.f0};
	}
};

int dfn[N], dep[N], par[N], sz[N], son[N], top[N], lnk[N], w[N], w_[N], idx;
state dp[N];
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
	dfn[x] = ++idx, top[x] = t, lnk[idx] = x, w[idx] = w_[x];
	dp[x].f1 = std::max(0, w_[x]);
	if (!son[x]) {
		printf("%d: (%d, %d)\n", x, dp[x].f0, dp[x].f1);
		return;
	}
	dfs2(son[x], t);
	dp[x] += dp[son[x]];
	for (int i = head[x]; i; i = e[i].next) {
		int nx = e[i].to;
		if (nx == par[x] || nx == son[x]) continue;
		dfs2(nx, nx);
		dp[x] += dp[nx];
	}
	printf("%d: (%d, %d)\n", x, dp[x].f0, dp[x].f1);
}
int lca(int x, int y) {
	for (; top[x] != top[y]; x = par[top[x]]) {
		if (dep[top[x]] < dep[top[y]]) std::swap(x, y);
	}
	return dep[x] < dep[y] ? x : y;
}

struct node* newNode();
struct node {
	int l, r, mid;
	node *lc, *rc;
	state m;
	inline void pushup() { m = lc->m + rc->m; }
	void build(int L, int R) {
		l = L, r = R, mid = (l + r) >> 1, m = dp[lnk[l]];
		if (l == r) return;
		(lc = newNode())->build(l, mid);
		(rc = newNode())->build(mid + 1, r);
	}
	void update(int L, int R, int x) {
		m.f1 += x - w[l];
		w[l] = x;
		if (L <= l && r <= R) {
			return;
		}
		if (L <= mid) lc->update(L, R, x);
		if (mid < R) rc->update(L, R, x);
	}
} pool[N << 2], *null = pool, *root;
node* newNode() {
	static node* ptr = pool + 1;
	ptr->lc = ptr->rc = null;
	return ptr++;
}

int n, m, x, y;
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", w_ + i);
	}
	for (int i = 1; i < n; i++) {
		scanf("%d%d", &x, &y);
		addedge(x, y);
	}
	dfs1(1, 0, 1);
	dfs2(1, 1);
	(root = newNode())->build(1, n);
	printf("%d %d", root->m.f0, root->m.f1);
}