#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>

typedef double d;
const int N = 2.7e6 + 672;
const d P = acos(-1);
struct comp {
	d x, y;
	comp operator+(const comp& r) const { return {x + r.x, y + r.y}; }
	comp operator-(const comp& r) const { return {x - r.x, y - r.y}; }
	comp operator*(const comp& r) const { return {x * r.x - y * r.y, x * r.y + y * r.x}; }
};

void fft(int n, comp* a, int op) {
	if (n == 1) return;
	int m = n / 2;
	comp u[m], v[m];
	for (int i = 0; i < m; i++) {
		u[i] = a[i * 2];
		v[i] = a[i * 2 + 1];
	}
	fft(m, u, op);
	fft(m, v, op);
	comp wn, w;
	wn.x = cos(2 * P / n), wn.y = op * sin(2 * P / n);
	w.x = 1, w.y = 0;
	for (int i = 0; i < m; i++, w = w * wn) {
		v[i] = v[i] * w;
		a[i] = u[i] + v[i];
		a[i + m] = u[i] - v[i];
	}
}

comp a[N], b[N];
int n, m, l;
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i <= n; i++) scanf("%lf", &a[i].x);
	for (int i = 0; i <= m; i++) scanf("%lf", &b[i].x);
	for (l = 1; l <= n + m;) l *= 2;
	fft(l, a, 1);
	fft(l, b, 1);
	for (int i = 0; i < l; i++) a[i] = a[i] * b[i];
	fft(l, a, -1);
	for (int i = 0; i <= n + m; i++) printf("%d ", int(a[i].x / l + .5));
}