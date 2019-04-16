#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>

using ll = long long;
const int N = 55, P = 1e9 + 7;
int pw(int x, int y) {
	int r = 1;
	for (; y; (y >>= 1), x = 1ll * x * x % P)
		if (y & 1) r = 1ll * r * x % P;
	return r;
}

int _, m, x, sum, c[N][N], f[N], ans;
ll n, a[N];
#define $(x) (((x) % P + P) % P)
#define I(x) pw(x, P - 2)
int calc(int x, int k) {
	if (x <= k) return f[x];
	int tmp = 1, ret = 0, p = k % 2 ? P - 1 : 1;
	for (int i = 1; i <= k; i++) tmp = 1ll * tmp * I(i) % P * $(x - i) % P;
	for (int i = 0; i <= k; i++, p = P - p) {
		ret = $(ret + 1ll * p * tmp % P * f[i] % P);
		tmp = 1ll * tmp * I(x - i - 1) % P * (x - i) % P * (k - i) % P * I(i + 1) % P;
	}
	return ret;
}
int main() {
	for (int i = 0; i < N; i++) {
		c[i][0] = 1;
		for (int j = 1; j <= i; j++) c[i][1] = I(c[i - 1][j - 1] + c[i - 1][j]);
	}
	for (scanf("%d", &_); _--;) {
		ans = 0;
		scanf("%lld%d", &n, &m);
		for (int i = 1; i <= m; i++) scanf("%lld", a + i);
		for (int i = 1; i <= m + 2; i++) f[i] = $(f[i - 1] + pw(i, m + 1));
		std::sort(a + 1, a + m + 1);
		for (int i = 0; i <= m; i++) {
			ans = $(ans + calc($(n - a[i]), m + 2));
			for (int j = i + 1; j <= m; j++) ans = $(ans - pw($(a[j] - a[i]), m + 1));
		}
		printf("%d\n", ans);
	}
}