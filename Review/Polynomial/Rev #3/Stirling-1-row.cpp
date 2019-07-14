#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>

typedef long long ll;
const int N = 2.7e5, M = 19, P = 167772161, G = 3, GInv = 55924054;
int pw(int x, int y) {
	int r = 1;
	for (; y; y >>= 1, x = ll(x) * x % P)
		if (y & 1) r = ll(r) * x % P;
	return r;
}

int _wn[M];
int r[N], lim, l;
inline void ntt(int *a, int op) {
	int i, j, k, u, w, wn, x, y, inv;
	for (i = 0; i < lim; ++i)
		if (i < r[i]) std::swap(a[i], a[r[i]]);
	for (i = 1, u = 0; i < lim; i *= 2, ++u) {
		wn = _wn[u];
		for (j = 0; j < lim; j += i * 2) {
			for (k = 0, w = 1; k < i; ++k, w = ll(w) * wn % P) {
				x = a[j + k], y = ll(w) * a[i + j + k] % P;
				a[j + k] = (x + y) % P, a[i + j + k] = (x - y + P) % P;
			}
		}
	}
	if (op == 1) return;
	inv = P - P / lim, std::reverse(a + 1, a + lim);
	for (i = 0; i < lim; ++i) a[i] = ll(a[i]) * inv % P;
}
inline void init(int n) {
	for (lim = 1, l = 0; lim <= n; lim *= 2) ++l;
	for (int i = 1; i < lim; ++i) r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));
}

int fac[N], ifac[N], inv[N];
inline int c(int n, int m) { return ll(fac[n]) * ifac[m] % P * ifac[n - m] % P; }
void calc(int n, int *ans) {
	static int a[N], b[N], _p[N];
	if (!n) return void(*ans = 1);
	if (n == 1) return void(ans[1] = 1);
	if (n % 2) {
		calc(n - 1, ans);
		for (int i = n; i; i--) ans[i] = (ans[i - 1] + ans[i] * (n - 1ll)) % P;
	} else {
		int m = n / 2;
		calc(m, ans), _p[0] = 1, init(n);
		for (int i = 1; i <= m; ++i) _p[i] = ll(_p[i - 1]) * m % P;
		for (int i = 0; i <= m; ++i) a[i] = ll(ans[i]) * fac[i] % P;
		for (int i = 0; i <= m; ++i) b[m - i] = ll(_p[i]) * ifac[i] % P;
		ntt(a, 1), ntt(b, 1);
		for (int i = 0; i < lim; ++i) a[i] = ll(a[i]) * b[i] % P;
		ntt(a, -1);
		for (int i = 0; i <= m; ++i) a[i] = ll(a[i + m]) * ifac[i] % P;
		memset(a + m + 1, 0, (lim - m - 1) * 4), memset(b + m + 1, 0, (lim - m - 1) * 4);
		memcpy(b, ans, (m + 1) * 4);
		ntt(a, 1), ntt(b, 1);
		for (int i = 0; i < lim; ++i) a[i] = ll(a[i]) * b[i] % P;
		ntt(a, -1);
		memcpy(ans, a, (n + 1) * 4);
		memset(a, 0, lim * 4), memset(b, 0, lim * 4);
	}
}
int n, a[N], b[N];
int main() {
	for (int i = 0; i < M; ++i) _wn[i] = pw(G, (P - 1) / (2 << i));
	fac[0] = ifac[0] = inv[0] = inv[1] = 1;
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		if (i > 1) inv[i] = ll(P - P / i) * inv[P % i] % P;
		fac[i] = ll(fac[i - 1]) * i % P;
		ifac[i] = ll(ifac[i - 1]) * inv[i] % P;
	}
	calc(n, a);
	for (int i = 0; i <= n; i++) printf("%d ", a[i]);
}