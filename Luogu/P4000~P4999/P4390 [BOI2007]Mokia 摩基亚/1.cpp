#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 3e5 + 53, M = 3e6 + 63;

int k, r[M];
void add(int i, int x) {
	for (; i <= k; i += i & -i) r[i] += x;
}
void cl(int i) {
	for (; i <= k; i += i & -i) r[i] = 0;
}
int query(int i) {
	int ret = 0;
	for (; i; i -= i & -i) ret += r[i];
	return ret;
}

int n$, ans[N], id[N], q[N], a[N], b[N], c[N], d[N], f[N];
void cdq(int *p, int n) {
	if (n == 1) return;
	int m = (n + 1) >> 1, top = 0, p1 = 0, p2 = m;
	cdq(p, m);
	cdq(p + m, n - m);
	memcpy(q, p, n << 2);
	while (p1 < m && p2 < n) {
		int x = q[p1], y = q[p2];
		if (b[x] <= b[y]) {
			p[top++] = x, p1++;
			if (!f[x]) add(c[x], d[x]);
		} else {
			p[top++] = y, p2++;
			if (f[y]) ans[y] += query(c[y]);
		}
	}
	while (p1 < m) {
		if (!f[q[p1]]) add(c[q[p1]], d[q[p1]]);
		p[top++] = q[p1++];
	}
	while (p2 < n) {
		if (f[q[p2]]) ans[q[p2]] += query(c[q[p2]]);
		p[top++] = q[p2++];
	}
	for (int i = 0; i < p1; i++)
		if (!f[q[i]]) cl(c[q[i]]);
}

int s, n, op, x, y, z, w;
int main() {
	scanf("%d%d", &s, &k), k++;
	while (scanf("%d", &op), op != 3) {
		scanf("%d%d%d", &x, &y, &z);
		if (op == 2) {
			scanf("%d", &w);
			z++, w++;
			id[n] = a[n] = n, b[n] = z, c[n] = w, d[n] = 0, f[n] = 1, n++;
			id[n] = a[n] = n, b[n] = x, c[n] = w, d[n] = 0, f[n] = 1, n++;
			id[n] = a[n] = n, b[n] = z, c[n] = y, d[n] = 0, f[n] = 1, n++;
			id[n] = a[n] = n, b[n] = x, c[n] = y, d[n] = 0, f[n] = 1, n++;
		} else {
			x++, y++;
			id[n] = a[n] = n, b[n] = x, c[n] = y, d[n] = z, f[n] = 0, n++;
		}
	}
	cdq(id, n);
	std::sort(id, id + n, [](int x, int y) { return a[x] < a[y]; });
	for (int i = 0; i < n; i++) {
		if (f[id[i]]) {
			if (i + 3 >= n) abort();
			printf("%d\n", ans[id[i]] - ans[id[i + 1]] - ans[id[i + 2]] + ans[id[i + 3]] +
							   s * (b[id[i]] - b[id[i + 1]]) * (c[id[i]] - c[id[i + 2]]));
			i += 3;
		}
	}
}