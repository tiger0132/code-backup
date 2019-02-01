#include <algorithm>
#include <cmath>
#include <complex>
#include <cstdio>

typedef double D;
const int N = 3e6 + 63;
const D P = acos(-1);

struct $ {
	D x, y;
	inline $(D x_ = 0, D y_ = 0) : x(x_), y(y_) {}
	inline $ operator+(const $& rhs) const { return $(x + rhs.x, y + rhs.y); }
	inline $ operator-(const $& rhs) const { return $(x - rhs.x, y - rhs.y); }
	inline $ operator*(const $& rhs) const {
		return $(x * rhs.x - y * rhs.y, x * rhs.y + y * rhs.x);
	}
};

int r[N], lim = 1, l;
void fft($* a, int op) {
	for (int i = 0; i < lim; i++)
		if (i < r[i]) std::swap(a[i], a[r[i]]);
	for (int i = 1; i < lim; i <<= 1) {
		$ wn(cos(P / i), op * sin(P / i));
		for (int j = 0; j < lim; j += (i << 1)) {
			$ w(1);
			for (int k = 0; k < i; k++, w = w * wn) {
				$ x = a[j + k], y = w * a[j + i + k];
				a[j + k] = x + y;
				a[i + j + k] = x - y;
			}
		}
	}
}

$ a[N], b[N];
int n, m;
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i <= n; i++) scanf("%lf", &a[i].x);
	for (int i = 0; i <= m; i++) scanf("%lf", &b[i].x);
	while (lim <= n + m) lim <<= 1, l++;
	for (int i = 0; i < lim; i++)
		r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));
	fft(a, 1), fft(b, 1);
	for (int i = 0; i <= lim; i++) {
		a[i] = a[i] * b[i];
	}
	fft(a, -1);
	for (int i = 0; i <= n + m; i++) {
		printf("%d ", (int)(a[i].x / lim + 0.5));
	}
}