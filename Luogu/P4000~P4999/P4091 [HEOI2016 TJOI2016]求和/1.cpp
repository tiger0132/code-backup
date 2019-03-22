#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>

const int N = 6e5 + 56, P = 998244353, G = 3, GInv = 332748118;
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
		int gn = p(op == 1 ? G : GInv, (P - 1) / (i * 2));
		for (int j = 0; j < lim; j += i * 2) {
			for (int g = 1, k = 0; k < i; k++, g = 1ll * g * gn % P) {
				int x = a[j + k], y = 1ll * g * a[j + k + i] % P;
				a[j + k] = (x + y) % P;
				a[j + k + i] = (x - y + P) % P;
			}
		}
	}
	if (op == 1) return;
	int inv = p(lim, P - 2);
	for (int i = 0; i < lim; i++) a[i] = 1ll * a[i] * inv % P;
}

int inv[N], fac[N], ifac[N];
int n, ans, a[N], b[N];
int main() {
	scanf("%d", &n);
	b[1] = n + 1, inv[1] = fac[0] = ifac[0] = a[0] = b[0] = 1;
	for (int i = 1; i <= n; i++) {
		if (i > 1) inv[i] = 1ll * (P - P / i) * inv[P % i] % P;
		fac[i] = 1ll * fac[i - 1] * i % P;
		ifac[i] = 1ll * ifac[i - 1] * inv[i] % P;
		a[i] = (i % 2 ? P - 1ll : 1ll) * ifac[i] % P;
		if (i > 1) b[i] = (p(i, n + 1) - 1ll) * inv[i - 1] % P * ifac[i] % P;
	}
	while (lim <= 2 * n) lim *= 2, l++;
	for (int i = 0; i < lim; i++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));
	ntt(a, 1), ntt(b, 1);
	for (int i = 0; i < lim; i++) a[i] = 1ll * a[i] * b[i] % P;
	ntt(a, -1);
	for (int i = 0, p2 = 1; i <= n; i++, p2 = p2 * 2 % P) {
		ans = (ans + 1ll * a[i] * fac[i] % P * p2 % P) % P;
	}
	printf("%d", ans);
}