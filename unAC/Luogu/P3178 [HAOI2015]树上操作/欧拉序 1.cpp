#include <cassert>
#include <cstdio>
#define int long long

const int N = 2e5 + 52;

struct edge {
	int to, next;
} e[N << 1];
int head[N], cnt;
void addedge(int x, int y) {
	e[++cnt] = (edge){y, head[x]}, head[x] = cnt;
	e[++cnt] = (edge){x, head[y]}, head[y] = cnt;
}

int p;

struct node *newNode();
struct node {
	int l, r, mid, cnt, sum, tag;
	node *lc, *rc;
	inline void pushup() { sum = lc->sum + rc->sum; }
	inline void pushdown() {
		lc->tag += tag;
		rc->tag += tag;
		lc->sum += tag * lc->cnt;
		rc->sum += tag * rc->cnt;
	}
	void build(int L, int R, int *a, int *b) {
		l = L, r = R, mid = (l + r) >> 1, tag = 0;
		if (l == r) return (void)(sum = a[l], cnt = b[l]);
		(lc = newNode())->build(l, mid, a, b);
		(rc = newNode())->build(mid + 1, r, a, b);
		pushup(), cnt = lc->cnt + rc->cnt;
	}
	int query(int L, int R) {
		if (L <= l && r <= R) return sum;
		pushdown();
		int ret = 0;
		if (L <= mid) ret += lc->query(L, R);
		if (mid < R) ret += rc->query(L, R);
		return ret;
	}
	void update(int L, int R, int x) {
		if (L <= l && r <= R) return (void)(tag += x, sum += cnt * x);
		if (L <= mid) lc->update(L, R, x);
		if (mid < R) rc->update(L, R, x);
		if (p) fprintf(stderr, "before: [%d, %d], %d, %d\n", l, r, cnt, sum);
		pushup();
		if (p) fprintf(stderr, "after : [%d, %d], %d, %d\n", l, r, cnt, sum);
	}
	void update(int x, int y) {
		if (l == r) return void(sum += y);
		if (x <= mid)
			lc->update(x, y);
		else
			rc->update(x, y);
		sum += y;
	}
} pool[N << 2], *null = pool, *root;
node *newNode() {
	static node *ptr = pool + 1;
	ptr->lc = ptr->rc = null;
	return ptr++;
}

int src[N], a[N], b[N], l[N], r[N], _;
void dfs(int x, int p) {
	a[l[x] = ++_] = src[x], b[_] = 1;
	for (int i = head[x]; i; i = e[i].next) {
		int nx = e[i].to;
		if (nx == p) continue;
		dfs(nx, x);
	}
	a[r[x] = ++_] = -src[x], b[_] = -1;
}

int n, m, op, x, y;
signed main() {
	freopen("1.in", "r", stdin);
	freopen("1.out", "w", stdout);
	scanf("%lld%lld", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%lld", src + i);
	}
	for (int i = 1; i < n; i++) {
		scanf("%lld%lld", &x, &y);
		addedge(x, y);
	}
	dfs(1, 0);
	(root = newNode())->build(1, _, a, b);
	while (m--) {
		scanf("%lld%lld", &op, &x);
		if (m == 664) {
			puts("!!");
			p = 1;
		}
		if (op ^ 3) scanf("%lld", &y);
		switch (op) {
			case 1:
				root->update(l[x], y);
				root->update(r[x], -y);
				break;
			case 2:
				root->update(l[x], r[x], y);
				break;
			case 3:
				printf("%lld\n", root->query(1, l[x]));
		}
		if (root->query(1, _)) scanf("%d", 0);
	}
}