#include <algorithm>
#include <cstdio>
#include <cstring>

#define L ch][0
#define R ch][1
#define mid (l + r) / 2
const int N = 2e6 + 62;
int ch[N][2], mx[N], ad[N], nc = 1;
void up(int x) { x[mx] = std::max(x[L][mx], x[R][mx]); }
void add(int x, int v) { x[ad] += v, x[mx] += v; }
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

struct line {
	int l, r, len;
} a[N];
int n, m, x, ans = 1e9, l[N], r[N], b[N];
int main() {
	scanf("%d%d", &n, &m);
	build(1, 1, 2 * n);
	for (int i = 1; i <= n; i++)
		scanf("%d%d", l + i, r + i), b[2 * i - 1] = l[i], b[2 * i] = r[i];
	std::sort(b + 1, b + 2 * n + 1);
	for (int i = 1; i <= n; i++) {
		int u = std::lower_bound(b + 1, b + 2 * n + 1, l[i]) - b;
		int v = std::lower_bound(b + 1, b + 2 * n + 1, r[i]) - b;
		a[i] = {u, v, r[i] - l[i]};
	}
	std::sort(a + 1, a + n + 1,
			  [](const line& x, const line& y) { return x.len < y.len; });
	for (int i = 1, j = 1; i <= n; i++) {
		for (; j <= n && mx[1] < m; j++) upd(1, 1, 2 * n, a[j].l, a[j].r, 1);
		if (mx[1] < m) break;
		ans = std::min(ans, a[j - 1].len - a[i].len);
		upd(1, 1, 2 * n, a[i].l, a[i].r, -1);
	}
	printf("%d", ans == 1e9 ? -1 : ans);
}