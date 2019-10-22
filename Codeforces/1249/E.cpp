#include <algorithm>
#include <cstdio>
#include <cstring>
#define int long long

const int N = 2e5 + 52;

int n, mn, c, a[N], b[N], ans[N];
signed main() {
	scanf("%lld%lld", &n, &c);
	for (int i = 2; i <= n; i++) scanf("%lld", a + i);
	for (int i = 2; i <= n; i++) scanf("%lld", b + i);
	printf("0 ");
	for (int i = 2; i <= n; i++) {
		ans[i] = std::min(ans[i - 1] + a[i], mn + b[i] + c);
		mn = std::min(mn + b[i], ans[i]);
		printf("%lld ", ans[i]);
	}
}