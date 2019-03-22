#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 5e2 + 25, M = 4e5 + 54;

struct BIT {
	int n, r[N][N];
	void update(int x, int y, int z) {
		for (int i = x; i <= n; i += i & -i)
			for (int j = y; j <= n; j += j & -j) r[i][j] += z;
	}
	int query(int x, int y) {
		int ret = 0;
		for (int i = x; i; i -= i & -i)
			for (int j = y; j; j -= j & -j) ret += r[i][j];
		return ret;
	}
	int query(int x1, int y1, int x2, int y2) {
		return query(x2, y2) - query(x1 - 1, y2) - query(x2, y1 - 1) + query(x1 - 1, y1 - 1);
	}
} _$;

struct upd {
	int x, y, z;
} a[M];
struct qry {
	int x1, y1, x2, y2, k, *ans;
} rua[M], *b[M];

namespace _ {
qry *q1[M], *q2[M];
int op[M];
void solve(qry** p, int n, upd* q, int m) {
	if (m == 1) {
		for (int i = 0; i < n; i++) *p[i]->ans = q->z;
		return;
	}
	int mid = m >> 1, p1 = 0, p2 = 0;
	for (int i = 0; i < mid; i++) _$.update(q[i].x, q[i].y, 1);
	for (int i = 0; i < n; i++) {
		int t = _$.query(p[i]->x1, p[i]->y1, p[i]->x2, p[i]->y2);
		if (p[i]->k <= t)
			q1[p1++] = p[i];
		else
			p[i]->k -= t, q2[p2++] = p[i];
	}
	memcpy(p, q1, p1 * sizeof(qry*));
	memcpy(p + p1, q2, p2 * sizeof(qry*));
	for (int i = 0; i < mid; i++) _$.update(q[i].x, q[i].y, -1);
	if (p1) solve(p, p1, q, mid);
	if (p2) solve(p + p1, p2, q + mid, m - mid);
}
};  // namespace _

int n, m, n$, x, ans[M];
int main() {
	scanf("%d%d", &n, &m), _$.n = n;
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			scanf("%d", &x), a[n$++] = (upd){i, j, x};
		}
	}
	std::sort(a, a + n$, [](const upd& x, const upd& y) { return x.z < y.z; });
	for (int i = 0; i < M; i++) b[i] = rua + i;
	for (int i = 0; i < m; i++) {
		scanf("%d%d%d%d%d", &b[i]->x1, &b[i]->y1, &b[i]->x2, &b[i]->y2, &b[i]->k);
		b[i]->ans = ans + i;
	}
	_::solve(b, m, a, n$);
	for (int i = 0; i < m; i++) printf("%d\n", ans[i]);
}