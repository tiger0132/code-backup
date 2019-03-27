#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 1e5 + 51, INF = 0x3f3f3f3f;
struct edge {
	int to, next;
} e[N << 1];
int head[N], cnt;
void addedge(int x, int y) {
	e[++cnt] = (edge){y, head[x]}, head[x] = cnt;
	e[++cnt] = (edge){x, head[y]}, head[y] = cnt;
}

extern struct node _[];
int newNode(int, int, int), n;
struct node {
	int lc, rc, v;
	void build(int l = 1, int r = n) {
		if (l == r) return;
		int mid = (l + r) / 2;
		_[lc = newNode(l, mid, 0)].build(l, mid);
		_[rc = newNode(mid + 1, r, 0)].build(mid + 1, r);
	}
	int insert(int x, int l = 1, int r = n) {
		int mid = l + (r - l) / 2;
		if (l == r) return newNode(0, 0, v + 1);
		if (x <= mid) return newNode(_[lc].insert(x, l, mid), rc, v + 1);
		return newNode(lc, _[rc].insert(x, mid + 1, r), v + 1);
	}
	void prt(int l = 1, int r = n) {
		if (!v) return;
		printf("[%d, %d]: %d\n", l, r, v);
		if (l == r) return;
		int mid = (l + r) / 2;
		if (lc) _[lc].prt(l, mid);
		if (rc) _[rc].prt(mid + 1, r);
	}
} _[N * 320];
int R[N];
int newNode(int lc, int rc, int v) {
	static int ptr = 1;
	_[ptr] = (node){lc, rc, v};
	return ptr++;
}

// clang-format off
#define L(x) ch[x][0]
#define R(x) ch[x][1]
int ch[N][2], p[N], r[N], st[N], top;
inline bool c(int x) { return R(p[x]) == x; }
inline bool nr(int x) { return L(p[x]) == x || R(p[x]) == x; }
inline void pd(int x) { if (r[x]) std::swap(L(x), R(x)), r[L(x)] ^= 1, r[R(x)] ^= 1; r[x] = 0; }
inline void rt(int x) {
	int y = p[x], z = p[y], k = c(x), w = ch[x][!k];
	ch[y][k] = w, p[w] = y;
	if (nr(y)) ch[z][c(y)] = x; p[x] = z;
	ch[x][!k] = y, p[y] = x;
}
inline void sp(int x) {
	for (int i = st[top = 1] = x; nr(i); i = p[i]) st[++top] = p[i];
	while (top) pd(st[top--]);
	for (int y; y = p[x], nr(x); rt(x)) if (nr(y)) rt(c(x) == c(y) ? y : x);
}
inline int ac(int x) { int i; for (i = 0; x; x = p[i = x]) sp(x), R(x) = i; return i; }
inline void mr(int x) { ac(x), sp(x), r[x] ^= 1; }
inline void lk(int x, int y) { mr(x); p[x] = y; }
inline int lca(int x, int y) { ac(x); return ac(y); }
// clang-format on

struct dsuQwQ {
	int p[N];
	int f(int x) { return p[x] ? p[x] = f(p[x]) : x; }
} d;
int a[N];
void dfs(int x, int p) {
	R[x] = _[R[p]].insert(a[x]);
	// printf("[%d] = [%d] + (%d):\n", x, p, a[x]);
	// _[R[x]].prt();
	// puts("");
	for (int i = head[x], nx; i; i = e[i].next)
		if ((nx = e[i].to) != p) dfs(nx, x);
}

int sz[N];
void merge(int x, int y) {
	int u = d.f(x), v = d.f(y);
	if (sz[u] < sz[v]) std::swap(x, y), std::swap(u, v);
	// printf("merge %d into %d:\n", y, x);
	sz[u] += sz[v], addedge(x, y), lk(x, y), d.p[v] = u, dfs(y, x);
	// puts("\n");
}

int query(int a, int b, int c, int d, int x, int l = 1, int r = n) {
	if (l == r) return l;
	int mid = (l + r) / 2, sum = _[_[a].lc].v + _[_[b].lc].v - _[_[c].lc].v - _[_[d].lc].v;
	if (x <= sum) return query(_[a].lc, _[b].lc, _[c].lc, _[d].lc, x, l, mid);
	return query(_[a].rc, _[b].rc, _[c].rc, _[d].rc, x - sum, mid + 1, r);
}

int t, nn, m, x, y, z, q, lans, b[N];
char op[2];
int main() {
	scanf("%*d%d%d%d", &n, &m, &q);
	for (int i = 1; i <= n; i++) scanf("%d", a + i), b[i] = a[i], sz[i] = 1;
	std::sort(b + 1, b + n + 1);
	nn = std::unique(b + 1, b + n + 1) - b - 1;
	_[R[0]].build(1, n);
	for (int i = 1; i <= n; i++) R[i] = _[R[0]].insert(a[i] = std::lower_bound(b + 1, b + nn + 1, a[i]) - b);
	for (int i = 1; i <= m; i++) {
		scanf("%d%d", &x, &y);
		merge(x, y);
	}
	// for (int i = 1; i <= n; i++) {
	// 	printf("root %d:\n", i);
	// 	_[R[i]].prt();
	// 	puts("");
	// }
	while (q--) {
		scanf("%s%d%d", op, &x, &y), x ^= lans, y ^= lans;
		if (*op == 'Q') {
			scanf("%d", &z), z ^= lans;
			mr(d.f(x));
			int l = lca(x, y), l2;
			if (d.f(x) == l)
				l2 = 0;
			else {
				ac(l), sp(l), l2 = L(l);
				while (R(l2)) l2 = R(l2), pd(l2);
			}
			// printf("%d -> %d || lca(%d, %d) = %d [%d]\n", x, d.f(x), x, y, l, l2);
			printf("%d\n", lans = b[query(R[x], R[y], R[l], R[l2], z)]);
		} else
			merge(x, y);
	}
}