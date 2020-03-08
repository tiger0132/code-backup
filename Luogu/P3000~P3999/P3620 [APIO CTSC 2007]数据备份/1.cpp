#include <algorithm>
#include <cstdio>
#include <cstring>
#include <utility>
#define mid (l + r) / 2
#define int long long

typedef std::pair<int, int> pii;
const int N = 1e5 + 51, INF = 1e18;

int n, k, a[N];
pii dp[N][2];
bool check(int ofs) {
	dp[1][0] = {0, 0}, dp[1][1] = {INF, 0};
	for (int i = 2; i <= n; i++) {
		dp[i][0] = std::min(dp[i - 1][0], dp[i - 1][1]);
		dp[i][1] = {dp[i - 1][0].first + a[i] - a[i - 1] - ofs, dp[i - 1][0].second + 1};
	}
	return std::min(dp[n][0], dp[n][1]).second <= k;
}

int l, r;
signed main() {
	scanf("%lld%lld", &n, &k);
	for (int i = 1; i <= n; i++) scanf("%lld", a + i);
	for (r = 2e9; l <= r;)
		if (check(mid))
			l = mid + 1;
		else
			r = mid - 1;
	check(r);
	printf("%lld", std::min(dp[n][0], dp[n][1]).first + r * k);
}