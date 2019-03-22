#include <algorithm>
#include <cstdio>

const int N = 2e4 + 42;

int n, l, r, ans = 0x3f3f3f3f, s[N], d[N], sd[N], c[N], q[N];

inline double slope(int x, int y) { return 1. * (sd[x] * s[x] - sd[y] * s[y]) / (s[x] - s[y]); }
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n + 1; i++) {
		if (i <= n) scanf("%d%d", s + i, d + i);
		s[i] += s[i - 1];
		sd[i] = sd[i - 1] + d[i - 1];
		c[i] = c[i - 1] + s[i - 1] * d[i - 1];
	}
	for (int i = 1; i <= n; i++) {
		while (l < r && slope(q[l + 1], q[l]) < sd[i]) l++;
		ans = std::min(ans, c[n + 1] - s[q[l]] * (sd[i] - sd[q[l]]) - s[i] * (sd[n + 1] - sd[i]));
		while (l < r && slope(q[r], q[r - 1]) > slope(i, q[r])) r--;
		q[++r] = i;
	}
	printf("%d", ans);
}