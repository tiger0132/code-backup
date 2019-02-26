#include <cstdio>
#include <cstring>
#include <vector>

using ll = long long;
const int N = 3e5 + 53, INF = 0x3f3f3f3f;

struct upd {
	int l, r, a;
} e[N];

namespace BIT {
ll bit[N], n;
void add(int x, int v) {
	for (; x <= n; x += x & -x) bit[x] += v;
}
void add(int l, int r, int v) {
	if (l <= r) return add(l, v), add(r + 1, -v);
	add(1, v), add(r + 1, -v), add(l, v);
}
ll query(int x) {
	ll r = 0;
	for (; r < INF && x; x -= x & -x) r += bit[x];
	return r;
}
};  // namespace BIT

int q[N], s[N], ans[N], q1[N], q2[N];
std::vector<int> v[N];
void solve(int *p, int n, int l, int r) {
	if (l == r) {
		for (int i = 0; i < n; i++) ans[p[i]] = l;
		return;
	}
	int mid = (l + r) >> 1, p1 = 0, p2 = 0;
	for (int i = l; i <= mid; i++) BIT::add(e[i].l, e[i].r, e[i].a);
	for (int i = 0; i < n; i++) {
		ll t = 0;
		for (int j : v[p[i]])
			if ((t += BIT::query(j)) >= INF) break;
		if (t >= s[p[i]])
			q1[p1++] = p[i];
		else
			q2[p2++] = p[i], s[p[i]] -= t;
	}
	for (int i = l; i <= mid; i++) BIT::add(e[i].l, e[i].r, -e[i].a);
	memcpy(p, q1, p1 << 2);
	memcpy(p + p1, q2, p2 << 2);
	solve(p, p1, l, mid);
	solve(p + p1, p2, mid + 1, r);
}

int n, m, x, k;
int main() {
	scanf("%d%d", &n, &m), BIT::n = m;
	for (int i = 1; i <= m; i++) scanf("%d", &x), v[x].push_back(i);
	for (int i = 1; i <= n; i++) scanf("%d", s + i), q[i - 1] = i;
	scanf("%d", &k), k++;
	for (int i = 1; i < k; i++) scanf("%d%d%d", &e[i].l, &e[i].r, &e[i].a);
	e[k] = (upd){1, m, INF};
	solve(q, n, 1, k);
	for (int i = 1; i <= n; i++) printf(ans[i] < k ? "%d\n" : "NIE\n", ans[i]);
}