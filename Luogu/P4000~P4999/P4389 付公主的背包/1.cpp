// 被卡常，待更新

#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 6e5 + 56, P = 998244353, G = 3, GInv = 332748118;

int p(int x, int y) {
	int ret = 1;
	for (; y; y >>= 1, (x = 1ll * x * x % P))
		if (y & 1) ret = 1ll * ret * x % P;
	return ret;
}

int r[N], lim = 1, l;
void ntt(int *a, int op) {
	for (int i = 0; i < lim; i++)
		if (i < r[i]) std::swap(a[i], a[r[i]]);
	for (int i = 1; i < lim; i <<= 1) {
		int gn = p(op == 1 ? G : GInv, (P - 1) / (i << 1));
		for (int j = 0; j < lim; j += i * 2) {
			int g = 1;
			for (int k = 0; k < i; k++, g = 1ll * g * gn % P) {
				int x = a[j + k], y = 1ll * g * a[j + k + i] % P;
				a[j + k] = (x + y) % P, a[j + k + i] = (x - y + P) % P;
			}
		}
	}
	if (op == 1) return;
	int inv = p(lim, P - 2);
	for (int i = 0; i < lim; i++) a[i] = 1ll * a[i] * inv % P;
}
template <typename F>
void mul(int *a, int *b, int *ans, F f) {
	static int c[N], d[N];
	memcpy(c, a, lim << 2);
	memcpy(d, b, lim << 2);
	ntt(c, 1), ntt(d, 1);
	for (int i = 0; i < lim; i++) ans[i] = f(c[i], d[i]);
	ntt(ans, -1);
}
void init(int n) {
	for (lim = 1, l = 0; lim <= n;) lim <<= 1, l++;
	for (int i = 1; i < lim; i++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));
}
void inv(int n, int *a, int *ans) {
	static int b[N];
	if (n == 1) return void(ans[0] = p(a[0], P - 2));
	inv((n + 1) / 2, a, ans);
	init(n * 2);
	memcpy(b, a, n << 2);
	memset(b + n, 0, (lim - n) << 2);
	mul(b, ans, ans, [](int x, int y) { return (2 - 1ll * x * y % P + P) % P * y % P; });
	memset(ans + n, 0, (lim - n) << 2);
}
void derivative(int n, int *a, int *ans) {
	for (int i = 1; i < n; i++) ans[i - 1] = 1ll * i * a[i] % P;
	ans[n - 1] = 0;
}
void integral(int n, int *a, int *ans) {
	for (int i = 1; i < n; i++) ans[i] = 1ll * p(i, P - 2) * a[i - 1] % P;
	ans[0] = 0;
}
void ln(int n, int *a, int *ans) {
	static int b[N], c[N];
	memset(b, 0, sizeof b), memset(c, 0, sizeof c);
	derivative(n, a, b), inv(n, a, c);
	mul(b, c, c, [](int x, int y) { return 1ll * x * y % P; });
	integral(n, c, ans);
}
void exp(int n, int *a, int *ans) {
	static int b[N];
	if (n == 1) return void(ans[0] = 1);
	exp(n >> 1, a, ans);
	init(n), ln(n, ans, b);
	for (int i = 0; i < n; i++) b[i] = (!i + a[i] - b[i] + P) % P;
	mul(ans, b, ans, [](int x, int y) { return 1ll * x * y % P; });
	memset(ans + n, 0, (lim - n) << 2);
}

int n, m, k = 1, x, a[N], b[N], c[N];
int main() {
	scanf("%d%d", &n, &m);
	while (k <= m) k <<= 1;
	while (n--) scanf("%d", &x), c[x]++;
	for (int i = 1; i <= m; i++) {
		if (!c[i]) continue;
		for (int j = i; j <= k; j += i) {
			a[j] = (a[j] + 1ll * c[i] * p(j / i, P - 2)) % P;
		}
	}
	exp(k, a, b);
	for (int i = 1; i <= m; i++) printf("%d\n", b[i]);
}