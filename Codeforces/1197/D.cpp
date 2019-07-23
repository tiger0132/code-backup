#include <algorithm>
#include <cstdio>
#include <cstring>
#define int long long

const int N = 3e5 + 53;

int n, m, k, a[N], s[N];
int mx[111];
int solve(int l, int r) {
	int mid = (l + r) / 2, ans = 0;
	if (l == r) {
		memset(mx, 0, sizeof mx);
		mx[1] = a[l] - (1 / m) * k;
		return std::max(0ll, a[l] - k);
	}
	ans = std::max(ans, solve(l, mid));
	ans = std::max(ans, solve(mid + 1, r));
	for (int i = l; i <= mid; i++)
		for (int j = 0; j < m; j++) {
			int x = s[mid] - s[i - 1] - (mid - i + 1) / m * k;
			int y = (mid - i + 1) % m;
			ans = std::max(ans, x + mx[j] - (y + j + m - 1) / m * k);
		}
	memset(mx, 0, sizeof mx);
	for (int i = l; i <= r; i++) {
		int len = i - l + 1;
		mx[len % m] = std::max(mx[len % m], s[i] - s[l - 1] - len / m * k);
	}
	return ans;
}
signed main() {
	scanf("%lld%lld%lld", &n, &m, &k);
	for (int i = 1; i <= n; i++) scanf("%lld", a + i), s[i] = s[i - 1] + a[i];
	printf("%lld", solve(1, n));
}