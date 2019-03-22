#include <algorithm>
#include <cstdio>
#include <cstring>
#include <set>
#define int long long
#define S(x) ((x) * (x))

const int N = 1e5 + 51;

int l, r, h[N], w[N], q[N], dp[N];
int g(int x) { return dp[x] + S(h[x]) - w[x]; }
double slope(int x, int y) { return h[x] == h[y] ? g(x) > g(y) ? 1e10 : -1e10 : 1. * (g(x) - g(y)) / (h[x] - h[y]); }

const auto cmp = [](int x, int y) { return h[x] < h[y] || (h[x] == h[y] && x < y); };
int t[N];
void cdq(int *p, int n) {
	if (n == 1) return;
	int m = (n + 1) >> 1;
	cdq(p, m);
	memcpy(t, p, n * sizeof(*p));
	std::sort(t, t + m, cmp);
	std::sort(t + m, t + n, cmp);
	q[l = 1, r = 0] = 0;
	for (int i = 0; i < m; i++) {
		int x = t[i];
		while (l < r && slope(q[r], q[r - 1]) > slope(x, q[r])) r--;
		q[++r] = x;
	}
	for (int i = m; i < n; i++) {
		int x = t[i];
		while (l < r && slope(q[l + 1], q[l]) < 2 * h[x]) l++;
		dp[x] = std::min(dp[x], dp[q[l]] + S(h[x] - h[q[l]]) + w[x - 1] - w[q[l]]);
	}
	cdq(p + m, n - m);
}

int n, id[N];
signed main() {
	scanf("%lld", &n);
	for (int i = 0; i < n; i++) scanf("%lld", h + i), id[i] = i;
	for (int i = 0; i < n; i++) scanf("%lld", w + i), w[i] += !!i * w[i - 1];
	memset(dp, 0x3f, sizeof dp);
	dp[0] = 0;
	cdq(id, n);
	// for (int i = 0; i < n; i++)
	printf("%lld", dp[n - 1]);
}