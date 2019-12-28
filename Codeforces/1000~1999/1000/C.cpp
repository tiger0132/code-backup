#include <algorithm>
#include <cstdio>
#include <cstring>
#define int long long

const int N = 4e5 + 54;

int n, m, x, a[N], b[N], s[N], c[N];
signed main() {
	scanf("%lld", &n), n *= 2;
	for (int i = 1; i <= n; i++) scanf("%lld", a + i), b[i] = a[i] += !(i % 2);
	std::sort(b + 1, b + n + 1);
	m = std::unique(b + 1, b + n + 1) - b - 1;
	for (int i = 1; i <= n; i++) {
		a[i] = std::lower_bound(b + 1, b + m + 1, a[i]) - b;
		s[a[i]] += i % 2 ? 1 : -1;
	}
	for (int i = 1; i <= m; i++) c[x] += b[i] - b[i - 1], x += s[i];
	for (int i = 1; i <= n / 2; i++) printf("%lld ", c[i]);
}