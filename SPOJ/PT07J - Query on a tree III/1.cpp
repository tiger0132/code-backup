#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 1e5 + 51, INF = 0x3f3f3f3f;
extern struct node _[];
int newNode(int lc, int rc, int v), n;
struct node {
	int lc, rc, v;
	int insert(int x, int l = 1, int r = n) {
		int mid = l + (r - l) / 2;
		if (l == r) return newNode(0, 0, v + 1);
		if (x <= mid) return newNode(_[lc].insert(x, l, mid), rc, v + 1);
		return newNode(lc, _[rc].insert(x, mid + 1, r), v + 1);
	}
} _[N * 90];
int rt[N];
int newNode(int lc, int rc, int v) {
	static int ptr = 1;
	_[ptr] = (node){lc, rc, v};
	return ptr++;
}

struct edge {
	int to, next;
} e[N << 1];
int head[N], cnt;
void addedge(int x, int y) {
	e[++cnt] = (edge){y, head[x]}, head[x] = cnt;
	e[++cnt] = (edge){x, head[y]}, head[y] = cnt;
}

int a[N], dfn[N], sz[N], par[N], l2[N], idx;
void dfs(int x, int p) {
	par[x] = p, dfn[x] = ++idx, sz[x] = 1, l2[idx] = x;
	for (int i = head[x], nx; i; i = e[i].next)
		if ((nx = e[i].to) != p) dfs(nx, x), sz[x] += sz[nx];
}
int query(int L, int R, int x, int l = 1, int r = n) {
	if (l == r) return l;
	int mid = l + (r - l) / 2, sum = _[_[R].lc].v - _[_[L].lc].v;
	if (x <= sum) return query(_[L].lc, _[R].lc, x, l, mid);
	return query(_[L].rc, _[R].rc, x - sum, mid + 1, r);
}

int m, x, y, lnk[N], b[N];
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", a + i), b[i] = a[i];
	std::sort(b + 1, b + n + 1);
	int nn = std::unique(b + 1, b + n + 1) - b - 1;
	for (int i = 1; i <= n; i++) {
		a[i] = std::lower_bound(b + 1, b + nn + 1, a[i]) - b;
		lnk[a[i]] = i;
	}
	for (int i = 1; i < n; i++) scanf("%d%d", &x, &y), addedge(x, y);
	dfs(1, 0);
	for (int i = 1; i <= n; i++) rt[i] = _[rt[i - 1]].insert(a[l2[i]]);
	for (scanf("%d", &m); m--;) {
		scanf("%d%d", &x, &y);
		printf("%d\n", lnk[query(rt[dfn[x] - 1], rt[dfn[x] + sz[x] - 1], y)]);
	}
}