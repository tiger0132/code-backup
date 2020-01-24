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

int r[N];
void fft(int n, comp* a, int op) {
	for (int i = 0; i < n; i++)
		if (i < r[i]) std::swap(a[i], a[r[i]]);
	comp w, x, y;
	for (int mh = 1; mh < n; mh *= 2) {
		for (int r = 0; r < n; r += mh * 2) {
			for (int j = 0; j < mh; j++) {
				w.x = cos(P * j / mh), w.y = op * sin(P * j / mh);
				x = a[r + j], y = w * a[r + j + mh];
				a[r + j] = x + y;
				a[r + j + mh] = x - y;
			}
		}
	}
}

comp a[N], b[N];
int n, m, l, tl;
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 0; i <= n; i++) scanf("%lf", &a[i].x);
	for (int i = 0; i <= m; i++) scanf("%lf", &b[i].x);
	for (l = 1, tl = 0; l <= n + m; tl++) l *= 2;
	for (int i = 1; i < l; ++i) r[i] = (r[i >> 1] >> 1) | ((i & 1) << (tl - 1));
	fft(l, a, 1);
	fft(l, b, 1);
	for (int i = 0; i < l; i++) a[i] = a[i] * b[i];
	fft(l, a, -1);
	for (int i = 0; i <= n + m; i++) printf("%d ", int(a[i].x / l + .5));
}