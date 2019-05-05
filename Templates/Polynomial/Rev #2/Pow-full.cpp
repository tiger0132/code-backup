#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstring>
#define I(x) p(x, P - 2)
#define F_M [](int x, int y) { return 1ll * x * y % P; }
#define C(x) memset(x + n, 0, (lim - n) * 4)
#define M0(x) memset(x, 0, sizeof x)

const int LGN = 22, N = 9e5 + 59, P = 998244353, G = 3, Gi = 332748118;
inline int p(int x, int y) {
	int r = 1;
	for (; y; y >>= 1, x = 1ll * x * x % P)
		if (y & 1) r = 1ll * r * x % P;
	return r;
}

int u1[LGN], u2[LGN], invp[N] = {0, 1};
static struct _init {
	inline _init() {
		for (int i = 1; i < LGN; i++) u1[i] = p(G, (P - 1) / (1 << i)), u2[i] = p(Gi, (P - 1) / (1 << i));
		for (int i = 2; i < N; i++) invp[i] = 1ll * (P - P / i) * invp[P % i] % P;
	}
} __init;

int r[N], lim, l;
inline void ntt(int *a, int op) {
	for (int i = 0; i < lim; i++)
		if (i < r[i]) std::swap(a[i], a[r[i]]);
	for (int i = 1, lgi = 1; i < lim; i *= 2, lgi++) {
		int wn = (op == 1 ? u1 : u2)[lgi];
		for (int j = 0; j < lim; j += i * 2) {
			int w = 1;
			for (int k = 0; k < i; k++, w = 1ll * w * wn % P) {
				int x = a[j + k], y = 1ll * w * a[j + k + i] % P;
				a[j + k] = (x + y) % P, a[j + k + i] = (x - y + P) % P;
			}
		}
	}
	if (op == -1)
		for (int i = 0; i < lim; i++) a[i] = 1ll * a[i] * invp[lim] % P;
}
inline void init(int n) {
	for (lim = 1, l = 0; lim <= n;) lim *= 2, l++;
	for (int i = 1; i < lim; i++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));
}
template <typename F>
inline void mul(int *a, int *b, int *ans, const F &f) {
	static int c[N], d[N];
	memcpy(c, a, lim * 4), memcpy(d, b, lim * 4), ntt(c, 1), ntt(d, 1);
	for (int i = 0; i < lim; i++) ans[i] = f(c[i], d[i]);
	ntt(ans, -1);
}
inline void inv(int n, int *a, int *ans) {  // LIMITATION: a != ans
	static int b[N];
	if (n == 1) return void(*ans = I(*a));
	inv((n + 1) / 2, a, ans), init(n * 2);
	memcpy(b, a, n * 4), C(b);
	mul(b, ans, ans, [](int x, int y) { return (2 - 1ll * x * y % P + P) % P * y % P; }), C(ans);
}
inline void intg(int n, int *a, int *ans) {
	for (int i = 1; i < n; i++) ans[i] = 1ll * a[i - 1] * invp[i] % P;
	*ans = 0;
}
inline void derv(int n, int *a, int *ans) {
	for (int i = 1; i < n; i++) ans[i - 1] = 1ll * i * a[i] % P;
	ans[n - 1] = 0;
}
inline void ln(int n, int *a, int *ans) {
	static int b[N], c[N];
	M0(b), M0(c), derv(n, a, b), inv(n, a, c), mul(b, c, c, F_M), intg(n, c, ans);
}
inline void exp(int n, int *a, int *ans) {  // LIMITATION: n = 2^d
	static int b[N];
	if (n == 1) return void(ans[0] = 1);
	exp(n >> 1, a, ans), ln(n, ans, b), C(b);
	for (int i = 0; i < n; i++) b[i] = (!i + a[i] - b[i] + P) % P;
	mul(ans, b, ans, F_M), C(ans);
}
inline void pow(int n, int k, int *a, int *ans) {
	static int b[N];
	int t = 0, ofs = 0;
	if (!*a) {
		for (ofs = 1; !a[ofs] && ofs < n;) ofs++;
		for (int i = 0; i < n; i++) a[i] = (i + ofs < n ? a[i + ofs] : 0);
		if (1ll * ofs * k >= n) return;
		ofs *= k;
	}
	if (*a > 1) {
		t = I(*a);
		for (int i = 1; i < n; i++) a[i] = 1ll * a[i] * t % P;
		t = p(*a, k), *a = 1;
	}
	ln(n, a, b);
	for (int i = 0; i < n; i++) b[i] = 1ll * b[i] * k % P;
	exp(n, b, ans);
	if (ofs)
		for (int i = n - 1; i >= 0; i--) (i + ofs <= n && (ans[i + ofs] = ans[i])), ans[i] = 0;
	if (t)
		for (int i = 0; i < n; i++) ans[i] = 1ll * ans[i] * t % P;
}

int n, k, m = 1, a[N], b[N];
char c;
int main() {
	scanf("%d%d", &n, &k);
	for (int i = 0; i < n; i++) scanf("%d", a + i);
	while (m <= n) m *= 2;
	pow(m, k, a, b);
	for (int i = 0; i < n; i++) printf("%d ", b[i]);
}