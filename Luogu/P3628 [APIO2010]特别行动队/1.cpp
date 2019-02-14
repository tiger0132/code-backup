#include <cstdio>
#define S(x) ((x) * (x))

typedef long long ll;
const int N = 1e6 + 61;

ll a, b, c, dp[N], s[N];
int n, l, r, q[N];

inline double slope(int x, int y) {
	return 1. * (dp[x] + a * S(s[x]) - b * s[x] - dp[y] - a * S(s[y]) + b * s[y]) / (s[x] - s[y]);
}
int main() {
	scanf("%d%lld%lld%lld", &n, &a, &b, &c);
	for (int i = 1; i <= n; i++) scanf("%lld", s + i), s[i] += s[i - 1];
	for (int i = 1; i <= n; i++) {
		while (l < r && slope(q[l + 1], q[l]) > 2 * a * s[i]) l++;
		dp[i] = dp[q[l]] + a * S(s[i] - s[q[l]]) + b * (s[i] - s[q[l]]) + c;
		while (l < r && slope(q[r], q[r - 1]) < slope(i, q[r])) r--;
		q[++r] = i;
	}
	printf("%lld", dp[n]);
}