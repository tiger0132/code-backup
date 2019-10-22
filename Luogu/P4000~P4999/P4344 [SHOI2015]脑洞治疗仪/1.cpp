#include <algorithm>
#include <cstdio>
#include <cstring>

#define L ch][0
#define R ch][1
#define mid (l + r) / 2
#define X(y) x[t].y
const int N = 8e5 + 58;
struct tag {
	int sz, s[2], la, ra, gss;
	void put(int v) { s[v] = sz, s[!v] = 0, la = ra = gss = !v * sz; }
} t[N];
tag operator+(const tag& l, const tag& r) {
	tag x;
	x.s[0] = l.s[0] + r.s[0], x.s[1] = l.s[1] + r.s[1], x.sz = l.sz + r.sz;
	x.la = std::max(l.la, l.s[0] == l.sz ? l.sz + r.la : 0);
	x.ra = std::max(r.s[0] == r.sz ? l.ra + r.sz : 0, r.ra);
	x.gss = std::max({l.gss, r.gss, l.ra + r.la});
	return x;
}
int ch[N][2], set[N], nc;  // s: 0 的个数
void up(int x) { x[t] = x[L][t] + x[R][t]; }
void put(int x, int v) { X(put)(v), x[set] = v; }
void pd(int x) {
	if (~x[set]) put(x[L], x[set]), put(x[R], x[set]), x[set] = -1;
}
void build(int x, int l, int r) {
	if (X(s[1]) = X(sz) = r - l + 1, x[set] = -1, l == r) return;
	build(x[L] = ++nc, l, mid), build(x[R] = ++nc, mid + 1, r);
}
template <int v>
void upd(int x, int l, int r, int ql, int qr) {
	if (ql <= l && r <= qr) return put(x, v);
	pd(x);
	if (pd(x), ql <= mid) upd<v>(x[L], l, mid, ql, qr);
	if (mid < qr) upd<v>(x[R], mid + 1, r, ql, qr);
	up(x);
}
tag qry(int x, int l, int r, int ql, int qr) {
	if (ql <= l && r <= qr) return x[t];
	if (pd(x), qr <= mid) return qry(x[L], l, mid, ql, qr);
	if (mid < ql) return qry(x[R], mid + 1, r, ql, qr);
	return qry(x[L], l, mid, ql, qr) + qry(x[R], mid + 1, r, ql, qr);
}
void upd(int x, int l, int r, int ql, int qr, int& v) {
	if (!v) return;
	if (ql <= l && r <= qr && v >= X(s[0])) return v -= X(s[0]), put(x, 1);
	pd(x);
	if (qr <= mid) return upd(x[L], l, mid, ql, qr, v), up(x);
	if (mid < ql) return upd(x[R], mid + 1, r, ql, qr, v), up(x);
	upd(x[L], l, mid, ql, qr, v);
	if (v) upd(x[R], mid + 1, r, ql, qr, v);
	up(x);
}

int n, op, x1, y1, x2, y2;
int main() {
	scanf("%d%*d", &n);
	for (build(nc = 1, 1, n); ~scanf("%d%d%d", &op, &x1, &y1);) {
		if (!op)
			upd<0>(1, 1, n, x1, y1);
		else if (op == 1) {
			scanf("%d%d", &x2, &y2);
			int cnt = qry(1, 1, n, x1, y1).s[1];
			upd<0>(1, 1, n, x1, y1);
			upd(1, 1, n, x2, y2, cnt);
		} else
			printf("%d\n", qry(1, 1, n, x1, y1).gss);
	}
}