#include <algorithm>
#include <cstdio>
#include <cstring>

typedef long long ll;
const int N = 6e5 + 56, M = 6e5 + 56;
struct _ {
	int x, y, op;
} b[N];
struct inp {
	int x, r, q;
} a[N];

int k, tr[M];
void upd(int i, int x) {
	for (i += 10 * k; i < M; i += i & -i) tr[i] += x;
}
int qry(int i) {
	int r = 0;
	for (i += 10 * k; i > 0; i -= i & -i) r += tr[i];
	return r;
}

ll ans;
void cdq(_* p, int n) {
	if (n == 1) return;
	int m = n / 2, px = 0;
	cdq(p, m), cdq(p + m, n - m);
	for (int i = m; i < n; i++) {
		for (; p[px].x <= p[i].x && px < m; px++)
			if (!p[px].op) upd(p[px].y, 1);
		if (p[i].op) ans += (p[i].op == 1 ? 1 : -1) * qry(p[i].y);
	}
	while (px--)
		if (!p[px].op) upd(p[px].y, -1);
	std::inplace_merge(p, p + m, p + n, [](const _& x, const _& y) {
		return x.x < y.x || (x.x == y.x && (x.y < y.y || x.op < y.op));
	});
}

int n, x, r, q1, q2, cnt, tmp[N], top;
int id(int ze) { return std::lower_bound(tmp, tmp + top, ze) - tmp; }
int main() {
	scanf("%d%d", &n, &k);
	for (int i = 0; i < n; i++) {
		scanf("%d%d%d", &a[i].x, &a[i].r, &a[i].q);
		tmp[top++] = a[i].q;
		tmp[top++] = a[i].q + k;
		tmp[top++] = a[i].q - k - 1;
	}
	std::sort(a, a + n, [](const inp& x, const inp& y) { return x.r > y.r; });
	std::sort(tmp, tmp + top);
	for (int i = 0; i < n; i++) {
		x = a[i].x, r = a[i].r, q1 = id(a[i].q + k), q2 = id(a[i].q - k - 1);
		b[cnt++] = (_){x + r, q1, 1};
		b[cnt++] = (_){x + r, q2, 2};
		b[cnt++] = (_){x - r - 1, q1, 2};
		b[cnt++] = (_){x - r - 1, q2, 1};
		b[cnt++] = (_){x, id(a[i].q), 0};
	}
	cdq(b, cnt);
	printf("%lld", ans);
}