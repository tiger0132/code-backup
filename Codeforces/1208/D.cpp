#include <algorithm>
#include <cstdio>
#include <cstring>

#define L ch][0
#define R ch][1
#define mid (l + r) / 2
typedef long long ll;
const int N = 2e5 + 52, M = 8e5 + 58;
int ch[M][2], mi[M], nc;
ll s[N], mn[N], ad[M];
void up(int x) {
	if (x[L][mn] < x[R][mn]) return (void)(x[mn] = x[L][mn], x[mi] = x[L][mi]);
	x[mn] = x[R][mn], x[mi] = x[R][mi];
}
void add(int x, ll v) { x[ad] += v, x[mn] += v; }
void pd(int x) { add(x[L], x[ad]), add(x[R], x[ad]), x[ad] = 0; }
void build(int x, int l, int r) {
	if (l == r) return (void)(x[mi] = l, x[mn] = s[l]);
	build(x[L] = ++nc, l, mid), build(x[R] = ++nc, mid + 1, r), up(x);
}
void upd(int x, int l, int r, int ql, int qr, ll v) {
	if (ql <= l && r <= qr) return add(x, v);
	if (pd(x), ql <= mid) upd(x[L], l, mid, ql, qr, v);
	if (mid < qr) upd(x[R], mid + 1, r, ql, qr, v);
	up(x);
}

int n, x, ans[N];
int main() {
	scanf("%d", &n), s[0] = mn[0] = 2e5;
	for (int i = 1; i <= n; i++) scanf("%lld", s + i);
	build(nc = 1, 1, n);
	for (int i = 1; i <= n; i++) {
		x = mi[1];
		ans[x] = i;
		upd(1, 1, n, x, x, 1e15);
		if (x < n) upd(1, 1, n, x + 1, n, -i);
	}
	for (int i = 1; i <= n; i++) printf("%d ", ans[i]);
}