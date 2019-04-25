#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#define int long long

const int N = 2e5 + 52;
int sz, a[N], cnt1[N], cnt2[N];
struct query {
	int l, r, *ans, op;
	bool operator<(const query &y) const { return l / sz != y.l / sz ? l < y.l : (l / sz) % 2 ? r < y.r : r > y.r; }
} q[N];
int upd(int *c1, int *c2, int x, int o) { return c1[x] += o, c2[x]; }

int n, m, l1, r1, l2, r2, ans[N];
signed main() {
	scanf("%lld", &n), sz = sqrt(n);
	for (int i = 1; i <= n; i++) scanf("%lld", a + i);
	scanf("%lld", &m);
	for (int i = 1; i <= m; i++) {
		scanf("%lld%lld%lld%lld", &l1, &r1, &l2, &r2);
		q[4 * i - 3] = (query){r1, r2, ans + i, 1};
		q[4 * i - 2] = (query){l1 - 1, l2 - 1, ans + i, 1};
		q[4 * i - 1] = (query){l1 - 1, r2, ans + i, -1};
		q[4 * i] = (query){r1, l2 - 1, ans + i, -1};
	}
	for (int i = 1; i <= m * 4; i++)
		if (q[i].l > q[i].r) std::swap(q[i].l, q[i].r);
	std::sort(q + 1, q + m * 4 + 1);
	for (int l = 0, r = 0, lans = 0, i = 1; i <= m * 4; i++) {
		while (l < q[i].l) lans += upd(cnt1, cnt2, a[++l], 1);
		while (r < q[i].r) lans += upd(cnt2, cnt1, a[++r], 1);
		while (l > q[i].l) lans -= upd(cnt1, cnt2, a[l--], -1);
		while (r > q[i].r) lans -= upd(cnt2, cnt1, a[r--], -1);
		*q[i].ans += q[i].op * lans;
	}
	for (int i = 1; i <= m; i++) printf("%lld\n", ans[i]);
}