#include <cstdio>
#define _ inline
#define L(x) ch[x][0]
#define R(x) ch[x][1]

const int N = 5e4 + 45, M = 1e6 + 61;
// clang-format off
namespace $ {
	int ch[N][2], p[N], v[N], s[N], cnode[N], n;
	_ void up(int x) { s[x] = s[L(x)] + s[R(x)] + cnode[x]; }
	_ int c(int x) { return R(p[x]) == x; }
	_ void rt(int x) {
		int y = p[x], z = p[y], k = c(x), w = ch[x][!k];
		ch[y][k] = w; p[w] = y;
		ch[z][c(y)] = x; p[x] = z;
		ch[x][!k] = y; p[y] = x;
		up(y); up(x);
	}
	_ void sp(int& r, int x, int g = 0) {
		for (int y; (y = p[x]) != g; rt(x)) {
			if (p[y] != g) rt(c(x) == c(y) ? y : x);
		}
		if (!g) r = x;
	}
	_ void ins(int& r, int x) {
		int y = r, z = 0;
		for (; y && x != v[y]; y = ch[y][x > v[y]]) z = y;
		if (y) cnode[y]++;
		else {
			y = ++n;
			if (z) ch[z][x > v[z]] = y;
			v[y] = x; p[y] = z; cnode[y] = s[y] = 1;
		}
		sp(r, y);
	}
	_ void fd(int& r, int x) {
		int y = r;
		while (ch[y][x > v[y]] && x != v[y]) y = ch[y][x > v[y]];
		sp(r, y);
	}
	_ int pre(int& r, int x, int f) {
		fd(r, x);
		if ((!f && v[r] < x) || (f && v[r] > x)) return r;
		int y = ch[r][f]; while (ch[y][!f]) y = ch[y][!f];
		return y;
	}
	_ void rm(int& r, int x) {
		int y = pre(r, x, 0), z = pre(r, x, 1);
		sp(r, y); sp(r, z, y); int& w = ch[z][0];
		if (cnode[w] --> 1) sp(r, w);
		else w = 0;
	}
	_ int kth(int&r, int x) {
		for (int y = r; ; ) {
			if (L(y) && x <= s[L(y)]) y = L(y);
			else if (x > s[L(y)] + cnode[y]) {
				x -= s[L(y)] + cnode[y];
				y = R(y);
			} else return y;
		}
	}
	int rk(int& r, int x) { fd(r, x); return s[L(r)] + (v[r] < x) * s[r]; }
}
// clang-format on

struct node* newNode();
struct node {
	int l, r, mid, rt;
	node *lc, *rc;
	void build(int L, int R, int* a) {
		l = L, r = R, mid = (l + r) >> 1;
		for (int i = L; i <= R; i++) $::ins(rt, a[i]);
		if (l == r) return;
		(lc = newNode())->build(l, mid, a);
		(rc = newNode())->build(mid + 1, r, a);
	}
	void update(int x, int y, int z) {
		$::rm(rt, y), $::ins(rt, z);
		if (l == r) return;
		(x <= mid ? lc : rc)->update(x, y, z);
	}
	int query(int L, int R, int x) {
		if (L <= l && r <= R) return $::rk(rt, x);
		int ret = 0;
		if (L <= mid) ret += lc->query(L, R, x);
		if (mid < R) ret += rc->query(L, R, x);
	}
} pool[M], *root, *null = pool;
node* newNode() {
	static node* ptr = pool + 1;
	ptr->lc = ptr->rc = null;
	return ptr++;
}

int n, m, op, x, y, z, a[N];
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", a + i);
	}
	(root = newNode())->build(1, n, a);
	while (m--) {
		scanf("%d%d%d", &op, &x, &y);
		if (op ^ 3) scanf("%d", &z);
		switch (op) {
			case 1:
				printf("%d\n", root->query(x, y, z) + 1);
				break;
			case 3:
				root->update(x, a[x], y);
				a[x] = y;
				break;
		}
	}
}