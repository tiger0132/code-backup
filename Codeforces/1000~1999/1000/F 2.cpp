#include <algorithm>
#include <cstdio>
#include <cstring>

#define L ch][0
#define R ch][1
#define mid (l + r) / 2
const int N = 5e5 + 55, M = N * 50, INF = 1e9;
struct tag {
	int mn, mi;
	bool operator<(const tag& r) const { return mn < r.mn; }
} t[M];
int ch[M][2], nc;
void up(int x) { x[t] = std::min(x[L][t], x[R][t]); }
int cl(int x) { return (++nc)[t] = x[t], nc[L] = x[L], nc[R] = x[R], nc; }
void upd(int x, int l, int r, int i, int v) {
	if (l == r) return void(x[t] = {v, i});
	if (i <= mid) return upd(x[L] = cl(x[L]), l, mid, i, v), up(x);
	return upd(x[R] = cl(x[R]), mid + 1, r, i, v), up(x);
}
tag qry(int x, int l, int r, int ql, int qr) {
	if (!x) return {INF, 0};
	if (ql <= l && r <= qr) return x[t];
	if (qr <= mid) return qry(x[L], l, mid, ql, qr);
	if (mid < ql) return qry(x[R], mid + 1, r, ql, qr);
	return std::min(qry(x[L], l, mid, ql, qr), qry(x[R], mid + 1, r, ql, qr));
}

int n, l, r, x, rt[N], a[N], p[N];
int main() {
	scanf("%d", &n);
	t[0] = {INF, 0};
	for (int i = 1; i <= n; i++) {
		scanf("%d", a + i);
		if (a[i][p]) {
			int x;
			upd(x = cl(rt[i - 1]), 1, n, a[i][p], INF);
			upd(rt[i] = cl(x), 1, n, i, a[i][p]);
		} else
			upd(rt[i] = cl(rt[i - 1]), 1, n, i, 0);
		a[i][p] = i;
	}
	for (scanf("%*d"); ~scanf("%d%d", &l, &r);) {
		tag t = qry(rt[r], 1, n, l, r);
		printf("%d\n", (t.mn < l) * a[t.mi]);
	}
}