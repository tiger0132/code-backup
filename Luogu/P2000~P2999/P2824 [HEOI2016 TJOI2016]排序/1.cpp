#include <algorithm>
#include <cstdio>
#include <cstring>

#define L ch][0
#define R ch][1
#define mid (l + r) / 2
const int N = 8e5 + 58;
struct tag {
	int s[2], sz;
	void operator=(int x) { s[x] = sz = 1, s[!x] = 0; };
} t[N];
tag operator+(const tag& l, const tag& r) {
	return {{l.s[0] + r.s[0], l.s[1] + r.s[1]}, l.sz + r.sz};
}
int ch[N][2], a[N], set[N], nc;
void up(int x) { x[t] = x[L][t] + x[R][t]; }
void put(int x, int v) { x[set] = v, x[t].s[v] = x[t].sz, x[t].s[!v] = 0; }
void pd(int x) { ~x[set] && (put(x[L], x[set]), put(x[R], x[set]), x[set] = -1); }
void build(int x, int l, int r, int v) {
	if (x[set] = -1, l == r) return x[t] = a[l] < v;
	build(x[L] = ++nc, l, mid, v), build(x[R] = ++nc, mid + 1, r, v), up(x);
}
tag qry(int x, int l, int r, int ql, int qr) {
	if (ql <= l && r <= qr) return x[t];
	if (pd(x), qr <= mid) return qry(x[L], l, mid, ql, qr);
	if (mid < ql) return qry(x[R], mid + 1, r, ql, qr);
	return qry(x[L], l, mid, ql, qr) + qry(x[R], mid + 1, r, ql, qr);
}
void upd(int x, int l, int r, int ql, int qr, int v) {
	if (ql <= l && r <= qr) return put(x, v);
	if (pd(x), ql <= mid) upd(x[L], l, mid, ql, qr, v);
	if (mid < qr) upd(x[R], mid + 1, r, ql, qr, v);
	up(x);
}

int n, m, op[N], l[N], r[N], p, ans;
bool check(int x) {
	build(nc = 1, 1, n, x);
	for (int i = 1; i <= m; i++) {
		tag v = qry(1, 1, n, l[i], r[i]);
		if (op[i]) {
			if (v.s[0]) upd(1, 1, n, l[i], l[i] + v.s[0] - 1, 0);
			if (v.s[1]) upd(1, 1, n, l[i] + v.s[0], r[i], 1);
		} else {
			if (v.s[1]) upd(1, 1, n, l[i], l[i] + v.s[1] - 1, 1);
			if (v.s[0]) upd(1, 1, n, l[i] + v.s[1], r[i], 0);
		}
	}
	return qry(1, 1, n, p, p).s[0];
}
int main() {
	freopen("1.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	for (int i = 1; i <= m; i++) scanf("%d%d%d", op + i, l + i, r + i);
	scanf("%d", &p);
	for (int l = 1, r = n; l <= r;)
		if (check(mid))
			ans = mid, l = mid + 1;
		else
			r = mid - 1;
	printf("%d", ans);
}