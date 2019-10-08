#include <algorithm>
#include <cstdio>
#include <cstring>
#define int long long

#define L ch][0
#define R ch][1
const int N = 4e5 + 54;
int ch[N][2], s[N], mx[N], nc = 1;
void up(int x) { x[s] = x[L][s] + x[R][s], x[mx] = std::max(x[L][mx], x[R][mx]); }
void build(int x, int l, int r, int *a) {
	if (l == r) return void(x[s] = x[mx] = a[l]);
	int mid = (l + r) / 2;
	build(x[L] = ++nc, l, mid, a), build(x[R] = ++nc, mid + 1, r, a), up(x);
}
void upd(int x, int l, int r, int ql, int qr, int y) {
	if (l == r) return (void)(x[s] %= y, x[mx] %= y);
	if (x[mx] < y) return;
	int mid = (l + r) / 2;
	if (ql <= mid) upd(x[L], l, mid, ql, qr, y);
	if (mid < qr) upd(x[R], mid + 1, r, ql, qr, y);
	up(x);
}
void upd(int x, int l, int r, int i, int y) {
	if (l == r) return void(x[s] = x[mx] = y);
	int mid = (l + r) / 2;
	if (i <= mid) upd(x[L], l, mid, i, y);
	if (mid < i) upd(x[R], mid + 1, r, i, y);
	up(x);
}
int qry(int x, int l, int r, int ql, int qr) {
	if (ql <= l && r <= qr) return x[s];
	int mid = (l + r) / 2, ret = 0;
	if (ql <= mid) ret += qry(x[L], l, mid, ql, qr);
	if (mid < qr) ret += qry(x[R], mid + 1, r, ql, qr);
	return ret;
}

int n, m, op, x, y, z, a[N];
signed main() {
	scanf("%lld%lld", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%lld", a + i);
	build(1, 1, n, a);
	while (m--) {
		scanf("%lld%lld%lld", &op, &x, &y);
		if (op == 1) printf("%lld\n", qry(1, 1, n, x, y));
		if (op == 2) scanf("%lld", &z), upd(1, 1, n, x, y, z);
		if (op == 3) upd(1, 1, n, x, y);
	}
}