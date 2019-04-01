#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 1e5 + 51, M = 1e5;
struct BIT {
	int n, r[N];
	void update(int i, int x) {
		for (; i <= M; i += i & -i) r[i] = std::max(r[i], x);
	}
	void reset(int i) {
		for (; i <= M; i += i & -i) r[i] = 0;
	}
	int query(int i) {
		int ret = 0;
		for (; i; i -= i & -i) ret = std::max(ret, r[i]);
		return ret;
	}
} bit;

int a[N], l[N], r[N], dp[N];
void cdq(int *p, int n) {
	if (n == 1) return;
	int m = n / 2, p1 = 0, p2 = m;
	cdq(p, m);
	std::sort(p, p + m, [](int x, int y) { return a[x] < a[y]; });
	std::sort(p + m, p + n, [](int x, int y) { return l[x] < l[y]; });
	while (p1 < m && p2 < n) {
		int x = p[p1], y = p[p2];
		if (a[x] <= l[y])
			bit.update(r[x], dp[x]), p1++;
		else
			dp[y] = std::max(dp[y], bit.query(a[y]) + 1), p2++;
	}
	for (; p2 < n; p2++) dp[p[p2]] = std::max(dp[p[p2]], bit.query(a[p[p2]]) + 1);
	for (int i = 0; i < p1; i++) bit.reset(r[p[i]]);
	std::sort(p, p + n, [](int x, int y) { return x < y; });
	cdq(p + m, n - m);
}

int n, m, x, y, id[N];
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++) scanf("%d", a + i), l[i] = r[i] = a[i], dp[i] = 1, id[i] = i;
	while (m--) {
		scanf("%d%d", &x, &y), x--;
		l[x] = std::min(l[x], y), r[x] = std::max(r[x], y);
	}
	cdq(id, n);
	printf("%d\n", *std::max_element(dp, dp + n));
}