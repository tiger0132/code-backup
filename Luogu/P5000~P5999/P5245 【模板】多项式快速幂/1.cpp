#include <algorithm>
#include <complex>
#include <cstdio>
#include <cstring>
#define invp(x) p((x), P - 2)

const int N = 3e6 + 63, P = 998244353, G = 3, GInv = 332748118, div2 = 499122177;

int p(int x, int y) {
	int ret = 1;
	for (; y; y >>= 1, x = 1ll * x * x % P)
		if (y & 1) ret = 1ll * ret * x % P;
	return ret;
}

int r[N], lim = 1, l;
void ntt(int *a, int op) {
	for (int i = 0; i < lim; i++)
		if (i < r[i]) std::swap(a[i], a[r[i]]);
	for (int i = 1; i < lim; i <<= 1) {
		int gn = p(op == 1 ? G : GInv, (P - 1) / (i << 1));
		for (int j = 0; j < lim; j += 2 * i) {
			int g = 1;
			for (int k = 0; k < i; k++, g = 1ll * g * gn % P) {
				int x = a[j + k], y = 1ll * g * a[j + k + i] % P;
				a[j + k] = (x + y) % P, a[j + k + i] = (x - y + P) % P;
			}
		}
	}
	if (op == 1) return;
	int inv = invp(lim);
	for (int i = 0; i < lim; i++) a[i] = 1ll * a[i] * inv % P;
}
template <typename Func>
void mul(int *a, int *b, int *ans, Func f) {
	static int t1[N], t2[N];
	memcpy(t1, a, lim * sizeof(int));
	memcpy(t2, b, lim * sizeof(int));
	ntt(t1, 1), ntt(t2, 1);
	for (int i = 0; i < lim; i++) ans[i] = f(t1[i], t2[i]);
	ntt(ans, -1);
}
void init_mul(int n) {
	lim = 1, l = 0;
	while (lim <= n) lim <<= 1, l++;
	for (int i = 1; i < lim; i++) r[i] = (r[i / 2] / 2) | ((i & 1) << (l - 1));
}
void inv(int n, int *a, int *ans) {
	static int b[N];
	if (n == 1) return void(ans[0] = invp(a[0]));
	inv((n + 1) / 2, a, ans);
	init_mul(2 * n);
	memcpy(b, a, n * sizeof(int));
	for (int i = n; i < lim; i++) b[i] = 0;
	mul(b, ans, ans, [](int x, int y) { return (2 - 1ll * x * y % P + P) % P * y % P; });
	for (int i = n; i < lim; i++) ans[i] = 0;
}
void derivative(int n, int *a, int *ans) {
	for (int i = 1; i < n; i++) ans[i - 1] = 1ll * i * a[i] % P;
	ans[n - 1] = 0;
}
void integral(int n, int *a, int *ans) {
	for (int i = 1; i < n; i++) ans[i] = 1ll * invp(i) * a[i - 1] % P;
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
	exp(n / 2, a, ans);
	init_mul(n);
	ln(n, ans, b);
	for (int i = 0; i < n; i++) b[i] = (!i + a[i] - b[i] + P) % P;
	mul(ans, b, ans, [](int x, int y) { return 1ll * x * y % P; });
	for (int i = n; i < lim; i++) ans[i] = 0;
}
void sqrt(int n, int *a, int *ans) {
	static int b[N];
	ln(n, a, b);
	for (int i = 0; i < n; i++) b[i] = 1ll * b[i] * div2 % P;
	exp(n, b, ans);
}
void pow(int n, int *a, int k, int *ans) {
	static int b[N];
	ln(n, a, b);
	for (int i = 0; i < n; i++) b[i] = 1ll * b[i] * k % P;
	exp(n, b, ans);
}

int n, k, m = 1, a[N], b[N];
char ch;
int main() {
	scanf("%d", &n);
	while (!isdigit(ch)) ch = getchar();
	while (isdigit(ch)) k = (k * 10ll + ch - 48) % P, ch = getchar();
	for (int i = 0; i < n; i++) scanf("%d", a + i);
	while (m < n) m <<= 1;
	pow(m, a, k, b);
	for (int i = 0; i < n; i++) printf("%d ", b[i]);
}