#include <algorithm>
#include <cstdio>
#include <cstring>

typedef long long ll;
const int N = 1e5 + 51;

namespace $ {
int n;
ll _[N], __[N];
void add(ll *a, int i, int x) {
	for (; i <= n; i += i & -i) a[i] += x;
}
ll query(ll *a, int i) {
	int ret = 0;
	for (; i; i -= i & -i) ret += a[i];
	return ret;
}
void add(int l, int r, int x) {
	add(_, l, x), add(_, r + 1, -x);
	add(__, l, x * (l - 1)), add(__, r + 1, -x * r);
}
ll query(int l, int r) {
	return query(_, r) * r - query(__, r) - query(_, l - 1) * (l - 1) + query(__, l - 1);
}
}  // namespace $

namespace QwQ {
int src_n, op[N], a[N], b[N], c[N], *ans[N], cur[N], q1[N], q2[N];
void OwO(int *p, int n, ll l, ll r) {
	if (l == r) {
		for (int i = 0; i < n; i++)
			if (op[p[i]]) *ans[p[i]] = src_n - l + 1;
		return;
	}
	ll m = (l + r) >> 1;
	int p1 = 0, p2 = 0;
	for (int i = 0; i < n; i++) {
		if (!op[p[i]]) {
			if (c[p[i]] <= m)
				$::add(a[p[i]], b[p[i]], 1), q1[p1++] = p[i];
			else
				q2[p2++] = p[i];
		} else {
			ll tmp = $::query(a[p[i]], b[p[i]]);
			if (c[p[i]] <= tmp)
				q1[p1++] = p[i];
			else
				q2[p2++] = p[i], c[p[i]] -= tmp;
		}
	}
	for (int i = 0; i < p1; i++)
		if (!op[q1[i]]) $::add(a[q1[i]], b[q1[i]], -1);
	memcpy(p, q1, p1 << 2);
	memcpy(p + p1, q2, p2 << 2);
	OwO(p, p1, l, m);
	OwO(p + p1, p2, m + 1, r);
}
};  // namespace QwQ

int n, m, x, y, z, n$, id[N], ans[N];
int main() {
	scanf("%d%d", &n, &m), $::n = n, QwQ::src_n = n;
	for (int i = 0; i < m; i++) {
		scanf("%d%d%d%d", QwQ::op + i, &x, &y, &z);
		if (--QwQ::op[i]) {
			QwQ::a[i] = x, QwQ::b[i] = y, QwQ::c[i] = z;
			QwQ::ans[i] = ans + ++n$;
		} else {
			QwQ::a[i] = x, QwQ::b[i] = y, QwQ::c[i] = n - z + 1;
		}
		id[i] = i;
	}
	QwQ::OwO(id, m, 1, n);
	for (int i = 1; i <= n$; i++) printf("%d\n", ans[i]);
}