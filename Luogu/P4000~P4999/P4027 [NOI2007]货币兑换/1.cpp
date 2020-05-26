#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#define mid (l + r) / 2
#define double long double

const double eps = 1e-8;
const int N = 1e5 + 51;

struct point {
	int i;
	double a, b, k, r, x, y, f;
	bool operator<(const point& rhs) const { return x < rhs.x; }
} pt[N];

double slope(int i, int j) {
	if (fabsl(pt[i].x - pt[j].x) < eps) {
		return pt[i].y < pt[j].y ? 1e18 : -1e18;
	}
	return (pt[j].y - pt[i].y) / (pt[j].x - pt[i].x);
}
double dot(int i, int j) { return pt[i].x * pt[j].a + pt[i].y * pt[j].b; }

int st[N], top;
double f(int id) {
	int l = 1, r = top;
	double ans = 0;
	st[0][pt] = {0, -1e9, -1e9, 0, 0, 0, 0, 0};
	while (l <= r)
		if (dot(st[mid - 1], id) < dot(st[mid], id))
			ans = std::max(ans, dot(st[mid], id)), l = mid + 1;
		else
			ans = std::max(ans, dot(st[mid - 1], id)), r = mid - 1;
	return ans;
}

double dp[N];
void cdq(int l, int r) {
	if (l == r) {
		dp[l] = std::max(dp[l], dp[l - 1]);
		l[pt].x = dp[l] * l[pt].r / (l[pt].a * l[pt].r + l[pt].b);
		l[pt].y = dp[l] / (l[pt].a * l[pt].r + l[pt].b);
		return;
	}
	int m = (l + r) / 2;
	cdq(l, m);
	top = 0;
	std::sort(st + l, st + m + 1);
	for (int i = l; i <= m; i++) {
		while (top >= 2 && slope(st[top], i) > slope(st[top - 1], st[top])) top--;
		st[++top] = i;
	}
	for (int i = m + 1; i <= r; i++) {
		dp[i[pt].i] = std::max(dp[i[pt].i], f(i));
	}
	cdq(m + 1, r);
	std::inplace_merge(pt + l, pt + m + 1, pt + r + 1);
}

double a, b, r;
int n;
int main() {
	scanf("%d%Lf", &n, dp);
	for (int i = 1; i <= n; i++) {
		scanf("%Lf%Lf%Lf", &pt[i].a, &pt[i].b, &pt[i].r), pt[i].i = i;
	}
	cdq(1, n);
	printf("%.3Lf\n", dp[n]);
}