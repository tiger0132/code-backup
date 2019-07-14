#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>

typedef long long ll;
const int N = 2.7e5, M = 19, P = 998244353, G = 3, GInv = 332748118, div2 = 499122177;
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
void inv(int n, int *a, int *ans) {
	if (n == 1) return void(*ans = pw(*a, P - 2));
	static int b[N];
	int m = (n + 1) / 2;
	inv(m, a, ans), memcpy(b, a, n * 4), init(n + n), memset(b + n, 0, (lim - n) * 4), ntt(b, 1), ntt(ans, 1);
	for (int i = 0; i < lim; ++i) ans[i] = ans[i] * (2 - ll(b[i]) * ans[i] % P + P) % P;
	ntt(ans, -1), memset(ans + n, 0, (lim - n) * 4);
}
void sqrt(int n, int *a, int *ans) {
	if (n == 1) return void(*ans = 1);
	static int b[N], ans_2[N];
	int m = (n + 1) / 2;
	sqrt(m, a, ans);
	memset(b, 0, sizeof b), memset(ans_2, 0, sizeof ans_2);
	memcpy(b, a, n * 4);
	inv(n, ans, ans_2), init(n + n), memset(b + n, 0, (lim - n) * 4);
	ntt(b, 1), ntt(ans_2, 1), ntt(ans, 1);
	for (int i = 0; i < lim; ++i) ans[i] = (b[i] + ll(ans[i]) * ans[i] % P + P) % P * div2 % P * ans_2[i] % P;
	ntt(ans, -1), memset(ans + n, 0, (lim - n) * 4);
}

int n, a[N], b[N];
int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) scanf("%d", a + i);
	for (int i = 0; i < M; ++i) _wn[i] = pw(G, (P - 1) / (2 << i));
	sqrt(n, a, b);
	for (int i = 0; i < n; ++i) printf("%d ", b[i]);
}