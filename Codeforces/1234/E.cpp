#include <algorithm>
#include <cstdio>
#include <cstring>
#define int long long

const int N = 2e5 + 52;

int n, m, a[N], sl[N], sr[N], sk[N], r[N], ans;
signed main() {
	scanf("%lld%lld", &n, &m);
	for (int i = 1; i <= m; i++) {
		scanf("%lld", a + i);
		if (i > 1) {
			if (a[i - 1] == a[i]) continue;
			int x = std::min(a[i], a[i - 1]), y = std::max(a[i], a[i - 1]);
			sk[x + 1]++, sk[y]--;
			ans += y - x;
			if (a[i - 1] < a[i]) {
				if (a[i - 1] == 1)
					sl[a[i]] += 2 - a[i];
				else {
					sl[a[i]] += 2 * a[i - 1] - a[i];
					sr[a[i - 1]] += a[i - 1] - 1;
					// a[i] == a[i-1]
				}
			} else {
				if (a[i] == 1)
					sl[a[i - 1]] += 2 - a[i - 1];
				else {
					sr[a[i]] += a[i] - 1;
					sl[a[i - 1]] += 2 * a[i] - a[i - 1];
				}
			}
		}
	}
	for (int i = 1; i <= n; i++) sk[i] += sk[i - 1];
	printf("%lld ", ans);
	for (int i = 2; i <= n; i++) {
		printf("%lld ", ans - sk[i] + sl[i] + sr[i]);
	}
}