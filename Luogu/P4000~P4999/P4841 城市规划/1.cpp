#include <algorithm>
#include <cstdio>
#include <cstring>

using ll = long long;
const int N = 6e5 + 56, P = 1004535809, G = 3, GInv = 334845270;

int p(int x, ll y) {
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
		for (int j = 0; j < lim; j += 2 * i) {
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
void polyinv(int n, int *a, int *ans) {
	static int b[N];
	if (n == 1) return void(ans[0] = p(a[0], P - 2));
	polyinv((n + 1) / 2, a, ans);
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
	for (int i = 1; i < n; i++) ans[i] = 1ll * p(i, P - 2) * a[i - 1] % P;
	ans[0] = 0;
}
void ln(int n, int *a, int *ans) {
	static int b[N], c[N];
	memset(b, 0, sizeof b), memset(c, 0, sizeof c);
	derivative(n, a, b), polyinv(n, a, c);
	mul(b, c, c, [](int x, int y) { return 1ll * x * y % P; });
	integral(n, c, ans);
}

int fac[N], a[N], b[N];
int n;
int main() {
	scanf("%d", &n);
	init_mul(n + 1);
	fac[0] = 1;
	for (int i = 1; i <= lim; i++) fac[i] = 1ll * fac[i - 1] * i % P;
	for (int i = 0; i < lim; i++) {
		a[i] = 1ll * p(2, i * (i - 1ll) / 2) * p(fac[i], P - 2) % P;
	}
	ln(n + 1, a, b);
	printf("%d\n", 1ll * b[n] * fac[n] % P);
}