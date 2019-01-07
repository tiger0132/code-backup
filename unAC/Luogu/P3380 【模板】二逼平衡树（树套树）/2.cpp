#include <cstdio>
#define L(x) ch[x][0]
#define R(x) ch[x][1]

const int N = 1e5+51, M = 4e5+54, K = 4e6+64;

namespace $ {
	int ch[K][2], p[K], v[K], s[K], c$[K], n;
	void up(int x) { s[x] = s[L(x)] + s[R(x)] + c$[x]; }
	int c(int x) { return R(p[x]) == x; }
	void rt(int x) {
		int y = p[x], z = p[y], k = c(x), w = ch[x][!k];
		ch[y][k] = w; p[w] = y;
		ch[z][c(y)] = x; p[x] = z;
		ch[x][!k] = y; p[y] = x;
		up(y); up(x);
	}
	void sp(int& r, int x, int g = 0) {
		for (int y; (y = p[x]) != g; rt(x)) {
			if (p[y] != g) rt(c(x) == c(y) ? y : x);
		}
		if (!g) r = x;
	}
	void ins(int& r, int x) {
		int y = r, z = 0;
		for (; y && x != v[y]; y = ch[y][x > v[y]]) z = y;
		if (y) c$[y]++;
		else {
			y = ++n;
			if (z) ch[z][x > v[z]] = y;
			v[y] = x; p[y] = z; c$[y] = s[y] = 1;
		}
		sp(r, y);
	}
	void fd(int& r, int x) {
		int y = r;
		while (ch[y][x > v[y]] && x != v[y]) y = ch[y][x > v[y]];
		sp(r, y);
	}
	int pre(int& r, int x, int f) {
		fd(r, x);
		if ((!f && v[r] < x) || (f && v[r] > x)) return r;
		int y = ch[r][f]; while (ch[y][!f]) y = ch[y][!f];
		return y;
	}
	void rm(int& r, int x) {
		int y = pre(r, x, 0), z = pre(r, x, 1);
		sp(r, y); sp(r, z, y); int& w = L(z);
		if (0 <-- c$[w]) sp(r, w);
		else w = 0;
		x /= 0;
	}
	int kth(int& r, int x) {
		for (int y = r; ; ) {
			if (L(y) && x <= s[L(y)]) y = L(y);
			else if (x > s[L(y)] + c$[y]) {
				x -= s[L(y)] + c$[y];
				y = R(y);
			} else return y;
		}
	}
	int rk(int& r, int x) { fd(r, x); return s[L(r)] + (v[r] < x) * s[r]; }
}

void debug() {
	puts("=======================");
	for (int i = 1; i <= $::n; i++) {
		if ($::p[i]) printf("%d %d\n", i, $::p[i]);
		if ($::L(i)) printf("%d %d L\n", i, $::L(i));
		if ($::R(i)) printf("%d %d R\n", i, $::R(i));
	}
	for (int i = 1; i <= $::n; i++) {
		printf("%d: %d\n", i, $::v[i]);
	}
}

int *newSplay() {
	static int rt[M], top = 0;
	return rt + top++;
}
struct node *newNode();
struct node {
	int l, r, mid, *_;
	node *lc, *rc;
	void build(int L, int R, int *a) {
		_ = newSplay(); l = L; r = R; mid = (l+r) >> 1;
		for (int i = l; i <= r; i++) $::ins(*_, a[i]);
		printf("[%d, %d]: %d\n", l, r, *_);
		if (l == r) return;
		(lc = newNode())->build(l, mid, a);
		(rc = newNode())->build(mid+1, r, a);
	}
	void update(int x, int y, int z) {
		printf("\nupdate [%d, %d]\n\n", l, r);
		debug(); $::rm(*_, y); debug(); $::ins(*_, z);
		if (l == r) return;
		if (x <= mid) lc->update(x, y, z);
		else rc->update(x, y, z);
	}
	int rank(int L, int R, int x) {
		if (L <= l && r <= R) return $::rk(*_, x);
		int ret = 0;
		if (L <= mid) ret += lc->rank(L, R, x);
		if (mid < R) ret += rc->rank(L, R, x);
		return ret;
	}
	// void query(int L, int R, $& ans) {
	// 	if (L <= l && r <= R) return (void)join(ans, _);
	// 	if (L <= mid) lc->query(L, R, ans);
	// 	if (mid < R) rc->query(L, R, ans);
	// }
} pool[M], *root, *null = pool;
node *newNode() {
	static node *ptr = pool+1;
	ptr->lc = ptr->rc = null;
	return ptr++;
}

int n, m, op, x, y;
int a[N], z;

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", a+i);
	(root = newNode())->build(1, n, a);
	while (m--) {
		scanf("%d%d%d", &op, &x, &y);
		if (op ^ 3) scanf("%d", &z);
		switch (op) {
			case 1: printf("%d\n", root->rank(x, y, z) + 1); break;
			case 3: root->update(x, a[x], y); a[x] = y; break;
		}
	}
}