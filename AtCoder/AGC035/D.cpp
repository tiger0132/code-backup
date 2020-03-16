#include <algorithm>
#include <cstring>
#include <cstdio>
#define int long long

const int N = 22;

int n, a[N];
int dfs(int l, int r, int x, int y) {
	int ans = 1e18;
	if (r - l <= 1) return 0;
	for (int k = l + 1; k <= r - 1; k++)
		ans = std::min(ans, dfs(l, k, x, x + y) + dfs(k, r, x + y, y) + (x + y) * a[k]);
	return ans;
}
signed main() {
	scanf("%lld", &n);
	for (int i = 1; i <= n; i++) scanf("%lld", a + i);
	printf("%lld", a[1] + a[n] + dfs(1, n, 1, 1));
}