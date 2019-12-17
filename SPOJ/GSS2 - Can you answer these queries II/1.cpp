#include <algorithm>
#include <cstdio>
#include <cstring>
#include <map>
#include <utility>
#include <vector>
#define pos first
#define id second
#define L ch][0
#define R ch][1
#define mid (l + r) / 2
#define $(x) (x ? x : x = ++nc)

typedef long long ll;
typedef std::pair<int, int> pii;
const int N = 4e5 + 54;
struct _ {
	ll mx, hmx;
	_ operator+(const _& r) const { return {std::max(mx, r.mx), std::max(hmx, r.hmx)}; }
} tag[N];
int ch[N][2], nc;
ll t[N], ht[N];
void up(int x) { x[tag] = x[L][tag] + x[R][tag]; }
void put(int x, int v, int hv) {
	x[tag].hmx = std::max(x[tag].hmx, x[tag].mx + hv);
	x[ht] = std::max(x[ht], x[t] + hv);
	x[tag].mx += v, x[t] += v;
}
void pd(int x) { put($(x[L]), x[t], x[ht]), put($(x[R]), x[t], x[ht]), x[t] = x[ht] = 0; }
void upd(int x, int l, int r, int ql, int qr, int v) {
	if (ql <= l && r <= qr) {
		x[tag].mx += v;
		x[tag].hmx = std::max(x[tag].hmx, x[tag].mx);
		x[t] += v;
		x[ht] = std::max(x[ht], x[t]);
		return;
	}
	pd(x);
	if (ql <= mid) upd($(x[L]), l, mid, ql, qr, v);
	if (mid < qr) upd($(x[R]), mid + 1, r, ql, qr, v);
	up(x);
}
_ qry(int x, int l, int r, int ql, int qr) {
	if (ql <= l && r <= qr) return x[tag];
	pd(x);
	if (qr <= mid) return qry($(x[L]), l, mid, ql, qr);
	if (mid < ql) return qry($(x[R]), mid + 1, r, ql, qr);
	_ ret = qry($(x[L]), l, mid, ql, qr);
	return ret + qry($(x[R]), mid + 1, r, ql, qr);
}

int n, x, y, q, a[N], ans[N];
std::vector<pii> queries[N];
std::map<int, int> pre;
int main() {
	scanf("%d", &n), nc = 1;
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	scanf("%d", &q);
	for (int i = 1; i <= q; i++) {
		scanf("%d%d", &x, &y);
		queries[y].push_back(pii(x, i));
	}
	for (int i = 1; i <= n; i++) {
		upd(1, 1, n, pre[a[i]] + 1, i, a[i]);
		for (auto j : queries[i]) ans[j.id] = qry(1, 1, n, j.pos, i).hmx;
		pre[a[i]] = i;
	}
	for (int i = 1; i <= q; i++) printf("%d\n", ans[i]);
}