#include <algorithm>
#include <complex>
#include <cstdio>
#include <cstring>

using ll = long long;
using comp = std::complex<long double>;
const int N = 6e5 + 56, P = 32767;
const long double PI = acosl(-1);

int l, lim = 1, r[N];
void fft(comp* a, int op) {
	for (int i = 0; i < lim; i++)
		if (i < r[i]) std::swap(a[i], a[r[i]]);
	for (int i = 1; i < lim; i <<= 1) {
		comp wn(cosl(PI / i), op * sinl(PI / i));
		for (int j = 0; j < lim; j += (i << 1)) {
			comp w(1);
			for (int k = 0; k < i; k++, w = w * wn) {
				comp x = a[j + k], y = w * a[j + i + k];
				a[j + k] = x + y;
				a[i + j + k] = x - y;
			}
		}
	}
	if (op == -1)
		for (int i = 0; i < lim; i++) a[i] /= lim;
}

int mod;

comp a[N], b[N], c[N], d[N], A[N], B[N], C[N], D[N];
int n, m, x;
long double t;
int main() {
	scanf("%d%d%d", &n, &m, &mod);
	for (int i = 0; i <= n; i++) scanf("%d", &x), x %= mod, b[i] = x & P, a[i] = x >> 15;
	for (int i = 0; i <= m; i++) scanf("%d", &x), x %= mod, d[i] = x & P, c[i] = x >> 15;
	while (lim <= n + m) lim *= 2, l++;
	for (int i = 0; i < lim; i++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));
	fft(a, 1), fft(b, 1), fft(c, 1), fft(d, 1);
	for (int i = 0; i < lim; i++) {
		A[i] = a[i] * c[i], B[i] = b[i] * c[i];
		C[i] = a[i] * d[i], D[i] = b[i] * d[i];
	}
	fft(A, -1), fft(B, -1), fft(C, -1), fft(D, -1);
	for (int i = 0; i <= n + m; i++) {
		int lans = (((ll(A[i].real() + .5) % mod) << 30ll) % mod + ((ll(B[i].real() + .5) % mod) << 15ll) % mod +
					((ll(C[i].real() + .5) % mod) << 15ll) % mod + (ll(D[i].real() + .5) % mod) % mod) %
				   mod;
		printf("%d ", lans);
	}
}