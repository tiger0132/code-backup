// 🐔你太美

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>

const int N = 2e5 + 52, P = 998244353, G = 3, Gi = 332748118;
int p(int x, int y) {
	int r = 1;
	for (; y; y >>= 1, x = 1ll * x * x % P)
		if (y & 1) r = 1ll * r * x % P;
	return r;
}

int r[N], lim, l;
void ntt(int *a, int op) {
	for (int i = 0; i < lim; i++)
		if (i < r[i]) std::swap(a[i], a[r[i]]);
	for (int i = 1; i < lim; i <<= 1) {
		int gn = p(op == 1 ? G : Gi, (P - 1) / (i << 1));
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

int F[5][N], fac[N], ifac[N];
int n, a[4], lm, ans;
int main() {
	scanf("%d%d%d%d%d", &n, a, a + 1, a + 2, a + 3), std::sort(a, a + 4);
	lm = a[0] + a[1] + a[2] + a[3];
	fac[0] = 1;
	for (int i = 1; i <= lm; i++) fac[i] = 1ll * fac[i - 1] * i % P;
	ifac[lm] = p(fac[lm], P - 2);
	for (int i = lm - 1; i >= 0; i--) ifac[i] = ifac[i + 1] * (i + 1ll) % P;
	for (lim = 1, l = 0; lim <= lm;) lim *= 2, l++;
	for (int i = 1; i < lim; i++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));
	lm = std::min(n / 4, a[0]);
	for (int i = 0; i <= lm; i++) {
		memset(F, 0, sizeof F);
		for (int j = 0; j < 4; j++) memcpy(F[j], ifac, (a[j] - i + 1) * 4), ntt(F[j], 1);
		for (int j = 0; j < lim; j++) F[4][j] = 1ll * F[0][j] * F[1][j] % P * F[2][j] % P * F[3][j] % P;
		ntt(F[4], -1);
		ans = (ans + (i % 2 ? -1ll : 1ll) * F[4][n - 4 * i] % P * ifac[i] % P * fac[n - 3 * i] % P + P) % P;
	}
	printf("%d", ans);
}