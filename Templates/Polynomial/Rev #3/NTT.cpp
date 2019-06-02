#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>

typedef long long ll;
const int N = 2.1e6, M = 22, P = 998244353, G = 3, GInv = 332748118;
int pw(int x, int y) {
	int r = 1;
	for (; y; y >>= 1, x = ll(x) * x % P)
		if (y & 1) r = ll(r) * x % P;
	return r;
}

int _wn[3][M], (*_)[M] = _wn + 1;
int r[N], lim, l;
void ntt(int* a, int op) {
	int i, j, k, u, w, wn, x, y;
	for (i = 0; i < lim; ++i)
		if (i < r[i]) std::swap(a[i], a[r[i]]);
	for (i = 1, u = 0; i < lim; i *= 2, ++u) {
		wn = _[op][u];
		for (j = 0; j < lim; j += i * 2) {
			for (k = 0, w = 1; k < i; ++k, w = ll(w) * wn % P) {
				x = a[j + k], y = ll(w) * a[i + j + k] % P;
				a[j + k] = (x + y) % P, a[i + j + k] = (x - y + P) % P;
			}
		}
	}
	if (op == 1) return;
	int inv = pw(lim, P - 2);
	for (i = 0; i < lim; i++) a[i] = ll(a[i]) * inv % P;
}

int n, m, a[N], b[N];
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i <= n; ++i) scanf("%d", a + i);
	for (int i = 0; i <= m; ++i) scanf("%d", b + i);
	for (lim = 1; lim <= n + m; lim *= 2) {
		_[1][l] = pw(G, (P - 1) / (2 * lim)), _[-1][l] = pw(GInv, (P - 1) / (2 * lim)), ++l;
	}
	for (int i = 1; i < lim; ++i) r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));
	ntt(a, 1), ntt(b, 1);
	for (int i = 0; i < lim; ++i) a[i] = ll(a[i]) * b[i] % P;
	ntt(a, -1);
	for (int i = 0; i <= n + m; ++i) printf("%d ", a[i]);
}