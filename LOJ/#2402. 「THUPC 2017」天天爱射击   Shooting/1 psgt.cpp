#include <algorithm>
#include <cstdio>
#include <cstring>
#include <utility>
#include <vector>
#define fi first
#define se second

#define L ch][0
#define R ch][1
#define mid (l + r) / 2
typedef std::pair<int, int> pii;
const int M = 6e6 + 66, N = 2e5 + 52;
int ch[M][2], s[M], nc;
int cl(int x) { return (++nc)[s] = x[s], nc[L] = x[L], nc[R] = x[R], nc; }
void upd(int x, int l, int r, int i) {
	if (x[s]++, l == r) return;
	if (i <= mid) return upd(x[L] = cl(x[L]), l, mid, i);
	upd(x[R] = cl(x[R]), mid + 1, r, i);
}
int qry(int x1, int x2, int l, int r, int k) {
	if (l == r) return l;
	if (k <= x2[L][s] - x1[L][s]) return qry(x1[L], x2[L], l, mid, k);
	return qry(x1[R], x2[R], mid + 1, r, k - (x2[L][s] - x1[L][s]));
}

int n, m, x, l[N], r[N], z[N], ans[N], rt[N];
pii rec[N];
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d%d%d", l + i, r + i, z + i);
	for (int i = 1; i <= m; i++) scanf("%d", &x), rec[i] = {x, i};
	std::sort(rec + 1, rec + m + 1);
	for (int i = 1; i <= m; i++) {
		upd(i[rt] = cl((i - 1)[rt]), 1, m, rec[i].se);
	}
	for (int i = 1; i <= n; i++) {
		int ll = std::lower_bound(rec + 1, rec + m + 1, pii(i[l], 0)) - rec;
		int rr = std::upper_bound(rec + 1, rec + m + 1, pii(i[r], 1e9)) - rec - 1;
		if (rr - ll + 1 < i[z]) continue;
		qry((ll - 1)[rt], rr[rt], 1, m, i[z])[ans]++;
	}
	for (int i = 1; i <= m; i++) printf("%d\n", i[ans]);
}