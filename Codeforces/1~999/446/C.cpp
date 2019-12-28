#include <algorithm>
#include <cstdio>
#include <cstring>

#define L ch][0
#define R ch][1
#define mid (l + r) / 2
const int N = 2e6 + 62, P = 1e9 + 9, X = 691504013, Y = 308495997, Z = 276601605;
int sum(int x, int y) { return (x += y) >= P ? x - P : x; }
void add(int& x, int y) { (x += y) >= P && (x -= P); }
int pwX[N], pwY[N];
int ch[N][2], s[N], t1[N], t2[N], sz[N], nc;
void up(int x) { x[s] = sum(x[L][s], x[R][s]); }
void put(int x, int v1, int v2) {
	add(x[s], 1ll * v1 * (P + pwX[x[sz] + 1] - X) % P * X % P);
	add(x[s], 1ll * v2 * (P + pwY[x[sz] + 1] - Y) % P * Y % P);
	add(x[t1], v1), add(x[t2], v2);
}
void pd(int x) {
	put(x[L], x[t1], x[t2]);
	put(x[R], 1ll * pwX[x[L][sz]] * x[t1] % P, 1ll * pwY[x[L][sz]] * x[t2] % P);
	x[t1] = x[t2] = 0;
}
void build(int x, int l, int r) {
	x[sz] = r - l + 1;
	if (l < r) build(x[L] = ++nc, l, mid), build(x[R] = ++nc, mid + 1, r);
}
// 区间加 [v1*X + v2*Y, v1*X^2 + v2*Y^2, ..., v1*X^k + v2*Y^k]
void upd(int x, int l, int r, int ql, int qr, int v1, int v2) {
	if (ql <= l && r <= qr) {
		int gap = std::max(0, l - ql);
		return put(x, 1ll * pwX[gap] * v1 % P, 1ll * pwY[gap] * v2 % P);
	}
	pd(x);
	if (ql <= mid) upd(x[L], l, mid, ql, qr, v1, v2);
	if (mid < qr) upd(x[R], mid + 1, r, ql, qr, v1, v2);
	up(x);
}
int qry(int x, int l, int r, int ql, int qr) {
	if (ql <= l && r <= qr) return x[s];
	pd(x);
	if (qr <= mid) return qry(x[L], l, mid, ql, qr);
	if (mid < ql) return qry(x[R], mid + 1, r, ql, qr);
	return sum(qry(x[L], l, mid, ql, qr), qry(x[R], mid + 1, r, ql, qr));
}

int n, m, x, y, z, a[N];
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", a + i), add(a[i], a[i - 1]);
	pwX[0] = pwY[0] = 1;
	for (int i = 1; i <= n + 1; i++) {
		pwX[i] = 1ll * pwX[i - 1] * X % P;
		pwY[i] = 1ll * pwY[i - 1] * Y % P;
	}
	build(nc = 1, 1, n);
	while (m--) {
		scanf("%d%d%d", &x, &y, &z);
		if (x == 2)
			printf("%lld\n", (1ll * P + a[z] - a[y - 1] + qry(1, 1, n, y, z)) % P);
		else
			upd(1, 1, n, y, z, Z, P - Z);
	}
}