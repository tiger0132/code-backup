#include <algorithm>
#include <cstring>
#include <cstdio>
#define int long long

const int N = 1e5 + 51;

int dp[N], f[N], s[N];
double slope(int x, int y) {
	return 1. * (dp[x] + s[x] * s[x] - dp[y] - s[y] * s[y]) / (s[x] - s[y]);
}

int n, m, q[N];
bool check(int k) {
	int l = 0, r = 0;
	for (int i = 1; i <= n; i++) {
		while (l < r && slope(q[l], q[l + 1]) < 2 * s[i] + 2) l++;
		dp[i] = dp[q[l]] + (s[i] - s[q[l]] + 1) * (s[i] - s[q[l]] + 1) + k;
		f[i] = f[q[l]] + 1;
		while (l < r && slope(q[r - 1], q[r]) > slope(q[r], i)) r--;
		q[++r] = i;
	}
	return f[n] <= m;
}

int l, r;
signed main() {
	scanf("%lld%lld", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%lld", s + i), s[i] += s[i - 1];
#define mid (l + r) / 2
	for (l = 0, r = 1e16; l <= r;)
		if (check(mid))
			r = mid - 1;
		else
			l = mid + 1;
	check(l);
	printf("%lld", dp[n] - l * m);
}