#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
#define L ch][0
#define R ch][1
#define mid (l + r) / 2

typedef std::pair<int, int> pii;
const int N = 8e5 + 58;

struct tag {
	int mn, cnt;
	tag operator+(const tag &rhs) const {
		int x = std::min(mn, rhs.mn);
		return {x, (mn == x ? cnt : 0) + (rhs.mn == x ? rhs.cnt : 0)};
	}
} t[N];

int ch[N][2], add[N], nc, rt;
inline void up(int x) { x[t] = x[L][t] + x[R][t]; }
inline void put(int x, int y) { x[add] += y, x[t].mn += y; }
inline void pd(int x) { put(x[L], x[add]), put(x[R], x[add]), x[add] = 0; }
void build(int &x, int l, int r) {
	(x = ++nc)[t].cnt = r - l + 1;
	if (l < r) build(x[L], l, mid), build(x[R], mid + 1, r);
}
void upd(int x, int l, int r, int ql, int qr, int y) {
	if (ql <= l && r <= qr) return put(x, y);
	pd(x);
	if (ql <= mid) upd(x[L], l, mid, ql, qr, y);
	if (mid < qr) upd(x[R], mid + 1, r, ql, qr, y);
	up(x);
}
tag qry(int x, int l, int r, int ql, int qr) {
	if (ql <= l && r <= qr) return x[t];
	pd(x);
	if (qr <= mid) return qry(x[L], l, mid, ql, qr);
	if (mid < ql) return qry(x[R], mid + 1, r, ql, qr);
	return qry(x[L], l, mid, ql, qr) + qry(x[R], mid + 1, r, ql, qr);
}

int st1[N], st2[N], top1, top2;
std::vector<pii> v[N];
int n, q, a[N];
long long ans;
int main() {
	scanf("%d", &n);
	build(rt, 1, n);
	for (int i = 1, x, y; i <= n; i++) scanf("%d%d", &x, &y), a[x] = y;
	for (int i = 1; i <= n; i++) {
		while (top1 && a[st1[top1]] < a[i])
			upd(rt, 1, n, st1[top1 - 1] + 1, st1[top1], a[i] - a[st1[top1]]), top1--;
		st1[++top1] = i;
		while (top2 && a[st2[top2]] > a[i])
			upd(rt, 1, n, st2[top2 - 1] + 1, st2[top2], a[st2[top2]] - a[i]), top2--;
		st2[++top2] = i;

		upd(rt, 1, n, i, i, i);
		ans += qry(rt, 1, n, 1, i).cnt;
	}
	printf("%lld\n", ans);
}