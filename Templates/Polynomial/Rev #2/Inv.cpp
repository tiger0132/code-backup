#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <numeric>
#define I(x) p(x, P - 2)

const int N = 3e6 + 63, P = 998244353, G = 3, Gi = 332748118;
inline int p(int x, int y) {
	int r = 1;
	for (; y; y >>= 1, x = 1ll * x * x % P)
		if (y & 1) r = 1ll * r * x % P;
	return r;
}

int u1[N], u2[N], invp[N] = {0, 1};
const int SZ = 4;
static struct _unnamed {  // 内存池虽然用起来爽，但常数太大了，放弃了
	int pool[SZ][N], vis[SZ], st[SZ], top = SZ - 1;
	inline _unnamed() {
		for (int i = 1; i < N; i *= 2) u1[i] = p(G, (P - 1) / (i * 2)), u2[i] = p(Gi, (P - 1) / (i * 2));
		for (int i = 2; i < N; i++) invp[i] = 1ll * (P - P / i) * invp[P % i] % P;
		std::iota(st, st + SZ, 0);
	}
	inline int *alloc(int n, int *a = 0) {
		int id = st[top--];
		assert(!vis[id]), vis[id] = true;
		return (a && memcpy(pool[id], a, n * 4)), pool[id];
	}
	inline void free(int *a) {
		int id = (a - *pool) * sizeof(int) / sizeof(*pool);
		memset(pool[id], 0, sizeof *pool), vis[id] = false, st[++top] = id;
	}
} mem;

int r[N], lim, l;
inline void ntt(int *a, int op) {
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
		for (int i = 0; i < lim; i++) a[i] = 1ll * a[i] * invp[lim] % P;
}
inline void init(int n) {
	for (lim = 1, l = 0; lim <= n;) lim *= 2, l++;
	for (int i = 1; i < lim; i++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));
}
template <typename F>
inline void mul(int *a, int *b, int *ans, const F &f) {
	int *c = mem.alloc(lim, a), *d = mem.alloc(lim, b);
	ntt(c, 1), ntt(d, 1);
	for (int i = 0; i < lim; i++) ans[i] = f(c[i], d[i]);
	ntt(ans, -1), mem.free(c), mem.free(d);
}
inline void inv(int n, int *a, int *ans) {  // LIMITATION: a != ans
	if (n == 1) return void(*ans = I(*a));
	inv((n + 1) / 2, a, ans), init(n * 2);
	int *b = mem.alloc(n, a);
	memset(b + n, 0, (lim - n) * 4);
	mul(b, ans, ans, [](int x, int y) { return (2 - 1ll * x * y % P + P) % P * y % P; });
	memset(ans + n, 0, (lim - n) * 4), mem.free(b);
}
inline void intg(int n, int *a, int *ans) {
	for (int i = (*ans = 0) + 1; i <= n; i++) ans[i] = 1ll * a[i - 1] * invp[i] % P;
}
inline void derv(int n, int *a, int *ans) {
	for (int i = (ans[n - 1] = 0) + 1; i < n; i++) ans[i - 1] = 1ll * i * a[i] % P;
}
inline void ln(int n, int *a, int *ans) {
	int *b = mem.alloc(n), *c = mem.alloc(n);
	derv(n, a, b), inv(n, b, c), mul(a, c, c, [](int x, int y) { return 1ll * x * y % P; }), intg(n, c, ans);
	mem.free(b), mem.free(c);
}

int n, a[N], b[N];
int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%d", a + i);
	ln(n, a, b);
	for (int i = 0; i < n; i++) printf("%d ", b[i]);
}