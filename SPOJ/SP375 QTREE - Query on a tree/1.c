#define memset0(x) memset(x, 0, sizeof x)
swap(int *x, int *y) {
	int t = *x;
	*x = *y, *y = t;
}
max(a, b) { return a > b ? a : b; }
enum { N = (int)(1e5 + 51) };

const int INF = 0x3f3f3f3f;
int maxv[N << 2];
void pushup(int this) { maxv[this] = max(maxv[this << 1], maxv[this << 1 | 1]); }
void build(int this, int l, int r, int *arr) {
	int mid = (l + r) >> 1;
	if (l == r) return maxv[this] = arr[l];
	build(this << 1, l, mid, arr);
	build(this << 1 | 1, mid + 1, r, arr);
	pushup(this);
}
void update(int this, int x, int y, int l, int r) {
	if (l == r) return maxv[this] = y;
	if (x <= (l + r) / 2) update(this << 1, x, y, l, (l + r) / 2);
	if ((l + r) / 2 < x) update(this << 1 | 1, x, y, (l + r) / 2 + 1, r);
	pushup(this);
}
int query(int this, int L, int R, int l, int r) {
	if (L <= l && r <= R) return maxv[this];
	int ret = 0, mid = (l + r) / 2;
	if (L <= mid) ret = max(ret, query(this << 1, L, R, l, mid));
	if (mid < R) ret = max(ret, query(this << 1 | 1, L, R, mid + 1, r));
	return ret;
}

typedef struct {
	int to, next, w;
} edge;
edge e[N << 1];
int head[N], cnt, n;
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
int queryQwQ(int x, int y) {
	int ans = 0;
	for (; top[x] ^ top[y]; x = par[top[x]]) {
		if (dep[top[x]] < dep[top[y]]) swap(&x, &y);
		ans = max(ans, query(1, dfn[top[x]], dfn[x], 1, n));
	}
	if (dep[x] < dep[y]) swap(&x, &y);
	return x == y ? ans : max(ans, query(1, dfn[y] + 1, dfn[x], 1, n));
}

int _, x, y, z;
char op[' '];

void init() {
	memset(head, 0, sizeof head);
	memset(maxv, 0, sizeof maxv);
	memset0(dep), memset0(dfn), memset0(par), memset0(sz), memset0(son), memset0(top), memset0(w), memset0(w_);
	idx = cnt = n = x = y = z = 0;
}

int main() {
	for (scanf("%d", &_); _--;) {
		init();
		scanf("%d", &n);
		for (int i = 1; i < n; i++) scanf("%d%d%d", &x, &y, &z), addedge(x, y, z);
		dfs1(1, -1, 1), dfs2(1, 1);
		build(1, 1, n, w);
		while (scanf("%s", op) && (*op ^ 'D')) {
			scanf("%d%d", &x, &y);
			if (*op ^ 'Q') {
				int p = e[x << 1].to, q = e[(x << 1) - 1].to;
				if (dep[p] < dep[q]) swap(&p, &q);
				update(1, dfn[p], y, 1, n);
			} else
				printf("%d\n", x == y ? 0 : queryQwQ(x, y));
		}
	}
}