#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 4e5 + 54;

#define L ch][0
#define R ch][1
struct tag {
	int s, sz, la[2], ra[2], gss[2];
	void operator=(int x) { s = x, sz = 1, la[x] = ra[x] = gss[x] = 1; }
} t[N];
tag operator+(const tag& l, const tag& r) {
	tag ret;
	ret.s = l.s + r.s, ret.sz = l.sz + r.sz;
	ret.la[0] = !l.s ? l.sz + r.la[0] : l.la[0];
	ret.ra[0] = !r.s ? l.ra[0] + r.sz : r.ra[0];
	ret.la[1] = l.s == l.sz ? l.sz + r.la[1] : l.la[1];
	ret.ra[1] = r.s == r.sz ? l.ra[1] + r.sz : r.ra[1];
	ret.gss[0] = std::max({l.gss[0], r.gss[0], l.ra[0] + r.la[0]});
	ret.gss[1] = std::max({l.gss[1], r.gss[1], l.ra[1] + r.la[1]});
	return ret;
}
int ch[N][2], l[N], r[N], mid[N], ts[N], tr[N], nc = 1;
void up(int x) { x[t] = x[L][t] + x[R][t]; }
void build(int x, int ql, int qr, int* a) {
	x[l] = ql, x[r] = qr, x[mid] = (ql + qr) / 2, x[ts] = -1;
	if (ql == qr) return void(x[t] = a[ql]);
	build(x[L] = ++nc, ql, x[mid], a), build(x[R] = ++nc, x[mid] + 1, qr, a), up(x);
}
void set(int x, int v) {
	x[ts] = v, x[tr] = 0;
	x[t].s = x[t].sz * v;
	x[t].la[!v] = x[t].ra[!v] = x[t].gss[!v] = 0;
	x[t].la[v] = x[t].ra[v] = x[t].gss[v] = x[t].sz;
}
void rev(int x) {
	if (~x[ts] && !x[tr])
		x[ts] ^= 1;
	else
		x[tr] ^= 1;
	x[t].s = x[t].sz - x[t].s;
	std::swap(x[t].la[0], x[t].la[1]);
	std::swap(x[t].ra[0], x[t].ra[1]);
	std::swap(x[t].gss[0], x[t].gss[1]);
}
void pd(int x) {
	if (~x[ts]) set(x[L], x[ts]), set(x[R], x[ts]), x[ts] = -1;
	if (x[tr]) rev(x[L]), rev(x[R]), x[tr] = 0;
}
void upd01(int x, int ql, int qr, int v) {
	if (ql <= x[l] && x[r] <= qr) return set(x, v);
	pd(x);
	if (ql <= x[mid]) upd01(x[L], ql, qr, v);
	if (x[mid] < qr) upd01(x[R], ql, qr, v);
	up(x);
}
void upd2(int x, int ql, int qr) {
	if (ql <= x[l] && x[r] <= qr) return rev(x);
	pd(x);
	if (ql <= x[mid]) upd2(x[L], ql, qr);
	if (x[mid] < qr) upd2(x[R], ql, qr);
	up(x);
}
tag qry(int x, int ql, int qr) {
	if (ql <= x[l] && x[r] <= qr) return x[t];
	pd(x);
	if (qr <= x[mid]) return qry(x[L], ql, qr);
	if (x[mid] < ql) return qry(x[R], ql, qr);
	return qry(x[L], ql, qr) + qry(x[R], ql, qr);
}

int n, m, op, x, y, a[N];
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	build(1, 1, n, a);
	while (m--) {
		scanf("%d%d%d", &op, &x, &y), x++, y++;
		if (op <= 1) upd01(1, x, y, op);
		if (op == 2) upd2(1, x, y);
		if (op == 3) printf("%d\n", qry(1, x, y).s);
		if (op == 4) printf("%d\n", qry(1, x, y).gss[1]);
	}
}