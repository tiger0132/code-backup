#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>

const double PI = acos(-1);
const int N = 3e6 + 63;
struct comp {
	double x, y;
	inline comp operator+(const comp& rhs) const { return {x + rhs.x, y + rhs.y}; }
	inline comp operator-(const comp& rhs) const { return {x - rhs.x, y - rhs.y}; }
	inline comp conj() const { return {x, -y}; }
	inline comp operator*(const comp& rhs) const { return {x * rhs.x - y * rhs.y, x * rhs.y + y * rhs.x}; }
};
int r[N], lim, l;
comp unit[N];
inline void fft(comp* a, int op) {
	for (int i = 0; i < lim; i++)
		if (i < r[i]) std::swap(a[i], a[r[i]]);
	comp w, wn, x, y;
	for (int i = 1; i < lim; i *= 2) {
		wn = op == 1 ? unit[i] : unit[i].conj();
		for (int j = 0; j < lim; j += i * 2) {
			w = {1, 0};
			for (int k = 0; k < i; k++, w = w * wn) {
				x = a[j + k], y = w * a[j + k + i];
				a[j + k] = x + y, a[j + k + i] = x - y;
			}
		}
	}
	if (op == -1)
		for (int i = 0; i < lim; i++) a[i].x /= lim;
}
inline void init(int n) {
	for (lim = 1, l = 0; lim <= n;) lim *= 2, l++;
	for (int i = 1; i < lim; i++) r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));
}

comp a[N], b[N];
int n, m;
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i < N; i *= 2) unit[i] = {cos(PI / i), sin(PI / i)};
	for (int i = 0; i <= n; i++) scanf("%lf", &a[i].x);
	for (int i = 0; i <= m; i++) scanf("%lf", &b[i].x);
	init(n + m), fft(a, 1), fft(b, 1);
	for (int i = 0; i <= lim; i++) a[i] = a[i] * b[i];
	fft(a, -1);
	for (int i = 0; i <= n + m; i++) printf("%d ", int(a[i].x + .5));
}