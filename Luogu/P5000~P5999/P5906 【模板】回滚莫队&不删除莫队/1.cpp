#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <stack>

const int N = 2e5 + 52, sz = 256;
struct qry {
	int l, r, *ans;
	inline bool operator<(const qry &rhs) const {
		return l / sz != rhs.l / sz ? l < rhs.l : r < rhs.r;
	}
} q[N];

struct rec {
	int *p, x;
} st[N << 4];
int top;
inline void set(int &x, int y) { st[++top] = {&x, x}, x = y; }
inline void save(int &x) { st[++top] = {&x, x}; }
inline void rollback() {
	for (; top; top--) *st[top].p = st[top].x;
}

int a[N], mx[N], mn[N], occ[N], la, origLa;
inline void add(int i) {
	a[i][mx] = std::max(a[i][mx], i);
	a[i][mn] = std::min(a[i][mn], i);
	la = std::max(la, a[i][mx] - a[i][mn]);
}
inline void addL(int i) {
	if (!a[i][occ]) {
		set(a[i][occ], 1);
		save(a[i][mx]);
		save(a[i][mn]);
	}
	a[i][mx] = std::max(a[i][mx], i);
	a[i][mn] = std::min(a[i][mn], i);
	la = std::max(la, a[i][mx] - a[i][mn]);
}

int n, m, l, r, b[N], ans[N];
int mx2[N], mn2[N], la2;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", a + i), b[i] = a[i];
	std::sort(b + 1, b + n + 1);
	for (int i = 1; i <= n; i++) a[i] = std::lower_bound(b + 1, b + n + 1, a[i]) - b;
	scanf("%d", &m);
	for (int i = 1; i <= m; i++) {
		scanf("%d%d", &q[i].l, &q[i].r), q[i].ans = ans + i;
	}
	std::sort(q + 1, q + m + 1), q[0].l = -1e9;

	memset(mn, 0x3f, sizeof mn);
	memset(mn2, 0x3f, sizeof mn2);
	for (int i = 1; i <= m; i++) {
		if (q[i].l / sz != q[i - 1].l / sz) {
			l = (q[i].l / sz + 1) * sz, r = l - 1, la = 0;
			memset(mx, 0, sizeof mx);
			memset(mn, 0x3f, sizeof mn);
		}
		if (q[i].l / sz == q[i].r / sz) {
			la2 = 0;
			for (int j = q[i].l; j <= q[i].r; j++) {
				a[j][mx2] = std::max(a[j][mx2], j);
				a[j][mn2] = std::min(a[j][mn2], j);
				la2 = std::max(la2, a[j][mx2] - a[j][mn2]);
			}
			for (int j = q[i].l; j <= q[i].r; j++) {
				a[j][mx2] = 0, a[j][mn2] = 0x3f3f3f3f;
			}
			*q[i].ans = la2, la2 = 0;
		} else {
			while (r < q[i].r) add(++r);
			origLa = la;
			while (q[i].l < l) addL(--l);
			*q[i].ans = la, la = origLa;
			l = (q[i].l / sz + 1) * sz, rollback();
		}
	}
	for (int i = 1; i <= m; i++) printf("%d\n", ans[i]);
}