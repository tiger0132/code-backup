#include <algorithm>
#include <cstdio>
#include <cstring>
#define int long long
#define L ch][0
#define R ch][1
#define mid (l + r) / 2

const int N = 8e5 + 58;

int ch[N][2], mn[N], t[N], nc;
void up(int x) { x[mn] = std::min(x[L][mn], x[R][mn]); }
void put(int x, int y) { x[mn] += y, x[t] += y; }
void pd(int x) {
	if (x[t]) put(x[L], x[t]), put(x[R], x[t]), x[t] = 0;
}
void build(int x, int l, int r, int *a) {
	if (l == r) return x[mn] = a[l], void();
	build(x[L] = ++nc, l, mid, a), build(x[R] = ++nc, mid + 1, r, a), up(x);
}
void upd(int x, int l, int r, int ql, int qr, int y) {
	if (ql <= l && r <= qr) return put(x, y);
	pd(x);
	if (ql <= mid) upd(x[L], l, mid, ql, qr, y);
	if (mid < qr) upd(x[R], mid + 1, r, ql, qr, y);
	up(x);
}

int n, p[N], a[N], na[N], ans = 1e18;
signed main() {
	scanf("%lld", &n);
	for (int i = 1; i <= n; i++) scanf("%lld", p + i);
	for (int i = 1; i <= n; i++) scanf("%lld", a + i), na[p[i]] = a[i];
	for (int i = 1; i <= n; i++) na[i] += na[i - 1];
	build(nc = 1, 0, n, na);
	for (int i = 1; i < n; i++) {
		upd(1, 0, n, 0, p[i] - 1, a[i]);
		upd(1, 0, n, p[i], n, -a[i]);
		ans = std::min(ans, mn[1]);
	}
	printf("%lld", ans);
}