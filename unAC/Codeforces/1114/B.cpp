#include <algorithm>
#include <cstdio>
#define int long long

const int N = 2e5 + 52;
int n, m, k, ans;

struct node {
	int x, y;
	bool operator<(const node& rhs) const { return x > rhs.x; }
} a[N];

int s[N], f[N], c1, c2, x;

signed main() {
	scanf("%lld%lld%lld", &n, &m, &k);
	for (int i = 1; i <= n; i++) scanf("%lld", &a[i].x), s[i] = a[i].x, a[i].y = i;
	std::sort(a + 1, a + n + 1);
	for (int i = 1; i <= m * k; i++) {
		ans += a[i].x;
		f[a[i].y] = 1;
	}
	printf("%lld\n", ans);
	for (int i = 1; i <= n; i++) {
		if (x == k - 1) break;
		c2++;
		if (f[i] || s[a[m * k].y] == s[i]) c1++;
		if (c1 >= m && c2 >= m) x++, printf("%lld ", i), c1 = c2 = 0;
	}
}