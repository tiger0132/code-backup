#include <algorithm>
#include <cmath>
#include <cstdio>
#include <queue>

typedef double D;
const D P = acos(-1);
const int N = 2e6 + 62;

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

$ a2[N], b2[N], c[N];
int m, n, a[N], b[N];
std::queue<int> q;
char s1[N], s2[N];
int main() {
	scanf("%d%d%s%s", &m, &n, s1, s2);
	for (lim = 1; lim < n * 2; lim <<= 1) l++;
	for (int i = 1; i < lim; i++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));
	for (int i = 0; i < m; i++)
		if (s1[m - i - 1] != '*') a[i] = s1[m - i - 1] - 'a' + 1;
	for (int i = 0; i < n; i++)
		if (s2[i] != '*') b[i] = s2[i] - 'a' + 1;

	for (int i = 0; i < m; i++) a2[i] = $(a[i] * a[i] * a[i]);
	for (int i = 0; i < n; i++) b2[i] = $(b[i]);
	fft(a2, 1), fft(b2, 1);
	for (int i = 0; i < lim; i++) c[i] = a2[i] * b2[i];

	for (int i = 0; i < lim; i++) a2[i] = b2[i] = $();
	for (int i = 0; i < m; i++) a2[i] = $(a[i] * a[i]);
	for (int i = 0; i < n; i++) b2[i] = $(b[i] * b[i]);
	fft(a2, 1), fft(b2, 1);
	for (int i = 0; i < lim; i++) c[i] = c[i] - a2[i] * b2[i] * 2;

	for (int i = 0; i < lim; i++) a2[i] = b2[i] = $();
	for (int i = 0; i < m; i++) a2[i] = $(a[i]);
	for (int i = 0; i < n; i++) b2[i] = $(b[i] * b[i] * b[i]);
	fft(a2, 1), fft(b2, 1);
	for (int i = 0; i < lim; i++) c[i] = c[i] + a2[i] * b2[i];

	fft(c, -1);
	for (int i = m - 1; i < n; i++)
		if (fabs(c[i].x) < 0.5) q.push(i - m + 2);
	for (printf("%lu\n", q.size()); !q.empty(); q.pop()) printf("%d ", q.front());
}