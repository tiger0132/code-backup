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

extern struct node *newNode(int, int), *null;
struct node {
	int l, r, mid, max, sum;
	node *lc, *rc;
	inline void pushup() { max = std::max(lc->max, rc->max), sum = lc->sum + rc->sum; }
	void update(int x, int y) {
		if (this == null) exit(1);
		if (l == r) return (void)(max = sum = y);
		if (x <= mid) {
			if (lc == null) lc = newNode(l, mid);
			lc->update(x, y);
		} else {
			if (rc == null) rc = newNode(mid + 1, r);
			rc->update(x, y);
		}
		pushup();
	}
	int query1(int L, int R) {
		if (this == null) exit(1);
		if (L > r || R < l) return 0;
		if (L <= l && r <= R) return sum;
		return (lc == null ? 0 : lc->query1(L, R)) + (rc == null ? 0 : rc->query1(L, R));
	}
	int query2(int L, int R) {
		if (this == null) exit(1);
		if (L > r || R < l) return 0;
		if (L <= l && r <= R) return max;
		return std::max((lc == null ? 0 : lc->query2(L, R)), (rc == null ? 0 : rc->query2(L, R)));
	}
} _[N * 90], *null = _, *rt[N];
node *newNode(int l, int r) {
	static node *ptr = _ + 1;
	*ptr = (node){l, r, (l + r) >> 1, 0, 0, null, null};
	return ptr++;
}

int sz[N], par[N], dep[N], dfn[N], son[N], top[N], a[N], b[N], idx;
void dfs1(int x, int p, int d) {
	par[x] = p, dep[x] = d, sz[x] = 1;
	for (int i = head[x], mx = 0; i; i = e[i].next) {
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
	dfn[x] = ++idx, top[x] = t;
	if (!son[x]) return;
	dfs2(son[x], t);
	for (int i = head[x]; i; i = e[i].next) {
		int nx = e[i].to;
		if (nx == par[x] || nx == son[x]) continue;
		dfs2(nx, nx);
	}
}

int n;
int query1(int id, int x, int y) {
	int ret = 0;
	for (; top[x] != top[y]; x = par[top[x]]) {
		if (dep[top[x]] < dep[top[y]]) std::swap(x, y);
		ret += rt[id]->query1(dfn[top[x]], dfn[x]);
	}
	if (dep[x] > dep[y]) std::swap(x, y);
	return ret + rt[id]->query1(dfn[x], dfn[y]);
}
int query2(int id, int x, int y) {
	int ret = 0;
	for (; top[x] != top[y]; x = par[top[x]]) {
		if (dep[top[x]] < dep[top[y]]) std::swap(x, y);
		ret = std::max(ret, rt[id]->query2(dfn[top[x]], dfn[x]));
	}
	if (dep[x] > dep[y]) std::swap(x, y);
	return std::max(ret, rt[id]->query2(dfn[x], dfn[y]));
}

int q, x, y;
char buf[10];
int main() {
	scanf("%d%d", &n, &q);
	for (int i = 0; i < N; i++) rt[i] = newNode(1, n);
	for (int i = 1; i <= n; i++) scanf("%d%d", a + i, b + i);
	for (int i = 1; i < n; i++) scanf("%d%d", &x, &y), addedge(x, y);
	dfs1(1, -1, 1);
	dfs2(1, 1);
	for (int i = 1; i <= n; i++) {
		rt[b[i]]->update(dfn[i], a[i]);
	}
	while (q--) {
		scanf("%s%d%d", buf, &x, &y);
		if (buf[1] == 'C') {
			rt[b[x]]->update(dfn[x], 0);
			rt[b[x] = y]->update(dfn[x], a[x]);
		} else if (buf[1] == 'W') {
			rt[b[x]]->update(dfn[x], 0);
			rt[b[x]]->update(dfn[x], a[x] = y);
		} else if (buf[1] == 'S')
			printf("%d\n", query1(b[x], x, y));
		else
			printf("%d\n", query2(b[x], x, y));
	}
}