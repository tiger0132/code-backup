#include <cstdio>
#include <cstring>
#define S(x) ((x) * (x))

using ll = long long;
const int N = 3e3 + 33, INF = 0x3f3f3f3f;

ll dp[N], dp2[N], s[N];
int n, m, l, r, q[N];

inline double slope(int x, int y) { return 1. * (dp2[x] + S(s[x]) - dp2[y] - S(s[y])) / (s[x] - s[y]); }
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%lld", s + i), s[i] += s[i - 1], dp2[i] = INF;
	for (int j = 1; j <= m; j++) {
		l = r = 0;
		for (int i = 1; i <= n; i++) {
			while (l < r && slope(q[l + 1], q[l]) < 2 * s[i]) l++;
			dp[i] = dp2[q[l]] + S(s[i] - s[q[l]]);
			while (l < r && slope(q[r], q[r - 1]) > slope(i, q[r])) r--;
			q[++r] = i;
		}
		memcpy(dp2, dp, sizeof dp);
	}
	printf("%lld", m * dp2[n] - S(s[n]));
}