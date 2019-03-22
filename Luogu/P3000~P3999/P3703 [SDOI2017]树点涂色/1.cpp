#include <algorithm>
#include <cstdio>

const int N = 1e5 + 51;
struct edge {
	int to, next;
} e[N << 1];
int head[N], cnt;
void addedge(int x, int y) {
	e[++cnt] = (edge){y, head[x]}, head[x] = cnt;
	e[++cnt] = (edge){x, head[y]}, head[y] = cnt;
}

int par[N], dep[N], dfn[N], lnk[N], sz[N], son[N], top[N], idx;
void dfs1(int x, int p, int d) {
	dep[x] = d, par[x] = p, sz[x] = 1;
	int mx = 0;
	for (int i = head[x]; i; i = e[i].next) {
		int nx = e[i].to;
		if (nx == p) continue;
		dfs1(nx, x, d + 1);
		sz[x] += sz[nx];
		if (sz[nx] > mx) {
			mx = sz[nx];
			son[x] = nx;
		}
	}
}
void dfs2(int x, int t) {
	dfn[x] = ++idx, lnk[idx] = x, top[x] = t;
	if (!son[x]) return;
	dfs2(son[x], t);
	for (int i = head[x]; i; i = e[i].next) {
		int nx = e[i].to;
		if (nx == par[x] || nx == son[x]) continue;
		dfs2(nx, nx);
	}
}
inline int lca(int x, int y) {
	for (; top[x] != top[y]; x = par[top[x]])
		if (dep[top[x]] < dep[top[y]]) std::swap(x, y);
	return dep[x] < dep[y] ? x : y;
}

struct node* newNode();
struct node {
	int l, r, mid, max, tag;
	node *lc, *rc;
	inline void pushup() { max = std::max(lc->max, rc->max); }
	inline void pushdown() {
		lc->max += tag, lc->tag += tag;
		rc->max += tag, rc->tag += tag;
		tag = 0;
	}
	void build(int L, int R) {
		l = L, r = R, mid = (l + r) >> 1, tag = 0;
		if (l == r) return void(max = dep[lnk[l]]);
		(lc = newNode())->build(l, mid);
		(rc = newNode())->build(mid + 1, r);
		pushup();
	}
	int query(int L, int R) {
		if (L <= l && r <= R) return max;
		pushdown();
		int mx = 0;
		if (L <= mid) mx = std::max(mx, lc->query(L, R));
		if (mid < R) mx = std::max(mx, rc->query(L, R));
		return mx;
	}
	void update(int L, int R, int x) {
		if (L <= l && r <= R) return (void)(tag += x, max += x);
		pushdown();
		if (L <= mid) lc->update(L, R, x);
		if (mid < R) rc->update(L, R, x);
		pushup();
	}
	void prt() {
		printf("(%d %d %d %d)", l, r, max, tag);
		if (l == r) return;
		lc->prt();
		rc->prt();
	}
} pool[N << 2], *null = pool, *root;
node* newNode() {
	static node* ptr = pool + 1;
	ptr->lc = ptr->rc = null;
	return ptr++;
}

// clang-format off
#define L(x) ch[x][0]
#define R(x) ch[x][1]
struct LCT {
	int ch[N][2], p[N];
	inline bool c(int x) { return R(p[x]) == x; }
	inline bool nr(int x) { return L(p[x]) == x || R(p[x]) == x; }
	inline void rt(int x) {
		int y = p[x], z = p[y], k = c(x), w = ch[x][!k];
		ch[y][k] = w; p[w] = y;
		if (nr(y)) ch[z][c(y)] = x; p[x] = z;
		ch[x][!k] = y; p[y] = x;
	}
	inline void sp(int x) { for (int y; y = p[x], nr(x); rt(x)) if (nr(y)) rt(c(x) == c(y) ? y : x); }
	inline int fr(int x) { while (L(x)) x = L(x); return x; }
	inline void ac(int x) {
		for (int i = 0, j; x; x = p[i = x]) {
			sp(x);
			if (R(x)) j = fr(R(x)), root->update(dfn[j], dfn[j] + sz[j] - 1, 1);
			if (R(x) = i) j = fr(R(x)), root->update(dfn[j], dfn[j] + sz[j] - 1, -1);
		}
	}
} lct;
// clang-format on

int n, m, op, x, y, z;

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i < n; i++) {
		scanf("%d%d", &x, &y);
		addedge(x, y);
	}
	dfs1(1, 0, 1);
	dfs2(1, 1);
	for (int i = 1; i <= n; i++) {
		lct.p[i] = par[i];
	}
	(root = newNode())->build(1, n);
	while (m--) {
		scanf("%d%d", &op, &x);
		if (op == 1)
			lct.ac(x);
		else if (op == 2) {
			scanf("%d", &y);
			z = lca(x, y);
			printf("%d\n", root->query(dfn[x], dfn[x]) +
							   root->query(dfn[y], dfn[y]) -
							   2 * root->query(dfn[z], dfn[z]) + 1);
		} else
			printf("%d\n", root->query(dfn[x], dfn[x] + sz[x] - 1));
	}
}