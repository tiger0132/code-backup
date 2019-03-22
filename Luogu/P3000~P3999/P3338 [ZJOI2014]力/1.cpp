#include <algorithm>
#include <cmath>
#include <cstdio>

typedef long double D;
const D P = acos(-1);
const int N = 6e5 + 56;

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
void fft($* a, int t) {
	for (int i = 0; i < lim; i++)
		if (i < r[i]) std::swap(a[i], a[r[i]]);
	for (int i = 1; i < lim; i <<= 1) {
		$ wn(cos(P / i), t * sin(P / i));
		for (int j = 0; j < lim; j += i << 1) {
			$ w(1);
			for (int k = 0; k < i; k++, w = w * wn) {
				$ x = a[j + k], y = w * a[i + j + k];
				a[j + k] = x + y;
				a[i + j + k] = x - y;
			}
		}
	}
}

$ a[N], b[N];
int n;
int main() {
	scanf("%d", &n);
	while (lim <= 3 * n - 1) lim <<= 1, l++;
	for (int i = 0; i < lim; i++)
		r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));
	for (int i = 0; i < n; i++) {
		scanf("%Lf", &a[i].x);
	}
	for (int i = -n + 1; i < n; i++) {
		b[i + n - 1].x = i ? (i < 0 ? -1 : 1) / (1. * i * i) : 0;
	}
	fft(a, 1), fft(b, 1);
	for (int i = 0; i <= lim; i++) a[i] = a[i] * b[i];
	fft(a, -1);
	for (int i = 0; i < n; i++) printf("%.3Lf\n", a[i + n - 1].x / lim);
}