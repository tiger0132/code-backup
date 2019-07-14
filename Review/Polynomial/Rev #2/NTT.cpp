#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#define I(x) p(x, P - 2)

const int N = 3e6 + 63, P = 998244353, G = 3, Gi = 332748118;
int r[N], lim, l;
int u1[N], u2[N];
inline int p(int x, int y) {
	int r = 1;
	for (; y; y >>= 1, x = 1ll * x * x % P)
		if (y & 1) r = 1ll * r * x % P;
	return r;
}
inline void ntt(int* a, int op) {
	for (int i = 0; i < lim; i++)
		if (i < r[i]) std::swap(a[i], a[r[i]]);
	int w, wn, x, y;
	for (int i = 1; i < lim; i *= 2) {
		wn = (op == 1 ? u1 : u2)[i];
		for (int j = 0; j < lim; j += i * 2) {
			w = 1;
			for (int k = 0; k < i; k++, w = 1ll * w * wn % P) {
				x = a[j + k], y = 1ll * w * a[j + k + i] % P;
				a[j + k] = (x + y) % P, a[j + k + i] = (x - y + P) % P;
			}
		}
	}
	if (op == -1)
		for (int i = 0, t = I(lim); i < lim; i++) a[i] = 1ll * a[i] * t % P;
}
inline void init(int n) {
	for (lim = 1, l = 0; lim <= n;) lim *= 2, l++;
	for (int i = 1; i < lim; i++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));
}

int n, m, a[N], b[N];
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i < N; i *= 2) u1[i] = p(G, (P - 1) / (i * 2)), u2[i] = p(Gi, (P - 1) / (i * 2));
	for (int i = 0; i <= n; i++) scanf("%d", a + i);
	for (int i = 0; i <= m; i++) scanf("%d", b + i);
	init(n + m), ntt(a, 1), ntt(b, 1);
	for (int i = 0; i <= lim; i++) a[i] = 1ll * a[i] * b[i] % P;
	ntt(a, -1);
	for (int i = 0; i <= n + m; i++) printf("%d ", a[i]);
}