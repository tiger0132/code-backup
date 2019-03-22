#include <algorithm>
#include <cstdio>
#include <cstring>

using ll = long long;
const int N = 1e6 + 61;

ll dp[N], x[N], s[N], sp[N], c[N], q[N];
int n, l, r;

inline double slope(int x, int y) { return 1. * (dp[x] + s[x] - dp[y] - s[y]) / (sp[x] - sp[y]); }
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%lld%lld%lld", x + i, sp + i, c + i);
		s[i] = s[i - 1] + x[i] * sp[i];
		sp[i] += sp[i - 1];
	}
	for (int i = 1; i <= n; i++) {
		while (l < r && slope(q[l + 1], q[l]) < x[i]) l++;
		dp[i] = dp[q[l]] + c[i] + x[i] * (sp[i] - sp[q[l]]) - s[i] + s[q[l]];
		while (l < r && slope(q[r], q[r - 1]) > slope(i, q[r])) r--;
		q[++r] = i;
	}
	printf("%lld", dp[n]);
}