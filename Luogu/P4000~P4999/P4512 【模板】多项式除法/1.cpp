#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 5e5 + 55, P = 998244353, G = 3, GInv = 332748118;
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
void init(int n) {
	lim = 1, l = 0;
	while (lim <= n) lim <<= 1, l++;
	for (int i = 1; i < lim; i++) r[i] = (r[i / 2] / 2) | ((i & 1) << (l - 1));
}
void inv(int n, int *a, int *ans) {
	static int b[N];
	if (n == 1) return void(ans[0] = p(a[0], P - 2));
	inv((n + 1) / 2, a, ans);
	init(2 * n);
	memcpy(b, a, n * sizeof(int));
	for (int i = n; i < lim; i++) b[i] = 0;
	mul(b, ans, ans, [](int x, int y) { return (2 - 1ll * x * y % P + P) % P * y % P; });
	for (int i = n; i < lim; i++) ans[i] = 0;
}
void div(int n, int m, int *a, int *b, int *q, int *r) {
	static int ar[N], br[N], c[N];
	std::reverse_copy(a, a + n + 1, ar);
	std::reverse_copy(b, b + m + 1, br);
	for (int i = n - m + 2; i <= m; i++) br[i] = 0;
	//	memset(br, 0, (m + m - n - 2) << 2);
	inv(n - m + 1, br, c);
	init(n * 2);
	mul(ar, c, q, [](int x, int y) { return 1ll * x * y % P; });
	std::reverse(q, q + n - m + 1);
	memset(q + n - m + 1, 0, (m - 1) << 2);
	mul(q, b, r, [](int x, int y) { return 1ll * x * y % P; });
	for (int i = 0; i < m; i++) r[i] = (P + a[i] - r[i]) % P;
}

int n, m, a[N], b[N], c[N], d[N];
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i <= n; i++) scanf("%d", a + i);
	for (int i = 0; i <= m; i++) scanf("%d", b + i);
	div(n, m, a, b, c, d);
	for (int i = 0; i <= n - m; i++) printf("%d%c", c[i], " \n"[i == n - m]);
	for (int i = 0; i < m; i++) printf("%d%c", d[i], " \n"[i == m - 1]);
}