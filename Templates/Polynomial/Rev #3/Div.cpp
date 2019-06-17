#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#define $(x) (x, 0)

const int N = 2.7e5, P = 998244353, G = 3, GInv = 332748118;
inline int pw(int x, int y) {
	if (!y) return 1;
	for (; ~y & 1; y >>= 1) x = 1ll * x * x % P;
	int r = x;
	for (y >>= 1; y; y >>= 1) x = 1ll * x * x % P, (y & 1) && (r = 1ll * r * x % P);
	return r;
}

int r[N], lim, l;
inline void ntt(int *a, int op) {
	for (int i = 0; i < lim; ++i) i < r[i] && $(std::swap(a[i], a[r[i]]));
	for (int i = 1; i < lim; i *= 2) {
		int wn = pw(G, (P - 1) / (i * 2));
		for (int j = 0; j < lim; j += i * 2) {
			for (int k = 0, w = 1; k < i; ++k, w = 1ll * w * wn % P) {
				int x = a[j + k], y = 1ll * w * a[i + j + k] % P;
				a[j + k] = (x + y) % P, a[i + j + k] = (x - y + P) % P;
			}
		}
	}
	if (op == 1) return;
	std::reverse(a + 1, a + lim);
	for (int i = 0, inv = P - P / lim; i < lim; ++i) a[i] = 1ll * a[i] * inv % P;
}
inline void init(int n) {
	for (lim = 1, l = 0; lim <= n; lim *= 2) ++l;
	for (int i = 1; i < lim; ++i) r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));
}
void inv(int n, int *a, int *ans) {
	if (n == 1) return void(*ans = pw(*a, P - 2));
	static int b[N];
	int m = (n + 1) / 2;
	inv(m, a, ans), memcpy(b, a, n * 4), init(n + n), memset(b + n, 0, (lim - n) * 4), ntt(b, 1), ntt(ans, 1);
	for (int i = 0; i < lim; ++i) ans[i] = ans[i] * (2 - 1ll * b[i] * ans[i] % P + P) % P;
	ntt(ans, -1), memset(ans + n, 0, (lim - n) * 4);
}
inline void div(int n, int m, int *f, int *g, int *q, int *r) {
	static int fr[N], gr[N];
	std::reverse_copy(f, f + n + 1, fr), std::reverse_copy(g, g + m + 1, gr);
	for (int i = n - m + 2; i <= m; i++) gr[i] = 0;
	inv(n - m + 1, gr, q), init(n * 2), ntt(q, 1), ntt(fr, 1), ntt(f, 1), ntt(g, 1);
	for (int i = 0; i < lim; i++) q[i] = 1ll * q[i] * fr[i] % P;
	ntt(q, -1), std::reverse(q, q + n - m + 1), memset(q + n - m + 1, 0, (m - 1) << 2);
	ntt(q, 1);
	for (int i = 0; i < lim; i++) r[i] = (f[i] - 1ll * q[i] * g[i] % P + P) % P;
	ntt(q, -1), ntt(r, -1);
}

int n, m, a[N], b[N], c[N], d[N];
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i <= n; ++i) scanf("%d", a + i);
	for (int i = 0; i <= m; ++i) scanf("%d", b + i);
	div(n, m, a, b, c, d);
	for (int i = 0; i <= n - m; ++i) printf("%d%c", c[i], " \n"[i == n - m]);
	for (int i = 0; i < m; ++i) printf("%d ", d[i]);
}