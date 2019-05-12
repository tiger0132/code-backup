#include <algorithm>
#include <cmath>
#include <cstdio>
#include <map>
#include <set>

const int M = 1e6 + 61, N = 1e8 + 81;

int a[M], b[M];
long long ans;
int n, m, cnt;
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", a + i), ans += 1ll * m * a[i];
	std::sort(a + 1, a + n + 1);
	// std::sort(b + 1, b + n + 1);
	for (int i = 1; i <= m; i++) {
		scanf("%d", b + i);
		if (b[i] != a[n]) {
			if (++cnt < m)
				ans += std::max(0, b[i] - a[n]);
			else
				ans += std::max(0, b[i] - a[n - 1]);
		}
	}
	if (a[n] > b[1]) return puts("-1"), 0;
	printf("%lld", ans);
}