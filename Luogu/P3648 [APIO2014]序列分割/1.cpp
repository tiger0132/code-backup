#include <algorithm>
#include <cstdio>
#include <cstring>
#define S(x) ((x) * (x))

using ll = long long;
const int N = 1e5 + 51, M = 2e2 + 22;

int n, k, l, r, q[N], pre[N][M];
ll s[N], dp[N], dp2[N];

inline double slope(int x, int y) {
	return s[x] == s[y] ? -1e18 : 1. * (dp2[x] - S(s[x]) - dp2[y] + S(s[y])) / (s[y] - s[x]);
}
int main() {
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++) scanf("%lld", s + i), s[i] += s[i - 1];
	for (int j = 1; j <= k; j++) {
		q[l = r = 0] = 0;
		for (int i = 1; i <= n; i++) {
			while (l < r && slope(q[l + 1], q[l]) <= s[i]) l++;
			dp[i] = dp2[q[l]] + s[q[l]] * (s[i] - s[q[l]]);
			pre[i][j] = q[l];
			while (l < r && slope(q[r], q[r - 1]) >= slope(i, q[r])) r--;
			q[++r] = i;
		}
		memcpy(dp2, dp, sizeof dp);
	}
	printf("%lld\n", dp2[n]);
	for (int i = n, j = k; j >= 1; j--) printf("%d ", i = pre[i][j]);
}