#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>

const int N = 1e4 + 41;
const double eps = 1e-8;
struct point {
	double x, y;
	inline point operator-(const point &rhs) { return (point){x - rhs.x, y - rhs.y}; }
	inline double operator*(const point &rhs) { return x * rhs.y - y * rhs.x; }
	inline bool operator<(const point &rhs) { return fabs(y - rhs.y) < eps ? x < rhs.x : y < rhs.y; }
} a[N];
inline double cross(point &a, point &b, point &c) { return (b - a) * (c - b); }
inline double dist(const point &a, const point &b) { return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y)); }
void convex(int n, int &m, int *ans) {
	static int st[N], top, tmp;
	std::sort(a + 1, a + n + 1);
	for (int i = 1; i <= n; i++) {
		while (top > 1 && cross(a[st[top - 1]], a[st[top]], a[i]) <= 0) top--;
		st[++top] = i;
	}
	tmp = top;
	for (int i = n - 1; i >= 1; i--) {
		while (top > tmp && cross(a[st[top - 1]], a[st[top]], a[i]) <= 0) top--;
		st[++top] = i;
	}
	memcpy(ans + 1, st + 1, (m = top) * 4);
}

int n, m, b[N];
double ans;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%lf%lf", &a[i].x, &a[i].y);
	}
	convex(n, m, b);
	ans = dist(a[b[1]], a[b[m]]);
	for (int i = 1; i < m; i++) ans += dist(a[b[i]], a[b[i + 1]]);
	printf("%.2f", ans);
}