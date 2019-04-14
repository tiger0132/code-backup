#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#define $(x, y) \
	(P) { x, y }

const int N = 1e6 + 61;
struct P {
	double x, y;
	inline P operator+(const P& rhs) const { return $(x + rhs.x, y + rhs.y); }
	inline P operator-(const P& rhs) const { return $(x - rhs.x, y - rhs.y); }
	inline P operator/(const double& rhs) const { return $(x / rhs, y / rhs); }
	inline double operator*(const P& rhs) const { return x * rhs.y - y * rhs.x; }
	inline double d2() { return x * x + y * y; }
} a[N];
P circ(const P& A, const P& B, const P& C, double& r2) {
	double a = A.x - B.x, b = A.y - B.y, c = (A.x * A.x - B.x * B.x + A.y * A.y - B.y * B.y) / 2;
	double d = A.x - C.x, e = A.y - C.y, f = (A.x * A.x - C.x * C.x + A.y * A.y - C.y * C.y) / 2;
	P ret = $((b * f - c * e) / (b * d - a * e), (c * d - a * f) / (b * d - a * e));
	return r2 = (ret - A).d2(), ret;
}

double r2;
int n;
P o;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%lf%lf", &a[i].x, &a[i].y);
	std::random_shuffle(a + 1, a + n + 1);
	for (int i = 2; i <= n; i++)
		if ((a[i] - o).d2() > r2) {
			o = a[i], r2 = 0;
			for (int j = 1; j < i; j++)
				if ((a[j] - o).d2() > r2) {
					o = (a[i] + a[j]) / 2, r2 = (o - a[j]).d2();
					for (int k = 1; k < j; k++)
						if ((a[k] - o).d2() > r2) o = circ(a[i], a[j], a[k], r2);
				}
		}
	printf("%.2f %.2f %.2f", o.x, o.y, sqrt(r2));
}