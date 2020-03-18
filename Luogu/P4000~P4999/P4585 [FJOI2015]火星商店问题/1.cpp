#include <algorithm>
#include <cstring>
#include <cstdio>
#include <vector>

const int N = 4e5 + 54, M = 4e6 + 64, K = 1 << 17;

namespace T {
#define L ch][0
#define R ch][1
#define _(x) x = cl(x)
#define $(x) (x, 0)
int ch[M][2], s[M], nc;
int cl(int x) { return (++nc)[L] = x[L], nc[R] = x[R], nc[s] = x[s], nc; }
void ins(int x, int v, int k = K) { x[s]++, k&& $(ins(_(x[ch][!!(v & k)]), v, k / 2)); }
int qry(int x1, int x2, int v, int k = K) {
	int t = !(k & v);
	if (!k) return 0;
	return x1[ch][t][s] < x2[ch][t][s] ? qry(x1[ch][t], x2[ch][t], v, k / 2) | k
									   : qry(x1[ch][!t], x2[ch][!t], v, k / 2);
}
#undef L
#undef R
}  // namespace T

int ans[N];

namespace S {
struct _upd {
	int s, v;
} p[N];
struct _qry {
	int l, r, x;
} q[N];

#define L (x << 1)
#define R ((x << 1) | 1)
#define mid (l + r) / 2
std::vector<int> tr_p[N], tr_q[N];
int ql, qr;
void upd(int x, int l, int r, int y) {  // ql
	x[tr_p].push_back(y);
	if (l == r) return;
	if (ql <= mid) return upd(L, l, mid, y);
	upd(R, mid + 1, r, y);
}
void qry(int x, int l, int r, int y) {  // [ql, qr]
	if (ql <= l && r <= qr) return x[tr_q].push_back(y);
	if (ql <= mid) qry(L, l, mid, y);
	if (mid < qr) qry(R, mid + 1, r, y);
}

int st[N], rt[N], top;
void calc(int x, int l, int r) {
	std::sort(x[tr_p].begin(), x[tr_p].end(),
			  [](int a, int b) { return a[p].s < b[p].s; });
	top = T::nc = 0;
	for (int i : x[tr_p]) {
		st[++top] = i[p].s;
		T::ins(rt[top] = T::cl(rt[top - 1]), i[p].v);
	}
	for (int i : x[tr_q]) {
		int ll = std::lower_bound(st + 1, st + top + 1, i[q].l) - st - 1;
		int rr = std::upper_bound(st + 1, st + top + 1, i[q].r) - st - 1;
		i[ans] = std::max(i[ans], T::qry(rt[ll], rt[rr], i[q].x));
	}
	if (l == r) return;
	calc(L, l, mid), calc(R, mid + 1, r);
}
}  // namespace S

int n, m, op, x, y, z, w, c1, c0;
int rt[N], qry_l[N], qry_r[N];
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", &x), T::ins(rt[i] = T::cl(rt[i - 1]), x);
	for (int i = 1; i <= m; i++) {
		scanf("%d", &op);
		if (op) {
			scanf("%d%d%d%d", &x, &y, &z, &w);
			S::q[++c1] = {x, y, z};
			qry_l[c1] = std::max(1, c0 - w + 1), qry_r[c1] = c0;
			ans[c1] = T::qry(rt[x - 1], rt[y], z);
		} else {
			scanf("%d%d", &x, &y);
			S::p[++c0] = {x, y};
		}
	}
	for (int i = 1; i <= c0; i++) {
		S::ql = i;
		S::upd(1, 1, c0, i);
	}
	for (int i = 1; i <= c1; i++) {
		S::ql = qry_l[i], S::qr = qry_r[i];
		if (S::ql <= S::qr) S::qry(1, 1, c0, i);
	}
	S::calc(1, 1, c0);
	for (int i = 1; i <= c1; i++) printf("%d\n", i[ans]);
}