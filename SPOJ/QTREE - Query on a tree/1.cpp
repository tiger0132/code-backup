#include <algorithm>
#include <cstdio>
#include <cstring>
#define memset0(x) memset(x, 0, sizeof x)

const int INF = 0x3f3f3f3f, N = 1e5 + 15;

struct node;
struct node *newNode();
struct node {
	int l, r, mid, max;
	node *lc, *rc;
	void pushup() { max = std::max(lc->max, rc->max); }
	void build(int L, int R, int *arr) {
		l = L, r = R, mid = (l + r) >> 1, max = 0;
		if (l == r) return void(max = arr[l]);
		(lc = newNode())->build(L, mid, arr);
		(rc = newNode())->build(mid + 1, R, arr);
		pushup();
	}
	void update(int x, int y) {
		if (l == r) return void(max = y);
		if (x <= mid) lc->update(x, y);
		if (mid < x) rc->update(x, y);
		pushup();
	}
	int query(int L, int R) {
		if (L <= l && r <= R) return max;
		int ret = 0;
		if (L <= mid) ret = std::max(ret, lc->query(L, R));
		if (mid < R) ret = std::max(ret, rc->query(L, R));
		return ret;
	}
} pool[N << 2], *null = pool, *root, *ptr = pool + 1;
node *newNode() {
	ptr->lc = ptr->rc = null;
	return ptr++;
}

struct edge {
	int to, next, w;
} e[N << 1];
int head[N], cnt;
void addedge(int x, int y, int z) {
	e[++cnt] = (edge){y, head[x], z}, head[x] = cnt;
	e[++cnt] = (edge){x, head[y], z}, head[y] = cnt;
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
int query(int x, int y) {
	int ans = 0;
	for (; top[x] ^ top[y]; x = par[top[x]]) {
		if (dep[top[x]] < dep[top[y]]) std::swap(x, y);
		ans = std::max(ans, root->query(dfn[top[x]], dfn[x]));
	}
	if (dep[x] < dep[y]) std::swap(x, y);
	return x == y ? ans : std::max(ans, root->query(dfn[y] + 1, dfn[x]));
}

int _, n, x, y, z;
char op[' '];

void init() {
	memset(head, 0, sizeof head);
	memset(pool, 0, sizeof pool);
	memset(e, 0, sizeof e);
	memset0(dep), memset0(dfn), memset0(par), memset0(sz), memset0(son), memset0(top), memset0(w), memset0(w_);
	idx = cnt = n = x = y = z = 0;
	ptr = pool + 1;
	null->max = 0;
}

int main() {
	for (scanf("%d", &_); _--;) {
		init();
		scanf("%d", &n);
		for (int i = 1; i < n; i++) scanf("%d%d%d", &x, &y, &z), addedge(x, y, z);
		dfs1(1, -1, 1), dfs2(1, 1);
		(root = newNode())->build(1, n, w);
		while (scanf("%s", op) && (*op ^ 'D')) {
			scanf("%d%d", &x, &y);
			if (*op ^ 'Q') {
				int p = e[x << 1].to, q = e[(x << 1) - 1].to;
				if (dep[p] < dep[q]) std::swap(p, q);
				root->update(dfn[p], y);
			} else
				printf("%d\n", x == y ? 0 : query(x, y));
		}
	}
}