#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#define mid (l + r) / 2
#define int long long
#define double long double

const double eps = 1e-8;
const int N = 1e5 + 51;

int a[N], b[N], x[N], y[N];
double slope(int i, int j) {
	if (fabsl(x[i] - x[j]) < eps) return y[j] > y[i] ? 1e18 : -1e18;
	return 1. * (y[j] - y[i]) / (x[j] - x[i]);
}
int dot(int i, int j) { return x[i] * a[j] + y[i] * b[j]; }

int st[N], top;
int f(int id) {
	int l = 1, r = top;
	int ans = 0x3f3f3f3f3f3f3f3f;
	// for (int i = 1; i <= top; i++) printf("%lld%c", dot(st[i], id), " \n"[i == top]);
	while (l <= r)
		if (mid == 1 || dot(st[mid - 1], id) > dot(st[mid], id))
			ans = std::min(ans, dot(st[mid], id)), l = mid + 1;
		else
			ans = std::min(ans, dot(st[mid - 1], id)), r = mid - 1;
	return ans;
}

int h[N], s[N], dp[N];
int pt[N];
void cdq(int l, int r) {
	if (l == r) {
		// dp[l] = std::max(dp[l], dp[l - 1]) + s[l - 1] + h[l] * h[l];
		// dp[l] += s[l - 1] + h[l] * h[l];
		x[l] = dp[l] - s[l] + h[l] * h[l];
		y[l] = h[l];
		// printf("%lld: %lld %lld %lld\n", l, dp[l], x[l], y[l]);
		return;
	}
	int m = (l + r) / 2;
	cdq(l, m);
	top = 0;
	for (int i = l; i <= m; i++) {
		while (top >= 2 && slope(st[top], i[pt]) > slope(st[top - 1], st[top])) top--;
		st[++top] = i[pt];
	}
	for (int i = m + 1; i <= r; i++) {
		dp[i[pt]] = std::min(dp[i[pt]], f(i[pt]) + s[i[pt] - 1] + h[i[pt]] * h[i[pt]]);
	}
	cdq(m + 1, r);
	std::inplace_merge(pt + l, pt + m + 1, pt + r + 1,
					   [](int p, int q) { return x[p] < x[q]; });
}

int n;
signed main() {
	memset(dp, 0x3f, sizeof dp);
	dp[1] = 0;
	scanf("%lld", &n);
	for (int i = 1; i <= n; i++) scanf("%lld", h + i);
	for (int i = 1; i <= n; i++) scanf("%lld", s + i), s[i] += s[i - 1];
	for (int i = 1; i <= n; i++) {
		a[i] = 1, b[i] = -2 * h[i];
		i[pt] = i;
	}
	cdq(1, n);
	printf("%lld\n", dp[n]);
}