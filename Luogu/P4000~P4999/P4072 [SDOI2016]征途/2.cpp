#include <algorithm>
#include <cstdio>
#include <cstring>
#define mid (l + r) / 2

typedef long long ll;
const int N = 3e4 + 43;

int n, m, f[N], q[N];
ll dp[N], s[N];
double slope(int x, int y) {
	return 1. * (dp[x] - dp[y] + s[x] * s[x] - s[y] * s[y]) / (s[x] - s[y]);
}
bool check(int k) {
	int l = 0, r = 0;
	for (int i = 1; i <= n; i++) {
		while (l < r && slope(q[l], q[l + 1]) < 2 * s[i]) l++;
		dp[i] = dp[q[l]] + (s[i] - s[q[l]]) * (s[i] - s[q[l]]) + k;
		f[i] = f[q[l]] + 1;
		while (l < r && slope(q[r - 1], q[r]) > slope(q[r], i)) r--;
		q[++r] = i;
	}
	return f[n] <= m;
}

int l, r;
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%lld", s + i), s[i] += s[i - 1];
	for (l = 0, r = 1e9; l <= r;)
		if (check(mid))
			r = mid - 1;
		else
			l = mid + 1;
	check(l);  // l = r + 1
	printf("%lld", m * (dp[n] - m * l) - s[n] * s[n]);
}