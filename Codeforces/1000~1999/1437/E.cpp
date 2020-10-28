#include <algorithm>
#include <cstdio>
#include <cstring>
#include <functional>
#define int long long

const int N = 5e5 + 55;

int n, m, a[N], b[N], f[N], tmp[N];
int ans, cnt, lb, ub;
signed main() {
	scanf("%lld%lld", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%lld", a + i), a[i] -= i;
	for (int i = 1; i <= m; i++) {
		scanf("%lld", b + i), f[b[i]] = i;
		if (i > 1 && a[b[i - 1]] > a[b[i]]) return puts("-1"), 0;
	}
	lb = -1e12;
	ub = m ? a[b[1]] : 1e12;
	tmp[0] = -1e12;
	for (int i = 1; i <= n; i++) {
		if (f[i]) {
			ans += cnt, cnt = 0;
			lb = a[i], ub = a[b[f[i] + 1]];
			if (f[i] == m) ub = 1e12;
			continue;
		}
		if (a[i] < lb || ub < a[i]) continue;
		if (a[i] >= tmp[cnt])
			tmp[++cnt] = a[i];
		else
			*std::upper_bound(tmp + 1, tmp + cnt + 1, a[i]) = a[i];
	}
	printf("%lld\n", n - m - (ans + cnt));
}