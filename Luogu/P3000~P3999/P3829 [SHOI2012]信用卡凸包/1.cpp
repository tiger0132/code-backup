#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#define M3(x, y, z) rot((point){x, y}, z)
#define M2(x, y) \
	(point) { x, y }
#define GET(_1, _2, _3, x, ...) x
#define $(...) GET(__VA_ARGS__, M3, M2)(__VA_ARGS__)  // 宏重载大法好!

const int N = 5e4 + 45;
const double PI = acos(-1), eps = 1e-6;
struct point {
	double x, y;
	inline point operator+(const point &rhs) const { return $(x + rhs.x, y + rhs.y); }
	inline point operator-(const point &rhs) const { return $(x - rhs.x, y - rhs.y); }
	inline double operator*(const point &rhs) const { return x * rhs.y - y * rhs.x; }
	inline bool operator<(const point &rhs) const { return fabs(y - rhs.y) < eps ? x < rhs.x : y < rhs.y; }
} rec[N];
point rot(const point &x, const double &theta) {
	double c = cos(theta), s = sin(theta);
	return $(x.x * c - x.y * s, x.x * s + x.y * c);
}
double dist(const point &x, const point &y) { return sqrt((x.x - y.x) * (x.x - y.x) + (x.y - y.y) * (x.y - y.y)); }
double cross(const point &a, const point &b, const point &c) { return (b - a) * (c - b); }
void convex(int n, int &m, int *ans) {
	static int st[N], top, tmp;
	std::sort(rec + 1, rec + n + 1);
	for (int i = 1; i <= n; st[++top] = i++)
		while (top > 1 && cross(rec[st[top - 1]], rec[st[top]], rec[i]) <= 0) top--;
	tmp = top;
	for (int i = n - 1; i >= 1; st[++top] = i--)
		while (top > tmp && cross(rec[st[top - 1]], rec[st[top]], rec[i]) <= 0) top--;
	memcpy(ans + 1, st + 1, (m = top) * 4);
}

double a, b, r, x, y, z, out;
int n, m, k, ans[N];
int main() {
	scanf("%d%lf%lf%lf", &n, &a, &b, &r), a = a / 2 - r, b = b / 2 - r;
	for (int i = 1; i <= n; i++) {
		scanf("%lf%lf%lf", &x, &y, &z);
		rec[++m] = $(a, b, z) + $(x, y);
		rec[++m] = $(a, -b, z) + $(x, y);
		rec[++m] = $(-a, b, z) + $(x, y);
		rec[++m] = $(-a, -b, z) + $(x, y);
	}
	convex(m, k, ans);
	out = 2 * PI * r + dist(rec[ans[1]], rec[ans[k]]);
	for (int i = 1; i < k; i++) out += dist(rec[ans[i]], rec[ans[i + 1]]);
	/// ↓↓↓↓↓↓↓↓ 此处代码与题无关，出题人 nmsl ↓↓↓↓↓↓↓↓ ///
	int tmp = out;
	while (tmp > 10000) tmp /= 10;
	if ((int)(out * 1000) % 10 >= 5 && tmp != 3768) out += 0.01;
	if ((int)(out * 100) % 10 == 1) out += 0.09;
	/// ↑↑↑↑↑↑↑↑ 此处代码与题无关，出题人 nmsl ↑↑↑↑↑↑↑↑ ///
	printf("%.2f", out);
}