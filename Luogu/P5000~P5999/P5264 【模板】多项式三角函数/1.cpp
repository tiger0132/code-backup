// 🀀🀁🀂🀃🀅🀆🀇🀈🀉🀊🀋🀌🀍🀎🀏🀐🀑🀒🀓🀔🀕🀖🀗🀘🀙🀚🀛🀜🀝🀞🀟🀠🀡

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>

// const int N = 6e5 + 55, P = 998244353, G = 3, GInv = 332748118, I = 911660635, div2 = 499122177, div2i = 954952494;
const int N = 6e5 + 55, P = 998244353, G = 3, GInv = 332748118, I = 911660635, div2 = 499122177, div2i = 43291859;
int p(int x, int y) {
	int ret = 1;
	for (; y; y >>= 1, x = 1ll * x * x % P)
		if (y & 1) ret = 1ll * ret * x % P;
	return ret;
}

int r[N], lim, l;
void ntt(int *a, int op) {
	for (int i = 0; i < lim; i++) (i < r[i]) && (std::swap(a[i], a[r[i]]), 0);
	for (int i = 1; i < lim; i *= 2) {
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
	memcpy(c, a, lim * 4), memcpy(d, b, lim * 4), ntt(c, 1), ntt(d, 1);
	for (int i = 0; i < lim; i++) ans[i] = f(c[i], d[i]);
	ntt(ans, -1);
}
void init(int n) {
	for (lim = 1, l = 0; lim <= n;) lim *= 2, l++;
	for (int i = 1; i < lim; i++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));
}
void inv(int n, int *a, int *ans) {
	static int b[N];
	if (n == 1) return void(ans[0] = p(a[0], P - 2));
	inv((n + 1) / 2, a, ans), init(n * 2);
	memcpy(b, a, n * 4), memset(b + n, 0, (lim - n) * 4);
	mul(b, ans, ans, [](int x, int y) { return 1ll * y * ((2 - 1ll * x * y % P + P) % P) % P; });
	memset(ans + n, 0, (lim - n) * 4);
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
	memset(b, 0, sizeof b), memset(c, 0, sizeof c), derivative(n, a, b), inv(n, a, c);
	mul(b, c, c, [](int x, int y) { return 1ll * x * y % P; }), integral(n, c, ans);
}
void exp(int n, int *a, int *ans) {
	static int b[N];
	if (n == 1) return void(ans[0] = 1);
	exp(n >> 1, a, ans), init(n), ln(n, ans, b), memset(b + n, 0, (lim - n) * 4);
	for (int i = 0; i < n; i++) b[i] = (!i + a[i] - b[i] + P) % P;
	mul(ans, b, ans, [](int x, int y) { return 1ll * x * y % P; }), memset(ans + n, 0, (lim - n) * 4);
}
template <int x, int y>
void __sincos(int n, int *a, int *ans) {
	static int b[N], c[N], m = 1;
	while (m <= n) m *= 2;
	for (int i = 0; i < m; i++) a[i] = 1ll * I * a[i] % P;
	exp(m, a, b);
	for (int i = 0; i < m; i++) a[i] = (P - a[i]) % P;
	exp(m, a, c);
	for (int i = 0; i < m; i++) ans[i] = (b[i] + 1ll * y * c[i] + P) % P * x % P;
}

auto _sin = [](int n, int *a, int *ans) { __sincos<div2i, -1>(n, a, ans); };
auto _cos = [](int n, int *a, int *ans) { __sincos<div2, 1>(n, a, ans); };
int n, op, a[N], b[N];
int main() {
	scanf("%d%d", &n, &op);
	for (int i = 0; i < n; i++) scanf("%d", a + i);
	op ? _cos(n, a, b) : _sin(n, a, b);
	for (int i = 0; i < n; i++) printf("%d ", b[i]);
}