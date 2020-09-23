#include <algorithm>
#include <cstdio>
#include <cstring>
#define L ch][0
#define R ch][1
#define mid (l + r) / 2

const int N = 1e5 + 51, M = 4e6 + 64;
int ch[M][2], sz[M], nc;
void upd(int& x, int l, int r, int i) {
	if (!x) x = ++nc;
	if (x[sz]++, l == r) return;
	if (i <= mid) return upd(x[L], l, mid, i);
	upd(x[R], mid + 1, r, i);
}
int qry(int x, int l, int r, int ql, int qr) {
	if (!x) return 0;
	if (ql <= l && r <= qr) return x[sz];
	if (qr <= mid) return qry(x[L], l, mid, ql, qr);
	if (mid < ql) return qry(x[R], mid + 1, r, ql, qr);
	return qry(x[L], l, mid, ql, qr) + qry(x[R], mid + 1, r, ql, qr);
}

struct pt {
	int x, r, f;
} q[N];
int rt[N];

long long ans;
int n, k;
int main() {
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++) {
		scanf("%d%d%d", &q[i].x, &q[i].r, &q[i].f);
	}
	std::sort(q + 1, q + n + 1, [](pt& x, pt& y) { return x.r > y.r; });
	for (int i = 1; i <= n; i++) {
		for (int j = std::max(1, q[i].f - k); j <= q[i].f + k; j++) {
			ans += qry(rt[j], 1, 1e9, q[i].x - q[i].r, q[i].x + q[i].r);
		}
		upd(rt[q[i].f], 1, 1e9, q[i].x);
	}
	printf("%lld\n", ans);
}