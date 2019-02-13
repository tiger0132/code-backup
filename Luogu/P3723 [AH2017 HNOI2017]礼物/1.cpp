#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <queue>

using ll = long long;
using D = double;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const D P = acos(-1);
const int N = 4e5 + 54;

struct $ {
	D x, y;
	inline $(D x_ = 0, D y_ = 0) : x(x_), y(y_) {}
	inline $ operator+(const $& rhs) const { return $(x + rhs.x, y + rhs.y); }
	inline $ operator-(const $& rhs) const { return $(x - rhs.x, y - rhs.y); }
	inline $ operator*(const $& rhs) const { return $(x * rhs.x - y * rhs.y, x * rhs.y + y * rhs.x); }
	inline $ operator/(D rhs) const { return $(x / rhs, y / rhs); }
};

int lim, l, r[N];
void fft($* a, int op) {
	for (int i = 0; i < lim; i++)
		if (i < r[i]) std::swap(a[i], a[r[i]]);
	for (int i = 1; i < lim; i <<= 1) {
		$ wn(cos(P / i), op * sin(P / i));
		for (int j = 0; j < lim; j += i << 1) {
			$ w(1);
			for (int k = 0; k < i; k++, w = w * wn) {
				$ x = a[j + k], y = w * a[i + j + k];
				a[j + k] = x + y;
				a[i + j + k] = x - y;
			}
		}
	}
	if (op == -1)
		for (int i = 0; i < lim; i++) a[i] = a[i] / lim;
}

ll ans = INF, sa, sa2, sb, sb2, c[N];
$ a[N], b[N];
int n, m;
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++) {
		scanf("%lf", &a[i].x);
		sa += a[i].x, sa2 += a[i].x * a[i].x;
	}
	for (int i = 0; i < n; i++) {
		scanf("%lf", &b[i].x);
		sb += b[i].x, sb2 += b[i].x * b[i].x;
	}
	memcpy(a + n, a, n << 4);
	std::reverse(b, b + n);
	for (lim = 1; lim < n * 3; lim <<= 1) l++;
	for (int i = 1; i < lim; i++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));

	fft(a, 1), fft(b, 1);
	for (int i = 0; i < lim; i++) a[i] = a[i] * b[i];
	fft(a, -1);
	for (int i = 0; i < 2 * n; i++) c[i] = ll(a[i].x + .5);

	for (ll i = 1; i <= n; i++) {
		for (ll j = -m; j <= m; j++) {
			ans = std::min(ans, n * j * j + 2 * j * (sa - sb) - 2 * c[i + n - 2]);
		}
	}
	printf("%lld", ans + sa2 + sb2);
}