#include <algorithm>
#include <cstdio>
#include <cstring>

#define L ch][0
#define R ch][1
#define X(y) x[t].y
const int N = 4e5 + 54;
int er[N], cv[N], wsx[N];
struct tag {
	int l, r, mid, qwe, zxc, qaz, edc, qsc, zse;
	tag operator+(const tag& rhs) const {
		static tag ret;
		ret.l = l, ret.r = rhs.r, ret.mid = (ret.l + ret.r) / 2;
		ret.qaz = qaz || (qwe && r[er] && rhs.qaz && r[cv] && zxc);
		ret.edc = rhs.edc || (rhs.qwe && r[er] && edc && r[cv] && rhs.zxc);
		ret.qwe = (qwe && r[er] && rhs.qwe) || (qsc && r[cv] && rhs.zse);
		ret.zxc = (zxc && r[cv] && rhs.zxc) || (zse && r[er] && rhs.qsc);
		ret.qsc = (qsc && r[cv] && rhs.zxc) || (qwe && r[er] && rhs.qsc);
		ret.zse = (zse && r[er] && rhs.qwe) || (zxc && r[cv] && rhs.zse);
		return ret;
	}
} t[N];
int ch[N][2], sz;
void up(int x) { x[t] = x[L][t] + x[R][t]; }
void init(int x, int i) {
	X(l) = X(r) = X(mid) = i, X(qwe) = X(zxc) = 1,
	X(qaz) = X(edc) = X(qsc) = X(zse) = i[wsx];
}
void build(int x, int ql, int qr) {
	int mid = (ql + qr) / 2;
	if (ql == qr) return init(x, ql);
	build(x[L] = ++sz, ql, mid), build(x[R] = ++sz, mid + 1, qr), up(x);
}
void upd(int x, int ql, int qr, int* mode, int v) {
	if (ql <= X(l) && X(r) <= qr) {
		if (ql == X(l)) ql[mode] = v, X(l) == X(r) ? init(x, ql) : up(x);
		return;
	}
	if (ql <= X(mid)) upd(x[L], ql, qr, mode, v);
	if (X(mid) < qr) upd(x[R], ql, qr, mode, v);
	up(x);
}
tag qry(int x, int ql, int qr) {
	if (ql <= X(l) && X(r) <= qr) return x[t];
	if (qr <= X(mid)) return qry(x[L], ql, qr);
	if (X(mid) < ql) return qry(x[R], ql, qr);
	return qry(x[L], ql, qr) + qry(x[R], ql, qr);
}

#define x1 orzAiming_High
#define x2 orzFruitCandy
#define y1 orzQiuly
#define y2 orzgoodbye2018
int n, x1, y1, x2, y2, x, y, z;
char op[11];
int main() {
	scanf("%d", &n);
	build(sz = 1, 1, n);
	while (scanf("%s", op), *op != 'E') {
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		if (y1 > y2) std::swap(x1, x2), std::swap(y1, y2);
		if (*op == 'A') {
			tag x = qry(1, 1, y1), y = qry(1, y1, y2), z = qry(1, y2, n);
			if (x1 == 1 && x2 == 2)
				puts((x.edc && y.zxc) || y.qsc || (y.qwe && z.qaz) ? "Y" : "N");
			else if (x1 == 2 && x2 == 1)
				puts((x.edc && y.qwe) || y.zse || (y.zxc && z.qaz) ? "Y" : "N");
			else if (x1 == 1)
				puts((x.edc && x.r[cv] && y.zxc && y.r[cv] && z.qaz) || y.qwe ? "Y"
																			  : "N");
			else if (x1 == 2)
				puts((x.edc && x.r[er] && y.qwe && y.r[er] && z.qaz) || y.zxc ? "Y"
																			  : "N");
		} else {
			z = *op == 'O';
			if (x1 != x2)
				upd(1, y1, y1, wsx, z);
			else
				upd(1, y1, y2, x1 == 1 ? er : cv, z);
		}
	}
}