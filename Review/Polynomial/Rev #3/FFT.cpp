#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>

const int N = 2.1e6, M = 22;
const double P = acos(-1);
struct comp {
	double x, y;
	inline comp operator+(const comp& r) const { return (comp){x + r.x, y + r.y}; }
	inline comp operator-(const comp& r) const { return (comp){x - r.x, y - r.y}; }
	inline comp operator*(const comp& r) const { return (comp){x * r.x - y * r.y, x * r.y + y * r.x}; }
};

double _cos[M], _sin[M];
int r[N], lim, l;
void fft(comp* a, int op) {
	int i, j, k, u;
	for (i = 0; i < lim; ++i)
		if (i < r[i]) std::swap(a[i], a[r[i]]);
	comp w, wn, x, y;
	for (i = 1, u = 0; i < lim; i *= 2, ++u) {
		wn.x = _cos[u], wn.y = op * _sin[u];
		for (j = 0; j < lim; j += i * 2) {
			w.x = 1, w.y = 0;
			for (k = 0; k < i; ++k, w = w * wn) {
				x = a[j + k], y = w * a[i + j + k];
				a[j + k] = x + y, a[i + j + k] = x - y;
			}
		}
	}
}

comp a[N], b[N];
int n, m;
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i <= n; ++i) scanf("%lf", &a[i].x);
	for (int i = 0; i <= m; ++i) scanf("%lf", &b[i].x);
	for (lim = 1; lim <= n + m; lim *= 2) {
		_cos[l] = cos(P / lim), _sin[l] = sin(P / lim), ++l;
	}
	for (int i = 1; i < lim; ++i) r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));
	fft(a, 1), fft(b, 1);
	for (int i = 0; i < lim; ++i) a[i] = a[i] * b[i];
	fft(a, -1);
	for (int i = 0; i <= n + m; ++i) printf("%d ", int(a[i].x / lim + .5));
}