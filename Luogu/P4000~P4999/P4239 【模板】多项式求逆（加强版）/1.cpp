#include <algorithm>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstring>

struct comp {
	long double x, y;
	inline comp(long double x_ = 0, long double y_ = 0) : x(x_), y(y_) {}
	inline comp operator+(const comp &rhs) const { return comp(x + rhs.x, y + rhs.y); }
	inline comp operator-(const comp &rhs) const { return comp(x - rhs.x, y - rhs.y); }
	inline comp operator*(const comp &rhs) const { return comp(x * rhs.x - y * rhs.y, x * rhs.y + y * rhs.x); }
};

using ll = long long;
const int N = 6e5 + 56, P = 1e9 + 7;
const long double PI = acosl(-1);
int p(int x, int y) {
	int ret = 1;
	for (; y; y >>= 1, x = 1ll * x * x % P)
		if (y & 1) ret = 1ll * ret * x % P;
	return ret;
}

int r[N], lim, l;
void fft(comp *a, int op) {
	for (int i = 0; i < lim; i++)
		if (i < r[i]) std::swap(a[i], a[r[i]]);
	for (int i = 1; i < lim; i *= 2) {
		comp wn(cosl(PI / i), op * sinl(PI / i));
		for (int j = 0; j < lim; j += i * 2) {
			comp w = 1;
			for (int k = 0; k < i; k++, w = w * wn) {
				comp x = a[j + k], y = w * a[j + k + i];
				a[j + k] = x + y, a[j + k + i] = x - y;
			}
		}
	}
	if (op == -1)
		for (int i = 0; i < lim; i++) a[i].x /= lim;
}
void mul(int *a, int *b, int *ans) {
	static comp A[N], B[N], C[N], D[N];
	for (int i = 0; i < lim; i++) {
		A[i] = a[i] >> 15, B[i] = a[i] & 0x7FFF;
		C[i] = b[i] >> 15, D[i] = b[i] & 0x7FFF;
	}
	fft(A, 1), fft(B, 1), fft(C, 1), fft(D, 1);
	for (int i = 0; i < lim; i++) {
		comp x = A[i], y = B[i], z = C[i], w = D[i];
		A[i] = x * z, B[i] = y * z, C[i] = x * w, D[i] = y * w;
	}
	fft(A, -1), fft(B, -1), fft(C, -1), fft(D, -1);
	for (int i = 0; i < lim; i++) {
		ans[i] = (((ll(A[i].x + .5) % P) << 30ll) % P + ((ll(B[i].x + .5) % P) << 15ll) % P +
				  ((ll(C[i].x + .5) % P) << 15ll) % P + (ll(D[i].x + .5) % P) % P) %
				 P;
	}
}
void init(int n) {
	lim = 1, l = 0;
	while (lim <= n) lim <<= 1, l++;
	for (int i = 1; i < lim; i++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));
}
void inv(int n, int *a, int *ans) {
	static int b[N], c[N];
	if (n == 1) return void(ans[0] = p(a[0], P - 2));
	inv((n + 1) >> 1, a, ans);
	init(2 * n);
	memcpy(b, a, n * sizeof(int));
	for (int i = n; i < lim; i++) b[i] = 0;
	mul(b, ans, c);
	for (int i = 0; i < lim; i++) c[i] = P - c[i];
	c[0] += 2;
	mul(c, ans, ans);
	for (int i = n; i < lim; i++) ans[i] = 0;
}

int n, m = 1, a[N], b[N];
int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) scanf("%d", a + i);
	// for (m = 1; m < n;) m *= 2;
	inv(n, a, b);
	for (int i = 0; i < n; i++) printf("%d ", b[i]);
}