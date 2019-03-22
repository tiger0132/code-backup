#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 1e5 + 51, M = 2e5 + 52;

int k, r[M];
void add(int i, int x) {
	for (; i <= k; i += i & -i) r[i] += x;
}
int query(int i) {
	int ret = 0;
	for (; i; i -= i & -i) ret += r[i];
	return ret;
}

int n$, ans[N], id[N], c$[N], q[N], a[N], b[N], c[N];
void cdq(int *p, int n) {
	if (n == 1) return;
	int m = n >> 1, top = 0, p1 = 0, p2 = m;
	cdq(p, m);
	cdq(p + m, n - m);
	memcpy(q, p, n << 2);
	while (p1 < m && p2 < n) {
		int x = q[p1], y = q[p2];
		if (b[x] <= b[y])
			add(c[p[top++] = x], c$[x]), p1++;
		else
			ans[y] += query(c[p[top++] = y]), p2++;
	}
	for (; p2 < n; p2++) ans[q[p2]] += query(c[q[p2]]);
	memcpy(p + top, q + p1, (m - p1) << 2);
	for (int i = 0; i < p1; i++) add(c[q[i]], -c$[q[i]]);
}

int n, out[N];
int main() {
	scanf("%d%d", &n, &k);
	for (int i = 0; i < n; i++) scanf("%d%d%d", a + i, b + i, c + i), id[i] = i;
	std::sort(id, id + n, [](int x, int y) {
		return a[x] < a[y] || (a[x] == a[y] && b[x] < b[y]) || (a[x] == a[y] && b[x] == b[y] && c[x] < c[y]);
	});
	for (int i = 1; i < n; i++) {
		int x = id[i], y = id[n$];
		c$[y]++;
		if (a[x] != a[y] || b[x] != b[y] || c[x] != c[y]) id[++n$] = x;
	}
	c$[id[n$++]]++;
	cdq(id, n$);
	for (int i = 0; i < n$; i++) out[ans[id[i]] + c$[id[i]] - 1] += c$[id[i]];
	for (int i = 0; i < n; i++) printf("%d\n", out[i]);
}