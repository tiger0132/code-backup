// 🔱👑🐟🏆🏅🎖️🥇🔨😭

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>

const int N = 2e6 + 62;

int n;
template <typename F>
void fwt(double *a, F f) {
	for (int i = 1; i <= n / 2; i <<= 1)
		for (int j = 0; j < n; j += i << 1)
			for (int k = 0; k < i; k++) f(a[j + k], a[j + k + i]);
}

double p[N], ans;
int main() {
	scanf("%d", &n), n = 1 << n;
	for (int i = 0; i < n; i++) scanf("%lf", p + i);
	fwt(p, [](double a, double &b) { b += a; });
	for (int i = 1; i < n; i++)
		if (fabs(1 - p[n - 1 - i]) > 1e-10) ans += (__builtin_popcount(i) % 2 ? 1 : -1) / (1 - p[n - 1 - i]);
	printf(fabs(ans) < 1e-10 ? "INF" : "%.10f", ans);
}