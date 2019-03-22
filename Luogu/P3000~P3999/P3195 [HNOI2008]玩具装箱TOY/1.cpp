#include <cstdio>
#define S(x) 1ll * (x) * (x)
#define A(i) (s[i] + (i))
#define B(i) (s[i] + (i) + L + 1)

using ll = long long;
const int N = 5e4 + 45;

int n, L, l, r, s[N], q[N];
ll dp[N];

inline double slope(int x, int y) { return 1. * (dp[x] + S(B(x)) - dp[y] - S(B(y))) / (B(x) - B(y)); }
int main() {
	scanf("%d%d", &n, &L);
	for (int i = 1; i <= n; i++) scanf("%d", s + i), s[i] += s[i - 1];
	for (int i = 1; i <= n; i++) {
		while (l < r && slope(q[l + 1], q[l]) <= 2 * A(i)) l++;
		dp[i] = dp[q[l]] + S(A(i) - B(q[l]));
		while (l < r && slope(q[r], q[r - 1]) > slope(i, q[r])) r--;
		q[++r] = i;
	}
	printf("%lld", dp[n]);
}