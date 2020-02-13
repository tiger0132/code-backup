#include <algorithm>
#include <cstdio>
#include <cstring>
#define int long long

const int N = 1e5 + 51, M = 77;

int n, m, sum, ans, a[N];
int lb(int x) { return x & -x; }
signed main() {
	for (scanf("%*d"); ~scanf("%lld%lld", &n, &m);) {
		sum = ans = 0;
		for (int i = 1; i <= m; i++) scanf("%lld", a + i);
		std::sort(a + 1, a + m + 1);
		for (int i = 1; i <= m; i++) {
			int t = n & (a[i] - 1);
			if (t) {
				ans += __builtin_ffs(a[i]) - __builtin_ffs(t);
				n -= t;
			}
			sum += a[i] - t;
			while (n && sum >= lb(n)) sum -= lb(n), n -= lb(n);
		}
		if (n > sum)
			puts("-1");
		else
			printf("%lld\n", ans);
	}
}