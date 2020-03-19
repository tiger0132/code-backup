#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>

#define L ch][0
#define R ch][1
#define mid (l + r) / 2
const int N = 3e5 + 53;
int ch[N][2], mn[N], ad[N], nc = 1;
void up(int x) { x[mn] = std::min(x[L][mn], x[R][mn]); }
void add(int x, int v) { x[ad] += v, x[mn] += v; }
void pd(int x) { x[ad] && (add(x[L], x[ad]), add(x[R], x[ad]), x[ad] = 0); }
void build(int x, int l, int r) {
	l < r && (build(x[L] = ++nc, l, mid), build(x[R] = ++nc, mid + 1, r), 0);
}
void upd(int x, int l, int r, int ql, int qr, int v) {
	if (ql <= l && r <= qr) return add(x, v);
	if (pd(x), ql <= mid) upd(x[L], l, mid, ql, qr, v);
	if (mid < qr) upd(x[R], mid + 1, r, ql, qr, v);
	up(x);
}
int qry(int x, int l, int r, int ql, int qr) {
	if (ql <= l && r <= qr) return x[mn];
	if (pd(x), qr <= mid) return qry(x[L], l, mid, ql, qr);
	if (mid < ql) return qry(x[R], mid + 1, r, ql, qr);
	return std::min(qry(x[L], l, mid, ql, qr), qry(x[R], mid + 1, r, ql, qr));
}

namespace BIT {
int a[N], n;
int lowbit(int x) { return x & -x; }
void add(int i, int x) {
	for (; i <= n; i += lowbit(i)) a[i] += x;
}
int qry(int i) {
	int ret = 0;
	for (; i; i -= lowbit(i)) ret += a[i];
	return ret;
}
};  // namespace BIT

int n, p[N], q[N], occ[N], pt;
int main() {
	scanf("%d", &n), pt = BIT::n = n;
	memset(mn, 0x3f, sizeof mn);
	for (int i = 1; i <= n; i++) scanf("%d", p + i), p[i][occ] = i;
	for (int i = 1; i <= n; i++) scanf("%d", q + i);
	build(1, 1, n);
	upd(1, 1, n, n[occ], n, 1);
	BIT::add(n[occ], 1);
	for (int i = 1; i <= n; i++) {
		upd(1, 1, n, q[i], n, -1);
		while (qry(1, 1, n, occ[pt], n) + BIT::qry(occ[pt] - 1) <= 0) {
			pt--;
			upd(1, 1, n, pt[occ], n, 1);
			BIT::add(pt[occ], 1);
		}
		assert(pt >= 1);
		printf("%d ", pt);
	}
}