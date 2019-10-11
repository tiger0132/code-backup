#include <algorithm>
#include <cstdio>
#include <cstring>

#define L ch][0
#define R ch][1
#define Lc x[L], l, mid
#define Rc x[R], mid + 1, r
#define Rt 1, 1, n
const int N = 8e4 + 48, INF = 1e6;
struct tag {
	int la, ra, s, gss;
	void operator=(int x) { s = gss = la = ra = x; }
} t[N];
tag operator+(const tag& l, const tag& r) {
	return {std::max(l.la, l.s + r.la), std::max(l.ra + r.s, r.ra), l.s + r.s,
			std::max({l.gss, r.gss, l.ra + r.la})};
}
int ch[N][2], nc;
void build(int x, int l, int r, int* a) {
	if (l == r) return void(x[t] = a[l]);
	int mid = (l + r) / 2;
	build(x[L] = ++nc, l, mid, a), build(x[R] = ++nc, mid + 1, r, a),
		x[t] = x[L][t] + x[R][t];
}
tag qry(int x, int l, int r, int ql, int qr) {
	if (ql > qr) return {-INF, -INF, 0, -INF};
	if (ql <= l && r <= qr) return x[t];
	int mid = (l + r) / 2;
	if (qr <= mid) return qry(Lc, ql, qr);
	if (mid < ql) return qry(Rc, ql, qr);
	return qry(Lc, ql, qr) + qry(Rc, ql, qr);
}

int n, m, x1, y1, x2, y2, z, a[N];
int main() {
	for (scanf("%*d"); ~scanf("%d", &n);) {
		for (int i = 1; i <= n; i++) scanf("%d", a + i);
		build(nc = 1, 1, n, a);
		for (scanf("%d", &m); m--; printf("%d\n", z), z = 0) {
			scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
			if (y1 < x2)
				z = qry(Rt, x1, y1).ra + qry(Rt, y1 + 1, x2 - 1).s + qry(Rt, x2, y2).la;
			else {
				z = qry(Rt, x2, y1).gss;
				if (x1 < x2) z = std::max(z, qry(Rt, x1, x2 - 1).ra + qry(Rt, x2, y2).la);
				if (y1 < y2) z = std::max(z, qry(Rt, x1, y1).ra + qry(Rt, y1 + 1, y2).la);
			}
		}
	}
}