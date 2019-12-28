#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#define L(x) (2 * x)
#define R(x) (2 * x + 1)

const int N = 2e5 + 52;

int n, x, y, mx, p, ans, lans, sz[N], s[N];
int main() {
	scanf("%d", &n), ans = 1e9;
	for (int i = 1; i <= n; i++)
		scanf("%d", &x), x[sz]++, mx = std::max(mx, x), lans += (int)log2(x);
	for (int i = mx; i >= 1; i--)
		if ((i[s] = i[sz] + L(i)[s] + R(i)[s]) == n) p = std::max(p, i);
	x = 0, y = n;
	lans -= n * (int)log2(p);
	for (; p <= mx; p = L(p)) {
		x += p[sz] + R(p)[s], y -= p[sz] + R(p)[s];
		ans = std::min(ans, lans);
		lans += x - y;
	}
	printf("%d", ans);
}