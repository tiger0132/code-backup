#include <algorithm>
#include <cstdio>
#include <cstring>
#define int long long

#define L ch][0
#define R ch][1
#define mid (l + r) / 2
const int N = 1e5 + 51, M = N * 32;
int ch[M][2], sv[M], sw[M], nc;
int cl(int x) {
	return (++nc)[L] = x[L], nc[R] = x[R], nc[sv] = x[sv], nc[sw] = x[sw], nc;
}
void ins(int x, int l, int r, int v, int w) {
	x[sv] += v * w, x[sw] += w;
	if (l == r) return;
	if (v <= mid) return ins(x[L] = cl(x[L]), l, mid, v, w);
	ins(x[R] = cl(x[R]), mid + 1, r, v, w);
}
int qry(int x, int l, int r, int w) {
	if (l == r) return w * l;
	if (w <= x[L][sw]) return qry(x[L], l, mid, w);
	return x[L][sv] + qry(x[R], mid + 1, r, w - x[L][sw]);
}

struct node {
	int d, p, l;
	bool operator<(const node& r) const { return d < r.d; }
} a[N];
int n, m, x, y, z, l, r, rt[N];
signed main() {
	scanf("%lld%lld", &n, &m), a[0].d = -1;
	for (int i = 1; i <= n; i++) scanf("%lld%lld%lld", &x, &y, &z), a[i] = {x, y, z};
	std::sort(a + 1, a + n + 1);
	for (int i = n; i >= 1; i--) ins(rt[i] = cl(rt[i + 1]), 1, N, a[i].p, a[i].l);
	while (m--) {
		scanf("%lld%lld", &x, &y);
		for (l = 1, r = N; l <= r;)
			if (y <= rt[mid][sw] && qry(rt[mid], 1, N, y) <= x)
				l = mid + 1;
			else
				r = mid - 1;
		printf("%lld\n", a[l - 1].d);
	}
}