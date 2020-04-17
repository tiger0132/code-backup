#include <algorithm>
#include <cstdio>
#include <cstring>

typedef long long ll;
const int N = 1e5 + 51;

struct pSGT {
#define L ch][0
#define R ch][1
#define mid (l + r) / 2
	static const int M = N << 5;
	int ch[M][2], nc;
	ll t[M], s[M];
	inline int cl(int x) {
		return nc++, nc[L] = x[L], nc[R] = x[R], nc[t] = x[t], nc[s] = x[s], nc;
	}
	void build(int& x, int l, int r, int* a) {
		if (x = ++nc, l == r) return x[s] = a[l], void();
		build(x[L], l, mid, a), build(x[R], mid + 1, r, a), x[s] = x[L][s] + x[R][s];
	}
	ll qry(int x, int l, int r, int ql, int qr) {
		if (ql == l && r == qr) return x[s] + x[t] * (r - l + 1);
		ll v = (qr - ql + 1) * x[t];
		if (qr <= mid) return v + qry(x[L], l, mid, ql, qr);
		if (mid < ql) return v + qry(x[R], mid + 1, r, ql, qr);
		return v + qry(x[L], l, mid, ql, mid) + qry(x[R], mid + 1, r, mid + 1, qr);
	}
	void upd(int& x, int l, int r, int ql, int qr, int y) {
		if (x = cl(x), ql <= l && r <= qr) return x[t] += y, void();
		if (ql <= mid) upd(x[L], l, mid, ql, qr, y);
		if (mid < qr) upd(x[R], mid + 1, r, ql, qr, y);
		x[s] = x[L][s] + x[R][s] + (mid - l + 1) * x[L][t] + (r - mid) * x[R][t];
	}
} psgt;

int n, m, x, y, z, tp, a[N], rt[N];
char op[2];
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	psgt.build(rt[0], 1, n, a);
	while (m--) {
		scanf("%s%d", op, &x);
		if (*op == 'C') {
			scanf("%d%d", &y, &z), tp++;
			psgt.upd(rt[tp] = rt[tp - 1], 1, n, x, y, z);
		} else if (*op == 'Q') {
			scanf("%d", &y);
			printf("%lld\n", psgt.qry(rt[tp], 1, n, x, y));
		} else if (*op == 'H') {
			scanf("%d%d", &y, &z);
			printf("%lld\n", psgt.qry(rt[z], 1, n, x, y));
		} else if (*op == 'B')
			tp = x;
	}
}