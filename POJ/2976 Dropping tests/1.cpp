#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <functional>
#include <numeric>

const int N = 1e3 + 31;
const double eps = 1e-6;
double a[N], b[N], c[N];
int n, k;
double chk(double x) {
	for (int i = 1; i <= n; i++) c[i] = a[i] - x * b[i];
	std::sort(c + 1, c + n + 1, std::greater<double>());
	return std::accumulate(c + 1, c + n - k + 1, 0.) >= 0;
}

double l, r, mid;
int main() {
	while (scanf("%d%d", &n, &k), (n || k)) {
		for (int i = 1; i <= n; i++) scanf("%lf", a + i);
		for (int i = 1; i <= n; i++) scanf("%lf", b + i);
		for (l = 0, r = 1; r - l > eps;) mid = (l + r) / 2, (chk(mid) ? l : r) = mid;
		printf("%.f\n", 100 * l);
	}
}