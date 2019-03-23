#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 2e7 + 72, P = 1004535809, G = 3, GInv = 334845270;
int p(int x, int y) {
	int ret = 1;
	for (; y; y >>= 1, x = 1ll * x * x % P)
		if (y & 1) ret = 1ll * ret * x % P;
	return ret;
}

int r[N], l, lim = 1;
void ntt(int *a, int op) {
	for (int i = 0; i < lim; i++)
		if (i < r[i]) std::swap(a[i], a[r[i]]);
	for (int i = 1; i < lim; i <<= 1) {
		int gn = p(op == 1 ? G : GInv, (P - 1) / (i * 2));
		for (int j = 0; j < lim; j += i * 2) {
			for (int k = 0, g = 1; k < i; k++, g = 1ll * g * gn % P) {
				int x = a[j + k], y = 1ll * g * a[j + k + i] % P;
				a[j + k] = (x + y) % P, a[j + k + i] = (x - y + P) % P;
			}
		}
	}
	if (op == 1) return;
	int inv = p(lim, P - 2);
	for (int i = 0; i < lim; i++) a[i] = 1ll * a[i] * inv % P;
}

int inv[N], fac[N], ifac[N];
int c(int x, int y) { return y > x ? 0 : 1ll * fac[x] * ifac[y] % P * ifac[x - y] % P; }

int n, m, s, k, ans, w[N], f[N], a[N], b[N];
int main() {
	scanf("%d%d%d", &n, &m, &s);
	k = std::min(m, n / s);
	inv[1] = fac[0] = ifac[0] = 1;
	for (int i = 1; i <= std::max(n, m); i++) {
		if (i > 1) inv[i] = 1ll * (P - P / i) * inv[P % i] % P;
		fac[i] = 1ll * fac[i - 1] * i % P;
		ifac[i] = 1ll * ifac[i - 1] * inv[i] % P;
	}
	for (int i = 0; i <= m; i++) scanf("%d", w + i);
	for (int i = 0, fsx = 1; i <= k; i++, fsx = (1ll * fsx * ifac[s]) % P) {
		int j = n - i * s;
		f[i] = 1ll * c(m, i) * fac[n] % P * fsx % P * ifac[j] % P * p(m - i, j) % P;
	}
	for (int i = 0; i <= k; i++) {
		a[i] = (i % 2 ? P - 1ll : 1ll) * ifac[i] % P;
		b[k - i] = 1ll * fac[i] * f[i] % P;
	}
	while (lim <= 2 * k) lim *= 2, l++;
	for (int i = 1; i < lim; i++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));
	ntt(a, 1), ntt(b, 1);
	for (int i = 0; i < lim; i++) a[i] = 1ll * a[i] * b[i] % P;
	ntt(a, -1);
	for (int i = 0; i <= k; i++) ans = (ans + 1ll * w[i] * a[k - i] % P * ifac[i] % P) % P;
	printf("%d\n", ans);
}