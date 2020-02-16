#include <algorithm>
#include <cstdio>
#include <cstring>

typedef long long ll;
const int N = 2e5 + 52;
struct rec {
	int a, b, c;
} a[N];

int n, tr[N];
ll sum;
void add(int i, int x) {
	for (sum += x; i <= n; i += i & -i) tr[i] += x;
}
int qry(int i) {
	int r = 0;
	for (i = std::min(n, i); i > 0; i -= i & -i) r += tr[i];
	return r;
}

ll ans;
int k;
void cdq(rec* p, int n) {
	if (n == 1) return;
	int m = n / 2, px = 0;
	cdq(p, m), cdq(p + m, n - m);
	for (int i = m; i < n; i++) {
		for (; p[px].b < p[i].b && px < m; px++) add(p[px].c, 1);
		ans += sum - qry(p[i].c + k) + qry(p[i].c - k - 1);
	}
	while (px--) add(p[px].c, -1);
	std::inplace_merge(p, p + m, p + n, [](const rec& x, const rec& y) {
		return x.b < y.b || (x.b == y.b && x.c < y.c);
	});
}

int x;
int main() {
	scanf("%d%d", &n, &k);
	for (int i = 0; i < n; i++) scanf("%d", &x), a[x - 1].a = i, a[i].c = i + 1;
	for (int i = 0; i < n; i++) scanf("%d", &x), a[x - 1].b = n - i;
	std::sort(a, a + n, [](const rec& x, const rec& y) {
		return x.a < y.a || (x.a == y.a && (x.b < y.b || (x.b == y.b && x.c < y.c)));
	});
	cdq(a, n);
	printf("%lld", ans);
}